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
/// \file parallel/MPI/mpi_interface/src/G4VMPIseedGenerator.cc
/// \brief Implementation of the G4VMPIseedGenerator class
//
// $Id: G4VMPIseedGenerator.cc,v 1.1 2007-11-16 14:05:41 kmura Exp $
// $Name: not supported by cvs2svn $
// ====================================================================
//   G4VMPIseedGenerator.cc
//
//                                         2007 Q
// ====================================================================
#include "G4VMPIseedGenerator.hh"

// ====================================================================
//
// class description
//
// ====================================================================

//////////////////////////////////////////
G4VMPIseedGenerator::G4VMPIseedGenerator()
  : masterSeed(123456789)
//////////////////////////////////////////
{
}


///////////////////////////////////////////
G4VMPIseedGenerator::~G4VMPIseedGenerator()
///////////////////////////////////////////
{
}


/////////////////////////////////////////////////////
void G4VMPIseedGenerator::SetMasterSeed(G4long aseed)
/////////////////////////////////////////////////////
{
  masterSeed= aseed;
  GenerateSeeds();
}

