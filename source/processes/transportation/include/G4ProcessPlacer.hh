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
// $Id: G4ProcessPlacer.hh,v 1.4 2002-05-24 08:17:19 dressel Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
// ----------------------------------------------------------------------
// Class G4ProcessPlacer
//
// Class description:
//
// Used internally by importance sampling and scoring. 
// See G4VProcessPlacer.hh.

// Author: Michael Dressel (Michael.Dressel@cern.ch)
// ----------------------------------------------------------------------
#ifndef G4ProcessPlacer_hh
#define G4ProcessPlacer_hh G4ProcessPlacer_hh 

#include "globals.hh"
#include "G4VProcessPlacer.hh"

class G4ProcessManager;
class G4ProcessVector;

class G4ProcessPlacer : public G4VProcessPlacer
{

public:  // with description

  G4ProcessPlacer(const G4String &particlename);
    // create a process placer for a particle type

  void AddProcessAsLastDoIt(G4VProcess *process);
    // place a post step do it process such that the 
    // PostStepDoIt function is called last
    // THE ORDER CHANGES BY SUBSEQUENT CALLS     

  void AddProcessAsSecondDoIt(G4VProcess *process);
    // place a post step do it process such that the 
    // PostStepDoIt function is called second
    // THE ORDER CHANGES BY SUBSEQUENT CALLS         

  void RemoveProcess(G4VProcess *process);
    // removes a given process 

private:

  G4ProcessManager &GetProcessManager();

  enum SecondOrLast
  {
    eSecond = 1,            
    eLast = 0
  };

  void AddProcessAs(G4VProcess *process, SecondOrLast);

  void PrintProcVec(G4ProcessVector* processVec);
  void PrintPostStepGPILVec();  
  void PrintPostStepDoItVec();  

private:

  G4String fParticleName;

};

#endif
