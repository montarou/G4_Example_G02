#ifndef MLVisManager_h
#define MLVisManager_h 1
////////////////////////////////////////////////////////////////////////////////
//
#ifdef G4VIS_USE

#include "G4VisManager.hh"
////////////////////////////////////////////////////////////////////////////////
//
class MLVisManager: public G4VisManager {

public:

  MLVisManager ();
  ~MLVisManager ();

private:

  void RegisterGraphicsSystems ();

};
#endif
////////////////////////////////////////////////////////////////////////////////
#endif
