///////////////////////////////////////////////////////////////////////////////
// File: HcalTB96EndOfEventAction.cc
// Date: 11/1998 Veronique Lefebure
// Modifications: 09/00 Sudeshna Banerjee, Sunanda Banerjee
///////////////////////////////////////////////////////////////////////////////
#include "HcalTB96EndOfEventAction.hh"
#include "HcalTB96Analysis.hh"
#include "G4CaloHit.hh"
#include "G4CaloSD.hh"
#include "CMSPrimaryGeneratorAction.hh"
#include "G4CaloHitsCollection.hh"
#include "G4CaloHit.hh"
#include "CMSCaloOrganization.hh"
#include "SDList.hh"
#include "HcalTB96SteppingAction.hh"

#include "G4ios.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include <iostream>
#include <map>
#include "G4RunManager.hh"
#include "G4UserSteppingAction.hh"

//#define debug
//#define ddebug

HcalTB96EndOfEventAction::HcalTB96EndOfEventAction
(CMSPrimaryGeneratorAction* pg): isInitialized(false),SDnames(0),numberOfSD(0){

  primaryGenerator = pg;
#ifdef debug
  cout << "Instantiate HcalTB96EndOfEventAction" << endl;
#endif

  cout << "Now Instantiate stepping action" << endl;
  instanciateSteppingAction();
  
  cout << "Get Calorimter organisation" << endl;
  theOrg = new CMSCaloOrganization;
  cout << "end of instantiation of EndofEventAction" << endl;
}

HcalTB96EndOfEventAction::~HcalTB96EndOfEventAction() {

  if (theOrg)
    delete theOrg;
  if (SDnames)
    delete SDnames;
  cout << "Deleting HcalTB96EndOfEventAction" << endl;
}

void HcalTB96EndOfEventAction::initialize() {

  isInitialized = true;
  numberOfSD = SDList::getInstance()->getNumberOfCaloSD();
#ifdef debug
  cout << "HcalTB96EndOfEventAction look for " << numberOfSD 
       << " calorimeter-like SD" << endl;
#endif
  if (numberOfSD > 0)
    SDnames = new nameType[numberOfSD];
  for (int i=0; i<numberOfSD; i++) {
    SDnames[i] = G4String(SDList::getInstance()->getCaloSDName(i));
#ifdef debug
    cout << "HcalTB96EndOfEventAction: found SD " << i << " name "
	 << SDnames[i] << endl;
#endif
  }       
}

void HcalTB96EndOfEventAction::StartOfEventAction(const G4Event* evt)
{ }

void HcalTB96EndOfEventAction::EndOfEventAction(const G4Event* evt){

  if (!isInitialized) initialize();

  theSteppingAction->endOfEvent();
  HcalTB96Analysis* analysis = HcalTB96Analysis::getInstance();
  
  //
  // Look for the Hit Collection 
  //
  
  G4HCofThisEvent* allHC = evt->GetHCofThisEvent();
  if (allHC == 0) {
#ifdef debug
    cout << "HcalTB96EndOfEventAction: No Hit Collection in this event" 
	 << endl;
#endif
    return;
  }
  	
  //
  // hits info
  //
  
  //Now make summary
  float hcalE[28], ecalE[49], fullE=0.;
  int i = 0;
  for (i = 0; i < 28; i++) {hcalE[i]=0.;}
  for (i = 0; i < 49; i++) {ecalE[i]=0.;}

  float* edep = new float[numberOfSD];
  int nhit=0;
  for (i = 0; i < numberOfSD; i++){

    //
    // Look for the Hit Collection
    //
    edep[i] = 0;
    int caloHCid = G4SDManager::GetSDMpointer()->GetCollectionID(SDnames[i]);

    G4CaloHitsCollection* theHC = 
      (G4CaloHitsCollection*) allHC->GetHC(caloHCid);
    if (theHC != 0) {

      G4int nentries = theHC->entries();
#ifdef debug
      cout << " There are " << nentries << " hits in " << SDnames[i] << " :" 
	   << endl;
#endif

      if (nentries > 0) {
  
	int j;
	for (j=0; j<nentries; j++){
	  G4CaloHit* aHit =  (*theHC)[j];
	  float En = aHit->getEnergyDeposit();
	  int unitID = aHit->getUnitID();
	  int id=-1;
	  if (unitID > 0 && unitID < 29) {
	    id = unitID - 1; // HCal
	    hcalE[id] += En/GeV;
	  } else {
	    int i0 = unitID/4096;
	    int i1 = (unitID/64)%64;
	    int i2 = unitID%64;
	    if (i0 == 1 && i1 < 8 && i2 < 8) {
	      id = i1*7 + i2; // ECal
	      ecalE[id] += En/GeV;
	    }
	  }
#ifdef ddebug
	  cout << "Seeing Energy = " << En/MeV << " MeV in Unit " << unitID 
	       << " " << id << endl;
#endif
	  fullE   += En/GeV;
	  edep[i] += En/GeV;
	  nhit++;
	}
      }
    }
  }

  G4ThreeVector pos = primaryGenerator->GetParticlePosition();
  float ener = primaryGenerator->GetParticleEnergy()/GeV;
  float x    = pos.x()/mm;
  float y    = pos.y()/mm;
  float z    = pos.z()/mm;
  float edec = edep[1];
  float edhc = edep[0];
  delete[] edep;

  analysis->InsertEnergy(fullE);
  for (i=0; i<28; i++) {
    analysis->InsertEnergyHcal(i,hcalE[i]);
  }
  for (i=0; i<49; i++) {
    analysis->InsertEnergyEcal(i,ecalE[i]);
  }
  analysis->setNtuple(hcalE, ecalE, ener, x, y, z, fullE, edec, edhc);
  analysis->EndOfEvent(nhit);
}

void HcalTB96EndOfEventAction::instanciateSteppingAction(){

	
  G4UserSteppingAction* theUA = const_cast<G4UserSteppingAction*>(G4RunManager::GetRunManager()->GetUserSteppingAction());
        
  if (theUA == 0) {
#ifdef debug
    cout << " HcalTB96EndOfEventAction::instanciateSteppingAction creates"
	 << " CMSSteppingAction" << endl;
#endif
    theSteppingAction = new HcalTB96SteppingAction;  
    G4RunManager::GetRunManager()->SetUserAction(theSteppingAction);
  }   
	
}
