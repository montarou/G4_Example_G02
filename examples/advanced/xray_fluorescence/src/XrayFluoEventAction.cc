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
// $Id: XrayFluoEventAction.cc
// GEANT4 tag $Name: xray_fluo-V03-02-00
//
// Author: Elena Guardincerri (Elena.Guardincerri@ge.infn.it)
//
// History:
// -----------
// 28 Nov 2001 Elena Guardincerri     Created
// 15 Jul 2003 Alfonso Mantero        "DetectorType" use integration
// 23 Sep 2003 Alfonso Mantero        differnt geometries integration
//
// -------------------------------------------------------------------

#include "XrayFluoEventAction.hh"
#include "XrayFluoSensorHit.hh"
#include "XrayFluoEventActionMessenger.hh"

//#include "XrayFluoRunAction.hh"
#include "XrayFluoDataSet.hh"

#include "XrayFluoAnalysisManager.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4SDManager.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"
#include <fstream>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XrayFluoEventAction::XrayFluoEventAction(XrayFluoDetectorConstruction* det)
  :drawFlag("all"),
   HPGeCollID(-1),
   eventMessenger(0),
   printModulo(1),
   detectorType(0)
{
  eventMessenger = new XrayFluoEventActionMessenger(this);
  detectorType = det->GetDetectorType();

  //runManager = new XrayFluoRunAction();
  G4cout << "XrayFluoEventAction created" << G4endl;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XrayFluoEventAction::XrayFluoEventAction(XrayFluoPlaneDetectorConstruction* det)
  :drawFlag("all"),
   HPGeCollID(-1),
   eventMessenger(0),
   printModulo(1),
   detectorType(0)
{
  eventMessenger = new XrayFluoEventActionMessenger(this);
  detectorType = det->GetDetectorType();

  //runManager = new XrayFluoRunAction();
  G4cout << "XrayFluoEventAction created" << G4endl;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XrayFluoEventAction::XrayFluoEventAction(XrayFluoMercuryDetectorConstruction* det)
  :drawFlag("all"),
   HPGeCollID(-1),
   eventMessenger(0),
   printModulo(1),
   detectorType(0)
{
  eventMessenger = new XrayFluoEventActionMessenger(this);
  detectorType = det->GetDetectorType();

  //runManager = new XrayFluoRunAction();
  G4cout << "XrayFluoEventAction created" << G4endl;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XrayFluoEventAction::~XrayFluoEventAction()
{
   delete eventMessenger;
   eventMessenger = 0;
   //delete  runManager;
   //runManager = 0;
   G4cout << "XrayFluoEventAction deleted" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void XrayFluoEventAction::BeginOfEventAction(const G4Event* evt)
{

  G4int eventNumber = (evt->GetEventID())+1;
  if ( eventNumber == 1){

  G4cout << "# = 100000 events" << G4endl;
  G4cout << "1--------+---------+---------+---------+---------5e6"<<G4endl;
  }

  if ( ((eventNumber) % 100000) == 0 )  {

    if ( eventNumber % (G4int)5e6 != 0 ) G4cout << "#" << std::flush;
    else G4cout << "#"<< G4endl;
    //    if ( eventNumber % 5e6 == 0 ) G4cout << "#"<< G4endl;

    XrayFluoAnalysisManager* analysis = XrayFluoAnalysisManager::getInstance();
    analysis->PlotCurrentResults();
  }

  if (HPGeCollID==-1)
    
    {
      G4SDManager * SDman = G4SDManager::GetSDMpointer();
      HPGeCollID = SDman->GetCollectionID("HPGeCollection");
      //the pointer points to the ID number of the sensitive detector
    }
}
  
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void XrayFluoEventAction::EndOfEventAction(const G4Event* evt)
{
  // extracted from hits, compute the total energy deposit (and total charged
  // track length) 
  G4HCofThisEvent* HCE = evt->GetHCofThisEvent();


  
  XrayFluoSensorHitsCollection* HPGeHC = 0;
  G4int n_hit = 0;
  G4double totEnergyDetect=0., totEnergy=0., energyD=0.;
  
  if (HCE) HPGeHC = (XrayFluoSensorHitsCollection*)(HCE->GetHC(HPGeCollID));
  if(HPGeHC)


    {
      n_hit = HPGeHC->entries();
      
      // if (n_hit) {G4cout << "Ecco quante hit ho nel detector "<< n_hit << G4endl;}
      
      for (G4int i=0;i<n_hit;i++)
	{
	  
	  totEnergy += (*HPGeHC)[i]->GetEdepTot(); 
	  
	  
	  
	  energyD = detectorType->ResponseFunction(totEnergy);
	  // energyD = totEnergy;
	  // G4cout << "energy deposit: "<< totEnergy  << G4endl;
	  
	  XrayFluoAnalysisManager* analysis = XrayFluoAnalysisManager::getInstance();
	  analysis->analyseEnergyDep(energyD);
	  
	  totEnergyDetect += energyD;
	  
	  
	}
    }
  
  // extract the trajectories and draw them
  
  if (G4VVisManager::GetConcreteInstance())
    {
      
      G4TrajectoryContainer * trajectoryContainer = evt->GetTrajectoryContainer();
      G4int n_trajectories = 0;
      if (trajectoryContainer) n_trajectories = trajectoryContainer->size();
      
      for (G4int i=0; i<n_trajectories; i++) 
	{ G4Trajectory* trj = (G4Trajectory*)((*(evt->GetTrajectoryContainer()))[i]);
	if (drawFlag == "all") trj->DrawTrajectory(50);
	else if ((drawFlag == "charged")&&(trj->GetCharge() != 0.))
	  trj->DrawTrajectory(50);
	else if ((drawFlag == "neutral")&&(trj->GetCharge() == 0.))
	  trj->DrawTrajectory(50);				   
	}
    }             
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....



G4double XrayFluoEventAction::RandomCut(G4double energy)
  
{
  G4double efficiency = 1.;
  G4double F = 0.15;
  G4double epsilon = 2.96 * eV;
  G4double deltaE = 220 * eV;
  G4double EdepDetect = 0.;
  //const XrayFluoDataSet* dataSet = runManager->GetEfficiencySet();
     
  //G4double id = 0;
 
  //efficiency = dataSet->FindValue(energy,id); 
 
  G4double  Random = G4UniformRand(); 

    if ( Random<efficiency )
      {
	G4double sigma = sqrt(F*epsilon*energy+pow(deltaE/2355,2));

	EdepDetect = G4RandGauss::shoot(energy, sigma );

  }
    else {EdepDetect = 0.;}
    return   EdepDetect;
    
};


