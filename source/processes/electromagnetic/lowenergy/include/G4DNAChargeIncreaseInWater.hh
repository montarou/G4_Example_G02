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
// -------------------------------------------------------------------
// $Id: G4DNAChargeIncreaseInWater.hh,v 1.4 2007-10-08 09:18:42 sincerti Exp $
// -------------------------------------------------------------------
//

#ifndef G4DNAChargeIncreaseInWater_HH
#define G4DNAChargeIncreaseInWater_HH 1

#include "G4VDNAProcessInWater.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

template<typename CrossSectionPolicy, typename FinalStatesPolicy>
class G4DNAChargeIncreaseInWater: 
public G4VDNAProcessInWater<CrossSectionPolicy, FinalStatesPolicy>
{
 public:
   
   G4DNAChargeIncreaseInWater(const G4String & name) : G4VDNAProcessInWater<CrossSectionPolicy, FinalStatesPolicy>(name) {}
   
   virtual ~G4DNAChargeIncreaseInWater() {}

   virtual G4VParticleChange * PostStepDoIt(const G4Track & aTrack, const G4Step & aStep);

   virtual G4bool IsApplicable(const G4ParticleDefinition& aParticleDefinition);

 private:
 
   // Hides default constructor and assignment operator as private
   G4DNAChargeIncreaseInWater(const G4DNAChargeIncreaseInWater & copy);
   G4DNAChargeIncreaseInWater & operator=(const G4DNAChargeIncreaseInWater & right);
 };

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "G4DNAChargeIncreaseInWater.icc"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif
