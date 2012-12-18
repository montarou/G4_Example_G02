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
/// \file electromagnetic/TestEm5/src/TrackingAction.cc
/// \brief Implementation of the TrackingAction class
//
//
// $Id: TrackingAction.cc,v 1.18 2008-08-28 15:28:04 maire Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TrackingAction.hh"

#include "DetectorConstruction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "HistoManager.hh"

#include "G4Track.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackingAction::TrackingAction(DetectorConstruction* DET,RunAction* RA,
                               EventAction* EA)
:fDetector(DET), fRunAction(RA), fEventAction(EA)
{ }
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackingAction::PreUserTrackingAction(const G4Track* aTrack )
{
  // few initialisations
  //
  if (aTrack->GetTrackID() == 1) {
    fXstartAbs = fDetector->GetxstartAbs();
    fXendAbs   = fDetector->GetxendAbs();
    fPrimaryCharge = aTrack->GetDefinition()->GetPDGCharge();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackingAction::PostUserTrackingAction(const G4Track* aTrack)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  G4ThreeVector position = aTrack->GetPosition();
  G4ThreeVector vertex   = aTrack->GetVertexPosition();  
  G4double charge        = aTrack->GetDefinition()->GetPDGCharge();

  G4bool transmit = ((position.x() >= fXendAbs) && (vertex.x() < fXendAbs));
  G4bool reflect  =  (position.x() <= fXstartAbs);
  G4bool notabsor = (transmit || reflect);

  //transmitted + reflected particles counter
  //
  G4int flag = 0;
  if (charge == fPrimaryCharge)  flag = 1;
  if (aTrack->GetTrackID() == 1) flag = 2;
  if (transmit) fEventAction->SetTransmitFlag(flag);
  if (reflect)  fEventAction->SetReflectFlag(flag);
      
  //
  //histograms
  //
  G4bool charged  = (charge != 0.);
  G4bool neutral = !charged;

  //energy spectrum at exit
  //
  G4int id = 0;  
       if (transmit && charged) id = 10;
  else if (transmit && neutral) id = 20;
  else if (reflect  && charged) id = 30;
  else if (reflect  && neutral) id = 40;

  if (id>0)   
  analysisManager->FillH1(id, aTrack->GetKineticEnergy());
    
  //energy leakage
  //
  if (notabsor) {
    G4int trackID = aTrack->GetTrackID();
    G4int index = 0; if (trackID > 1) index = 1;    //primary=0, secondaries=1
    G4double eleak = aTrack->GetKineticEnergy();
    if ((aTrack->GetDefinition() == G4Positron::Positron()) && (trackID > 1))
      eleak += 2*electron_mass_c2;
    fRunAction->AddEnergyLeak(eleak,index);  
  }

  //space angle distribution at exit : dN/dOmega
  //
  G4ThreeVector direction = aTrack->GetMomentumDirection();    
  id = 0;   
       if (transmit && charged) id = 12;
  else if (transmit && neutral) id = 22;
  else if (reflect  && charged) id = 32;
  else if (reflect  && neutral) id = 42;

  if (id>0) {
    G4double theta  = std::acos(direction.x());
    if (theta > 0.0) {
      G4double dteta  = analysisManager->GetH1Width(id);
      G4double unit   = analysisManager->GetH1Unit(id);    
      G4double weight = (unit*unit)/(twopi*std::sin(theta)*dteta);
      /*
      G4cout << "theta, dteta, unit, weight: " 
             << theta << "  "   
             << dteta << "  "   
             << unit << "  "   
             << weight << G4endl;   
      */
      analysisManager->FillH1(id,theta,weight);
    }
  }
  
  //energy fluence at exit : dE(MeV)/dOmega
  //
  id = 0;  
  if (transmit && charged) id = 11;
  else if (transmit && neutral) id = 21;
  else if (reflect  && charged) id = 31;
  else if (reflect  && neutral) id = 41;

  if (id>0) {
    G4double theta  = std::acos(direction.x());
    if (theta > 0.0) {
      G4double dteta  = analysisManager->GetH1Width(id);
      G4double unit   = analysisManager->GetH1Unit(id);    
      G4double weight = (unit*unit)/(twopi*std::sin(theta)*dteta);
      weight *= (aTrack->GetKineticEnergy()/MeV); 
      analysisManager->FillH1(id,theta,weight);
    } 
  }
  
  //projected angles distribution at exit
  //
  id = 0;   
  if (transmit && charged) id = 13;
  else if (transmit && neutral) id = 23;
  else if (reflect  && charged) id = 33;
  else if (reflect  && neutral) id = 43;

  if (id>0) {
    if (direction.x() != 0.0) {
      G4double tet = std::atan(direction.y()/std::fabs(direction.x()));
      analysisManager->FillH1(id,tet);
      if (transmit && (flag == 2)) fRunAction->AddMscProjTheta(tet);

      tet = std::atan(direction.z()/std::fabs(direction.x()));
      analysisManager->FillH1(id,tet);
      if (transmit && (flag == 2)) fRunAction->AddMscProjTheta(tet);
    }
  }

  //projected position and radius at exit
  //
  id = 0;   
  if (transmit && charged) id = 14;
  
  if (id>0) {
    G4double y = position.y(), z = position.z();
    G4double r = std::sqrt(y*y + z*z);
    analysisManager->FillH1(id,   y);
    analysisManager->FillH1(id,   z);
    analysisManager->FillH1(id+1, r);
  }
  
  //x-vertex of charged secondaries
  //
  if ((aTrack->GetParentID() == 1) && charged) {
    G4double xVertex = (aTrack->GetVertexPosition()).x();
    analysisManager->FillH1(6, xVertex);
    if (notabsor) analysisManager->FillH1(7, xVertex); 
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

