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
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  File:   G4ITDecay.cc                                                      //
//  Author: D.H. Wright (SLAC)                                                //
//  Date:   14 November 2014                                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "G4ITDecay.hh"
#include "G4IonTable.hh"
#include "G4ThreeVector.hh"
#include "G4LorentzVector.hh"
#include "G4DynamicParticle.hh"
#include "G4DecayProducts.hh"
#include "G4PhotonEvaporation.hh"
#include "G4VAtomDeexcitation.hh"
#include "G4AtomicShells.hh"
#include "G4Electron.hh"
#include "G4LossTableManager.hh"
#include "G4Fragment.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"


G4ITDecay::G4ITDecay(G4PhotonEvaporation* ptr)
  : G4NuclearDecay("IT decay", IT, 0.0, noFloat), photonEvaporation(ptr)
{}

G4ITDecay::G4ITDecay(const G4ParticleDefinition* theParentNucleus,
                     const G4double& branch, const G4double&,
                     const G4double& excitationE)
  : G4NuclearDecay("IT decay", IT, excitationE, noFloat)
{
  SetParent(theParentNucleus);  // Store name of parent nucleus, delete G4MT_parent 
  SetBR(branch);
  SetNumberOfDaughters(1);
  SetDaughter(0, theParentNucleus);

  SetupDecay(theParentNucleus);
}

void G4ITDecay::SetupDecay(const G4ParticleDefinition* theParentNucleus)
{
  theParent = theParentNucleus;
  parentZ = theParentNucleus->GetAtomicNumber();
  parentA = theParentNucleus->GetAtomicMass();
}

G4DecayProducts* G4ITDecay::DecayIt(G4double)
{
  // Set up final state
  // parentParticle is set at rest here because boost with correct momentum 
  // is done later
  G4LorentzVector atRest(theParent->GetPDGMass(), G4ThreeVector(0.,0.,0.) );
  G4DynamicParticle parentParticle(theParent, atRest);
  G4DecayProducts* products = new G4DecayProducts(parentParticle);

  // Let G4PhotonEvaporation do the decay
  G4Fragment parentNucleus(parentA, parentZ, atRest);

  // one emission, parent nucleaus become less excited
  G4Fragment* eOrGamma = photonEvaporation->EmittedFragment(&parentNucleus);

  // Modified nuclide is returned as dynDaughter
  auto theIonTable = G4ParticleTable::GetParticleTable()->GetIonTable();
  G4ParticleDefinition* daughterIon =
    theIonTable->GetIon(parentZ, parentA, parentNucleus.GetExcitationEnergy(), 
                        G4Ions::FloatLevelBase(parentNucleus.GetFloatingLevelNumber()));
  G4DynamicParticle* dynDaughter = new G4DynamicParticle(daughterIon,
                                                         parentNucleus.GetMomentum());

  if (nullptr != eOrGamma) {
    G4DynamicParticle* eOrGammaDyn =
      new G4DynamicParticle(eOrGamma->GetParticleDefinition(),
                            eOrGamma->GetMomentum() );
    eOrGammaDyn->SetProperTime(eOrGamma->GetCreationTime() );
    products->PushProducts(eOrGammaDyn);
    delete eOrGamma;

    // Now do atomic relaxation if e- is emitted
    if (applyARM) {
      G4int shellIndex = photonEvaporation->GetVacantShellNumber();
      if (shellIndex > -1) {
        G4VAtomDeexcitation* atomDeex =
          G4LossTableManager::Instance()->AtomDeexcitation();
        if (atomDeex->IsFluoActive() && parentZ > 5 && parentZ < 105) {
          G4int nShells = G4AtomicShells::GetNumberOfShells(parentZ);
          if (shellIndex >= nShells) shellIndex = nShells;
          G4AtomicShellEnumerator as = G4AtomicShellEnumerator(shellIndex);
          const G4AtomicShell* shell = atomDeex->GetAtomicShell(parentZ, as);
          std::vector<G4DynamicParticle*> armProducts;

          // VI, SI
          // Allows fixing of Bugzilla 1727
          G4double deexLimit = 0.1*keV;
          if (G4EmParameters::Instance()->DeexcitationIgnoreCut())  deexLimit =0.;
          //

          atomDeex->GenerateParticles(&armProducts, shell, parentZ, deexLimit,
                                                                    deexLimit);
          G4double productEnergy = 0.;
          for (G4int i = 0; i < G4int(armProducts.size()); i++)
            productEnergy += armProducts[i]->GetKineticEnergy();

          G4double deficit = shell->BindingEnergy() - productEnergy;
          if (deficit > 0.0) { 
            // Add a dummy electron to make up extra energy
            G4double cosTh = 1.-2.*G4UniformRand();
            G4double sinTh = std::sqrt(1.- cosTh*cosTh);
            G4double phi = twopi*G4UniformRand();
         
            G4ThreeVector electronDirection(sinTh*std::sin(phi),
                                            sinTh*std::cos(phi), cosTh);
            G4DynamicParticle* extra =
              new G4DynamicParticle(G4Electron::Electron(), electronDirection,
                                    deficit);
            armProducts.push_back(extra);
          } 

          std::size_t nArm = armProducts.size();
          if (nArm > 0) {
            G4ThreeVector bst = dynDaughter->Get4Momentum().boostVector();
            for (std::size_t i = 0; i < nArm; ++i) {
              G4DynamicParticle* dp = armProducts[i];
              G4LorentzVector lv = dp->Get4Momentum().boost(bst);
              dp->Set4Momentum(lv);
              products->PushProducts(dp);
            }
          }
        }
      }
    } // if ARM on 
  } // eOrGamma

  products->PushProducts(dynDaughter);

  // Energy conservation check
  /*
  G4int newSize = products->entries();
  G4DynamicParticle* temp = 0;
  G4double KEsum = 0.0;
  for (G4int i = 0; i < newSize; i++) {
    temp = products->operator[](i);
    KEsum += temp->GetKineticEnergy();
  }
  G4double eCons = G4MT_parent->GetPDGMass() - dynDaughter->GetMass() - KEsum;
  G4cout << " IT check: Ediff (keV) = " << eCons/keV << G4endl; 
  */
  return products;
}


void G4ITDecay::DumpNuclearInfo()
{
  if (theParent != nullptr) {
    G4cout << " G4ITDecay for parent nucleus " << theParent->GetParticleName() << G4endl;
  }
}

