// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//

#ifndef ExN06PhysicsList_h
#define ExN06PhysicsList_h 1

#include "globals.hh"
#include "G4VUserPhysicsList.hh"

class ExN06PhysicsList : public G4VUserPhysicsList
{
  public:
    ExN06PhysicsList();
    virtual ~ExN06PhysicsList();

  protected:
    // Construct particles and processes
    virtual void ConstructParticle();
    virtual void ConstructProcess();

    //
    virtual void SetCuts();

  protected:
    // these methods Construct particles
    virtual void ConstructBosons();
    virtual void ConstructLeptons();
    virtual void ConstructMesons();
    virtual void ConstructBaryons();

  protected:
  // these methods Construct physics processes and register them
  virtual void ConstructGeneral();
  virtual void ConstructEM();
  virtual void ConstructOp();

};

#endif /* ExN06PhysicsList_h */

