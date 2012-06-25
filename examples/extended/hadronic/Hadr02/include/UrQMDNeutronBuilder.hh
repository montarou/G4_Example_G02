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
/// \file hadronic/Hadr02/include/UrQMDNeutronBuilder.hh
/// \brief Definition of the UrQMDNeutronBuilder class
//
// $Id: UrQMDNeutronBuilder.hh,v 1.2 2009-03-31 18:38:33 vnivanch Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
//---------------------------------------------------------------------------
//
// ClassName:   UrQMDNeutronBuilder
//
// Author: 2012 Andrea Dotti
//
// Modified:
//
//----------------------------------------------------------------------------
//
#ifndef UrQMDNeutronBuilder_h
#define UrQMDNeutronBuilder_h 1

#include "globals.hh"

#include "G4HadronElasticProcess.hh"
#include "G4HadronFissionProcess.hh"
#include "G4HadronCaptureProcess.hh"
#include "G4NeutronInelasticProcess.hh"
#include "G4VNeutronBuilder.hh"

#include "G4UrQMD1_3Model.hh"

class UrQMDNeutronBuilder : public G4VNeutronBuilder
{
public: 

  UrQMDNeutronBuilder();
  virtual ~UrQMDNeutronBuilder();

  virtual void Build(G4HadronElasticProcess * aP);
  virtual void Build(G4HadronFissionProcess * aP);
  virtual void Build(G4HadronCaptureProcess * aP);
  virtual void Build(G4NeutronInelasticProcess * aP);
    
  void SetMinEnergy(G4double aM) {fMin = aM;}
  void SetMaxEnergy(G4double aM) {fMax = aM;}

private:
  G4UrQMD1_3Model * fModel;    
  G4double fMin;
  G4double fMax;

};


#endif

