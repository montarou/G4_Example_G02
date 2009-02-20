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
// $Id: G4BetheBlochModel.hh,v 1.17 2009-02-20 12:06:37 vnivanch Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
// -------------------------------------------------------------------
//
// GEANT4 Class header file
//
//
// File name:     G4BetheBlochModel
//
// Author:        Vladimir Ivanchenko on base of Laszlo Urban code
//
// Creation date: 03.01.2002
//
// Modifications:
//
// 23-12-02 V.Ivanchenko change interface in order to moveto cut per region
// 24-01-03 Make models region aware (V.Ivanchenko)
// 13-02-03 Add name (V.Ivanchenko)
// 12-11-03 Fix for GenericIons (V.Ivanchenko)
// 24-03-05 Add G4EmCorrections (V.Ivanchenko)
// 11-04-05 Major optimisation of internal interfaces (V.Ivanchenko)
// 11-04-04 Move MaxSecondaryEnergy to models (V.Ivanchenko)
// 11-02-06 ComputeCrossSectionPerElectron, ComputeCrossSectionPerAtom (mma)
// 12-08-08 Added methods GetParticleCharge, GetChargeSquareRatio, 
//          CorrectionsAlongStep needed for ions(V.Ivanchenko)

//
// Class Description:
//
// Implementation of Bethe-Bloch model of energy loss and
// delta-electron production by heavy charged particles

// -------------------------------------------------------------------
//

#ifndef G4BetheBlochModel_h
#define G4BetheBlochModel_h 1

#include "G4VEmModel.hh"

class G4EmCorrections;
class G4ParticleChangeForLoss;
class G4NistManager;


class G4BetheBlochModel : public G4VEmModel
{

public:

  G4BetheBlochModel(const G4ParticleDefinition* p = 0,
                    const G4String& nam = "BetheBloch");

  virtual ~G4BetheBlochModel();

  virtual void Initialise(const G4ParticleDefinition*, const G4DataVector&);

  virtual G4double MinEnergyCut(const G4ParticleDefinition*,
				const G4MaterialCutsCouple*);
			
  virtual G4double ComputeCrossSectionPerElectron(
				 const G4ParticleDefinition*,
				 G4double kineticEnergy,
				 G4double cutEnergy,
				 G4double maxEnergy);
				 
  virtual G4double ComputeCrossSectionPerAtom(
				 const G4ParticleDefinition*,
				 G4double kineticEnergy,
				 G4double Z, G4double A,
				 G4double cutEnergy,
				 G4double maxEnergy);
				 				 
  virtual G4double CrossSectionPerVolume(const G4Material*,
				 const G4ParticleDefinition*,
				 G4double kineticEnergy,
				 G4double cutEnergy,
				 G4double maxEnergy);
				 
  virtual G4double ComputeDEDXPerVolume(const G4Material*,
					const G4ParticleDefinition*,
					G4double kineticEnergy,
					G4double cutEnergy);

  virtual G4double GetChargeSquareRatio(const G4ParticleDefinition* p,
					const G4Material* mat,
					G4double kineticEnergy);

  virtual G4double GetParticleCharge(const G4ParticleDefinition* p,
				     const G4Material* mat,
				     G4double kineticEnergy);

  virtual void CorrectionsAlongStep(const G4MaterialCutsCouple*,
				    const G4DynamicParticle*,
				    G4double& eloss,
				    G4double& niel,
				    G4double length);

  virtual void SampleSecondaries(std::vector<G4DynamicParticle*>*,
				 const G4MaterialCutsCouple*,
				 const G4DynamicParticle*,
				 G4double tmin,
				 G4double maxEnergy);

protected:

  virtual G4double MaxSecondaryEnergy(const G4ParticleDefinition*,
				      G4double kinEnergy);

private:

  void SetParticle(const G4ParticleDefinition* p);

  // hide assignment operator
  G4BetheBlochModel & operator=(const  G4BetheBlochModel &right);
  G4BetheBlochModel(const  G4BetheBlochModel&);

  const G4ParticleDefinition* particle;
  const G4Material*           currentMaterial;
  G4ParticleDefinition*       theElectron;
  G4EmCorrections*            corr;
  G4ParticleChangeForLoss*    fParticleChange;
  G4NistManager*              nist;

  G4double mass;
  G4double tlimit;
  G4double spin;
  G4double magMoment2;
  G4double chargeSquare;
  G4double ratio;
  G4double formfact;
  G4double twoln10;
  G4double bg2lim;
  G4double taulim;
  G4double corrFactor;
  G4bool   isIon;
  G4bool   isInitialised;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif
