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
// $Id: HadrontherapyEventAction.cc,v 3.0, September 2004;
// -----------------------------------------------------------
//                 GEANT 4 - Hadrontherapy example
// -----------------------------------------------------------
// Code developed by:
//
// G.A.P. Cirrone, F. Di Rosa, G. Russo
// Laboratori Nazionali del Sud - INFN, Catania, Italy
//
// ----------------------------------------------------------


#ifndef HadrontherapyEventAction_h
#define HadrontherapyEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class HadrontherapyEventAction : public G4UserEventAction
{
public:
  HadrontherapyEventAction(G4double *, G4int, G4int, G4int);
  ~HadrontherapyEventAction();

public:
  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);
  
  
private:
  
  G4String drawFlag; //Visualisation flag
  G4int m_HitsCollectionID;
  G4double *matrix;
  G4int numberX;
  G4int numberY;
  G4int numberZ;
};

#endif



