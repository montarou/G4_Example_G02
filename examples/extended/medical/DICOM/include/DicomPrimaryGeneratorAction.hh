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
// $Id: DicomPrimaryGeneratorAction.hh,v 1.3 2003-06-04 22:24:07 pia Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
//

#ifndef DicomPrimaryGeneratorAction_h
#define DicomPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

class DicomPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  DicomPrimaryGeneratorAction();
  ~DicomPrimaryGeneratorAction();
  
  void GeneratePrimaries(G4Event*);
  
private:
  G4ParticleGun* particleGun;
};

#endif


