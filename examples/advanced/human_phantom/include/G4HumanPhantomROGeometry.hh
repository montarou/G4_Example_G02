//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: G4HumanPhantomROGeometry.hh,v 1.1 2006-09-26 17:29:00 guatelli Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
//    ************************************
//    *                                  *
//    *    G4HumanPhantomROGeometry.hh   *
//    *                                  *
//    ************************************
//
// The phantom is devided in voxels. 
// The energy deposit is integrated over the voxels
//

#ifndef G4HumanPhantomROGeometry_h
#define G4HumanPhantomROGeometry_h 

#include "G4VReadOutGeometry.hh"

class G4HumanPhantomROGeometry : public G4VReadOutGeometry
{
public:
  G4HumanPhantomROGeometry(G4String aString);
  ~G4HumanPhantomROGeometry();

private:
  G4VPhysicalVolume* Build();

private:
  G4VPhysicalVolume* ROvoxel_phys;
};
#endif
