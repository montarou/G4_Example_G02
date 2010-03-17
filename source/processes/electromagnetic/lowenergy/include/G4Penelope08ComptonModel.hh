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
// $Id: G4Penelope08ComptonModel.hh,v 1.1 2010-03-17 14:19:04 pandola Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
// Author: Luciano Pandola
//
// History:
// -----------
// 15 Feb 2010   L. Pandola   1st implementation. 
//
// -------------------------------------------------------------------
//
// Class description:
// Low Energy Electromagnetic Physics, Compton Scattering
// with Penelope Model, version 2008
// -------------------------------------------------------------------

#ifndef G4PENELOPE08COMPTONMODEL_HH
#define G4PENELOPE08COMPTONMODEL_HH 1

#include "globals.hh"
#include "G4VEmModel.hh"
#include "G4DataVector.hh"
#include "G4ParticleChangeForGamma.hh"
#include "G4AtomicDeexcitation.hh"

class G4ParticleDefinition;
class G4DynamicParticle;
class G4MaterialCutsCouple;
class G4Material;
class G4PenelopeOscillatorManager;
class G4PenelopeOscillator;

class G4Penelope08ComptonModel : public G4VEmModel 
{

public:
  
  G4Penelope08ComptonModel(const G4ParticleDefinition* p=0,
			 const G4String& processName ="PenCompton");
  
  virtual ~G4Penelope08ComptonModel();

  virtual void Initialise(const G4ParticleDefinition*, const G4DataVector&);

  virtual G4double CrossSectionPerVolume(const G4Material*,
                                         const G4ParticleDefinition*,
                                         G4double kineticEnergy,
                                         G4double cutEnergy = 0.0,
                                         G4double maxEnergy = DBL_MAX);
  
  //This is a dummy method. Never inkoved by the tracking, it just issues 
  //a warning if one tries to get Cross Sections per Atom via the 
  //G4EmCalculator.
  virtual G4double ComputeCrossSectionPerAtom(const G4ParticleDefinition*,
                                              G4double,
                                              G4double,
                                              G4double,
                                              G4double,
                                              G4double);

  virtual void SampleSecondaries(std::vector<G4DynamicParticle*>*,
				 const G4MaterialCutsCouple*,
				 const G4DynamicParticle*,
				 G4double tmin,
				 G4double maxEnergy);

  void SetVerbosityLevel(G4int lev){verboseLevel = lev;};
  G4int GetVerbosityLevel(){return verboseLevel;};

  void ActivateAuger(G4bool);

protected:
  G4ParticleChangeForGamma* fParticleChange;

private:
  //Differential cross section which is numerically integrated
  G4double DifferentialCrossSection (G4double cdt,G4double energy,
				     G4PenelopeOscillator* osc);

  G4double OscillatorTotalCrossSection(G4double energy,G4PenelopeOscillator* osc);

  G4double KleinNishinaCrossSection(G4double energy,const G4Material*);

  G4double GetAtomsPerMolecule(const G4Material*);

  G4Penelope08ComptonModel & operator=(const G4Penelope08ComptonModel &right);
  G4Penelope08ComptonModel(const G4Penelope08ComptonModel&);

  //Intrinsic energy limits of the model: cannot be extended by the parent process
  G4double fIntrinsicLowEnergyLimit;
  G4double fIntrinsicHighEnergyLimit;

  G4int verboseLevel;

  G4bool isInitialised;

  G4AtomicDeexcitation deexcitationManager;

  G4PenelopeOscillatorManager* oscManager;

  std::map<const G4Material*,G4double> *atomsPerMolecule;

};

#endif

