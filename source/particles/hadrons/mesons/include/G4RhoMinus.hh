// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4RhoMinus.hh,v 1.3 1999-12-15 14:51:04 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
// 
// ------------------------------------------------------------
//      GEANT 4 class header file
//
//      For information related to this code contact:
//      CERN, CN Division, ASD group
//      History: first implementation,  Hisaya Kurashige, 8 June 1998
// **********************************************************************
//  Change both methods to get the pointer into non-inlined H.Kurashige 4 Aug. 1998
// ------------------------------------------------------------

// Each class inheriting from G4VMeson
// corresponds to a particle type; one and only one
// instance for each class is guaranteed.

#ifndef G4RhoMinus_h
#define G4RhoMinus_h 1

#include "globals.hh"
#include "G4ios.hh"
#include "G4VMeson.hh"

// ######################################################################
// ###                         RhoMinus                                ###
// ######################################################################

class G4RhoMinus : public G4VMeson
{
 private:
   static G4RhoMinus theRhoMinus;
   static G4double  theRhoMinusLengthCut;
   static G4double* theRhoMinusKineticEnergyCuts;

 private: // constructors are hide as private  
   G4RhoMinus(
       const G4String&     aName,        G4double            mass,
       G4double            width,        G4double            charge,   
       G4int               iSpin,        G4int               iParity,    
       G4int               iConjugation, G4int               iIsospin,   
       G4int               iIsospin3,    G4int               gParity,
       const G4String&     pType,        G4int               lepton,      
       G4int               baryon,       G4int               encoding,
       G4bool              stable,       G4double            lifetime,
       G4DecayTable        *decaytable
   );

 public:
   virtual ~G4RhoMinus(){}

   static G4RhoMinus*      RhoMinusDefinition();
   static G4RhoMinus*      RhoMinus();
   static G4double GetCuts() {return theRhoMinusLengthCut;}   
   static G4double* GetCutsInEnergy() {return theRhoMinusKineticEnergyCuts;};

   virtual void        SetCuts(G4double aCut);
};

inline void G4RhoMinus::SetCuts(G4double aCut)
{
  G4ParticleWithCuts::SetCuts(aCut);
  theRhoMinusLengthCut = theCutInMaxInteractionLength;  
  theRhoMinusKineticEnergyCuts = theKineticEnergyCuts;
}


#endif





