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
//
// $Id: G4AntiSigmaMinus.cc,v 1.16 2010-10-01 02:41:43 kurasige Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
// 
// ----------------------------------------------------------------------
//      GEANT 4 class implementation file
//
//      History: first implementation, based on object model of
//      4th April 1996, G.Cosmo
// **********************************************************************
//  New impelemenataion as an utility class  M.Asai, 26 July 2004
// ----------------------------------------------------------------------

#include "G4AntiSigmaMinus.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"

#include "G4PhaseSpaceDecayChannel.hh"
#include "G4DecayTable.hh"

// ######################################################################
// ###                           AntiSigmaMinus                       ###
// ######################################################################

G4AntiSigmaMinus* G4AntiSigmaMinus::theInstance = 0;

G4AntiSigmaMinus* G4AntiSigmaMinus::Definition()
{
  if (theInstance !=0) return theInstance;
  const G4String name = "anti_sigma-";
  // search in particle table]
  G4ParticleTable* pTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* anInstance = pTable->FindParticle(name);
  if (anInstance ==0) 
  {
  // create particle
  //
  //    Arguments for constructor are as follows
  //               name             mass          width         charge
  //             2*spin           parity  C-conjugation
  //          2*Isospin       2*Isospin3       G-parity
  //               type    lepton number  baryon number   PDG encoding
  //             stable         lifetime    decay table
  //             shortlived      subType    anti_encoding

    anInstance = new G4ParticleDefinition(
                 name,    1.197449*GeV,  4.45e-12*MeV,       eplus,
                    1,              +1,             0,
                    2,              +2,             0,
             "baryon",               0,            -1,       -3112,
                false,       0.1479*ns,          NULL,
                false,       "sigma");

    // Magnetic Moment
    G4double mN = eplus*hbar_Planck/2./(proton_mass_c2 /c_squared);
    anInstance->SetPDGMagneticMoment( 1.160 * mN);
 
    //create Decay Table
    G4DecayTable* table = new G4DecayTable();
    
    // create decay channels
    G4VDecayChannel** mode = new G4VDecayChannel*[1];
  // anti_sigma- -> anti_neutron + pi+
    mode[0] = new G4PhaseSpaceDecayChannel("anti_sigma-",1.00,2,"anti_neutron","pi+");
    
    for (G4int index=0; index <1; index++ ) table->Insert(mode[index]);
    delete [] mode;
    
    anInstance->SetDecayTable(table);
  }
  theInstance = reinterpret_cast<G4AntiSigmaMinus*>(anInstance);
  return theInstance;
}

G4AntiSigmaMinus*  G4AntiSigmaMinus::AntiSigmaMinusDefinition()
{
  return Definition();
}

G4AntiSigmaMinus*  G4AntiSigmaMinus::AntiSigmaMinus()
{
  return Definition();
}

