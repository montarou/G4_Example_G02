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
/// \file field/field01/src/F01FieldMessenger.cc
/// \brief Implementation of the F01FieldMessenger class
//
//
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "F01FieldMessenger.hh"

#include "F01FieldSetup.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

#include "G4FieldManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

F01FieldMessenger::F01FieldMessenger(F01FieldSetup* fieldSetup)
 : fEMfieldSetup(fieldSetup)
{
  fFieldDir = new G4UIdirectory("/field/");
  fFieldDir->SetGuidance("F01 field tracking control.");

  fStepperCmd = new G4UIcmdWithAnInteger("/field/setStepperType",this);
  fStepperCmd->SetGuidance("Select stepper type for magnetic field");
  fStepperCmd->SetParameterName("choice",true);
  fStepperCmd->SetDefaultValue(4);
  fStepperCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fUpdateCmd = new G4UIcmdWithoutParameter("/field/update",this);
  fUpdateCmd->SetGuidance("Update calorimeter geometry.");
  fUpdateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
  fUpdateCmd->SetGuidance("if you changed geometrical value(s).");
  fUpdateCmd->AvailableForStates(G4State_Idle);

  fMagFieldZCmd = new G4UIcmdWithADoubleAndUnit("/field/setFieldZ",this);
  fMagFieldZCmd->SetGuidance("Define magnetic field.");
  fMagFieldZCmd->SetGuidance("Magnetic field will be in Z direction.");
  fMagFieldZCmd->SetParameterName("Bz",false,false);
  fMagFieldZCmd->SetDefaultUnit("tesla");
  fMagFieldZCmd->AvailableForStates(G4State_Idle);

  fMagFieldCmd = new G4UIcmdWith3VectorAndUnit("/field/setField",this);
  fMagFieldCmd->SetGuidance("Define magnetic field.");
  fMagFieldCmd->SetParameterName("Bx", "By", "Bz" ,false,false);
  fMagFieldCmd->SetDefaultUnit("tesla");
  fMagFieldCmd->AvailableForStates(G4State_Idle);

  fMinStepCmd = new G4UIcmdWithADoubleAndUnit("/field/setMinStep",this);
  fMinStepCmd->SetGuidance("Define minimal step");
  fMinStepCmd->SetGuidance("Magnetic field will be in Z direction.");
  fMinStepCmd->SetParameterName("minStep",false,false);
  fMinStepCmd->SetDefaultUnit("mm");
  fMinStepCmd->AvailableForStates(G4State_Idle);

  // Commands for integration accuracy
  //  1. Delta One Step =  length of potential error in each integration substep
  //         Recall that there can be up to 300 substeps in a physics step !!
  fDeltaOneStepCmd = new G4UIcmdWithADoubleAndUnit("/field/setDeltaOneStep",this);
  fDeltaOneStepCmd->SetGuidance("Define minimal step");
  fDeltaOneStepCmd->SetGuidance("Magnetic field will be in Z direction.");
  fDeltaOneStepCmd->SetParameterName("minStep",false,false);
  fDeltaOneStepCmd->SetDefaultUnit("mm");
  fDeltaOneStepCmd->AvailableForStates(G4State_Idle);

  // A choice:  Allow the user to reset the Eps Min/Max values to our default
  G4bool omitable= true,   currentAsDefault= false;
  fEpsMinCmd = new G4UIcmdWithADouble("/field/setEpsilonMin",this);
  fEpsMinCmd->SetGuidance(
                "Define minimum value of the relative integration error (EpsilonMin)"
                " - a dimensionless number\n"
                "Limit to ensure that large steps do NOT result in a very low value"
                "(ie high accuracy) that integration needs many steps and CPU cycles.");
  fEpsMinCmd->SetParameterName("minEpsilon",omitable,currentAsDefault);
  fEpsMinCmd->SetDefaultValue(1.0e-4); // A default eps_min
  fEpsMinCmd->AvailableForStates(G4State_Idle);

  fEpsMaxCmd = new G4UIcmdWithADouble("/field/setEpsilonMax",this);
  fEpsMaxCmd->SetGuidance(
                "Define minimum value of the relative integration error (EpsilonMax)"
                " - a dimensionless number\n"
                "Limit to ensure a very small step does NOT result in a large relative"
                " error (ie low accuracy) with unreliable results.");
  fEpsMaxCmd->SetParameterName("maxEpsilon",omitable,currentAsDefault);
  fEpsMinCmd->SetDefaultValue(1.0e-5); // A default eps_max
  fEpsMaxCmd->AvailableForStates(G4State_Idle);

  // HOW to Ensure that its value is  val < G4FieldManager::GetMaxAcceptedEpsilon() ??

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

F01FieldMessenger::~F01FieldMessenger()
{
  delete fStepperCmd;
  delete fMagFieldZCmd;
  delete fMagFieldCmd;
  delete fMinStepCmd;
  delete fDeltaOneStepCmd;
  delete fEpsMinCmd;
  delete fEpsMaxCmd;
  delete fFieldDir;
  delete fUpdateCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void F01FieldMessenger::SetNewValue( G4UIcommand* command, G4String newValue)
{
  if( command == fStepperCmd )
    fEMfieldSetup->SetStepperType(fStepperCmd->GetNewIntValue(newValue));
  if( command == fUpdateCmd )
    fEMfieldSetup->CreateStepperAndChordFinder();
  if( command == fMagFieldZCmd )
    fEMfieldSetup->SetFieldZValue(fMagFieldZCmd->GetNewDoubleValue(newValue));
  if( command == fMagFieldCmd )
    fEMfieldSetup->SetFieldValue(fMagFieldCmd->GetNew3VectorValue(newValue));
  if( command == fMinStepCmd )
    fEMfieldSetup->SetMinStep(fMinStepCmd->GetNewDoubleValue(newValue));
  if( command == fDeltaOneStepCmd )
    fEMfieldSetup->SetDeltaOneStep(fDeltaOneStepCmd->GetNewDoubleValue(newValue));
  if( command == fEpsMinCmd )
    fEMfieldSetup->SetEpsilonMin(fEpsMinCmd->GetNewDoubleValue(newValue));
  if( command == fEpsMaxCmd )
    fEMfieldSetup->SetEpsilonMax(fEpsMaxCmd->GetNewDoubleValue(newValue));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
