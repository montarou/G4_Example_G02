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
// $Id: TiaraFileAcess.cc,v 1.3 2003-06-25 09:13:01 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//

#include "TiaraFileAcess.hh"
#include <fstream>


void checkFileIsReadable(const G4String &fileName,
			 const G4String &caller) {
  std::ifstream file(fileName);
  if (! file) {
    G4Exception("checkFile: couldn't open file: " + fileName + "\n  called from: " + caller);
  }
  return;
}
