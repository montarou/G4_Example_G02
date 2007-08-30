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
// $Id: G4GPRNode.hh,v 1.1 2007-08-30 19:37:45 tinslay Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
// 
// J. Tinslay, August 2007. 
//
#ifndef G4GPRNODE_HH
#define G4GPRNODE_HH

#include "G4GPRObserverCollectionT.hh"

class G4GPRNode {

public:

  G4GPRNode(const G4String& id = "", G4bool initialState=true)
    :fId(id)
    ,fState(initialState) {}

  void FlipState() 
  {
    G4cout<<"jane node flipstate "<<fId<<" "<<!fState<<G4endl;
    fState = !fState;
    fObserverCollection(this);
  }

  G4bool GetState() {return fState;}
  const G4String& GetName() {return fId;}

  template <typename Pointer, typename PointerToMfn>
  void AddObserver(Pointer* pointer, PointerToMfn mfn) 
  {
    fObserverCollection.RegisterObserver("tmp", pointer, mfn);
  }

private:
  G4String fId;
  G4bool fState;
  
  G4GPRObserverCollectionT<G4GPRTypeList_1(G4GPRNode*), G4String> fObserverCollection;
};

#endif
