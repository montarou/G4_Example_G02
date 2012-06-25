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
/// \file geometry/olap/include/RandomDetector.hh
/// \brief Definition of the RandomDetector class
//
//
// $Id: RandomDetector.hh,v 1.2 2006-06-29 17:22:44 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
// 
// --------------------------------------------------------------
// RandomDetector
//
// Author: Martin Liendl - Martin.Liendl@cern.ch
//
// --------------------------------------------------------------
//
#ifndef RandomDetector_h
#define RandomDetector_h

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

class RandomDetector : public G4VUserDetectorConstruction
{
public:
  RandomDetector(G4double prop);
  //RandomDetector(G4int level, G4int perLevel, G4double);
  ~RandomDetector();
  
  G4VPhysicalVolume * Construct();

private:   
  G4int levels_, perLevel_;
  G4double overlapProp_; // propability of overlap
  G4double worldDim_;
};

#endif	
