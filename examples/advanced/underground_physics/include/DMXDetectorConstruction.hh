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
// --------------------------------------------------------------
//   GEANT 4 - Underground Dark Matter Detector Advanced Example
//
//      For information related to this code contact: Alex Howard
//      e-mail: a.s.howard@ic.ac.uk
// --------------------------------------------------------------
// Comments
//
//                  Underground Advanced
//               by A. Howard and H. Araujo 
//                    (27th November 2001)
//
// DetectorConstruction header
// --------------------------------------------------------------

#ifndef DMXDetectorConstruction_h
#define DMXDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;

class G4UserLimits;

class DMXScintSD;
class DMXPmtSD;

class DMXDetectorMessenger;

class DMXDetectorConstruction : public G4VUserDetectorConstruction 
{
public:

  DMXDetectorConstruction();
  ~DMXDetectorConstruction();

public:

  G4VPhysicalVolume* Construct();

  void SetRoomEnergyCut(G4double);
  void SetEnergyCut(G4double);
  void SetTimeCut(G4double);
  void SetRoomTimeCut(G4double);
  //  void UpdateGeometry();


private:

  void DefineMaterials();

  G4UserLimits*    theUserLimitsForRoom; 
  G4UserLimits*    theUserLimitsForDetector; 
  G4UserLimits*    theUserLimitsForXenon; 

  G4double         theMaxTimeCuts;
  G4double         theMaxStepSize;
  G4double         theDetectorStepSize;
  G4double         theMinEkine;
  G4double         theRoomMinEkine;
  
  G4double         theRoomTimeCut;


#include "DMXDetectorMaterial.ihh"  // materials used

  G4double worldRadius;                // sizes
  G4double worldHeight;
  G4double sourceZ;
  G4double sourceZ2;


  G4LogicalVolume*   world_log;        // pointers
  G4VPhysicalVolume* world_phys;  

#include "DMXDetectorRoom.ihh"

  G4LogicalVolume*   lab_log;
  G4VPhysicalVolume* lab_phys;  

  G4LogicalVolume*   LN2jacket_log;
  G4VPhysicalVolume* LN2jacket_phys;
  G4LogicalVolume*   LN2vacuum_log;
  G4VPhysicalVolume* LN2vacuum_phys;
  G4LogicalVolume*   LN2vessel_log;
  G4VPhysicalVolume* LN2vessel_phys;  
  G4LogicalVolume*   LN2_log;
  G4VPhysicalVolume* LN2_phys;
  G4LogicalVolume*   jacket_log;
  G4VPhysicalVolume* jacket_phys;
  G4LogicalVolume*   jacketflange_log;
  G4VPhysicalVolume* topjacketflange_phys;
  G4VPhysicalVolume* bottomjacketflange_phys;
  G4LogicalVolume*   vacuum_log;
  G4VPhysicalVolume* vacuum_phys;
  G4LogicalVolume*   copper_log;
  G4VPhysicalVolume* copper_phys;
  G4LogicalVolume*   coppertop_log;
  G4VPhysicalVolume* coppertop_phys;
  G4LogicalVolume*   vessel_log;
  G4VPhysicalVolume* vessel_phys;
  G4LogicalVolume*   vesseltop_log1;
  G4VPhysicalVolume* vesseltop_phys1;
  G4LogicalVolume*   vesseltop_log2;
  G4VPhysicalVolume* vesseltop_phys2;
  G4LogicalVolume*   vesselbottom_log1;
  G4VPhysicalVolume* vesselbottom_phys1;
  G4LogicalVolume*   vesselbottom_log2;
  G4VPhysicalVolume* vesselbottom_phys2;
  G4LogicalVolume*   pmtvesselbottom_log1;
  G4VPhysicalVolume* pmtvesselbottom_phys1;
  G4LogicalVolume*   pmtvesselbottom_log2;
  G4VPhysicalVolume* pmtvesselbottom_phys2;
  G4LogicalVolume*   GXe_log;
  G4VPhysicalVolume* GXe_phys;  
  G4LogicalVolume*   gaslag_log;
  G4VPhysicalVolume* gaslag_phys;  
  G4LogicalVolume*   CuShield_log; 
  G4VPhysicalVolume* CuShield_phys;  
  G4LogicalVolume*   LXe_log; 
  G4VPhysicalVolume* LXe_phys;  
  G4LogicalVolume*   liqLag_log; 
  G4VPhysicalVolume* liqLag_phys;  
  G4LogicalVolume*   alpha_log;   
  G4VPhysicalVolume* alpha_phys; 
  G4LogicalVolume*   recess_log;   
  G4VPhysicalVolume* recess_phys; 
  G4LogicalVolume*   americium_log;   
  G4VPhysicalVolume* americium_phys; 
  G4LogicalVolume*   ring_log;   
  G4VPhysicalVolume* ring_phys_gas[1]; 
  G4VPhysicalVolume* ring_phys_liq[5]; 
  G4LogicalVolume*   mirror_log;   
  G4VPhysicalVolume* mirror_phys; 
  G4LogicalVolume*   grid1_log;   
  G4VPhysicalVolume* grid1_phys; 
  G4LogicalVolume*   grid2_log;   
  G4VPhysicalVolume* grid2_phys; 
  G4LogicalVolume*   pmt_log;   
  G4VPhysicalVolume* pmt_phys; 
  G4LogicalVolume*   phcath_log;
  G4VPhysicalVolume* phcath_phys; 


  DMXScintSD*  LXeSD;            //pointer to sensitive detectors
  DMXPmtSD* pmtSD;

  // pointer to the Detector Messenger:
  DMXDetectorMessenger*  detectorMessenger;

};

#endif

