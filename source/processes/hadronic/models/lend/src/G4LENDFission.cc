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
#include "G4LENDFission.hh"

#include "G4Nucleus.hh"
#include "G4ParticleTable.hh"
  
G4HadFinalState * G4LENDFission::ApplyYourself(const G4HadProjectile& aTrack, G4Nucleus& aTarg )
{

   G4double temp = aTrack.GetMaterial()->GetTemperature();

   G4int iZ = int ( aTarg.GetZ() );
   G4int iA = int ( aTarg.GetN() );

   G4double ke = aTrack.GetKineticEnergy();

   G4HadFinalState* theResult = &theParticleChange;
   theResult->Clear();

   G4GIDI_target* aTarget = usedTarget_map.find( lend_manager->GetNucleusEncoding( iZ , iA ) )->second->GetTarget();
   std::vector<G4GIDI_Product>* products = aTarget->getFissionFinalState( ke*MeV, temp, NULL, NULL );
   if ( products != NULL ) 
   {
      for ( G4int j = 0; j < int( products->size() ); j++ ) 
      {
         G4int iZ = (*products)[j].Z; 
         G4int iA = (*products)[j].A; 

         //G4cout << "Z = "    << (*products)[j].Z 
         //       << ", A = "  << (*products)[j].A 
         //       << ", EK = " << (*products)[j].kineticEnergy << " [MeV]" 
         //       << ", px = " << (*products)[j].px
         //       << ", py = " << (*products)[j].py
         //       << ", pz = " << (*products)[j].pz
         //       << G4endl;

         G4DynamicParticle* theSec = new G4DynamicParticle;

         if ( iZ > 0 )
         {
                                                                                        //Ex  j?
            theSec->SetDefinition( G4ParticleTable::GetParticleTable()->FindIon( iZ, iA , 0, 0 ) );
         } 
         else if ( iA == 1 && iZ == 0 )
         {
            theSec->SetDefinition( G4Neutron::Neutron() );
         } 
         else
         {
            theSec->SetDefinition( G4Gamma::Gamma() );
         } 

         theSec->SetMomentum( G4ThreeVector( (*products)[j].px*MeV , (*products)[j].py*MeV , (*products)[j].pz*MeV ) );
         //G4cout << theSec->GetDefinition()->GetParticleName() << G4endl;
         theResult->AddSecondary( theSec );
      } 
   }
   delete products;

   theResult->SetStatusChange( stopAndKill );

   return theResult; 

}