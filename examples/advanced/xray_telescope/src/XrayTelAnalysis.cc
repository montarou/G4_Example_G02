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
// $Id: XrayTelAnalysis.cc,v 1.3 2001-12-10 16:53:46 pfeiffer Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
// Author:  A. Pfeiffer (Andreas.Pfeiffer@cern.ch) 
//         (copied from his UserAnalyser class)
//
// History:
// -----------
//  7 Nov 2001   MGP        Implementation
//
// -------------------------------------------------------------------

#include "XrayTelAnalysis.hh"
#include "globals.hh"
#include "G4Track.hh"
#include "G4SteppingManager.hh"
#include "G4ThreeVector.hh"

XrayTelAnalysis* XrayTelAnalysis::instance = 0;

XrayTelAnalysis::XrayTelAnalysis()
{
  histoManager = createIHistoManager();
  ntFactory = Lizard::createNTupleFactory();
  vectorFactory = createIVectorFactory();
  plotter = createIPlotter();
}

XrayTelAnalysis::~XrayTelAnalysis()
{ 
  delete ntFactory;
  ntFactory = 0;

  delete histoManager;
  histoManager = 0;

  delete vectorFactory;
  vectorFactory = 0;

  delete plotter;
  plotter = 0;
}

XrayTelAnalysis* XrayTelAnalysis::getInstance()
{
  if (instance == 0) instance = new XrayTelAnalysis;
  return instance;
}


void XrayTelAnalysis::book()
{
  histoManager->selectStore("XrayTel.his");

  // Book histograms
  histoManager->create1D("1","Energy, all", 20,0.,10.);
  histoManager->create2D("2","y-z, all", 100,-500.,500.,100,-500.,500.);
  histoManager->create1D("3","Energy, entering detector", 10,0.,1.);
  histoManager->create2D("4","y-z, entering detector", 200,-50.,50.,200,-50.,50.);

  // Divide the plot into 4 zones to show the 4 histograms during execution
  plotter->zone(2,2,0,0);

  // Book ntuples
  ntuple = ntFactory->createC("XrayTel.his::1");
  
  //  Add and bind the attributes to the ntuple
  if ( !( ntuple->addAndBind( "energy", eKin) &&
  	  ntuple->addAndBind( "y"     , y   ) &&
  	  ntuple->addAndBind( "z"     , z   ) &&
  	  ntuple->addAndBind( "dirx"  , dirX) &&
  	  ntuple->addAndBind( "diry"  , dirY) &&
  	  ntuple->addAndBind( "dirz"  , dirZ) ) )    
    {
      delete ntuple;
      G4Exception(" XrayTelAnalysis::book - Could not addAndBind ntuple");
    }  
}

void XrayTelAnalysis::finish()
{
  // Store histograms

  // Because of a Lizard feature, ntuples must be deleted at this stage, 
  // not in the destructor (otherwise the ntuples are not stored)

  histoManager->store("1");
  histoManager->store("3");
  histoManager->store("2");
  histoManager->store("4");

  delete ntuple;
  ntuple = 0;
  G4cout << "Deleted ntuple" << G4endl;
}

void XrayTelAnalysis::analyseStepping(const G4Track& track, G4bool entering)
{
  eKin = track.GetKineticEnergy();
  G4ThreeVector pos = track.GetPosition();
  y = pos.y();
  z = pos.z();
  G4ThreeVector dir = track.GetMomentumDirection();
  dirX = dir.x();
  dirY = dir.y();
  dirZ = dir.z();

  // Fill histograms, all tracks
  IHistogram1D* h1 = histoManager->retrieveHisto1D("1");
  h1->fill(eKin);
  IHistogram2D* h2 = histoManager->retrieveHisto2D("2");
  h2->fill(y,z);

  // Fill histograms and ntuple, tracks entering the detector
  if (entering)
    {
      // Fill and plot histograms
      IHistogram1D* h3 = histoManager->retrieveHisto1D("3");
      h3->fill(eKin);
      plot1D(h1);
      plot1D(h3);
      IHistogram2D* h4 = histoManager->retrieveHisto2D("4");
      h4->fill(y,z);
      plot2D(h2);
      plot2D(h4);

      // Fill ntuple
      ntuple->addRow();
    }
}

void XrayTelAnalysis::plot1D(IHistogram1D* histo)
{
  IVector* v = vectorFactory->from1D(histo);
  plotter->plot(v,0);
  plotter->refresh();
  delete v;	
}

void XrayTelAnalysis::plot2D(IHistogram2D* histo)
{
  IVector* v = vectorFactory->from2D(histo);
  plotter->plot(v,0);
  plotter->refresh();
  delete v;	
}
