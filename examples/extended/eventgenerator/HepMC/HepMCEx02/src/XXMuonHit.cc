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

// ====================================================================
//
//   XXMuonHit.cc
//   $Id: XXMuonHit.cc,v 1.1 2002-04-29 20:44:59 asaim Exp $
//
// ====================================================================
#include "XXMuonHit.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "g4std/iomanip"

G4Allocator<XXMuonHit> XXMuonHitAllocator;

//////////////////////
XXMuonHit::XXMuonHit()
  : moduleID(-1)
//////////////////////
{
}

/////////////////////////////////////////////////////////////
XXMuonHit::XXMuonHit(G4int imod, G4String aname, 
		     const G4ThreeVector& pxyz, 
		     const G4ThreeVector& xyz, G4double atof)
  : moduleID(imod), pname(aname), momentum(pxyz),
    position(xyz), tof(atof)
/////////////////////////////////////////////////////////////
{
}

///////////////////////
XXMuonHit::~XXMuonHit()
///////////////////////
{
}

////////////////////////////////////////////
XXMuonHit::XXMuonHit(const XXMuonHit& right)
////////////////////////////////////////////
{
  *this= right;
}

/////////////////////////////////////////////////////////////
const XXMuonHit& XXMuonHit::operator=(const XXMuonHit& right)
/////////////////////////////////////////////////////////////
{
  moduleID= right.moduleID;
  pname= right.pname;
  momentum= right.momentum;
  position= right.position;
  tof= right.tof;

  return *this;
}

///////////////////////////////////////////////////////
int XXMuonHit::operator==(const XXMuonHit& right) const
///////////////////////////////////////////////////////
{
  return 0;
}

//////////////////////
void XXMuonHit::Draw()
//////////////////////
{
  const G4double pt_min=20.*GeV;

  G4VVisManager* pVVisManager= G4VVisManager::GetConcreteInstance();
  if(pVVisManager) {
    G4Circle circle(position);
    circle.SetScreenSize(5.);
    circle.SetFillStyle(G4Circle::filled);

    G4Color color, goodColor(1.,0.,0.), badColor(0.,0.,1.);
    if(momentum.perp()>pt_min) color=goodColor;
    else color=badColor;

    G4VisAttributes attribs(color);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}

///////////////////////
void XXMuonHit::Print()
///////////////////////
{  
  G4int id= moduleID;
  G4String tag="B";
  if(moduleID >=10) {
    id -=10;
    tag="E";
  }
  G4cout << tag << id << " :" << setw(12) << pname.c_str()
	 << " : pT=" << setprecision(3)  << momentum.perp()/GeV
	 << " : TOF=" << setprecision(3) << tof/ns 
	 << " : x="  << setprecision(3) << position*(1./m) 
	 << G4endl;
}
