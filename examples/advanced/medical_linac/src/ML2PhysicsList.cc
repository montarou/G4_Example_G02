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
// The code was written by :
//	^Claudio Andenna claudio.andenna@iss.infn.it, claudio.andenna@ispesl.it
//      *Barbara Caccia barbara.caccia@iss.it
//      with the support of Pablo Cirrone (LNS, INFN Catania Italy)
//
// ^ISPESL and INFN Roma, gruppo collegato Sanità, Italy
// *Istituto Superiore di Sanità and INFN Roma, gruppo collegato Sanità, Italy
//  Viale Regina Elena 299, 00161 Roma (Italy)
//  tel (39) 06 49902246
//  fax (39) 06 49387075
//
// more information:
// http://g4advancedexamples.lngs.infn.it/Examples/medical-linac
//
//*******************************************************//
//
// This class provides all the physic models that can be activated inside ML2;
// Each model can be setted via macro commands;
// Inside ML2 the models can be activate with three different complementar methods:
//
// 1. Use of the *Packages*.
//    Packages (that are contained inside the
//    Geant4 distribution at $G4INSTALL/source/physics_lists/lists) provide a full set
//    of models (both electromagnetic and hadronic).
//    The User can use this method simply add the line /physic/addPackage <nameOfPackage>
//    in his/her macro file. No other action is required.
//    For ML2 applications we suggest the use of the QGSP_BIC package
//    for proton beams. The same can be used
//    also for ligth ion beam.
//   
//
// 2. Use of the *Physic Lists*.
//    Physic lists are also already ready to use inside the Geant4 distribution
//    ($G4INSTALL/source/physics_lists/builders). To use them the simple
//    /physic/addPhysics <nameOfPhysicList> command must be used in the macro.
//    In ML2 we provide physics list to activate Electromagnetic,
//    Hadronic elastic and Hadronic inelastic models.
//
//    For ML2 we suggest the use of:
//
//    /physic/addPhysic/emstandard_option3 (electromagnetic model)
//    /physic/addPhysic/QElastic (hadronic elastic model)
//    /physic/addPhysic/binary (hadronic inelastic models for proton and neutrons)
//    /physic/addPhysic/binary_ion (hadronic inelastic models for ions)
//
//    Example of the use of physics lists can be found in the macro files 
//


#include "ML2PhysicsList.hh"
#include "ML2PhysicsListMessenger.hh"
#include "ML2StepMax.hh"
#include "G4PhysListFactory.hh"
#include "G4VPhysicsConstructor.hh"

// Physic lists (contained inside the Geant4 distribution)
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronDElasticPhysics.hh"
#include "G4HadronHElasticPhysics.hh"
#include "G4HadronQElasticPhysics.hh"
#include "G4HadronInelasticQBBC.hh"
#include "G4IonBinaryCascadePhysics.hh"
#include "G4Decay.hh"

#include "G4LossTableManager.hh"
#include "G4UnitsTable.hh"
#include "G4ProcessManager.hh"

#include "G4IonFluctuations.hh"
#include "G4IonParametrisedLossModel.hh"
#include "G4EmProcessOptions.hh"

/////////////////////////////////////////////////////////////////////////////
ML2PhysicsList::ML2PhysicsList() : G4VModularPhysicsList()
{
  G4LossTableManager::Instance();
  defaultCutValue = 1.*mm;
  cutForGamma     = defaultCutValue;
  cutForElectron  = defaultCutValue;
  cutForPositron  = defaultCutValue;

  helIsRegisted  = false;
  bicIsRegisted  = false;
  biciIsRegisted = false;
  locIonIonInelasticIsRegistered = false;

  stepMaxProcess  = 0;

  pMessenger = new ML2PhysicsListMessenger(this);

  SetVerboseLevel(1);

  // EM physics
  emPhysicsList = new G4EmStandardPhysics_option3(1);
  emName = G4String("emstandard_opt3");

//  emPhysicsList = new G4EmLivermorePhysics();
//  emName = G4String("LowE_Livermore");

  // Deacy physics and all particles
  decPhysicsList = new G4DecayPhysics();
}

/////////////////////////////////////////////////////////////////////////////
ML2PhysicsList::~ML2PhysicsList()
{
  delete pMessenger;
  delete emPhysicsList;
  delete decPhysicsList;
  for(size_t i=0; i<hadronPhys.size(); i++) {delete hadronPhys[i];}
}

/////////////////////////////////////////////////////////////////////////////
void ML2PhysicsList::AddPackage(const G4String& name)
{
  G4PhysListFactory factory;
  G4VModularPhysicsList* phys =factory.GetReferencePhysList(name);
  G4int i=0;
  const G4VPhysicsConstructor* elem= phys->GetPhysics(i);
  G4VPhysicsConstructor* tmp = const_cast<G4VPhysicsConstructor*> (elem);
  while (elem !=0)
	{
	  RegisterPhysics(tmp);
	  elem= phys->GetPhysics(++i) ;
	  tmp = const_cast<G4VPhysicsConstructor*> (elem);
	}
    G4cout << "THE FOLLOWING PHYSICS PACKEGE LIST HAS BEEN ACTIVATED: "<<name<< G4endl;
}

/////////////////////////////////////////////////////////////////////////////
void ML2PhysicsList::ConstructParticle()
{
  decPhysicsList->ConstructParticle();
}

/////////////////////////////////////////////////////////////////////////////
void ML2PhysicsList::ConstructProcess()
{
  // transportation
  //
  AddTransportation();

  // electromagnetic physics list
  //
  emPhysicsList->ConstructProcess();
  em_config.AddModels();

  // decay physics list
  //
  decPhysicsList->ConstructProcess();

  // hadronic physics lists
  for(size_t i=0; i<hadronPhys.size(); i++) {
    hadronPhys[i]->ConstructProcess();
  }

  // step limitation (as a full process)
  //
  AddStepMax();
}

/////////////////////////////////////////////////////////////////////////////
void ML2PhysicsList::AddPhysicsList(const G4String& name)
{

  if (verboseLevel>1) {
    G4cout << "PhysicsList::AddPhysicsList: <" << name << ">" << G4endl;
  }
  if (name == emName) return;

  /////////////////////////////////////////////////////////////////////////////
  //   ELECTROMAGNETIC MODELS
  /////////////////////////////////////////////////////////////////////////////

  if (name == "standard_opt3") {
    emName = name;
    delete emPhysicsList;
    emPhysicsList = new G4EmStandardPhysics_option3();
    G4cout << "THE FOLLOWING ELECTROMAGNETIC PHYSICS LIST HAS BEEN ACTIVATED: G4EmStandardPhysics_option3" << G4endl;

 } else if (name == "LowE_Livermore") {
    emName = name;
    delete emPhysicsList;
    emPhysicsList = new G4EmLivermorePhysics();
    G4cout << "THE FOLLOWING ELECTROMAGNETIC PHYSICS LIST HAS BEEN ACTIVATED: G4EmLivermorePhysics" << G4endl;

 } else if (name == "LowE_Penelope") {
    emName = name;
    delete emPhysicsList;
    emPhysicsList = new G4EmPenelopePhysics();
    G4cout << "THE FOLLOWING ELECTROMAGNETIC PHYSICS LIST HAS BEEN ACTIVATED: G4EmLivermorePhysics" << G4endl;

    /////////////////////////////////////////////////////////////////////////////
    //   HADRONIC MODELS
    /////////////////////////////////////////////////////////////////////////////
  } else if (name == "elastic" && !helIsRegisted) {
    G4cout << "THE FOLLOWING HADRONIC ELASTIC PHYSICS LIST HAS BEEN ACTIVATED: G4HadronElasticPhysics()" << G4endl;
    hadronPhys.push_back( new G4HadronElasticPhysics());
    helIsRegisted = true;

  } else if (name == "DElastic" && !helIsRegisted) {
    hadronPhys.push_back( new G4HadronDElasticPhysics());
    helIsRegisted = true;

  } else if (name == "HElastic" && !helIsRegisted) {
    hadronPhys.push_back( new G4HadronHElasticPhysics());
    helIsRegisted = true;

  } else if (name == "QElastic" && !helIsRegisted) {
    hadronPhys.push_back( new G4HadronQElasticPhysics());
    helIsRegisted = true;

  } else if (name == "binary" && !bicIsRegisted) {
    hadronPhys.push_back(new G4HadronInelasticQBBC());
    bicIsRegisted = true;
    G4cout << "THE FOLLOWING HADRONIC INELASTIC PHYSICS LIST HAS BEEN ACTIVATED: G4HadronInelasticQBBC()" << G4endl;

  } else if (name == "binary_ion" && !biciIsRegisted) {
    hadronPhys.push_back(new G4IonBinaryCascadePhysics());
    biciIsRegisted = true;

  } else {

    G4cout << "PhysicsList::AddPhysicsList: <" << name << ">"
           << " is not defined"
           << G4endl;
  }
}

/////////////////////////////////////////////////////////////////////////////
void ML2PhysicsList::AddStepMax()
{
  // Step limitation seen as a process
  stepMaxProcess = new ML2StepMax();

  theParticleIterator->reset();
  while ((*theParticleIterator)()){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();

    if (stepMaxProcess->IsApplicable(*particle) && pmanager)
      {
	pmanager ->AddDiscreteProcess(stepMaxProcess);
      }
  }
}

/////////////////////////////////////////////////////////////////////////////
void ML2PhysicsList::SetCuts()
{

  if (verboseLevel >0){
    G4cout << "PhysicsList::SetCuts:";
    G4cout << "CutLength : " << G4BestUnit(defaultCutValue,"Length") << G4endl;
  }

  // set cut values for gamma at first and for e- second and next for e+,
  // because some processes for e+/e- need cut values for gamma
  SetCutValue(cutForGamma, "gamma");
  SetCutValue(cutForElectron, "e-");
  SetCutValue(cutForPositron, "e+");

  if (verboseLevel>0) DumpCutValuesTable();
}

/////////////////////////////////////////////////////////////////////////////
void ML2PhysicsList::SetCutForGamma(G4double cut)
{
  cutForGamma = cut;
  SetParticleCuts(cutForGamma, G4Gamma::Gamma());
}

/////////////////////////////////////////////////////////////////////////////
void ML2PhysicsList::SetCutForElectron(G4double cut)
{
  cutForElectron = cut;
  SetParticleCuts(cutForElectron, G4Electron::Electron());
}

/////////////////////////////////////////////////////////////////////////////
void ML2PhysicsList::SetCutForPositron(G4double cut)
{
  cutForPositron = cut;
  SetParticleCuts(cutForPositron, G4Positron::Positron());
}


