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
// $Id: RemSimROGeometry.hh,v 1.2 2004-02-03 09:16:45 guatelli Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
//    ************************************
//    *                                  *
//    *    RemSimROGeometry.hh   *
//    *                                  *
//    ************************************
//
//The phantom is devided in voxels. the dimension of the voxel is 1mm
//
#ifndef RemSimROGeometry_h
#define RemSimROGeometry_h 

#include "G4VReadOutGeometry.hh"

class RemSimROGeometry : public G4VReadOutGeometry
{
public:
  RemSimROGeometry( G4double phantomDimX,
                    G4double phantomDimY,
		    G4double phantomDimZ,
		    G4int numberOfVoxelsX,
                    G4int numberOfVoxelsY,
		    G4int numberOfVoxelsZ);
  ~RemSimROGeometry();
private:
  G4VPhysicalVolume* Build();

private:
  const G4double astronautDimensionX;
  const G4double astronautDimensionY;
  const G4double astronautDimensionZ;
  const G4int numberOfVoxelsAlongX;
  const G4int numberOfVoxelsAlongY;
  const G4int numberOfVoxelsAlongZ; 
  //G4VPhysicalVolume *ROPhantomYDivisionPhys;
};
#endif
