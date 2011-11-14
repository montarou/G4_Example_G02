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
//
// Author: Mathieu Karamitros (kara@cenbg.in2p3.fr)
//
// WARNING : This class is released as a prototype.
// It might strongly evolve or even disapear in the next releases.
//
// History:
// -----------
// 10 Oct 2011 M.Karamitros created
//
// -------------------------------------------------------------------

#include "G4DNAMolecularReaction.hh"
#include "G4DNAMolecularReactionTable.hh"
#include "G4VDNAReactionModel.hh"
#include "G4ITManager.hh"
#include "G4UnitsTable.hh"

using namespace std;

G4DNAMolecularReaction::G4DNAMolecularReaction():G4VITReactionProcess(),
    fMolReactionTable(reference_cast<const G4DNAMolecularReactionTable*>(fReactionTable))
{
    //ctor
    fVerbose = 0;
    fReactionModel = 0;
    R = -1;
    r = -1;
}

G4DNAMolecularReaction::~G4DNAMolecularReaction()
{
    //dtor
    if(fChanges) delete fChanges;
}

G4DNAMolecularReaction::G4DNAMolecularReaction(const G4DNAMolecularReaction& other):G4VITReactionProcess(other),
    fMolReactionTable(reference_cast<const G4DNAMolecularReactionTable*>(fReactionTable))
{
    //copy ctor
    fVerbose 	   = other.fVerbose ;
    fMolReactionTable = other.fMolReactionTable;
    fReactionModel = 0;
    R = -1;
    r = -1;
}

G4DNAMolecularReaction& G4DNAMolecularReaction::operator=(const G4DNAMolecularReaction& rhs)
{
    if (this == &rhs) return *this; // handle self assignment

    fVerbose 	   = rhs.fVerbose ;
    fMolReactionTable = rhs.fMolReactionTable;
    R = -1;
    r = -1;

    //assignment operator
    return *this;
}

G4bool G4DNAMolecularReaction::TestReactibility(const G4Track& trackA,
                                                const G4Track& trackB,
                                                const double /*stepTime*/,
                                                const bool userStepTimeLimit) /*const*/
{
    // DEBUG
    //    G4cout << "G4DNAMolecularReaction::TestReactibility" << G4endl;
    G4Molecule* moleculeA = GetMolecule(trackA);
    G4Molecule* moleculeB = GetMolecule(trackB);

    if(!fReactionModel)
    {
        G4ExceptionDescription exceptionDescription ("You have to give a reaction model to the molecular reaction process");
        G4Exception("G4DNAMolecularReaction::TestReactibility","MolecularReaction001",
                    FatalErrorInArgument,exceptionDescription);
        return false; // makes coverity happy
    }
    if(fMolReactionTable==0)
    {
        G4ExceptionDescription exceptionDescription ("You have to give a reaction table to the molecular reaction process");
        G4Exception("G4DNAMolecularReaction::TestReactibility","MolecularReaction002",
                    FatalErrorInArgument,exceptionDescription);
        return false; // makes coverity happy
    }

    // Retrieve reaction range
    R = -1 ; // reaction Range
    R = fReactionModel -> GetReactionRadius(moleculeA, moleculeB);

    r = -1 ; // separation distance

    G4bool output = (fReactionModel->FindReaction(trackA, trackB, R, r, userStepTimeLimit));

    //    DEBUG
#ifdef G4VERBOSE
    if(fVerbose>3)
    {
        G4cout <<"\033[1;39;36m" << "G4MolecularReaction "<< G4endl;
        G4cout << "FindReaction returned : " << G4BestUnit(output,"Length") << G4endl;
        G4cout <<" reaction radius : " << G4BestUnit(R,"Length")
              << " real distance : " << G4BestUnit((trackA.GetPosition() - trackB.GetPosition()).mag(), "Length")
              << " calculated distance by model (= -1 if real distance > reaction radius and the user limitation step is not reached) : "
              << G4BestUnit(r,"Length")
              << G4endl;
        G4cout
                << "TrackID A : " << trackA.GetTrackID()
                << ", TrackID B : " << trackB.GetTrackID()
                << " | MolA " << moleculeA->GetName()
                << ", MolB " << moleculeB->GetName()
                <<"\033[0m\n"
               << G4endl;
        G4cout << "--------------------------------------------" << G4endl;
    }
#endif
    return output ;
}


G4ITReactionChange* G4DNAMolecularReaction::MakeReaction(const G4Track& trackA, const G4Track& trackB)
{
    fChanges = new G4ITReactionChange();
    fChanges->Initialize(trackA, trackB);

    G4Molecule* moleculeA = GetMolecule(trackA);
    G4Molecule* moleculeB = GetMolecule(trackB);
    //__________________________________________________________________
    //  For DEBUG
#ifdef G4VERBOSE

    //      DEBUG
    //        // Print Reaction :
    //        G4cout << "Reaction : " << moleculeA->GetName()
    //        <<  " + "
    //        << moleculeB->GetName();


    // DEBUG
    if(fVerbose>3)
    {
        G4cout << "G4DNAMolecularReaction::MakeReaction" << G4endl;
        G4cout<<"trackA n°"<<trackA.GetTrackID()
             <<"\t | track B n°" << trackB.GetTrackID() << G4endl;

        G4cout<<"Track A : Position : "<< G4BestUnit(trackA.GetPosition(),"Length")
             <<"\t Global Time : "<< G4BestUnit(trackA.GetGlobalTime(), "Time")<< G4endl;

        G4cout<<"Track B : Position : "<< G4BestUnit(trackB.GetPosition() ,"Length")
             <<"\t Global Time : "<< G4BestUnit(trackB.GetGlobalTime(), "Time")<< G4endl;

        G4cout<<"Reaction range : " << G4BestUnit(R,"Length")
             << " \t Separation distance : " << G4BestUnit(r,"Length")<< G4endl;
        G4cout << "--------------------------------------------" << G4endl;
    }
#endif
    //__________________________________________________________________

    const G4DNAMolecularReactionData* reactionData =  fMolReactionTable->GetReactionData(moleculeA, moleculeB);

    G4int nbProducts = reactionData->GetNbProducts();

    if (nbProducts)
    {

        //      DEBUG
        //        if(fVerbose)
        //        {
        //            G4cout<<" -> ";
        //        }

        for (G4int j=0 ; j < nbProducts; j++)
        {
            G4Molecule* product = new G4Molecule(*reactionData->GetProduct(j));

            //            DEBUG
            //            if(fVerbose)
            //            {
            //                if (j!=0) G4cout<<" + ";
            //                G4cout<< product-> GetName() ;
            //            }

            G4Track* productTrack = product->BuildTrack(trackA.GetGlobalTime(),
                                                        (moleculeA->GetMass()*trackA.GetPosition()
                                                         +moleculeB->GetMass()*trackB.GetPosition())/
                                                        (moleculeA->GetMass()+moleculeB->GetMass()) );

            productTrack->SetTrackStatus(fAlive);

            fChanges->AddSecondary(productTrack);
            G4ITManager<G4Molecule>::Instance()->Push(productTrack);
        }
    }

    fChanges->KillParents(true);

    //    DEBUG
    //  G4cout<<G4endl;
    return fChanges;
}