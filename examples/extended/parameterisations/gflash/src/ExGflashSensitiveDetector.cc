#include "ExGflashSensitiveDetector.hh"
#include "ExGflashHitsCollection.hh"
#include "ExGflashHit.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Step.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include <iostream>

ExGflashSensitiveDetector::ExGflashSensitiveDetector(G4String name, ExGflashDetectorConstruction* det):
G4VSensitiveDetector(name), G4VGFlashSensitiveDetector(), Detector(det)
{
	//@@@@ xN08SensitiveDetector:: evtl name im constructor des G4VGFlashSensitiveDetector ?
	G4String caloname="ExGflashCollection";
	collectionName.insert(caloname);
}

ExGflashSensitiveDetector::~ExGflashSensitiveDetector() {}

void ExGflashSensitiveDetector::Initialize(G4HCofThisEvent*HCE)
{
	cout<<"::Initializing the sensitive detector"<<endl;
	static G4int HCID = -1;
	if(HCID<0){ HCID = GetCollectionID(0); }
	HCE->AddHitsCollection( HCID, caloHitsCollection );
	caloHitsCollection=new 
	ExGflashHitsCollection(SensitiveDetectorName,collectionName[0]); // first collection
}

void ExGflashSensitiveDetector::EndOfEvent(G4HCofThisEvent*HCE)
{
	if (HCE);	
	// No Hadronic
	//    cout<<"IEndOfEvent  " << HCID << endl;
}

G4bool ExGflashSensitiveDetector::ProcessHits(G4Step* aStep,G4TouchableHistory* ROhist)
{	//cout<<"This is ProcessHits"<<endl;
	G4double e=aStep->GetTotalEnergyDeposit();
	if(e<=0.)return false;
	
	G4TouchableHistory* theTouchable
	= (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());

	// enrgy deposited -> make Hit
	//const G4VPhysicalVolume* physVol= aStep->GetPreStepPoint()->GetPhysicalVolume();
	//G4TouchableHistory* theTouchable = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
	ExGflashHit* caloHit=new ExGflashHit();
	caloHit->SetEdep(e);
	caloHit->SetPos(aStep->GetPreStepPoint()->GetPosition());
	caloHitsCollection->insert(caloHit);
	if (ROhist); 
	G4VPhysicalVolume* physVol = theTouchable->GetVolume();
	G4int crystalnum=0;
	for(int i=0;i<100;i++) //@@@@@@@ ExGflashSensitiveDetector:vorsichty
	{
		if(physVol == Detector->GetCristal(i))   crystalnum= i;
	}
	caloHit->SetCrystalNum(crystalnum);
	
	return true;
}


G4bool ExGflashSensitiveDetector::ProcessHits(G4GFlashSpot*aSpot ,G4TouchableHistory* ROhist)
{	//cout<<"This is ProcessHits GFLASH"<<endl;
	G4double e=aSpot->GetEnergySpot()->GetEnergy();
	if(e<=0.)return false;
	
	G4VPhysicalVolume* pCurrentVolume = aSpot->GetTouchableHandle()->GetVolume();
	
	ExGflashHit* caloHit=new ExGflashHit();
	caloHit->SetEdep(e);
	caloHit->SetPos(aSpot->GetEnergySpot()->GetPosition());
	caloHitsCollection->insert(caloHit);
	if (ROhist); 
	//cout <<pCurrentVolume->GetName()   << endl;
	G4int crystalnum=0;
	for(int i=0;i<100;i++) //@@@@@@@ ExGflashSensitiveDetector:vorsichty
	{
		if(pCurrentVolume  == Detector->GetCristal(i))   crystalnum= i;
	}
	caloHit->SetCrystalNum(crystalnum);
	
	return true;
}
