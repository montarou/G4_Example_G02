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
// $Id: G4Plane3D.hh,v 1.4 2005-11-04 08:18:51 gcosmo Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
#ifndef G4PLANE3D_HH
#define G4PLANE3D_HH

#include "globals.hh"
#include "G4Point3D.hh"
#include "G4Normal3D.hh"
#include <CLHEP/Geometry/Plane3D.h>

typedef HepGeom::Plane3D<G4double> G4Plane3D;

#endif /* G4PLANE3D_HH */
