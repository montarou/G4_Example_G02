// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4CurveVector.hh,v 1.4 2001-04-20 19:55:24 gcosmo Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
// ----------------------------------------------------------------------
// Class G4CurveVector
//
// Class Description:
//
// Simple array of pointers to G4Curves.

// Author: J.Sulkimo, P.Urban.
// Revisions by: L.Broglia, G.Cosmo.
// ----------------------------------------------------------------------
#ifndef included_G4CurveVector
#define included_G4CurveVector

#include "g4std/vector"
#include "G4Curve.hh"

typedef G4std::vector<G4Curve*> G4CurveVector;

#endif
