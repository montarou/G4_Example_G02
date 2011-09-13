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
// $Id: G4PhotoNuclearProcess.cc,v 1.3 2009-03-31 19:16:38 vnivanch Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//

#include "G4PhotoNuclearProcess.hh"
#include <iostream>


void G4PhotoNuclearProcess::Description() const
{
  char* dirName = getenv("G4PhysListDocDir");
  if (dirName) {
    std::ofstream outFile;
    G4String outFileName = GetProcessName() + ".html";
    G4String pathName = G4String(dirName) + "/" + outFileName;
    outFile.open(pathName);
    outFile << "<html>\n";
    outFile << "<head>\n";

    outFile << "<title>Description of G4PhotoNuclearProcess</title>\n";
    outFile << "</head>\n";
    outFile << "<body>\n";

    outFile << "This process handles inelastic photon scattering from\n" 
            << "nuclei by invoking one or more hadronic models and one\n"
            << "or more hadronic cross sections.\n";

    outFile << "</body>\n";
    outFile << "</html>\n";
    outFile.close();
  }
}
