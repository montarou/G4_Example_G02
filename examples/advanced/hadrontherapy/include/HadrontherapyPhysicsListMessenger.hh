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
// $Id: HadrontherapyPhysicsListMessenger.hh,v 1.3 2005-05-18 07:53:27 guatelli Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
//
//
// -------------------------------------------------------------------

// Class description:
// System test for e/gamma, UI for PhysicsList
// Further documentation available from http://www.ge.infn.it/geant4/lowE

// -------------------------------------------------------------------

#ifndef HADRONTHERAPYPHYSICSLISTMESSENGER_HH
#define HADRONTHERAPYPHYSICSLISTMESSENGER_HH 1

#include "globals.hh"
#include "G4UImessenger.hh"

class HadrontherapyPhysicsList;
class G4UIdirectory;
class G4UIcmdWithoutParameter;
class G4UIcmdWithADouble;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithABool;
class G4UIcmdWithAString;

class HadrontherapyPhysicsListMessenger: public G4UImessenger {

public:
  
  HadrontherapyPhysicsListMessenger(HadrontherapyPhysicsList* physList);
  
  ~HadrontherapyPhysicsListMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  
private:
  
  HadrontherapyPhysicsList* physicsList;   
  G4UIdirectory* listDir;
  G4UIcmdWithAString* physicsListCmd;
};

#endif








