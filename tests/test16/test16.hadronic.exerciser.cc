// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: test16.hadronic.exerciser.cc,v 1.5 1999-12-15 14:54:52 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//

#include "globals.hh"
#include "G4UnitsTable.hh"
#include "g4rw/tvordvec.h"

static void OutputCases
(const G4RWTValOrderedVector <G4String> & particleNameList,
 const G4RWTValOrderedVector <G4double> & energyList,
 const G4RWTValOrderedVector <G4String> & materialNameList) {

  for (int iMaterial = 0;
       iMaterial < materialNameList.entries ();
       iMaterial++) {
    for (int iEnergy = 0;
	 iEnergy < energyList.entries ();
	 iEnergy++) {
      for (int iParticle = 0;
	   iParticle < particleNameList.entries ();
	   iParticle++) {

	cout << "\n#\n# " << particleNameList [iParticle]
	     << " at " << G4BestUnit (energyList [iEnergy], "Energy")
	     << " in " << materialNameList [iMaterial]
	     << "\n#";

	cout
	  << "\n/gun/particle " << particleNameList [iParticle]
	  << "\n/gun/energy " <<  G4BestUnit (energyList [iEnergy], "Energy")
	  << "\n/mydet/SelectMaterial " << materialNameList [iMaterial]
	  << "\n/run/beamOn 10";

      }
    }
  }
}


int main (int argc, char** argv) {

  G4UnitDefinition::BuildUnitsTable();

  cout <<
    "#"
    "\n# Auto-generated test input file for test16 hadronics."
    "\n#"
    "\n/control/verbose 2"
    "\n# /run/verbose 2"
    "\n/run/initialize"
    "\n/gun/direction 1 0 0";

  G4RWTValOrderedVector <G4String> particleNameList;
  particleNameList.append ("proton");
  particleNameList.append ("neutron");

  G4RWTValOrderedVector <G4double> energyList;
  energyList.append (1 * GeV);
  energyList.append (10 * GeV);
  energyList.append (20 * GeV);

  G4RWTValOrderedVector <G4String> materialNameList;
  materialNameList.append ("Pb");
  materialNameList.append ("Al");
  materialNameList.append ("Air");

  OutputCases (particleNameList, energyList, materialNameList);

  cout << G4endl;
}
