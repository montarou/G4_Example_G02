//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
// Rich advanced example for Geant4
// RichTbMaterialParameters.cc for Rich of LHCb
// History:
// Created: Sajan Easo (Sajan.Easo@cern.ch)
// Revision and changes: Patricia Mendez (Patricia.Mendez@cern.ch)
/////////////////////////////////////////////////////////////////////////////
#include <iostream.h>
#include <fstream.h>
#include "globals.hh"
#include "RichTbGeometryParameters.hh"
#include "RichTbMaterialParameters.hh"
#include "FilterTrData.hh"
#include "AerogelTypeSpec.hh"

#include "RichTbAnalysisManager.hh"


void InitializeRichTbMaterial(){

}

vector<G4double> InitializePhotonMomentumVector() {

  G4double PhotonEnergyStep=(PhotonMaxEnergy-PhotonMinEnergy)/
                            NumPhotWaveLengthBins;
  vector<G4double>PhotMomVect(NumPhotWaveLengthBins);
  for (G4int ibin=0; ibin<NumPhotWaveLengthBins; ibin++){
    PhotMomVect[ibin]=PhotonMinEnergy+PhotonEnergyStep*ibin;
  }
  return PhotMomVect;
}
vector<G4double> InitN2RefIndex(G4double pressure, G4double temperature){
 
  vector<G4double> PmV=InitN2RefPhotW();
  vector<G4double> RefN2(NumPhotWaveLengthBins);
  G4double GasRhoN2Cur=GasRhoN2atSTP*(GasTemperature_STP/temperature)*
                                     (pressure/ GasPressure_STP);
  G4double epho,pfe,cpfe;
  for(G4int ibinwn =0; ibinwn<NumPhotWaveLengthBins ; ibinwn++ ){

    epho = PmV[ibinwn]/eV;
    pfe  = SellN2F1/(SellN2E1*SellN2E1 - epho*epho )  +
      SellN2F2/(SellN2E2*SellN2E2 - epho*epho );
    cpfe=0.3738*(GasRhoN2Cur/GasMolWeightN2)*pfe;
    RefN2[ibinwn]=pow((1.0+2*cpfe)/(1.0-cpfe),0.5); 
  }
  return RefN2;
}
vector<G4double> InitN2RefPhotW() {
  return InitializePhotonMomentumVector() ; 
} 
vector<G4double> InitAgelPhotW() {
  return InitializePhotonMomentumVector() ; 
}
vector<G4double> InitializeHpdQE(G4int ihpdqe) {
  // Initialize the HPD QE
   G4int iqb;
   if(ihpdqe >= NumHpdTot ) {
     G4cout<<"Wrong HPD Number for QE " <<ihpdqe<<"  vs "
	 <<NumHpdTot <<G4endl;
   }
   vector<G4double>qeCurPerCent(NumQEbins);
   if(ihpdqe == 0 ){
    for(iqb=0; iqb<NumQEbins; iqb++){
      qeCurPerCent[iqb] =  Hpd0QEPerCent[iqb]* HpdQEReductionFactor;
   }  
  }
  if(ihpdqe == 1 ){
    for(iqb=0; iqb<NumQEbins; iqb++){
      qeCurPerCent[iqb] =  Hpd1QEPerCent[iqb]* HpdQEReductionFactor;
    }  
  }
  if(ihpdqe == 2 ){
    for(iqb=0; iqb<NumQEbins; iqb++){
      qeCurPerCent[iqb] =  Hpd2QEPerCent[iqb]* HpdQEReductionFactor;
    }  
  }
  if(ihpdqe == 3 ){
    for(iqb=0; iqb<NumQEbins; iqb++){
      qeCurPerCent[iqb] =  Hpd3QEPerCent[iqb]* HpdQEReductionFactor;
    }  
  }

 return  qeCurPerCent;
}
vector<G4double> InitializeHpdWaveL(G4int ihpdqe) {
  G4int iqb;
 if(ihpdqe >= NumHpdTot ) {
   G4cout<<"Wrong HPD Number for QE wavelength " <<ihpdqe<<"  vs "
	 <<NumHpdTot <<G4endl;
 }
 // for now all HPDs have the same wavelength bins.
 vector<G4double>HpdQEW(NumQEbins);
 for (iqb=0; iqb<NumQEbins; iqb++){
   HpdQEW[iqb]= HpdQEWaveL[iqb];
 }  
 return HpdQEW;
}

void  HistoRichTbMaterialProperties(RichTbRunConfig* RConfig) {


  G4int AerogelNum=0;
  G4double waL=200;

  G4double stepsize=7.0;

  G4double thickness=(GetCurAerogelLength(AerogelNum))/cm;
  AerogelType CurAerogelType=RConfig-> GetCurAerogelType(AerogelNum);



  G4double Aparam, Cparam;
  if(CurAerogelType == AerogelTypeA ) {
    Aparam =   AerogelTypeATotTrans;
    Cparam =  AerogelTypeAClarity*cm/(micrometer*micrometer*micrometer*micrometer);
   }


  
  for(G4int Iabin=0; Iabin<100; Iabin ++ ) {
   
    G4double waLInmu = waL/1000.0;
    G4double Aetr = Aparam* exp(-Cparam * thickness / pow(waLInmu,4) );

    waL += stepsize;
  }






  G4int ihpdqa;
  ihpdqa=0;
  vector<G4double>WaveL1 = InitializeHpdWaveL(ihpdqa); 
  vector<G4double>QEff1 = InitializeHpdQE(ihpdqa);



}
  

vector<G4int> getDeadPixelList(G4int ihpdNum,  G4int isectNum){
  vector<G4int>DeadPixelList;
  G4int isc,ipsc;


  if(DeadPixelList.size() >  MaxNumDeadPixelPerHpdSect ){
    G4cout<<" Too Many dead Pixels in Hpd "<<DeadPixelList.size()
          <<"   in Hpd "<<ihpdNum<<G4endl;
  }

  return DeadPixelList;
}
vector<G4double>GetAerogelRScatLength(AerogelType CurrentAerogelType) {

  vector<G4double>AgelRayleighScatLength(NumPhotWaveLengthBins);
  vector<G4double>AgelPhotW = InitAgelPhotW();
  G4double aClarity;
  if(CurrentAerogelType == AerogelTypeA ) {
    aClarity=AerogelTypeAClarity/(micrometer*micrometer*micrometer*micrometer);
    
  }else if (CurrentAerogelType == AerogelTypeB ) {
    aClarity=AerogelTypeBClarity/(micrometer*micrometer*micrometer*micrometer);
  }else if (CurrentAerogelType == AerogelTypeC ) {
    aClarity=AerogelTypeCClarity/(micrometer*micrometer*micrometer*micrometer);


  }else if (CurrentAerogelType == AerogelTypeD ) {
    aClarity=AerogelTypeDClarity/(micrometer*micrometer*micrometer*micrometer);

  }else if (CurrentAerogelType == AerogelTypeE ) {
    aClarity=AerogelTypeEClarity/(micrometer*micrometer*micrometer*micrometer);

  }else {G4cout<<"Unknown Aerogel Type for Rayleigh Scat Length "<<endl; }

  if(aClarity != 0.0 ) {    
    for(G4int ibinw=0; ibinw<NumPhotWaveLengthBins; ibinw++ ){
      G4double ephoton=AgelPhotW[ibinw]/eV;
      //In the following the 1000 is to convert form nm to micrometer
      G4double wphoton=(PhotMomWaveConv/ephoton)/1000.0;
      AgelRayleighScatLength[ibinw]=(pow(wphoton,4))/aClarity;
 
    }
  }

  return  AgelRayleighScatLength;
}
G4double GetCurrentBulkTrans(G4double currentMatRefIndex, 
                          G4double currentNeighbourRefIndex,
                          G4double MaxTotMeasuredTransmission){
  G4double ATrans=MaxTotMeasuredTransmission;
  G4double ePhot;
  // in the following the energy of the photon is not used since
  // it is only an approximate calulation. 
  G4double na=  currentMatRefIndex;
  G4double nb=  currentNeighbourRefIndex;
  G4double LossAtEntrance=pow(((na-nb)/(na+nb)),2.0);
  G4double LossAtExit=pow(((nb-na)/(nb+na)),2.0);
  
  G4double LightLossAtExternalSurface= LossAtEntrance+ LossAtExit;
  
  ATrans += LightLossAtExternalSurface;
  if(ATrans >= 1.0) ATrans=1.0;
  return ATrans;
}





