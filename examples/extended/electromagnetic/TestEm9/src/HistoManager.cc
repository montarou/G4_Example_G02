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
//---------------------------------------------------------------------------
//
// ClassName:   HistoManager
//
//
// Author:      V.Ivanchenko 30/01/01
//
//----------------------------------------------------------------------------
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "HistoManager.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

HistoManager* HistoManager::fManager = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

HistoManager* HistoManager::GetPointer()
{
  if(!fManager) {
    fManager = new HistoManager();
  }
  return fManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

HistoManager::HistoManager()
{
  verbose = 1;
  nEvt1  = -1;
  nEvt2  = -1;
  bookHisto();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

HistoManager::~HistoManager()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void HistoManager::bookHisto()
{
  maxEnergy = 50.0*MeV;
  beamEnergy= 1.*GeV;
  maxEnergyAbs = 10.*MeV;
  thKinE    = 1.*MeV;
  nBinsE = 100;
  nBinsEA= 40;
  nBinsED= 100;
  nTuple = false;
  nHisto = 10;

  histo.add1D("10",
    "Energy deposit (MeV) in central crystal",nBinsED,0.0,beamEnergy,MeV);

  histo.add1D("11",
    "Energy deposit (MeV) in 3x3",nBinsED,0.0,beamEnergy,MeV);

  histo.add1D("12",
    "Energy deposit (MeV) in 5x5",nBinsED,0.0,beamEnergy,MeV);

  histo.add1D("13",
    "Energy (MeV) of delta-electrons",nBinsE,0.0,maxEnergy,MeV);

  histo.add1D("14",
    "Energy (MeV) of gammas",nBinsE,0.0,maxEnergy,MeV);

  histo.add1D("15",
    "Energy (MeV) in abs1",nBinsEA,0.0,maxEnergyAbs,MeV);

  histo.add1D("16",
    "Energy (MeV) in abs2",nBinsEA,0.0,maxEnergyAbs,MeV);

  histo.add1D("17",
    "Energy (MeV) in abs3",nBinsEA,0.0,maxEnergyAbs,MeV);

  histo.add1D("18",
    "Energy (MeV) in abs4",nBinsEA,0.0,maxEnergyAbs,MeV);

  histo.add1D("19",
    "Number of vertex hits",20,-0.5,19.5,1.0);

  if(nTuple) {
    histo.addTuple( "100", "Dose deposite","float r, z, e" );
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void HistoManager::BeginOfEvent()
{
  n_evt++;

  Eabs1  = 0.0;
  Eabs2  = 0.0;
  Eabs3  = 0.0;
  Eabs4  = 0.0;
  Evertex.clear();
  Nvertex.clear();
  for (int i=0; i<25; i++) {
    E[i] = 0.0;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void HistoManager::EndOfEvent()
{
  G4double e9 = 0.0;
  G4double e25= 0.0;
  for (int i=0; i<25; i++) {
    e25 += E[i];
    if( ( 6<=i &&  8>=i) || (11<=i && 13>=i) || (16<=i && 18>=i)) e9 += E[i];
  }
  histo.fill(0,E[12],1.0);
  histo.fill(1,e9,1.0);
  histo.fill(2,e25,1.0);
  histo.fill(5,Eabs1,1.0);
  histo.fill(6,Eabs2,1.0);
  histo.fill(7,Eabs3,1.0);
  histo.fill(8,Eabs4,1.0);
  float nn = (double)(Nvertex.size());
  histo.fill(9,nn,1.0);

  if(nTuple) histo.addRow();

  Eabs1  = 0.0;
  Eabs2  = 0.0;
  Eabs3  = 0.0;
  Eabs4  = 0.0;
  Evertex.clear();
  Nvertex.clear();
  for (int i=0; i<25; i++) {
    E[i] = 0.0;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void HistoManager::BeginOfRun()
{
  n_evt  = 0;
  n_elec = 0;
  n_posit= 0;
  n_gam  = 0;
  n_step = 0;
  histo.book();

  if(verbose > 0) {
    G4cout << "HistoManager: Histograms are booked and run has been started"
           << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void HistoManager::EndOfRun()
{

  G4cout << "Histo: End of run actions are started" << G4endl;

  // average

  G4cout<<"========================================================"<<G4endl;
  G4double x = (G4double)n_evt;
  if(n_evt > 0) x = 1.0/x;
  G4double xe = x*(G4double)n_elec;
  G4double xg = x*(G4double)n_gam;
  G4double xp = x*(G4double)n_posit;
  G4double xs = x*(G4double)n_step;
  G4cout                    << "Number of events                     " << n_evt <<G4endl;
  G4cout << std::setprecision(4) << "Average number of e-                 " << xe << G4endl;
  G4cout << std::setprecision(4) << "Average number of gamma              " << xg << G4endl;
  G4cout << std::setprecision(4) << "Average number of e+                 " << xp << G4endl;
  G4cout << std::setprecision(4) << "Average number of steps              " << xs << G4endl;
  G4cout<<"========================================================"<<G4endl;
  G4cout<<G4endl;

  // normalise histograms
  for(G4int i=0; i<nHisto; i++) {
    histo.scale(i,x);
  }

  histo.save();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void HistoManager::SaveToTuple(const G4String& parname, G4double val)
{
  if(nTuple) histo.fillTuple(parname, val);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void HistoManager::SaveToTuple(const G4String& parname,G4double val, G4double)
{
  if(nTuple) histo.fillTuple(parname, val);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void HistoManager::AddEnergy(G4double, G4double)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void HistoManager::AddEndPoint(G4double )
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void HistoManager::AddDeltaElectron(const G4DynamicParticle* elec)
{
  G4double e = elec->GetKineticEnergy()/MeV;
  if(e > 0.0) n_elec++;
  histo.fill(3,e,1.0);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void HistoManager::AddPhoton(const G4DynamicParticle* ph)
{
  G4double e = ph->GetKineticEnergy()/MeV;
  if(e > 0.0) n_gam++;
  histo.fill(4,e,1.0);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void HistoManager::ScoreNewTrack(const G4Track* aTrack)
{
  //Save primary parameters

  ResetTrackLength();
  G4ParticleDefinition* particle = aTrack->GetDefinition();
  G4String name = particle->GetParticleName();
  G4int pid = aTrack->GetParentID();
  G4double kinE = aTrack->GetKineticEnergy();
  G4ThreeVector pos = aTrack->GetVertexPosition();

  if(0 == pid) {

    tCounter = 0;
    tType.clear();
    tScore.clear();

    SaveToTuple("TKIN", kinE/MeV);

    G4double mass = 0.0;
    if(particle) {
      mass = particle->GetPDGMass();
      SaveToTuple("MASS", mass/MeV);
      SaveToTuple("CHAR",(particle->GetPDGCharge())/eplus);
      G4double beta = 1.;
	if(mass > 0.) {
          G4double gamma = kinE/mass + 1.;
          beta = sqrt(1. - 1./(gamma*gamma));
	}
    }

    G4ThreeVector dir = aTrack->GetMomentumDirection();
    if(1 < verbose) {
      G4cout << "TrackingAction: Primary kinE(MeV)= " << kinE/MeV
           << "; m(MeV)= " << mass/MeV
           << "; pos= " << pos << ";  dir= " << dir << G4endl;
    }

    // delta-electron
  } else if (0 < pid && "e-" == name) {
    if(1 < verbose) {
      G4cout << "TrackingAction: Secondary electron " << G4endl;
    }
    AddDeltaElectron(aTrack->GetDynamicParticle());

  } else if (0 < pid && "e+" == name) {
    if(1 < verbose) {
      G4cout << "TrackingAction: Secondary positron " << G4endl;
    }
    AddPositron(aTrack->GetDynamicParticle());

  } else if (0 < pid && "gamma" == name) {
    if(1 < verbose) {
      G4cout << "TrackingAction: Secondary gamma; parentID= " << pid
             << " E= " << aTrack->GetKineticEnergy() << G4endl;
    }
    AddPhoton(aTrack->GetDynamicParticle());

  }

  // MC truth
  tCounter++;

  if(kinE > thKinE) {
    tScore.push_back((G4int)(tType.size()));

    if(pos.z() < thPosZ) tType.push_back(1);
    else                 tType.push_back(0);

  } else {
    tScore.push_back(tScore[pid]);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::AddEnergy(G4double edep, G4int volIndex, G4int copyNo)
{
  if(0 == volIndex) {
    E[copyNo] += edep;
  } else if (1 == volIndex) {
    Eabs1 += edep;
  } else if (2 == volIndex) {
    Eabs2 += edep;
  } else if (3 == volIndex) {
    Eabs3 += edep;
  } else if (4 == volIndex) {
    Eabs4 += edep;
  } else if (5 == volIndex) {
    G4int n = Nvertex.size();
    G4bool newPad = true;
    if (n > 0) {
      for(G4int i=0; i<n; i++) {
        if (copyNo == Nvertex[i]) {
          newPad = false;
          Evertex[i] += edep;
          break;
        }
      }
    }
    if(newPad) {
      Nvertex.push_back(copyNo);
      Evertex.push_back(edep);
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

