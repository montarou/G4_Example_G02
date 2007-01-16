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
// Authors: S. Guatelli and M. G. Pia, INFN Genova, Italy
// 
// Based on code developed by the undergraduate student G. Guerrieri 
// Note: this is a preliminary beta-version of the code; an improved 
// version will be distributed in the next Geant4 public release, compliant
// with the design in a forthcoming publication, and subject to a 
// design and code review.
//
#include "G4MIRDLegs.hh"

#include "globals.hh"

#include "G4SDManager.hh"
#include "G4Cons.hh"

#include "G4VisAttributes.hh"
#include "G4HumanPhantomMaterial.hh"
#include "G4EllipticalTube.hh"
#include "G4ThreeVector.hh"
#include "G4VPhysicalVolume.hh"
#include "G4RotationMatrix.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4UnionSolid.hh"

G4MIRDLegs::G4MIRDLegs()
{
}

G4MIRDLegs::~G4MIRDLegs()
{
}

G4VPhysicalVolume* G4MIRDLegs::ConstructLegs(G4VPhysicalVolume* mother, G4String sex, G4bool sensitivity)
{
 
  G4cout << "ConstructLegs for "<<sex << G4endl;

  G4HumanPhantomMaterial* material = new G4HumanPhantomMaterial();
  G4Material* soft = material -> GetMaterial("soft_tissue");
 
  G4double rmin1 = 0.* cm;
  G4double rmin2 = 0.* cm;
  G4double dz= 80.0 * cm; 
  G4double rmax1= 2.0 * cm;
  G4double rmax2= 10. * cm;
  G4double startphi= 0.* degree;
  G4double deltaphi= 360. * degree;

  G4Cons* leg1 = new G4Cons("Leg1",  
			   rmin1, rmax1, 
			   rmin2, rmax2, dz/2., 
			   startphi, deltaphi);
  
  G4UnionSolid* legs = new G4UnionSolid("Legs", leg1, leg1,0,
                                       G4ThreeVector(20. *cm, 0., 0.));

  G4LogicalVolume* logicLegs = new G4LogicalVolume(legs,
						   soft,
						   "LegsVolume",
						    0, 0, 0);
						   
  G4RotationMatrix* rm = new G4RotationMatrix();
  rm -> rotateX(90.* degree);

  G4VPhysicalVolume* physLegs = new G4PVPlacement(rm,
                                
				G4ThreeVector(-10. * cm, -40. * cm, 0. *cm),
      			       "physicalLegs",
  			       logicLegs,
			       mother,
			       false,
			       0, true);

  // Sensitive Body Part
  if (sensitivity == true)
  { 
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    logicLegs->SetSensitiveDetector( SDman->FindSensitiveDetector("BodyPartSD") );
  }

  // Visualization Attributes
  G4VisAttributes* LegsVisAtt = new G4VisAttributes(G4Colour(0.94,0.5,0.5));
  LegsVisAtt->SetForceSolid(false);
  logicLegs->SetVisAttributes(LegsVisAtt);

  G4cout << "Legs created !!!!!!" << G4endl;

  // Testing Legs Volume
  G4double LegsVol = logicLegs->GetSolid()->GetCubicVolume();
  G4cout << "Volume of Legs = " << LegsVol/cm3 << " cm^3" << G4endl;
  
  // Testing Legs Material
  G4String LegsMat = logicLegs->GetMaterial()->GetName();
  G4cout << "Material of Legs = " << LegsMat << G4endl;
  
  // Testing Density
  G4double LegsDensity = logicLegs->GetMaterial()->GetDensity();
  G4cout << "Density of Material = " << LegsDensity*cm3/g << " g/cm^3" << G4endl;

  // Testing Mass
  G4double LegsMass = (LegsVol)*LegsDensity;
  G4cout << "Mass of Legs = " << LegsMass/gram << " g" << G4endl;

  
  return physLegs;
}
