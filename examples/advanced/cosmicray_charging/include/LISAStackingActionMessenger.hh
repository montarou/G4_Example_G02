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
// ********************************************************************
// *                                                                  *
// * cosmicray_charging advanced example for Geant4                   *
// * (adapted simulation of test-mass charging in the LISA mission)   *
// *                                                                  *
// * Henrique Araujo (h.araujo@imperial.ac.uk) & Peter Wass           *
// * Imperial College London                                          *
// *                                                                  *
// ********************************************************************

#ifndef LISAStackingActionMessenger_h
#define LISAStackingActionMessenger_h 1

#include "G4UImessenger.hh"
#include "G4UIcommand.hh"
#include "G4UIcmdWithABool.hh"
#include "globals.hh"

class LISAStackingAction;

class LISAStackingActionMessenger: public G4UImessenger {

  public:
    LISAStackingActionMessenger(LISAStackingAction*);
    ~LISAStackingActionMessenger();

    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    LISAStackingAction* stackingAction;   

    G4UIcmdWithABool* SetPriSurvey;
    G4UIcmdWithABool* SetPartSurvey;

};

#endif
