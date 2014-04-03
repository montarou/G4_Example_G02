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
// $Id$
//
// Author: Mathieu Karamitros, kara@cenbg.in2p3.fr

// The code is developed in the framework of the ESA AO7146
//
// We would be very happy hearing from you, so do not hesitate to send us your feedback!
//
// In order for Geant4-DNA to be maintained and still open-source, article citations are crucial. 
// If you use Geant4-DNA chemistry and you publish papers about your software, in addition to the general paper on Geant4-DNA:
//
// The Geant4-DNA project, S. Incerti et al., Int. J. Model. Simul. Sci. Comput. 1 (2010) 157–178
//
// we ask that you please cite the following papers reference papers on chemistry:
//
// Diﬀusion-controlled reactions modelling in Geant4-DNA, M. Karamitros et al., 2014 (submitted)
// Modeling Radiation Chemistry in the Geant4 Toolkit, M. Karamitros et al., Prog. Nucl. Sci. Tec. 2 (2011) 503-508


#ifndef G4DNAWaterDissociationDisplacer_h
#define G4DNAWaterDissociationDisplacer_h 1

#include "G4VMolecularDissociationDisplacer.hh"

class G4DNAWaterDissociationDisplacer : public G4VMolecularDecayDisplacer
{
public :
    G4DNAWaterDissociationDisplacer();
    virtual ~G4DNAWaterDissociationDisplacer() ;

    virtual std::vector<G4ThreeVector> GetProductsDisplacement(const G4MolecularDissociationChannel*) const;
    virtual G4ThreeVector GetMotherMoleculeDisplacement(const G4MolecularDissociationChannel*) const;
    G4ThreeVector radialDistributionOfElectron() const;

#if defined G4EM_ALLOC_EXPORT
    G4DLLEXPORT static const DisplacementType Ionisation_DissociationDecay;
    G4DLLEXPORT static const DisplacementType A1B1_DissociationDecay;
    G4DLLEXPORT static const DisplacementType B1A1_DissociationDecay;
    G4DLLEXPORT static const DisplacementType AutoIonisation;
    G4DLLEXPORT static const DisplacementType DissociativeAttachment;
#else
    G4DLLIMPORT static const DisplacementType Ionisation_DissociationDecay;
    G4DLLIMPORT static const DisplacementType A1B1_DissociationDecay;
    G4DLLIMPORT static const DisplacementType B1A1_DissociationDecay;
    G4DLLIMPORT static const DisplacementType AutoIonisation;
    G4DLLIMPORT static const DisplacementType DissociativeAttachment;
#endif

private :
    G4ThreeVector radialDistributionOfProducts(G4double) const;
};
#endif

