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
// $Id: G4Fragment.hh,v 1.7 2010-05-03 16:50:53 vnivanch Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
//---------------------------------------------------------------------
//
// Geant4 header G4Fragment
//
// by V. Lara (May 1998)
//
// Modifications:
// 03.05.2010 V.Ivanchenko General cleanup of inline functions: objects 
//            are accessed by reference; remove double return 
//            tolerance of excitation energy at modent it is computed;
//            safe computation of excitation for exotic fragments

#ifndef G4Fragment_h
#define G4Fragment_h 1

#include "G4ios.hh"
#include <iomanip>
#include <vector>

#include "globals.hh"
#include "G4LorentzVector.hh"
//#include "G4ParticleMomentum.hh"
#include "G4ThreeVector.hh"
#include "G4NucleiProperties.hh"
//#include "G4ParticleTable.hh"
//#include "G4IonTable.hh"
#include "Randomize.hh"
#include "G4Proton.hh"
#include "G4Neutron.hh"
#include "G4HadronicException.hh"
#include "G4HadTmpUtil.hh"


class G4ParticleDefinition;

class G4Fragment;     // Forward deckaration
typedef std::vector<G4Fragment*> G4FragmentVector;

class G4Fragment 
{
public:

  // ============= CONSTRUCTORS ==================

  // Default constructor - obsolete
  G4Fragment();

  // Destructor
  ~G4Fragment();

  // Copy constructor
  G4Fragment(const G4Fragment &right);

  // A,Z and 4-momentum - main constructor for fragment
  G4Fragment(const G4int A, const G4int Z, const G4LorentzVector& aMomentum);

  // 4-momentum and pointer to G4particleDefinition (for gammas)
  G4Fragment(const G4LorentzVector& aMomentum, G4ParticleDefinition * aParticleDefinition);

  // ============= OPERATORS ==================
    
  const G4Fragment & operator=(const G4Fragment &right);
  G4bool operator==(const G4Fragment &right) const;
  G4bool operator!=(const G4Fragment &right) const;

  friend std::ostream& operator<<(std::ostream&, const G4Fragment*);
  friend std::ostream& operator<<(std::ostream&, const G4Fragment&);

  // ============= METHODS ==================

  inline G4double GetA() const;
  inline void SetA(const G4double value);
  
  inline G4double GetZ() const;
  inline void SetZ(const G4double value);

  inline G4int GetA_asInt() const;
  inline void SetA_asInt(const G4int value);
  
  inline G4int GetZ_asInt() const;
  inline void SetZ_asInt(const G4int value);
  
  inline G4double GetExcitationEnergy() const;
  void SetExcitationEnergy(const G4double value);
  
  inline const G4LorentzVector& GetMomentum() const;
  inline void SetMomentum(const G4LorentzVector& value);
  
  inline const G4ThreeVector& GetAngularMomentum() const;
  inline void SetAngularMomentum(const G4ThreeVector& value);
  
  inline G4int GetNumberOfExcitons() const;
  //  void SetNumberOfExcitons(const G4int value);
  
  inline G4int GetNumberOfHoles() const;
  inline void SetNumberOfHoles(const G4int value);
  
  inline G4int GetNumberOfCharged() const;
  void SetNumberOfCharged(const G4int value);

  inline G4int GetNumberOfParticles() const;
  inline void SetNumberOfParticles(const G4int value);

  inline G4ParticleDefinition * GetParticleDefinition() const;
  inline void SetParticleDefinition(G4ParticleDefinition * aParticleDefinition);

  inline G4double GetCreationTime() const;
  inline void SetCreationTime(const G4double time);

  // Some utility methods
  inline G4double GetGroundStateMass() const;
  // Some utility methods
  inline G4double ComputeGroundStateMass(const G4int Z, const G4int A) const;
  
  inline G4double GetBindingEnergy() const;

#ifdef PRECOMPOUND_TEST 
  G4String GetCreatorModel() const;
  void SetCreatorModel(const G4String & aModel); 
#endif

private:

  inline void CalculateExcitationEnergy();

  G4ThreeVector IsotropicRandom3Vector(const G4double Magnitude = 1.0) const;
  
  // ============= DATA MEMBERS ==================

  G4int theA;
  
  G4int theZ;
  
  G4double theExcitationEnergy;

  G4LorentzVector theMomentum;
  
  G4ThreeVector theAngularMomentum;
  
  G4int numberOfParticles;
  
  G4int numberOfHoles;
  
  G4int numberOfCharged;

  // Gamma evaporation requeriments

  G4ParticleDefinition * theParticleDefinition;
  
  G4double theCreationTime;

#ifdef PRECOMPOUND_TEST 
  G4String theCreatorModel;
#endif 
};

// Class G4Fragment 

inline G4double G4Fragment::GetA() const
{
  return G4double(theA);
}

inline void G4Fragment::SetA(const G4double value)
{
  theA = G4lrint(value);
}

inline G4double G4Fragment::GetZ()  const
{
  return G4double(theZ);
}

inline void G4Fragment::SetZ(const G4double value)
{
  theZ = G4lrint(value);
}

inline G4int G4Fragment::GetA_asInt() const
{
  return theA;
}

inline void G4Fragment::SetA_asInt(const G4int value)
{
  theA = value;
}

inline G4int G4Fragment::GetZ_asInt()  const
{
  return theZ;
}

inline void G4Fragment::SetZ_asInt(const G4int value)
{
  theZ = value;
}

inline G4double G4Fragment::GetExcitationEnergy()  const
{
  // temporary fix for what seems to be
  // a problem with rounding errors for on-shell lorentz-vectors in CLHEP.
  // HPW Apr 1999 @@@@@@@ 
  
  //VI  if(std::abs(theExcitationEnergy)<10*eV) return 0; 
  return theExcitationEnergy;
}

inline const G4LorentzVector& G4Fragment::GetMomentum()  const
{
  return theMomentum;
}

inline const G4ThreeVector& G4Fragment::GetAngularMomentum()  const
{
  return theAngularMomentum;
}

inline void G4Fragment::SetAngularMomentum(const G4ThreeVector& value)
{
  theAngularMomentum = value;
}

inline G4int G4Fragment::GetNumberOfExcitons()  const
{
  return numberOfParticles + numberOfHoles;
}

inline void G4Fragment::SetNumberOfParticles(const G4int value)
{
  numberOfParticles = value;
}

inline G4int G4Fragment::GetNumberOfHoles()  const
{
  return numberOfHoles;
}

inline void G4Fragment::SetNumberOfHoles(const G4int value)
{
  numberOfHoles = value;
}

inline G4int G4Fragment::GetNumberOfCharged()  const
{
  return numberOfCharged;
}

inline void G4Fragment::SetNumberOfCharged(const G4int value)
{
  if (value <= numberOfParticles) { numberOfCharged = value; }
  else 
  {
    G4String text = "G4Fragment::SetNumberOfCharged: Number of charged particles can't be greater than number of particles";
    throw G4HadronicException(__FILE__, __LINE__, text);
  }
}

inline G4int G4Fragment::GetNumberOfParticles()  const
{
  return numberOfParticles;
}

inline G4ParticleDefinition * G4Fragment::GetParticleDefinition(void) const
{
  return theParticleDefinition;
}

inline void G4Fragment::SetParticleDefinition(G4ParticleDefinition * aParticleDefinition)
{
  theParticleDefinition = aParticleDefinition;
}

inline G4double G4Fragment::GetCreationTime() const 
{
  return theCreationTime;
}

inline void G4Fragment::SetCreationTime(const G4double time)
{
  theCreationTime = time;
}

inline G4double G4Fragment::GetGroundStateMass() const
{
  return G4NucleiProperties::GetNuclearMass(theA, theZ); 
  //	if (theA == 0) return 0.0; // photon
  //	else return G4ParticleTable::GetParticleTable()->
  //		    GetIonTable()->GetIonMass(G4lrint(theZ),G4lrint(theA));
}

inline G4double 
G4Fragment::ComputeGroundStateMass(const G4int Z, const G4int A) const
{
  return G4NucleiProperties::GetNuclearMass(A, Z); 
}

inline void G4Fragment::CalculateExcitationEnergy()
{
  theExcitationEnergy = theMomentum.mag() - 
    G4NucleiProperties::GetNuclearMass(theA, theZ);
  if(theExcitationEnergy < 0.0) { theExcitationEnergy = 0.0; }
}
	
inline G4double G4Fragment::GetBindingEnergy() const
{
  return (theA-theZ)*CLHEP::neutron_mass_c2 + theZ*CLHEP::proton_mass_c2 
    - G4NucleiProperties::GetNuclearMass(theA, theZ);
}

inline void G4Fragment::SetMomentum(const G4LorentzVector& value)
{
  theMomentum = value;
  CalculateExcitationEnergy();
}

#endif


