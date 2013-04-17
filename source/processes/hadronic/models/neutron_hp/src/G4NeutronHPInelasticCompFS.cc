//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// neutron_hp -- source file
// J.P. Wellisch, Nov-1996
// A prototype of the low energy neutron transport model.
//
// 070523 bug fix for G4FPE_DEBUG on by A. Howard ( and T. Koi)
// 070606 bug fix and migrate to enable to Partial cases by T. Koi 
// 080603 bug fix for Hadron Hyper News #932 by T. Koi 
// 080612 bug fix contribution from Benoit Pirard and Laurent Desorgher (Univ. Bern) #4,6
// 080717 bug fix of calculation of residual momentum by T. Koi
// 080801 protect negative avalable energy by T. Koi
//        introduce theNDLDataA,Z which has A and Z of NDL data by T. Koi
// 081024 G4NucleiPropertiesTable:: to G4NucleiProperties::
// 090514 Fix bug in IC electron emission case 
//        Contribution from Chao Zhang (Chao.Zhang@usd.edu) and Dongming Mei(Dongming.Mei@usd.edu)
// 100406 "nothingWasKnownOnHadron=1" then sample mu isotropic in CM 
//        add two_body_reaction
// 100909 add safty 
// 101111 add safty for _nat_ data case in Binary reaction, but break conservation  
// 110430 add Reaction Q value and break up flag (MF3::QI and LR)
//
#include "G4NeutronHPInelasticCompFS.hh"
#include "G4NeutronHPManager.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4Nucleus.hh"
#include "G4NucleiProperties.hh"
#include "G4He3.hh"
#include "G4Alpha.hh"
#include "G4Electron.hh"
#include "G4NeutronHPDataUsed.hh"
#include "G4ParticleTable.hh"

void G4NeutronHPInelasticCompFS::InitGammas(G4double AR, G4double ZR)
{
  //   char the[100] = {""};
  //   std::ostrstream ost(the, 100, std::ios::out);
  //   ost <<gammaPath<<"z"<<ZR<<".a"<<AR;
  //   G4String * aName = new G4String(the);
  //   std::ifstream from(*aName, std::ios::in);

   std::ostringstream ost;
   ost <<gammaPath<<"z"<<ZR<<".a"<<AR;
   G4String aName = ost.str();
   std::ifstream from(aName, std::ios::in);

   if(!from) return; // no data found for this isotope
   //   std::ifstream theGammaData(*aName, std::ios::in);
   std::ifstream theGammaData(aName, std::ios::in);
    
   theGammas.Init(theGammaData);
   //   delete aName;
}

void G4NeutronHPInelasticCompFS::Init (G4double A, G4double Z, G4int M, G4String & dirName, G4String & aFSType)
{
  gammaPath = "/Inelastic/Gammas/";
    if(!getenv("G4NEUTRONHPDATA")) 
       throw G4HadronicException(__FILE__, __LINE__, "Please setenv G4NEUTRONHPDATA to point to the neutron cross-section files.");
  G4String tBase = getenv("G4NEUTRONHPDATA");
  gammaPath = tBase+gammaPath;
  G4String tString = dirName;
  G4bool dbool;
  G4NeutronHPDataUsed aFile = theNames.GetName(static_cast<G4int>(A), static_cast<G4int>(Z), M, tString, aFSType, dbool);
  G4String filename = aFile.GetName();
  SetAZMs( A, Z, M, aFile ); 
  //theBaseA = aFile.GetA();
  //theBaseZ = aFile.GetZ();
  //theNDLDataA = (int)aFile.GetA();
  //theNDLDataZ = aFile.GetZ();
  //if(!dbool || ( Z<2.5 && ( std::abs(theBaseZ - Z)>0.0001 || std::abs(theBaseA - A)>0.0001)))
  if ( !dbool || ( Z<2.5 && ( std::abs(theNDLDataZ - Z)>0.0001 || std::abs(theNDLDataA - A)>0.0001)) )
  {
    if(getenv("NeutronHPNamesLogging")) G4cout << "Skipped = "<< filename <<" "<<A<<" "<<Z<<G4endl;
    hasAnyData = false;
    hasFSData = false; 
    hasXsec = false;
    return;
  }
  //theBaseA = A;
  //theBaseZ = G4int(Z+.5);
   //std::ifstream theData(filename, std::ios::in);
   std::istringstream theData(std::ios::in);
   G4NeutronHPManager::GetInstance()->GetDataStream(filename,theData);
  if(!theData) //"!" is a operator of ios
  {
    hasAnyData = false;
    hasFSData = false; 
    hasXsec = false;
    //theData.close();
    return;
  }
  // here we go
  G4int infoType, dataType, dummy;
  G4int sfType, it;
  hasFSData = false; 
  while (theData >> infoType)
  {
    hasFSData = true; 
    theData >> dataType;
    theData >> sfType >> dummy;
    it = 50;
    if(sfType>=600||(sfType<100&&sfType>=50)) it = sfType%50;
    if(dataType==3) 
    {
      //theData >> dummy >> dummy;
      //TK110430
      // QI and LR introudced since G4NDL3.15
      G4double dqi;
      G4int ilr;
      theData >> dqi >> ilr;

      QI[ it ] = dqi*eV;
      LR[ it ] = ilr;
      theXsection[it] = new G4NeutronHPVector;
      G4int total;
      theData >> total;
      theXsection[it]->Init(theData, total, eV);
      //std::cout << theXsection[it]->GetXsec(1*MeV) << std::endl;
    }
    else if(dataType==4)
    {
      theAngularDistribution[it] = new G4NeutronHPAngular;
      theAngularDistribution[it]->Init(theData);
    }
    else if(dataType==5)
    {
      theEnergyDistribution[it] = new G4NeutronHPEnergyDistribution;
      theEnergyDistribution[it]->Init(theData); 
    }
    else if(dataType==6)
    {
      theEnergyAngData[it] = new G4NeutronHPEnAngCorrelation;
      theEnergyAngData[it]->Init(theData);
    }
    else if(dataType==12)
    {
      theFinalStatePhotons[it] = new G4NeutronHPPhotonDist;
      theFinalStatePhotons[it]->InitMean(theData);
    }
    else if(dataType==13)
    {
      theFinalStatePhotons[it] = new G4NeutronHPPhotonDist;
      theFinalStatePhotons[it]->InitPartials(theData);
    }
    else if(dataType==14)
    {
      theFinalStatePhotons[it]->InitAngular(theData);
    }
    else if(dataType==15)
    {
      theFinalStatePhotons[it]->InitEnergies(theData);
    }
    else
    {
      throw G4HadronicException(__FILE__, __LINE__, "Data-type unknown to G4NeutronHPInelasticCompFS");
    }
  }
  //theData.close();
}

G4int G4NeutronHPInelasticCompFS::SelectExitChannel(G4double eKinetic)
{

// it = 0 has without Photon
  G4double running[50];
  running[0] = 0;
  unsigned int i;
  for(i=0; i<50; i++)
  {
    if(i!=0) running[i]=running[i-1];
    if(theXsection[i] != 0) 
    {
      running[i] += std::max(0., theXsection[i]->GetXsec(eKinetic));
    }
  }
  G4double random = G4UniformRand();
  G4double sum = running[49];
  G4int it = 50;
  if(0!=sum)
  {
    G4int i0;
    for(i0=0; i0<50; i0++)
    {
      it = i0;
      if(random < running[i0]/sum) break;
    }
  }
//debug:  it = 1;
  return it;
}


                                                                                                       //n,p,d,t,he3,a
void G4NeutronHPInelasticCompFS::CompositeApply(const G4HadProjectile & theTrack, G4ParticleDefinition * aDefinition)
{

// prepare neutron
    theResult.Clear();
    G4double eKinetic = theTrack.GetKineticEnergy();
    const G4HadProjectile *incidentParticle = &theTrack;
    G4ReactionProduct theNeutron( const_cast<G4ParticleDefinition *>(incidentParticle->GetDefinition()) );
    theNeutron.SetMomentum( incidentParticle->Get4Momentum().vect() );
    theNeutron.SetKineticEnergy( eKinetic );

// prepare target
    G4int i;
    for(i=0; i<50; i++)
    { if(theXsection[i] != 0) { break; } } 

    G4double targetMass=0;
    G4double eps = 0.0001;
    targetMass = ( G4NucleiProperties::GetNuclearMass(static_cast<G4int>(theBaseA+eps), static_cast<G4int>(theBaseZ+eps))) /
                   G4Neutron::Neutron()->GetPDGMass();
//    if(theEnergyAngData[i]!=0)
//        targetMass = theEnergyAngData[i]->GetTargetMass();
//    else if(theAngularDistribution[i]!=0)
//        targetMass = theAngularDistribution[i]->GetTargetMass();
//    else if(theFinalStatePhotons[50]!=0)
//        targetMass = theFinalStatePhotons[50]->GetTargetMass();
    G4Nucleus aNucleus;
    G4ReactionProduct theTarget; 
    G4ThreeVector neuVelo = (1./incidentParticle->GetDefinition()->GetPDGMass())*theNeutron.GetMomentum();
    theTarget = aNucleus.GetBiasedThermalNucleus( targetMass, neuVelo, theTrack.GetMaterial()->GetTemperature());

// prepare the residual mass
    G4double residualMass=0;
    G4double residualZ = theBaseZ - aDefinition->GetPDGCharge();
    G4double residualA = theBaseA - aDefinition->GetBaryonNumber()+1;
    residualMass = ( G4NucleiProperties::GetNuclearMass(static_cast<G4int>(residualA+eps), static_cast<G4int>(residualZ+eps)) ) /
                     G4Neutron::Neutron()->GetPDGMass();

// prepare energy in target rest frame
    G4ReactionProduct boosted;
    boosted.Lorentz(theNeutron, theTarget);
    eKinetic = boosted.GetKineticEnergy();
//    G4double momentumInCMS = boosted.GetTotalMomentum();
  
// select exit channel for composite FS class.
    G4int it = SelectExitChannel( eKinetic );
   
// set target and neutron in the relevant exit channel
    InitDistributionInitialState(theNeutron, theTarget, it);    

    G4ReactionProductVector * thePhotons = 0;
    G4ReactionProductVector * theParticles = 0;
    G4ReactionProduct aHadron;
    aHadron.SetDefinition(aDefinition); // what if only cross-sections exist ==> Na 23 11 @@@@    
    G4double availableEnergy = theNeutron.GetKineticEnergy() + theNeutron.GetMass() - aHadron.GetMass() +
                             (targetMass - residualMass)*G4Neutron::Neutron()->GetPDGMass();
//080730c
    if ( availableEnergy < 0 )
    {
       //G4cout << "080730c Adjust availavleEnergy " << G4endl; 
       availableEnergy = 0; 
    }
    G4int nothingWasKnownOnHadron = 0;
    G4int dummy;
    G4double eGamm = 0;
    G4int iLevel=it-1;

//  TK without photon has it = 0
    if( 50 == it ) 
    {

//    TK Excitation level is not determined
      iLevel=-1;
      aHadron.SetKineticEnergy(availableEnergy*residualMass*G4Neutron::Neutron()->GetPDGMass()/
                               (aHadron.GetMass()+residualMass*G4Neutron::Neutron()->GetPDGMass()));

      //aHadron.SetMomentum(theNeutron.GetMomentum()*(1./theNeutron.GetTotalMomentum())*
      //                  std::sqrt(aHadron.GetTotalEnergy()*aHadron.GetTotalEnergy()-
      //                            aHadron.GetMass()*aHadron.GetMass()));

      //TK add safty 100909
      G4double p2 = ( aHadron.GetTotalEnergy()*aHadron.GetTotalEnergy() - aHadron.GetMass()*aHadron.GetMass() );
      G4double p = 0.0;
      if ( p2 > 0.0 ) p = std::sqrt( p ); 

      aHadron.SetMomentum(theNeutron.GetMomentum()*(1./theNeutron.GetTotalMomentum())*p );

    }
    else
    {
      while( iLevel!=-1 && theGammas.GetLevel(iLevel) == 0 ) { iLevel--; }
    }


    if ( theAngularDistribution[it] != 0 ) // MF4
    {
      if(theEnergyDistribution[it]!=0) // MF5
      {
	//************************************************************
	/*
        aHadron.SetKineticEnergy(theEnergyDistribution[it]->Sample(eKinetic, dummy));
        G4double eSecN = aHadron.GetKineticEnergy();
	*/
	//************************************************************
	//EMendoza --> maximum allowable energy should be taken into account.
        G4double dqi = 0.0;
        if ( QI[it] < 0 || 849 < QI[it] ) dqi = QI[it]; //For backword compatibility QI introduced since G4NDL3.15
	G4double MaxEne=eKinetic+dqi;
	G4double eSecN;
	do{
	  eSecN=theEnergyDistribution[it]->Sample(eKinetic, dummy);
	}while(eSecN>MaxEne);
	aHadron.SetKineticEnergy(eSecN);
	//************************************************************
        eGamm = eKinetic-eSecN;
        for(iLevel=theGammas.GetNumberOfLevels()-1; iLevel>=0; iLevel--)
        {
          if(theGammas.GetLevelEnergy(iLevel)<eGamm) break;
        }
        G4double random = 2*G4UniformRand();
        iLevel+=G4int(random);
        if(iLevel>theGammas.GetNumberOfLevels()-1)iLevel = theGammas.GetNumberOfLevels()-1;
      }
      else
      {
        G4double eExcitation = 0;
        if(iLevel>=0) eExcitation = theGammas.GetLevel(iLevel)->GetLevelEnergy();    
        while (eKinetic-eExcitation < 0 && iLevel>0)
	{
	  iLevel--;
	  eExcitation = theGammas.GetLevel(iLevel)->GetLevelEnergy();    
	}
        //110610TK BEGIN
        //Use QI value for calculating excitation energy of residual.
        G4bool useQI=false;
        G4double dqi = QI[it]; 
        if ( dqi < 0 || 849 < dqi ) useQI = true; //Former libraies does not have values of this range
 
        if ( useQI ) 
        {
           // QI introudced since G4NDL3.15
           eExcitation = -QI[it];
           //Re-evluate iLevel based on this eExcitation 
           iLevel = 0;
           G4bool find = false;
           G4int imaxEx = 0;
           while( !theGammas.GetLevel(iLevel+1) == 0 ) 
           { 
              G4double maxEx = 0.0;
              if ( maxEx < theGammas.GetLevel(iLevel)->GetLevelEnergy() ) 
              {
                 maxEx = theGammas.GetLevel(iLevel)->GetLevelEnergy();  
                 imaxEx = iLevel;
              }
              if ( eExcitation < theGammas.GetLevel(iLevel)->GetLevelEnergy() ) 
              {
                 find = true; 
                 iLevel--; 
                 // very small eExcitation, iLevel becomes -1, this is protected below.
                 if ( iLevel == -1 ) iLevel = 0; // But cause energy trouble. 
                 break;
              }
              iLevel++; 
           }
           // In case, cannot find proper level, then use the maximum level. 
           if ( !find ) iLevel = imaxEx;
        }
        //110610TK END
	
	if(getenv("InelasticCompFSLogging") && eKinetic-eExcitation < 0) 
	{
	  throw G4HadronicException(__FILE__, __LINE__, "SEVERE: InelasticCompFS: Consistency of data not good enough, please file report");
	}
	if(eKinetic-eExcitation < 0) eExcitation = 0;
	if(iLevel!= -1) aHadron.SetKineticEnergy(eKinetic - eExcitation);
	
      }
      theAngularDistribution[it]->SampleAndUpdate(aHadron);

      if( theFinalStatePhotons[it] == 0 )
      {
        //G4cout << "110610 USE Gamma Level" << G4endl;
// TK comment Most n,n* eneter to this  
	thePhotons = theGammas.GetDecayGammas(iLevel);
	eGamm -= theGammas.GetLevelEnergy(iLevel);
	if(eGamm>0) // @ ok for now, but really needs an efficient way of correllated sampling @
	{
          G4ReactionProduct * theRestEnergy = new G4ReactionProduct;
          theRestEnergy->SetDefinition(G4Gamma::Gamma());
          theRestEnergy->SetKineticEnergy(eGamm);
          G4double costh = 2.*G4UniformRand()-1.;
          G4double phi = twopi*G4UniformRand();
          theRestEnergy->SetMomentum(eGamm*std::sin(std::acos(costh))*std::cos(phi), 
                                     eGamm*std::sin(std::acos(costh))*std::sin(phi),
                                     eGamm*costh);
          if(thePhotons == 0) { thePhotons = new G4ReactionProductVector; }
          thePhotons->push_back(theRestEnergy);
	}
      }
    }
    else if(theEnergyAngData[it] != 0) // MF6  
    {
      theParticles = theEnergyAngData[it]->Sample(eKinetic);
    }
    else
    {
      // @@@ what to do, if we have photon data, but no info on the hadron itself
      nothingWasKnownOnHadron = 1;
    }

    //G4cout << "theFinalStatePhotons it " << it << G4endl;
    //G4cout << "theFinalStatePhotons[it] " << theFinalStatePhotons[it] << G4endl;
    //G4cout << "theFinalStatePhotons it " << it << G4endl;
    //G4cout << "theFinalStatePhotons[it] " << theFinalStatePhotons[it] << G4endl;
    //G4cout << "thePhotons " << thePhotons << G4endl;

    if ( theFinalStatePhotons[it] != 0 ) 
    {
       // the photon distributions are in the Nucleus rest frame.
       // TK residual rest frame
      G4ReactionProduct boosted_tmp;
      boosted_tmp.Lorentz(theNeutron, theTarget);
      G4double anEnergy = boosted_tmp.GetKineticEnergy();
      thePhotons = theFinalStatePhotons[it]->GetPhotons(anEnergy);
      G4double aBaseEnergy = theFinalStatePhotons[it]->GetLevelEnergy();
      G4double testEnergy = 0;
      if(thePhotons!=0 && thePhotons->size()!=0)
      { aBaseEnergy-=thePhotons->operator[](0)->GetTotalEnergy(); }
      if(theFinalStatePhotons[it]->NeedsCascade())
      {
	while(aBaseEnergy>0.01*keV)
        {
          // cascade down the levels
	  G4bool foundMatchingLevel = false;
          G4int closest = 2;
	  G4double deltaEold = -1;
	  for(G4int j=1; j<it; j++)
          {
            if(theFinalStatePhotons[j]!=0) 
            {
              testEnergy = theFinalStatePhotons[j]->GetLevelEnergy();
            }
            else
            {
              testEnergy = 0;
            }
	    G4double deltaE = std::abs(testEnergy-aBaseEnergy);
            if(deltaE<0.1*keV)
            {
              G4ReactionProductVector * theNext = 
        	theFinalStatePhotons[j]->GetPhotons(anEnergy);
              thePhotons->push_back(theNext->operator[](0));
              aBaseEnergy = testEnergy-theNext->operator[](0)->GetTotalEnergy();
              delete theNext;
	      foundMatchingLevel = true;
              break; // ===>
            }
	    if(theFinalStatePhotons[j]!=0 && ( deltaE<deltaEold||deltaEold<0.) )
	    {
	      closest = j;
	      deltaEold = deltaE;     
	    }
          } // <=== the break goes here.
	  if(!foundMatchingLevel)
	  {
            G4ReactionProductVector * theNext = 
               theFinalStatePhotons[closest]->GetPhotons(anEnergy);
            thePhotons->push_back(theNext->operator[](0));
            aBaseEnergy = aBaseEnergy-theNext->operator[](0)->GetTotalEnergy();
            delete theNext;
	  }
        } 
      }
    }
    unsigned int i0;
    if(thePhotons!=0)
    {
      for(i0=0; i0<thePhotons->size(); i0++)
      {
	// back to lab
	thePhotons->operator[](i0)->Lorentz(*(thePhotons->operator[](i0)), -1.*theTarget);
      }
    }
    //G4cout << "nothingWasKnownOnHadron " << nothingWasKnownOnHadron << G4endl;
    if(nothingWasKnownOnHadron)
    {
//    TKDB 100405
//    In this case, hadron should be isotropic in CM
//    mu and p should be correlated
//
      G4double totalPhotonEnergy = 0.0;
      if ( thePhotons != 0 )
      {
         unsigned int nPhotons = thePhotons->size();
         unsigned int ii0;
         for ( ii0=0; ii0<nPhotons; ii0++)
         {
            //thePhotons has energies at LAB system 
            totalPhotonEnergy += thePhotons->operator[](ii0)->GetTotalEnergy();
         }
      }

      //isotropic distribution in CM 
      G4double mu = 1.0 - 2 * G4UniformRand();

      // need momentums in target rest frame;
      G4LorentzVector target_in_LAB ( theTarget.GetMomentum() , theTarget.GetTotalEnergy() );
      G4ThreeVector boostToTargetRest = -target_in_LAB.boostVector();
      G4LorentzVector proj_in_LAB = incidentParticle->Get4Momentum();

      G4DynamicParticle* proj = new G4DynamicParticle( G4Neutron::Neutron() , proj_in_LAB.boost( boostToTargetRest ) ); 
      G4DynamicParticle* targ = new G4DynamicParticle( G4ParticleTable::GetParticleTable()->GetIon ( (G4int)theBaseZ , (G4int)theBaseA , totalPhotonEnergy )  , G4ThreeVector(0) );
      G4DynamicParticle* hadron = new G4DynamicParticle( aHadron.GetDefinition() , G4ThreeVector(0) );  // will be fill momentum

      two_body_reaction ( proj , targ , hadron , mu );

      G4LorentzVector hadron_in_trag_rest = hadron->Get4Momentum();
      G4LorentzVector hadron_in_LAB = hadron_in_trag_rest.boost ( -boostToTargetRest );
      aHadron.SetMomentum( hadron_in_LAB.v() );
      aHadron.SetKineticEnergy ( hadron_in_LAB.e() - hadron_in_LAB.m() );

      delete proj;
      delete targ; 
      delete hadron;

//TKDB 100405
/*
      G4double totalPhotonEnergy = 0;
      if(thePhotons!=0)
      {
        unsigned int nPhotons = thePhotons->size();
	unsigned int i0;
	for(i0=0; i0<nPhotons; i0++)
        {
          totalPhotonEnergy += thePhotons->operator[](i0)->GetTotalEnergy();
        }
      }
      availableEnergy -= totalPhotonEnergy;
      residualMass += totalPhotonEnergy/G4Neutron::Neutron()->GetPDGMass();
      aHadron.SetKineticEnergy(availableEnergy*residualMass*G4Neutron::Neutron()->GetPDGMass()/
                               (aHadron.GetMass()+residualMass*G4Neutron::Neutron()->GetPDGMass()));
      G4double CosTheta = 1.0 - 2.0*G4UniformRand();
      G4double SinTheta = std::sqrt(1.0 - CosTheta*CosTheta);
      G4double Phi = twopi*G4UniformRand();
      G4ThreeVector Vector(std::cos(Phi)*SinTheta, std::sin(Phi)*SinTheta, CosTheta);
      //aHadron.SetMomentum(Vector* std::sqrt(aHadron.GetTotalEnergy()*aHadron.GetTotalEnergy()-
      //                                 aHadron.GetMass()*aHadron.GetMass()));
      G4double p2 = aHadron.GetTotalEnergy()*aHadron.GetTotalEnergy()- aHadron.GetMass()*aHadron.GetMass();

      G4double p = 0.0;
      if ( p2 > 0.0 )
         p = std::sqrt ( p2 ); 

      aHadron.SetMomentum( Vector*p ); 
*/

    }

// fill the result
// Beware - the recoil is not necessarily in the particles...
// Can be calculated from momentum conservation?
// The idea is that the particles ar emitted forst, and the gammas only once the
// recoil is on the residual; assumption is that gammas do not contribute to 
// the recoil.
// This needs more design @@@

    G4int nSecondaries = 2; // the hadron and the recoil
    G4bool needsSeparateRecoil = false;
    G4int totalBaryonNumber = 0;
    G4int totalCharge = 0;
    G4ThreeVector totalMomentum(0);
    if(theParticles != 0) 
    {
      nSecondaries = theParticles->size();
      G4ParticleDefinition * aDef;
      unsigned int ii0;
      for(ii0=0; ii0<theParticles->size(); ii0++)
      {
        aDef = theParticles->operator[](ii0)->GetDefinition();
	totalBaryonNumber+=aDef->GetBaryonNumber();
	totalCharge+=G4int(aDef->GetPDGCharge()+eps);
        totalMomentum += theParticles->operator[](ii0)->GetMomentum();
      } 
      if(totalBaryonNumber!=G4int(theBaseA+eps+incidentParticle->GetDefinition()->GetBaryonNumber())) 
      {
        needsSeparateRecoil = true;
	nSecondaries++;
	residualA = G4int(theBaseA+eps+incidentParticle->GetDefinition()->GetBaryonNumber()
	                  -totalBaryonNumber);
	residualZ = G4int(theBaseZ+eps+incidentParticle->GetDefinition()->GetPDGCharge()
	                  -totalCharge);
      }
    }
    
    G4int nPhotons = 0;
    if(thePhotons!=0) { nPhotons = thePhotons->size(); }
    nSecondaries += nPhotons;
        
    G4DynamicParticle * theSec;
    
    if( theParticles==0 )
    {
      theSec = new G4DynamicParticle;   
      theSec->SetDefinition(aHadron.GetDefinition());
      theSec->SetMomentum(aHadron.GetMomentum());
      theResult.AddSecondary(theSec);    
 
 	aHadron.Lorentz(aHadron, theTarget);
        G4ReactionProduct theResidual;   
        theResidual.SetDefinition(G4ParticleTable::GetParticleTable()
	                          ->GetIon(static_cast<G4int>(residualZ), static_cast<G4int>(residualA), 0));  
        theResidual.SetKineticEnergy(aHadron.GetKineticEnergy()*aHadron.GetMass()/theResidual.GetMass());

        //080612TK contribution from Benoit Pirard and Laurent Desorgher (Univ. Bern) #6
        //theResidual.SetMomentum(-1.*aHadron.GetMomentum());
	G4ThreeVector incidentNeutronMomentum = theNeutron.GetMomentum();
        theResidual.SetMomentum(incidentNeutronMomentum - aHadron.GetMomentum());

	theResidual.Lorentz(theResidual, -1.*theTarget);
	G4ThreeVector totalPhotonMomentum(0,0,0);
	if(thePhotons!=0)
	{
          for(i=0; i<nPhotons; i++)
          {
            totalPhotonMomentum += thePhotons->operator[](i)->GetMomentum();
          }
	}
        theSec = new G4DynamicParticle;   
        theSec->SetDefinition(theResidual.GetDefinition());
        theSec->SetMomentum(theResidual.GetMomentum()-totalPhotonMomentum);
        theResult.AddSecondary(theSec);    
    }
    else
    {
      for(i0=0; i0<theParticles->size(); i0++)
      {
        theSec = new G4DynamicParticle; 
        theSec->SetDefinition(theParticles->operator[](i0)->GetDefinition());
        theSec->SetMomentum(theParticles->operator[](i0)->GetMomentum());
        theResult.AddSecondary(theSec); 
        delete theParticles->operator[](i0); 
      } 
      delete theParticles;
      if(needsSeparateRecoil && residualZ!=0)
      {
        G4ReactionProduct theResidual;   
        theResidual.SetDefinition(G4ParticleTable::GetParticleTable()
	                          ->GetIon(static_cast<G4int>(residualZ), static_cast<G4int>(residualA), 0));  
        G4double resiualKineticEnergy  = theResidual.GetMass()*theResidual.GetMass();
                 resiualKineticEnergy += totalMomentum*totalMomentum;
  	         resiualKineticEnergy  = std::sqrt(resiualKineticEnergy) - theResidual.GetMass();
//        cout << "Kinetic energy of the residual = "<<resiualKineticEnergy<<endl;
	theResidual.SetKineticEnergy(resiualKineticEnergy);

        //080612TK contribution from Benoit Pirard and Laurent Desorgher (Univ. Bern) #4
        //theResidual.SetMomentum(-1.*totalMomentum);
	//G4ThreeVector incidentNeutronMomentum = theNeutron.GetMomentum();
        //theResidual.SetMomentum(incidentNeutronMomentum - aHadron.GetMomentum());
//080717 TK Comment still do NOT include photon's mometum which produce by thePhotons
        theResidual.SetMomentum( theNeutron.GetMomentum() + theTarget.GetMomentum() - totalMomentum );

        theSec = new G4DynamicParticle;   
        theSec->SetDefinition(theResidual.GetDefinition());
        theSec->SetMomentum(theResidual.GetMomentum());
        theResult.AddSecondary(theSec);  
      }  
    }
    if(thePhotons!=0)
    {
      for(i=0; i<nPhotons; i++)
      {
        theSec = new G4DynamicParticle;    
        //Bug reported Chao Zhang (Chao.Zhang@usd.edu), Dongming Mei(Dongming.Mei@usd.edu) Feb. 25, 2009 
        //theSec->SetDefinition(G4Gamma::Gamma());
        theSec->SetDefinition( thePhotons->operator[](i)->GetDefinition() );
        //But never cause real effect at least with G4NDL3.13 TK
        theSec->SetMomentum(thePhotons->operator[](i)->GetMomentum());
        theResult.AddSecondary(theSec); 
        delete thePhotons->operator[](i);
      }
// some garbage collection
      delete thePhotons;
    }

//080721 
   G4ParticleDefinition* targ_pd = G4ParticleTable::GetParticleTable()->GetIon ( (G4int)theBaseZ , (G4int)theBaseA , 0.0 );
   G4LorentzVector targ_4p_lab ( theTarget.GetMomentum() , std::sqrt( targ_pd->GetPDGMass()*targ_pd->GetPDGMass() + theTarget.GetMomentum().mag2() ) );
   G4LorentzVector proj_4p_lab = theTrack.Get4Momentum();
   G4LorentzVector init_4p_lab = proj_4p_lab + targ_4p_lab;
   adjust_final_state ( init_4p_lab ); 

// clean up the primary neutron
    theResult.SetStatusChange(stopAndKill);
}



#include "G4RotationMatrix.hh" 
void G4NeutronHPInelasticCompFS::two_body_reaction ( G4DynamicParticle* proj, G4DynamicParticle* targ, G4DynamicParticle* hadron, G4double mu ) 
{

// Target rest flame
// 4vector in targ rest frame;
// targ could have excitation energy (photon energy will be emiited) tricky but,,,

   G4LorentzVector before = proj->Get4Momentum() + targ->Get4Momentum();

   G4ThreeVector p3_proj = proj->GetMomentum();
   G4ThreeVector d = p3_proj.unit();
   G4RotationMatrix rot; 
   G4RotationMatrix rot1; 
   rot1.setPhi( pi/2 + d.phi() );
   G4RotationMatrix rot2; 
   rot2.setTheta( d.theta() );
   rot=rot2*rot1;
   proj->SetMomentum( rot*p3_proj );

// Now proj only has pz component;

// mu in CM system 

   //Valid only for neutron incidence
   G4DynamicParticle* residual = new G4DynamicParticle ( G4ParticleTable::GetParticleTable()->GetIon ( (G4int)( targ->GetDefinition()->GetPDGCharge() - hadron->GetDefinition()->GetPDGCharge() ) , (G4int)(targ->GetDefinition()->GetBaryonNumber() - hadron->GetDefinition()->GetBaryonNumber()+1) , 0 ) , G4ThreeVector(0) ); 

   G4double Q = proj->GetDefinition()->GetPDGMass() + targ->GetDefinition()->GetPDGMass() 
	      - ( hadron->GetDefinition()->GetPDGMass() + residual->GetDefinition()->GetPDGMass() );

   // Non Relativistic Case 
   G4double A = targ->GetDefinition()->GetPDGMass() / proj->GetDefinition()->GetPDGMass();
   G4double AA = hadron->GetDefinition()->GetPDGMass() / proj->GetDefinition()->GetPDGMass(); 
   G4double E1 = proj->GetKineticEnergy();

// 101111
// In _nat_ data (Q+E1) could become negative value, following line is safty for this case.
   //if ( (Q+E1) < 0 ) 
   if ( ( 1 + (1+A)/A*Q/E1 ) < 0 ) 
   {
// 1.0e-6 eV is additional safty for numeric precision 
      Q = -( A/(1+A)*E1 ) + 1.0e-6*eV;
   }

   G4double beta = std::sqrt ( A*(A+1-AA)/AA*( 1 + (1+A)/A*Q/E1 ) );
   G4double gamma = AA/(A+1-AA)*beta;
   G4double E3 = AA/std::pow((1+A),2)*(beta*beta+1+2*beta*mu)*E1;
   G4double omega3 = (1+beta*mu)/std::sqrt(beta*beta+1+2*beta*mu);
   if ( omega3 > 1.0 ) omega3 = 1.0;

   G4double E4 = (A+1-AA)/std::pow((1+A),2)*(gamma*gamma+1-2*gamma*mu)*E1;
   G4double omega4 = (1-gamma*mu)/std::sqrt(gamma*gamma+1-2*gamma*mu);
   if ( omega4 > 1.0 ) omega4 = 1.0;

   hadron->SetKineticEnergy ( E3 );
   
   G4double M = hadron->GetDefinition()->GetPDGMass();
   G4double pmag = std::sqrt ((E3+M)*(E3+M)-M*M) ;
   G4ThreeVector p ( 0 , pmag*std::sqrt(1-omega3*omega3), pmag*omega3 );

   G4double M4 = residual->GetDefinition()->GetPDGMass();
   G4double pmag4 = std::sqrt ((E4+M4)*(E4+M4)-M4*M4) ;
   G4ThreeVector p4 ( 0 , -pmag4*std::sqrt(1-omega4*omega4), pmag4*omega4 );

// Rotate to orginal target rest flame.
   p *= rot.inverse();
   hadron->SetMomentum( p );
// Now hadron had 4 momentum in target rest flame 

// TypeA
   p4 *= rot.inverse();
   residual->SetMomentum ( p4 );

//TypeB1
   //residual->Set4Momentum ( p4_residual );
//TypeB2
   //residual->SetMomentum ( p4_residual.v() );

// Type A make difference in Momenutum
// Type B1 make difference in Mass of residual
// Type B2 make difference in total energy.

   delete residual;

}
