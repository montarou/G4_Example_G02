// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: MyTrackerHitsCollection.cc,v 1.2 1999-12-15 14:54:35 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//

#include "MyTrackerHitsCollection.hh"

MyTrackerHitsCollection::MyTrackerHitsCollection()
{}

MyTrackerHitsCollection::MyTrackerHitsCollection
                          (G4String dName,G4String aName)
:G4VHitsCollection(dName,aName)
{}

MyTrackerHitsCollection::~MyTrackerHitsCollection()
{}

void MyTrackerHitsCollection::DrawAllHits()
{
  G4int n_hit = theCollection.entries();
  for(G4int i=0;i<n_hit;i++)
  { theCollection[i].Draw(); }
}

void MyTrackerHitsCollection::PrintAllHits()
{
  G4int n_hit = theCollection.entries();
  for(G4int i=0;i<n_hit;i++)
  { theCollection[i].Print(); }
}



