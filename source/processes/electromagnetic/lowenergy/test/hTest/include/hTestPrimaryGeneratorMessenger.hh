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
#ifndef hTestPrimaryGeneratorMessenger_h
#define hTestPrimaryGeneratorMessenger_h 1

//---------------------------------------------------------------------------
//
// ClassName:   hTestPrimaryGeneratorAction
//  
// Description: Definition of physics list parameters via UI interface
//
// Author:      V.Ivanchenko 26/09/00
//
//----------------------------------------------------------------------------
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithAString.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class hTestPrimaryGeneratorAction;

class hTestPrimaryGeneratorMessenger: public G4UImessenger
{
  public:
  
    hTestPrimaryGeneratorMessenger(hTestPrimaryGeneratorAction* gen);
   ~hTestPrimaryGeneratorMessenger();
    
    void SetNewValue(G4UIcommand* command, G4String newValue);

  private:
  
    hTestPrimaryGeneratorAction*  theGen;

    G4UIcmdWithADoubleAndUnit* beamXCmd;
    G4UIcmdWithADoubleAndUnit* beamYCmd;
    G4UIcmdWithADoubleAndUnit* beamZCmd;
    G4UIcmdWithADoubleAndUnit* beamECmd;
    G4UIcmdWithADoubleAndUnit* sigmaXCmd;
    G4UIcmdWithADoubleAndUnit* sigmaYCmd;
    G4UIcmdWithADoubleAndUnit* sigmaZCmd;
    G4UIcmdWithADoubleAndUnit* sigmaECmd;
    G4UIcmdWithADoubleAndUnit* maxThetaCmd;
    G4UIcmdWithAString* partCmd;

};

#endif

