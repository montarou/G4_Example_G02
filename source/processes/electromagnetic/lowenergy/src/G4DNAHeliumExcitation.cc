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
// $Id: G4DNAHeliumExcitation.cc,v 1.1 2005-07-20 10:01:54 capra Exp $
// GEANT4 tag $Name: not supported by cvs2svn $

#include "G4DNAHeliumExcitation.hh"
#include "G4DNAGenericIonsManager.hh"

                                        G4DNAHeliumExcitationEnergyLimitsPolicy :: G4DNAHeliumExcitationEnergyLimitsPolicy()
:
 lowEnergyLimit(1*keV),
 zeroBelowLowEnergyLimit(false),
 highEnergyLimit(15*MeV),
 zeroAboveHighEnergyLimit(true)
{
}

                                        G4DNAHeliumExcitationIncomingParticlePolicy :: G4DNAHeliumExcitationIncomingParticlePolicy()
:
 kineticEnergyCorrection(0.9382723/3.727417)
{
 slaterEffectiveCharge[0]=1.7;
 slaterEffectiveCharge[1]=1.15;
 slaterEffectiveCharge[2]=1.15;
 sCoefficient[0]=0.5;
 sCoefficient[1]=0.25;
 sCoefficient[2]=0.25;
}

const G4ParticleDefinition *            G4DNAHeliumExcitationIncomingParticlePolicy :: IncomingParticleDefinition(void) const
{
 G4DNAGenericIonsManager *instance;
 instance = G4DNAGenericIonsManager::Instance();
 
 return instance->GetIon("helium");
}
