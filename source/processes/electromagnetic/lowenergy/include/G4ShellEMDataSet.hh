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
// $Id: G4ShellEMDataSet.hh,v 1.2 2001-09-07 18:39:15 vnivanch Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
// Author: Maria Grazia Pia (Maria.Grazia.Pia@cern.ch)
//
// History:
// -----------
// 31 Jul 2001   MGP        Created
//
// -------------------------------------------------------------------

// Class description:
// Low Energy Electromagnetic Physics
// Data set for an electromagnetic physics process
// A strategy pattern is used to encapsulate algorithms for data interpolation
// Further documentation available from http://www.ge.infn.it/geant4/lowE

// -------------------------------------------------------------------

#ifndef G4SHELLEMDATASET_HH
#define G4SHELLEMDATASET_HH 1

#include "globals.hh"
#include "G4DataVector.hh"
#include "G4VEMDataSet.hh"
#include "g4std/vector"

class G4EMDataSet;
class G4VDataSetAlgorithm;

class G4ShellEMDataSet : public G4VEMDataSet 
{ 
public:

  G4ShellEMDataSet(G4int Z, 
		       const G4VDataSetAlgorithm* interpolation,
		       G4double unitE = MeV, G4double unitData = barn);

  G4ShellEMDataSet(G4int Z, 
		       const G4String& dataFile,
		       const G4VDataSetAlgorithm* interpolation,
		       G4double unitE = MeV, G4double unitData = barn);

  ~G4ShellEMDataSet();
 
  G4double FindValue(G4double e) const;

  G4double FindValue(G4double e, G4int id) const;

  const G4VEMDataSet* GetComponent(G4int i) const { return components[i]; }

  void AddComponent(G4VEMDataSet* component);
  
  size_t NumberOfComponents() const { return nComponents; }

  void PrintData() const;

  const G4DataVector& GetEnergies(G4int i) const;
  const G4DataVector& GetData(G4int i) const;

private:

  void LoadData(const G4String& fileName);

  G4int z;

  const G4VDataSetAlgorithm* algorithm; // Not owned pointer 

  // G4std::map<G4int,G4VEMDataSet*,G4std::less<G4int> > componentsMap;
  G4std::vector<G4VEMDataSet*> components;
  size_t nComponents;

  G4double unit1;
  G4double unit2;
};
 
#endif









