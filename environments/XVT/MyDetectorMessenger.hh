// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: MyDetectorMessenger.hh,v 1.2 1999-12-15 14:48:45 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//

#ifndef MyDetectorMessenger_h
#define MyDetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

#include "G4ios.hh"
#include "g4std/strstream"

class G4UIcommand;
class MyDetectorConstruction;

class MyDetectorMessenger: public G4UImessenger
{
  public:
    MyDetectorMessenger(MyDetectorConstruction * myDC);
    void SetNewValue(G4UIcommand * command,G4String newValues);
  private:
    MyDetectorConstruction * myDetector;
};

#endif

