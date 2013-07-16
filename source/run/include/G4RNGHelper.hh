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
// Helper class for RNG Engine seeds.
// Used in MT builds to guarantee reproducibility.
// The function of this class is to return a RNG Engine seed
// given its index. It is a simple templated container that
// Allows to add seeds (AddOneSeed) and retrieve a seed (GetSeed)
// by index.
//
// The normal use is with G4RNGHelper where each element of th econtainer
// represents a seed. To enforce strong-reproducibility the variant with
// the RNG Engine status file names is avilable

#ifndef G4RNGHELPER_HH
#define G4RNGHELPER_HH

#include "G4Types.hh"
#include <vector>
#include "globals.hh"

template <class T>
class G4TemplateRNGHelper {
private:
    static G4TemplateRNGHelper* instance;
public:
    // The container is modeled as a (shared) singleton
    static G4TemplateRNGHelper* GetInstance() {
        if (!instance) instance = new G4TemplateRNGHelper();
        return instance;
    }
    typedef std::vector<T> SeedsQueue;
    typedef typename SeedsQueue::size_type SeedsQueueSize_type;
        
    virtual ~G4TemplateRNGHelper() {
        Clear();
        instance = 0;
    }
    
    //Returns seed given id
    virtual const T GetSeed(const G4int& seedId ) {
        if ( seedId < static_cast<G4int>(seeds.size()) )
        {
            T& seed = seeds[seedId];
            return seed;
        }
        G4ExceptionDescription msg;
        msg << "No seed number "<<seedId<<"("<<seeds.size()<<" available)";
        G4Exception("G4RNGHelper::GetSeed","Run0035", JustWarning,msg);
        return T();
    }
    
    //Adds one seed to the collection
    void AddOneSeed( const T& seed ) { seeds.push_back(seed); }
    
    //Number of available seeds
    const SeedsQueueSize_type GetNumberSeeds() const { return seeds.size(); }
    
    //Empty the seeds container
    virtual void Clear() { seeds.clear(); }
protected:
    SeedsQueue seeds;
};


typedef G4TemplateRNGHelper<long> G4RNGHelper;
typedef G4TemplateRNGHelper<G4String> G4StringRNGHelper;

#endif