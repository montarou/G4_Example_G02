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
#include "RemSimPhotonStandard.hh"

#include "G4ProcessManager.hh"
#include "G4Gamma.hh"
#include "G4ParticleDefinition.hh"
#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"

RemSimPhotonStandard::RemSimPhotonStandard(const G4String& name): G4VPhysicsConstructor(name)
{ }

RemSimPhotonStandard::~RemSimPhotonStandard()
{ }

void RemSimPhotonStandard::ConstructProcess()
{
  // Add standard processes for photons
  
  theParticleIterator->reset();

  while( (*theParticleIterator)() )
    {
      G4ParticleDefinition* particle = theParticleIterator->value();
      G4ProcessManager* manager = particle->GetProcessManager();
      G4String particleName = particle->GetParticleName();

      if (particleName == "gamma") 
	{
          
	  manager->AddDiscreteProcess(new G4PhotoElectricEffect);
	  manager->AddDiscreteProcess(new G4ComptonScattering);
	  manager->AddDiscreteProcess(new G4GammaConversion);
          G4cout<<"Gamma Processes registered"<<G4endl;
	}   
    }
}
