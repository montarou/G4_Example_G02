// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4NURBShexahedron.hh,v 1.5 1999-12-15 14:50:32 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
// Hexa hedron builder prototype
// OC 17 9 96

// Class Description:
// Hexa hedron builder prototype for NURBS.
// See documentation in graphics_reps/doc for details.
// Class Description - End:


#include "G4NURBS.hh"

#include "G4ThreeVector.hh"


#ifndef __C_G4NURBShexahedron__

#define __C_G4NURBShexahedron__ 1 

class	G4NURBShexahedron : public G4NURBS
	{
	
	// imagine the hexahedron is just a box, then
	// the eight corners must be given in the following order :
	//  DX  DY -DZ
	// -DX  DY -DZ
	// -DX -DY -DZ
	//  DX -DY -DZ
	//  DX  DY  DZ 
	// -DX  DY  DZ
	// -DX -DY  DZ
	//  DX -DY  DZ
 	// (ie, with Oz pointing to you, Ox on the right, Oy on the top:
	//  from the rear, from the upper right corner to the lower one
	// in anticlockwise sens, then the same for front side)

	public:
	  G4NURBShexahedron(const G4ThreeVector Corners [8]);
	  virtual G4Visible&  operator = (const G4Visible& right);
	  virtual G4VVisPrim& operator = (const G4VVisPrim& right);
	  const char*	Whoami() const;
	};

#endif
// end of __C_G4NURBShexahedron__




