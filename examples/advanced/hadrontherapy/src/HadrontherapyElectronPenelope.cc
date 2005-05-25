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
// $Id: HadrontherapyElectronPenelope.cc,v 1.4 2005-05-25 09:11:09 guatelli Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
// Author: Maria.Grazia.Pia@cern.ch
//
// History:
// -----------
// 22 Feb 2003 MGP          Designed for modular Physics List
//
// -------------------------------------------------------------------

#include "HadrontherapyElectronPenelope.hh"

#include "G4ProcessManager.hh"
#include "G4Gamma.hh"
#include "G4ParticleDefinition.hh"
#include "G4MultipleScattering.hh"
#include "G4PenelopeIonisation.hh"
#include "G4PenelopeBremsstrahlung.hh"
#include "G4PenelopeAnnihilation.hh"
#include "G4StepLimiter.hh"

HadrontherapyElectronPenelope::HadrontherapyElectronPenelope(const G4String& name): 
G4VPhysicsConstructor(name)
{ }

HadrontherapyElectronPenelope::~HadrontherapyElectronPenelope()
{ }

void HadrontherapyElectronPenelope::ConstructProcess()
{
  
  
  theParticleIterator->reset();

  while( (*theParticleIterator)() )
    {
      G4ParticleDefinition* particle = theParticleIterator->value();
      G4ProcessManager* manager = particle->GetProcessManager();
      G4String particleName = particle->GetParticleName();
     
      if (particleName == "e-") 
	{
	  manager -> AddProcess(new G4MultipleScattering, -1, 1,1);
	  G4PenelopeIonisation* ioni = new G4PenelopeIonisation();
   	  G4PenelopeBremsstrahlung* brem = new G4PenelopeBremsstrahlung();
          manager -> AddProcess(ioni, -1, 2,2);
	  manager -> AddProcess(brem, -1,-1,3); 
          manager->AddProcess(new G4MultipleScattering, -1, 1,1);
          manager->AddProcess(new G4StepLimiter(),      -1,-1,3); 
	}   
    }
}
