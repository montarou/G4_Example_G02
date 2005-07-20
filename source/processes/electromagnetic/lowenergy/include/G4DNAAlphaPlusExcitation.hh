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
//
// $Id: G4DNAAlphaPlusExcitation.hh,v 1.1 2005-07-20 10:01:54 capra Exp $
// GEANT4 tag $Name: not supported by cvs2svn $

#ifndef   G4DNAALPHAPLUSEXCITATION_HH
 #define  G4DNAALPHAPLUSEXCITATION_HH 1
 
 #include "G4DNAExcitationInWater.hh"
 #include "G4DNAMillerAndGreenExcitationTotalCrossSectionPolicy.hh"
 #include "G4DNAStopAndKillBelowEnergyLimitPolicy.hh"
 
 class G4DNAAlphaPlusExcitationEnergyLimitsPolicy
 {
  protected:
                      G4DNAAlphaPlusExcitationEnergyLimitsPolicy();
  
   const G4double     lowEnergyLimit;
   const G4bool       zeroBelowLowEnergyLimit;
   const G4double     highEnergyLimit;
   const G4bool       zeroAboveHighEnergyLimit;
 };
 
 class G4DNAAlphaPlusExcitationIncomingParticlePolicy
 {
  protected:
                                        G4DNAAlphaPlusExcitationIncomingParticlePolicy();
   const G4ParticleDefinition *         IncomingParticleDefinition(void) const;

   G4double                             slaterEffectiveCharge[3];
   G4double                             sCoefficient[3];
   const G4double                       kineticEnergyCorrection;
 };
 
 class G4DNAAlphaPlusExcitation : public G4DNAExcitationInWater<G4DNAMillerAndGreenExcitationTotalCrossSectionPolicy<G4DNAAlphaPlusExcitationIncomingParticlePolicy, G4DNAAlphaPlusExcitationEnergyLimitsPolicy>, G4DNAStopAndKillBelowEnergyLimitPolicy<G4DNAAlphaPlusExcitationEnergyLimitsPolicy> >
 {
  public:
                                         G4DNAAlphaPlusExcitation(const G4String & name = "G4DNAAlphaPlusExcitation") : G4DNAExcitationInWater<G4DNAMillerAndGreenExcitationTotalCrossSectionPolicy<G4DNAAlphaPlusExcitationIncomingParticlePolicy, G4DNAAlphaPlusExcitationEnergyLimitsPolicy>, G4DNAStopAndKillBelowEnergyLimitPolicy<G4DNAAlphaPlusExcitationEnergyLimitsPolicy> > (name) {}
   virtual                              ~G4DNAAlphaPlusExcitation() {}
 };
#endif /* G4DNAALPHAPLUSEXCITATION_HH */
