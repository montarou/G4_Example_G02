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
/// \file hadronic/Hadr01/src/DetectorMessenger.cc
/// \brief Implementation of the DetectorMessenger class
//
// $Id: DetectorMessenger.cc,v 1.7 2007-05-16 11:43:30 vnivanch Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
/////////////////////////////////////////////////////////////////////////
//
// DetectorMessenger
//
// Created: 31.01.03 V.Ivanchenko
//
// Modified:
// 04.06.2006 Adoptation of hadr01 (V.Ivanchenko)
// 16.11.2006 Add beamCmd (V.Ivanchenko)
//
////////////////////////////////////////////////////////////////////////
//

#include "DetectorMessenger.hh"

#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "HistoManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::DetectorMessenger(DetectorConstruction * Det)
:fDetector(Det)
{
  fTestDir = new G4UIdirectory("/testhadr/");
  fTestDir->SetGuidance(" Hadronic Extended Example.");

  fMatCmd = new G4UIcmdWithAString("/testhadr/TargetMat",this);
  fMatCmd->SetGuidance("Select Material for the target");
  fMatCmd->SetParameterName("tMaterial",false);
  fMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fMat1Cmd = new G4UIcmdWithAString("/testhadr/WorldMat",this);
  fMat1Cmd->SetGuidance("Select Material for world");
  fMat1Cmd->SetParameterName("wMaterial",false);
  fMat1Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fRCmd = new G4UIcmdWithADoubleAndUnit("/testhadr/TargetRadius",this);
  fRCmd->SetGuidance("Set radius of the target");
  fRCmd->SetParameterName("radius",false);
  fRCmd->SetUnitCategory("Length");
  fRCmd->SetRange("radius>0");
  fRCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fLCmd = new G4UIcmdWithADoubleAndUnit("/testhadr/TargetLength",this);
  fLCmd->SetGuidance("Set length of the target");
  fLCmd->SetParameterName("length",false);
  fLCmd->SetUnitCategory("Length");
  fLCmd->SetRange("length>0");
  fLCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fBinCmd = new G4UIcmdWithAnInteger("/testhadr/NumberOfBinsE",this);
  fBinCmd->SetGuidance("Set number of bins for Energy");
  fBinCmd->SetParameterName("NEbins",false);
  fBinCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fNOfAbsCmd = new G4UIcmdWithAnInteger("/testhadr/NumberDivZ",this);
  fNOfAbsCmd->SetGuidance("Set number of slices");
  fNOfAbsCmd->SetParameterName("NZ",false);
  fNOfAbsCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fEdepCmd = new G4UIcmdWithADoubleAndUnit("/testhadr/MaxEdep",this);
  fEdepCmd->SetGuidance("Set max energy in histogram");
  fEdepCmd->SetParameterName("edep",false);
  fEdepCmd->SetUnitCategory("Energy");
  fEdepCmd->SetRange("edep>0");
  fEdepCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fUpdateCmd = new G4UIcmdWithoutParameter("/testhadr/Update",this);
  fUpdateCmd->SetGuidance("Update geometry.");
  fUpdateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
  fUpdateCmd->SetGuidance("if you changed geometrical value(s)");
  fUpdateCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fBeamCmd = new G4UIcmdWithABool("/testhadr/DefaultBeamPosition",this);
  fBeamCmd->SetGuidance("show inelastic and elastic cross sections");

  fVerbCmd = new G4UIcmdWithAnInteger("/testhadr/Verbose",this);
  fVerbCmd->SetGuidance("Set verbose for ");
  fVerbCmd->SetParameterName("verb",false);
  fVerbCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::~DetectorMessenger()
{
  delete fMatCmd;
  delete fMat1Cmd;
  delete fRCmd;
  delete fLCmd;
  delete fBinCmd;
  delete fNOfAbsCmd;
  delete fUpdateCmd;
  delete fTestDir;
  delete fBeamCmd;
  delete fVerbCmd;
  delete fEdepCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  HistoManager* h = HistoManager::GetPointer();
  if( command == fMatCmd ) {
   fDetector->SetTargetMaterial(newValue);
  } else if( command == fMat1Cmd ) {
   fDetector->SetWorldMaterial(newValue);
  } else if( command == fRCmd ) {
    fDetector->SetTargetRadius(fRCmd->GetNewDoubleValue(newValue));
  } else if( command == fLCmd ) {
    h->SetTargetLength(fLCmd->GetNewDoubleValue(newValue));
  } else if( command == fNOfAbsCmd ) {
    h->SetNumberOfSlices(fNOfAbsCmd->GetNewIntValue(newValue));
  } else if( command == fBinCmd ) {
    h->SetNumberOfBinsE(fBinCmd->GetNewIntValue(newValue));
  } else if( command == fVerbCmd ) {
    h->SetVerbose(fVerbCmd->GetNewIntValue(newValue));
  } else if (command == fBeamCmd) {
    h->SetDefaultBeamPositionFlag(fBeamCmd->GetNewBoolValue(newValue));
  } else if (command == fEdepCmd) {
    h->SetMaxEnergyDeposit(fEdepCmd->GetNewDoubleValue(newValue));
  } else if( command == fUpdateCmd ) {
    fDetector->UpdateGeometry();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

