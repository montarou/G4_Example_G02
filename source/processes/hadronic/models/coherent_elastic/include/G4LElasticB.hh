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
// $Id: G4LElasticB.hh,v 1.3 2006-04-18 16:53:05 vnivanch Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
//
// G4 Model: Low energy elastic scattering with 4-momentum balance 
// Derived fron G4LElastic of F.W. Jones, TRIUMF, 04-JUN-96
//  
// Modified:
// 14-Dec-05 V.Ivanchenko rename the class
// 13-Apr-06 V.Ivanchenko move to coherent_elastic 
//
// use -scheme for elastic scattering: HPW, 20th June 1997
// most of the code comes from the old Low-energy Elastic class
//


#ifndef G4LElasticB_h
#define G4LElasticB_h 1
 
// Class Description
// Final state production model for hadron nuclear elastic scattering; 
// To be used in your physics list in case you need this physics.
// In this case you want to register an object of this class with 
// the corresponding process.
// Class Description - End

#include "globals.hh"
#include "G4HadronicInteraction.hh"
#include "G4HadProjectile.hh"
#include "G4Nucleus.hh"

class G4ParticleDefinition;
class G4VQCrossSection;
class G4QElastic;

class G4LElasticB : public G4HadronicInteraction
{
public:

  G4LElasticB(G4double elim = 0.0, G4double plim = 200.*MeV);

  virtual ~G4LElasticB();
 
  G4HadFinalState * ApplyYourself(const G4HadProjectile & aTrack, 
				  G4Nucleus & targetNucleus);

private:

  G4double SampleT(G4double p, G4double m1, G4double m2, G4double A);

  G4int Rtmi(G4double* x, G4double xli, G4double xri, G4double eps, 
	     G4int iend,
	     G4double aa, G4double bb, G4double cc, G4double dd, 
	     G4double rr);

  G4double Fctcos(G4double t, 
		  G4double aa, G4double bb, G4double cc, G4double dd, 
		  G4double rr);

  void Defs1(G4double p, G4double px, G4double py, G4double pz, 
	     G4double pxinc, G4double pyinc, G4double pzinc, 
	     G4double* pxnew, G4double* pynew, G4double* pznew);

  G4VQCrossSection*           qCManager;
  G4QElastic*                 qElastic;
  const G4ParticleDefinition* theProton;
  const G4ParticleDefinition* theNeutron;
  const G4ParticleDefinition* theDeuteron;
  const G4ParticleDefinition* theAlpha;

  G4double plablim;  // in MeV/c
  G4double ekinlim;  // in MeV
};

#endif
