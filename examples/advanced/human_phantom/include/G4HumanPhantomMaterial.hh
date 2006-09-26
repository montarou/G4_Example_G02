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
// $Id: G4HumanPhantomMaterial.hh,v 1.1 2006-09-26 17:29:00 guatelli Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
//    **********************************
//    *                                *
//    *      G4HumanPhantomMaterial.hh          *
//    *                                *
//    **********************************
//
//Code developed by: Susanna Guatelli
//
// This class manages the elements and materials
//
#ifndef G4HumanPhantomMaterial_H
#define G4HumanPhantomMaterial_H 1

#include "globals.hh"
class G4Material;

class G4HumanPhantomMaterial
{ 
public:
  G4HumanPhantomMaterial();
  ~ G4HumanPhantomMaterial();

public:
  void  DefineMaterials();
  G4Material* GetMaterial(G4String); //returns the material

private:
  // G4Material* matW; 
  //G4Material* matplexiglass;
  //G4Material* matPb;
  //G4Material* matir192;
  //G4Material* Titanium;
  // G4Material* matAir;
  G4Material* matH2O;
  G4Material* soft;
  G4Material* skeleton;
  G4Material* lung;
  G4Material* adipose;
  G4Material* glandular; 
  G4Material* adipose_glandular;
  //G4Material*Vacuum; 
 
  //G4Material* muscle;
};
#endif
