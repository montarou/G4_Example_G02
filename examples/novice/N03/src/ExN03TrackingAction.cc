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
// $Id: ExN03TrackingAction.cc,v 1.2 2002-11-20 18:46:24 japost Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
//
//

///////////////////////
// ExN03TrackingAction.cc
///////////////////////


#include "ExN03TrackingAction.hh"
#include "G4SmoothTrajectory.hh"
#include "G4TrackingManager.hh"
//#include "G4ios.hh"


void ExN03TrackingAction :: PreUserTrackingAction(const G4Track* aTrack)
{
  fpTrackingManager->SetTrajectory( new G4SmoothTrajectory( aTrack) );
  // cout << "spong ExN03TrackingAction :: PreUserTrackingAction" << endl;
}
