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
/// \file runAndEvent/RE02/include/RE02PrimaryGeneratorAction.hh
/// \brief Definition of the RE02PrimaryGeneratorAction class
//
//
// $Id: RE02PrimaryGeneratorAction.hh,v 1.3 2006-11-18 01:37:23 asaim Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
 
#ifndef RE02PrimaryGeneratorAction_h
#define RE02PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class RE02DetectorConstruction;
class G4ParticleGun;
class G4Event;

//
class RE02PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    RE02PrimaryGeneratorAction();    
   ~RE02PrimaryGeneratorAction();

  public:
    void GeneratePrimaries(G4Event*);

  private:
    G4double fsigmaPosition; // Initial beam spot size in x-y plane.
    G4ParticleGun* particleGun;
};

//

#endif


