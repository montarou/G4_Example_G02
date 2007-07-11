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
// $Id: G4ScoringManager.hh,v 1.2 2007-07-11 07:00:52 asaim Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//

#ifndef G4ScoringManager_h
#define G4ScoringManager_h 1

#include "globals.hh"
#include "G4ScoringWorld.hh"
#include <vector>
class G4ScoringMessenger;

// class description:
//
//  This is a singleton class which manages the interactive scoring.
// The user cannot access to the constructor. The pointer of the
// only existing object can be got via G4ScoringManager::GetScoringManager()
// static method. The first invokation of this static method makes
// the singleton object.
//

typedef std::vector<G4ScoringWorld*> WorldVec;
typedef std::vector<G4ScoringWorld*>::iterator WorldVecItr;

class G4ScoringManager 
{
  public: // with description
      static G4ScoringManager* GetScoringManager();
      // Returns the pointer to the singleton object.
  public:
      static G4ScoringManager* GetScoringManagerIfExist();

  protected:
      G4ScoringManager();

  public:
      ~G4ScoringManager();

  public:
      void List() const;

  private: 
      static G4ScoringManager * fSManager;
      G4int verboseLevel;
      G4ScoringMessenger* fMessenger;

      WorldVec fWorldVec;

  public:
      inline void SetVerboseLevel(G4int vl) 
      { verboseLevel = vl; }
      inline G4int GetVerboseLevel() const
      { return verboseLevel; }
      inline size_t GetNumberOfWorlds() const
      { return fWorldVec.size(); }
      inline G4ScoringWorld* GetWorld(G4int i) const
      { return fWorldVec[i]; }
      inline G4String GetWorldName(G4int i) const
      { return fWorldVec[i]->GetWorldName(); }
};




#endif

