// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: test11.hadronic.exerciser.cc,v 1.10 2000-01-22 15:36:11 stesting Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//

#include "globals.hh"
#include "G4UnitsTable.hh"
#include "g4rw/tvordvec.h"

static void OutputCases
(G4int N,  // Number of events per case.
 const G4RWTValOrderedVector <G4String> & particleNameList,
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

	G4cout
	  << "\n#\n# " << particleNameList [iParticle]
	  << " at " << G4BestUnit (energyList [iEnergy], "Energy")
	  << " in " << materialNameList [iMaterial]
	  << "\n#";

	G4cout
	  << "\n/gun/particle " << particleNameList [iParticle]
	  << "\n/gun/energy " <<  G4BestUnit (energyList [iEnergy], "Energy")
	  << "\n/mydet/SelectMaterial " << materialNameList [iMaterial]
 	  << "\n/run/beamOn " << N;

      }
    }
  }
}


int main (int argc, char** argv) {

  G4int N = 1;
  if (argc > 1) {
    if (strcmp (argv[1], "large_N") == 0) {
      N = 20;
    }
  }

  G4UnitDefinition::BuildUnitsTable();

  G4cout <<
    "#"
    "\n# Auto-generated test input file for test11 hadronics."
    "\n#"
    "\n/control/verbose 2"
    "\n# /run/verbose 2"
    "\n/run/particle/setCut 1 m"
    "\n/run/initialize"
    "\n/gun/direction 1 0 0";

  G4RWTValOrderedVector <G4String> particleNameList;
  particleNameList.append ("proton");
  particleNameList.append ("neutron");
  particleNameList.append ("pi+");
  particleNameList.append ("pi-");
  particleNameList.append ("kaon+");
  particleNameList.append ("kaon-");
  particleNameList.append ("kaon0S");
  particleNameList.append ("kaon0L");

  G4RWTValOrderedVector <G4double> energyList;
  energyList.append (10 * GeV);

  G4RWTValOrderedVector <G4String> materialNameList;
  materialNameList.append ("U");
  materialNameList.append ("Pb");
  materialNameList.append ("Al");
  materialNameList.append ("Air");

  OutputCases (N, particleNameList, energyList, materialNameList);

  G4cout << G4endl;
}
