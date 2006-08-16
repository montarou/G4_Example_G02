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
// $Id: ExN03TrackingAction.hh,v 1.6 2006-08-16 15:54:30 allison Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
//

#ifndef ExN03TrackingAction_h
#define ExN03TrackingAction_h 1

#include "G4UserTrackingAction.hh"

class G4Track;

///////////////////////////
class ExN03TrackingAction : public G4UserTrackingAction
///////////////////////////
{
   public:
   virtual void PreUserTrackingAction(const G4Track* aTrack);
};

#endif


