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
// $Id: G4TestSetup.hh,v 1.2 2001-10-15 15:27:17 pia Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
// Author: Maria Grazia Pia (Maria.Grazia.Pia@cern.ch)
//
// History:
// -----------
// 07 Oct 2001   MGP        Created
//
// -------------------------------------------------------------------
// Class description:
// Test DoIt method of physics processes
// Further documentation available from http://www.ge.infn.it/geant4/lowE/index.html

// -------------------------------------------------------------------

#ifndef G4TESTSETUP_HH
#define G4TESTSETUP_HH 1

#include "globals.hh"

class G4VProcess;
class G4ParticleDefinition;
class G4ProcessManager;
class G4VContinuousDiscreteProcess;
class G4Material;
class G4PVPlacement;
class G4Track;
class G4Step;

class G4TestSetup {
 
public:

  G4TestSetup();

  virtual ~G4TestSetup();
 
  void init();

  const G4Track* makeTrack();

  const G4Step* makeStep();

  G4VProcess* createTestProcess();

  G4String setupName();

private:
  
  // Hide copy constructor and assignment operator
  G4TestSetup(const G4TestSetup&);
  G4TestSetup& operator=(const G4TestSetup& right);

  void makeElectronProcesses();
  void makeGeometry();
  void makeMaterials();

  G4int selection;
  G4int processType;
  G4String selName;
  G4String pName;

  G4ParticleDefinition* part;
  G4Material* material;
  G4Track* track;
  G4Step* step;
  G4PVPlacement* physicalFrame;

  G4VContinuousDiscreteProcess* ioniProcess;
  G4VContinuousDiscreteProcess* bremProcess;
  G4ProcessManager* eProcessManager;
  G4ProcessManager* positronProcessManager;
  G4ProcessManager* processManager;

  G4bool ioniSel;
  G4bool bremSel;

  G4double eMin;
  G4double eMax;
};
 
#endif
