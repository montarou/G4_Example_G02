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

#ifndef G4MOLECULEITERATOR_HH_
#define G4MOLECULEITERATOR_HH_

#include <map>

template<typename MOLECULE>
class G4MoleculeIterator
{
protected :
	typedef std::map<G4String, MOLECULE*> MAP;
	MAP* fMap;
	G4bool fDefined;
	typename MAP::iterator fIt;

public:
	G4MoleculeIterator(MAP& _map) : fMap(&_map) {
		fDefined = false;
	}

	virtual ~G4MoleculeIterator()
	{

	}

	G4MoleculeIterator(const G4MoleculeIterator& right)
	{
		fMap = right.fMap;
		fDefined = right.fDefined;
		fIt = right.fIt;
	}

	G4MoleculeIterator& operator=(const G4MoleculeIterator& right)
	{
		if(this == &right) return *this;
		fMap = right.fMap;
		fDefined = right.fDefined;
		fIt = right.fIt;
		return *this;
	}


	G4bool operator++ (int) {
		if(!fDefined) return false;
		fIt++;
		return fIt != fMap->end() ? true : false;
	}


	G4bool operator++ () {
		if(!fDefined) return false;
		fIt++;
		return fIt != fMap->end() ? true : false;
	}

	void reset()
	{
		fDefined=false;
	}

	G4bool operator()()
	{
		if(fDefined == false)
		{
			fDefined = true;
			fIt=fMap->begin();
			return true;
		}
		else
		{
			fIt++;
		}
		if(fIt == fMap->end()) return false;
		return true;
	}

	const G4String& Name()
	{
		return fIt->first;
	}

	MOLECULE* value()
	{
		return fIt->second;
	}
};

#endif /* G4MOLECULEITERATOR_HH_ */