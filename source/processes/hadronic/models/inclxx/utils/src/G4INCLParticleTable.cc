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
// INCL++ intra-nuclear cascade model
// Pekka Kaitaniemi, CEA and Helsinki Institute of Physics
// Davide Mancusi, CEA
// Alain Boudard, CEA
// Sylvie Leray, CEA
// Joseph Cugnon, University of Liege
//
#define INCLXX_IN_GEANT4_MODE 1

#include "globals.hh"

#include "G4INCLParticleTable.hh"
#include <algorithm>
// #include <cassert>
#include <cmath>
#include <cctype>
#include <sstream>
#ifdef INCLXX_IN_GEANT4_MODE
#include "G4SystemOfUnits.hh"
#endif

#ifdef INCLXX_IN_GEANT4_MODE
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#endif

namespace G4INCL {

  namespace ParticleTable {

    namespace {

      /// \brief Static instance of the NaturalIsotopicAbundances class
      const NaturalIsotopicDistributions *theNaturalIsotopicDistributions = NULL;

      const G4double theINCLNucleonMass = 938.2796;
      const G4double theINCLPionMass = 138.0;
      G4ThreadLocal G4double protonMass = 0.0;
      G4ThreadLocal G4double neutronMass = 0.0;
      G4ThreadLocal G4double piPlusMass = 0.0;
      G4ThreadLocal G4double piMinusMass = 0.0;
      G4ThreadLocal G4double piZeroMass = 0.0;

      // Hard-coded values of the real particle masses (MeV/c^2)
      G4ThreadLocal G4double theRealProtonMass = 938.27203;
      G4ThreadLocal G4double theRealNeutronMass = 939.56536;
      G4ThreadLocal G4double theRealChargedPiMass = 139.57018;
      G4ThreadLocal G4double theRealPiZeroMass = 134.9766;

      const G4int mediumNucleiTableSize = 30;

      const G4double mediumDiffuseness[mediumNucleiTableSize] =
      {0.0,0.0,0.0,0.0,0.0,1.78,1.77,1.77,1.77,1.71,
        1.69,1.69,1.635,1.730,1.81,1.833,1.798,
        1.841,0.567,0.571, 0.560,0.549,0.550,0.551,
        0.580,0.575,0.569,0.537,0.0,0.0};
      const G4double mediumRadius[mediumNucleiTableSize] =
      {0.0,0.0,0.0,0.0,0.0,0.334,0.327,0.479,0.631,0.838,
        0.811,1.07,1.403,1.335,1.25,1.544,1.498,1.513,
        2.58,2.77, 2.775,2.78,2.88,2.98,3.22,3.03,2.84,
        3.14,0.0,0.0};

      const G4double positionRMS[clusterTableZSize][clusterTableASize] = {
        /*     A=   0     1     2     3     4     5     6     7     8     9    10    11    12 */
        /* Z=0 */ {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0},
        /* Z=1 */ {-1.0, -1.0, 2.10, 1.80, 1.70, 1.83, 2.60, 2.50, -1.0, -1.0, -1.0, -1.0, -1.0},
        /* Z=2 */ {-1.0, -1.0, -1.0, 1.80, 1.68, 1.70, 2.60, 2.50, 2.50, 2.50, 2.50, -1.0, -1.0},
        /* Z=3 */ {-1.0, -1.0, -1.0, -1.0, 1.70, 1.83, 2.56, 2.40, 2.50, 2.50, 2.50, 2.50, 2.50},
        /* Z=4 */ {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, 2.60, 2.50, 2.50, 2.51, 2.50, 2.50, 2.50},
        /* Z=5 */ {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, 2.50, 2.50, 2.50, 2.50, 2.45, 2.40, 2.50},
        /* Z=6 */ {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, 2.50, 2.50, 2.50, 2.50, 2.47},
        /* Z=7 */ {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, 2.50, 2.50, 2.50},
        /* Z=8 */ {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, 2.50}
      };

      const G4double momentumRMS[clusterTableZSize][clusterTableASize] = {
        /*     A=   0     1     2     3     4     5     6     7     8     9    10    11    12 */
        /* Z=0 */ {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0},
        /* Z=1 */ {-1.0, -1.0, 77.0, 110., 153., 100., 100., 100., -1.0, -1.0, -1.0, -1.0, -1.0},
        /* Z=2 */ {-1.0, -1.0, -1.0, 110., 153., 100., 100., 100., 100., 100., 100., -1.0, -1.0},
        /* Z=3 */ {-1.0, -1.0, -1.0, -1.0, 153., 100., 100., 100., 100., 100., 100., 100., 100.},
        /* Z=4 */ {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, 100., 100., 100., 100., 100., 100., 100.},
        /* Z=5 */ {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, 100., 100., 100., 100., 100., 100., 100.},
        /* Z=6 */ {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, 100., 100., 100., 100., 100.},
        /* Z=7 */ {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, 100., 100., 100.},
        /* Z=8 */ {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, 100.}
      };

      const G4int elementTableSize = 113; // up to Cn

      /// \brief Table of chemical element names
      const std::string elementTable[elementTableSize] = {
        "",
        "H",
        "He",
        "Li",
        "Be",
        "B",
        "C",
        "N",
        "O",
        "F",
        "Ne",
        "Na",
        "Mg",
        "Al",
        "Si",
        "P",
        "S",
        "Cl",
        "Ar",
        "K",
        "Ca",
        "Sc",
        "Ti",
        "V",
        "Cr",
        "Mn",
        "Fe",
        "Co",
        "Ni",
        "Cu",
        "Zn",
        "Ga",
        "Ge",
        "As",
        "Se",
        "Br",
        "Kr",
        "Rb",
        "Sr",
        "Y",
        "Zr",
        "Nb",
        "Mo",
        "Tc",
        "Ru",
        "Rh",
        "Pd",
        "Ag",
        "Cd",
        "In",
        "Sn",
        "Sb",
        "Te",
        "I",
        "Xe",
        "Cs",
        "Ba",
        "La",
        "Ce",
        "Pr",
        "Nd",
        "Pm",
        "Sm",
        "Eu",
        "Gd",
        "Tb",
        "Dy",
        "Ho",
        "Er",
        "Tm",
        "Yb",
        "Lu",
        "Hf",
        "Ta",
        "W",
        "Re",
        "Os",
        "Ir",
        "Pt",
        "Au",
        "Hg",
        "Tl",
        "Pb",
        "Bi",
        "Po",
        "At",
        "Rn",
        "Fr",
        "Ra",
        "Ac",
        "Th",
        "Pa",
        "U",
        "Np",
        "Pu",
        "Am",
        "Cm",
        "Bk",
        "Cf",
        "Es",
        "Fm",
        "Md",
        "No",
        "Lr",
        "Rf",
        "Db",
        "Sg",
        "Bh",
        "Hs",
        "Mt",
        "Ds",
        "Rg",
        "Cn"
      };

      /// \brief Digit names to compose IUPAC element names
      const std::string elementIUPACDigits = "nubtqphsoe";

#define INCL_DEFAULT_SEPARATION_ENERGY 6.83
      const G4double theINCLProtonSeparationEnergy = INCL_DEFAULT_SEPARATION_ENERGY;
      const G4double theINCLNeutronSeparationEnergy = INCL_DEFAULT_SEPARATION_ENERGY;
      G4ThreadLocal G4double protonSeparationEnergy = INCL_DEFAULT_SEPARATION_ENERGY;
      G4ThreadLocal G4double neutronSeparationEnergy = INCL_DEFAULT_SEPARATION_ENERGY;
#undef INCL_DEFAULT_SEPARATION_ENERGY

      G4ThreadLocal G4double rpCorrelationCoefficient[UnknownParticle];

      G4ThreadLocal G4double neutronSkinThickness = 0.0;
      G4ThreadLocal G4double neutronSkinAdditionalDiffuseness = 0.0;

#ifdef INCLXX_IN_GEANT4_MODE
      G4ThreadLocal G4IonTable *theG4IonTable;
#else
      std::vector< std::vector <G4bool> > massTableMask;
      std::vector< std::vector <G4double> > massTable;
#endif

#ifndef INCLXX_IN_GEANT4_MODE
      /// \brief Read nuclear masses from a data file
      void readRealMasses(std::string const &path);
#endif

      /// \brief Transform a IUPAC char to an char representing an integer digit
      char iupacToInt(char c) {
        return (char)(((G4int)'0')+elementIUPACDigits.find(c));
      }

      /// \brief Transform an integer digit (represented by a char) to a IUPAC char
      char intToIUPAC(char n) { return elementIUPACDigits.at(n); }

#ifndef INCLXX_IN_GEANT4_MODE
      void readRealMasses(std::string const &path) {
        // Clear the existing tables, if any
        massTableMask.clear();
        massTable.clear();

        // File name
        std::string fileName(path + "/walletlifetime.dat");
        INCL_DEBUG("Reading real nuclear masses from file " << fileName << std::endl);

        // Open the file stream
        std::ifstream massTableIn(fileName.c_str());
        if(!massTableIn.good()) {
          std::cerr << "Cannot open " << fileName << " data file." << std::endl;
          std::abort();
          return;
        }

        // Read in the data
        unsigned int Z, A;
        const G4double amu = 931.494061; // atomic mass unit in MeV/c^2
        const G4double eMass = 0.5109988; // electron mass in MeV/c^2
        G4double excess;
        massTableIn >> A >> Z >> excess;
        do {
          // Dynamically determine the table size
          if(Z>=massTable.size()) {
            massTable.resize(Z+1);
            massTableMask.resize(Z+1);
          }
          if(A>=massTable[Z].size()) {
            massTable[Z].resize(A+1, 0.);
            massTableMask[Z].resize(A+1, false);
          }

          massTable.at(Z).at(A) = A*amu + excess - Z*eMass;
          massTableMask.at(Z).at(A) = true;

          massTableIn >> A >> Z >> excess;
        } while(massTableIn.good());

      }
#endif

      /// \brief Get the singleton instance of the natural isotopic distributions
      const NaturalIsotopicDistributions *getNaturalIsotopicDistributions() {
        if(!theNaturalIsotopicDistributions)
          theNaturalIsotopicDistributions = new NaturalIsotopicDistributions;
        return theNaturalIsotopicDistributions;
      }

    } // namespace

    void initialize(Config const * const theConfig /*=0*/) {
      protonMass = theINCLNucleonMass;
      neutronMass = theINCLNucleonMass;
      piPlusMass = theINCLPionMass;
      piMinusMass = theINCLPionMass;
      piZeroMass = theINCLPionMass;

#ifndef INCLXX_IN_GEANT4_MODE
      std::string dataFilePath;
      if(theConfig)
        dataFilePath = theConfig->getINCLXXDataFilePath();
      readRealMasses(dataFilePath);
#endif

      if(theConfig && theConfig->getUseRealMasses()) {
        getTableMass = getRealMass;
        getTableParticleMass = getRealMass;
      } else {
        getTableMass = getINCLMass;
        getTableParticleMass = getINCLMass;
      }
#ifdef INCLXX_IN_GEANT4_MODE
      G4ParticleTable *theG4ParticleTable = G4ParticleTable::GetParticleTable();
      theG4IonTable = theG4ParticleTable->GetIonTable();
      theRealProtonMass = theG4ParticleTable->FindParticle("proton")->GetPDGMass() / MeV;
      theRealNeutronMass = theG4ParticleTable->FindParticle("neutron")->GetPDGMass() / MeV;
      theRealChargedPiMass = theG4ParticleTable->FindParticle("pi+")->GetPDGMass() / MeV;
      theRealPiZeroMass = theG4ParticleTable->FindParticle("pi0")->GetPDGMass() / MeV;
#endif

      effectiveDeltaDecayThreshold = theRealNeutronMass + theRealChargedPiMass + 0.5;

      // Initialise the separation-energy function
      if(!theConfig || theConfig->getSeparationEnergyType()==INCLSeparationEnergy)
        getSeparationEnergy = getSeparationEnergyINCL;
      else if(theConfig->getSeparationEnergyType()==RealSeparationEnergy)
        getSeparationEnergy = getSeparationEnergyReal;
      else if(theConfig->getSeparationEnergyType()==RealForLightSeparationEnergy)
        getSeparationEnergy = getSeparationEnergyRealForLight;
      else {
        INCL_FATAL("Unrecognized separation-energy type in ParticleTable initialization: " << theConfig->getSeparationEnergyType() << std::endl);
        std::abort();
        return;
      }

      // Initialise the Fermi-momentum function
      if(!theConfig || theConfig->getFermiMomentumType()==ConstantFermiMomentum)
        getFermiMomentum = ParticleTable::getFermiMomentumConstant;
      else if(theConfig->getFermiMomentumType()==ConstantLightFermiMomentum)
        getFermiMomentum = ParticleTable::getFermiMomentumConstantLight;
      else if(theConfig->getFermiMomentumType()==MassDependentFermiMomentum)
        getFermiMomentum = ParticleTable::getFermiMomentumMassDependent;
      else {
        INCL_FATAL("Unrecognized Fermi-momentum type in ParticleTable initialization: " << theConfig->getFermiMomentumType() << std::endl);
        std::abort();
        return;
      }

      // Initialise the r-p correlation coefficients
      std::fill(rpCorrelationCoefficient, rpCorrelationCoefficient + UnknownParticle, 1.);
      if(theConfig) {
        rpCorrelationCoefficient[Proton] = theConfig->getRPCorrelationCoefficient(Proton);
        rpCorrelationCoefficient[Neutron] = theConfig->getRPCorrelationCoefficient(Neutron);
      }

      // Initialise the neutron-skin parameters
      if(theConfig) {
        neutronSkinThickness = theConfig->getNeutronSkinThickness();
        neutronSkinAdditionalDiffuseness = theConfig->getNeutronSkinAdditionalDiffuseness();
      }

    }

    G4int getIsospin(const ParticleType t) {
      // Actually this is the 3rd component of isospin (I_z) multiplied by 2!
      if(t == Proton) {
        return 1;
      } else if(t == Neutron) {
        return -1;
      } else if(t == PiPlus) {
        return 2;
      } else if(t == PiMinus) {
        return -2;
      } else if(t == PiZero) {
        return 0;
      } else if(t == DeltaPlusPlus) {
        return 3;
      } else if(t == DeltaPlus) {
        return 1;
      } else if(t == DeltaZero) {
        return -1;
      } else if(t == DeltaMinus) {
        return -3;
      }

      INCL_ERROR("Requested isospin of an unknown particle!");
      return -10; // Unknown
    }

    std::string getShortName(const ParticleSpecies &s) {
      if(s.theType==Composite)
        return getShortName(s.theA,s.theZ);
      else
        return getShortName(s.theType);
    }

    std::string getName(const ParticleSpecies &s) {
      if(s.theType==Composite)
        return getName(s.theA,s.theZ);
      else
        return getName(s.theType);
    }

    std::string getName(const G4int A, const G4int Z) {
      std::stringstream stream;
      stream << getElementName(Z) << "-" << A;
      return stream.str();
    }

    std::string getShortName(const G4int A, const G4int Z) {
      std::stringstream stream;
      stream << getElementName(Z);
      if(A>0)
        stream << A;
      return stream.str();
    }

    std::string getName(const ParticleType p) {
      if(p == G4INCL::Proton) {
        return std::string("proton");
      } else if(p == G4INCL::Neutron) {
        return std::string("neutron");
      } else if(p == G4INCL::DeltaPlusPlus) {
        return std::string("delta++");
      } else if(p == G4INCL::DeltaPlus) {
        return std::string("delta+");
      } else if(p == G4INCL::DeltaZero) {
        return std::string("delta0");
      } else if(p == G4INCL::DeltaMinus) {
        return std::string("delta-");
      } else if(p == G4INCL::PiPlus) {
        return std::string("pi+");
      } else if(p == G4INCL::PiZero) {
        return std::string("pi0");
      } else if(p == G4INCL::PiMinus) {
        return std::string("pi-");
      } else if(p == G4INCL::Composite) {
        return std::string("composite");
      }
      return std::string("unknown");
    }

    std::string getShortName(const ParticleType p) {
      if(p == G4INCL::Proton) {
        return std::string("p");
      } else if(p == G4INCL::Neutron) {
        return std::string("n");
      } else if(p == G4INCL::DeltaPlusPlus) {
        return std::string("d++");
      } else if(p == G4INCL::DeltaPlus) {
        return std::string("d+");
      } else if(p == G4INCL::DeltaZero) {
        return std::string("d0");
      } else if(p == G4INCL::DeltaMinus) {
        return std::string("d-");
      } else if(p == G4INCL::PiPlus) {
        return std::string("pi+");
      } else if(p == G4INCL::PiZero) {
        return std::string("pi0");
      } else if(p == G4INCL::PiMinus) {
        return std::string("pi-");
      } else if(p == G4INCL::Composite) {
        return std::string("comp");
      }
      return std::string("unknown");
    }

    G4double getINCLMass(const ParticleType pt) {
      if(pt == Proton) {
        return protonMass;
      } else if(pt == Neutron) {
        return neutronMass;
      } else if(pt == PiPlus) {
        return piPlusMass;
      } else if(pt == PiMinus) {
        return piMinusMass;
      } else if(pt == PiZero) {
        return piZeroMass;
      } else {
        INCL_ERROR("getMass : Unknown particle type." << std::endl);
        return 0.0;
      }
    }

    G4double getRealMass(const ParticleType t) {
      switch(t) {
        case Proton:
          return theRealProtonMass;
          break;
        case Neutron:
          return theRealNeutronMass;
          break;
        case PiPlus:
        case PiMinus:
          return theRealChargedPiMass;
          break;
        case PiZero:
          return theRealPiZeroMass;
          break;
        default:
          INCL_ERROR("Particle::getRealMass : Unknown particle type." << std::endl);
          return 0.0;
          break;
      }
    }

    G4double getRealMass(const G4int A, const G4int Z) {
// assert(A>=0);
      // For nuclei with Z<0 or Z>A, assume that the exotic charge state is due to pions
      if(Z<0)
        return A*neutronMass - Z*getRealMass(PiMinus);
      else if(Z>A)
        return A*protonMass + (A-Z)*getRealMass(PiPlus);
      else if(Z==0)
        return A*getRealMass(Neutron);
      else if(A==Z)
        return A*getRealMass(Proton);
      else if(A>1) {
#ifndef INCLXX_IN_GEANT4_MODE
        if(hasMassTable(A,Z))
          return massTable.at(Z).at(A);
        else {
          INCL_DEBUG("Real mass unavailable for isotope A=" << A << ", Z=" << Z
                << ", using Weizsaecker's formula"
                << std::endl);
          return getWeizsaeckerMass(A,Z);
        }
#else
        return theG4IonTable->GetNucleusMass(Z,A) / MeV;
#endif
      } else
        return 0.;
    }

    G4double getINCLMass(const G4int A, const G4int Z) {
// assert(A>=0);
      // For nuclei with Z<0 or Z>A, assume that the exotic charge state is due to pions
      if(Z<0)
        return A*neutronMass - Z*getINCLMass(PiMinus);
      else if(Z>A)
        return A*protonMass + (A-Z)*getINCLMass(PiPlus);
      else if(A>1)
        return Z*(protonMass - protonSeparationEnergy) + (A-Z)*(neutronMass - neutronSeparationEnergy);
      else if(A==1 && Z==0)
        return getINCLMass(Neutron);
      else if(A==1 && Z==1)
        return getINCLMass(Proton);
      else
        return 0.;
    }

#ifndef INCLXX_IN_GEANT4_MODE
    G4double hasMassTable(const unsigned int A, const unsigned int Z) {
      return ( Z > 0 && A > 0
          && Z < massTableMask.size() && A < massTableMask.at(Z).size()
          && massTableMask.at(Z).at(A));
    }

    G4double getWeizsaeckerMass(const G4int A, const G4int Z) {
      const G4int Npairing = (A-Z)%2;                  // pairing
      const G4int Zpairing = Z%2;
      const G4double fA = (G4double) A;
      const G4double fZ = (G4double) Z;
      G4double binding =
        - 15.67*fA                          // nuclear volume
        + 17.23*Math::pow23(fA)                // surface energy
        + 93.15*((fA/2.-fZ)*(fA/2.-fZ))/fA       // asymmetry
        + 0.6984523*fZ*fZ*Math::powMinus13(fA);      // coulomb
      if( Npairing == Zpairing ) binding += (Npairing+Zpairing-1) * 12.0 / std::sqrt(fA);  // pairing

      return fZ*getRealMass(Proton)+((G4double)(A-Z))*getRealMass(Neutron)+binding;
    }
#endif

    G4double getTableQValue(const G4int A1, const G4int Z1, const G4int A2, const G4int Z2) {
      return getTableMass(A1,Z1) + getTableMass(A2,Z2) - getTableMass(A1+A2,Z1+Z2);
    }

    G4double getTableQValue(const G4int A1, const G4int Z1, const G4int A2, const G4int Z2, const G4int A3, const G4int Z3) {
      return getTableMass(A1,Z1) + getTableMass(A2,Z2) - getTableMass(A3,Z3) - getTableMass(A1+A2-A3,Z1+Z2-Z3);
    }

    G4double getTableSpeciesMass(const ParticleSpecies &p) {
      if(p.theType == Composite)
        return (*getTableMass)(p.theA, p.theZ);
      else
        return (*getTableParticleMass)(p.theType);
    }

    G4int getMassNumber(const ParticleType t) {
      switch(t) {
        case Proton:
        case Neutron:
        case DeltaPlusPlus:
        case DeltaPlus:
        case DeltaZero:
        case DeltaMinus:
          return 1;
          break;
        case PiPlus:
        case PiMinus:
        case PiZero:
          return 0;
          break;
        default:
          return 0;
          break;
      }
    }

    G4int getChargeNumber(const ParticleType t) {
      switch(t) {
        case DeltaPlusPlus:
          return 2;
          break;
        case Proton:
        case DeltaPlus:
        case PiPlus:
          return 1;
          break;
        case Neutron:
        case DeltaZero:
        case PiZero:
          return 0;
          break;
        case DeltaMinus:
        case PiMinus:
          return -1;
          break;
        default:
          return 0;
          break;
      }
    }

    G4double getNuclearRadius(const ParticleType t, const G4int A, const G4int Z) {
// assert(A>0 && Z>=0 && Z<=A);
      if(A >= 19 || (A < 6 && A >= 2)) {
        // For large (Woods-Saxon or Modified Harmonic Oscillator) or small
        // (Gaussian) nuclei, the radius parameter is just the nuclear radius
        return getRadiusParameter(t,A,Z);
      } else if(A < clusterTableASize && Z < clusterTableZSize && A >= 6) {
        const G4double thisRMS = positionRMS[Z][A];
        if(thisRMS>0.0)
          return thisRMS;
        else {
          INCL_DEBUG("getNuclearRadius: Radius for nucleus A = " << A << " Z = " << Z << " is not available" << std::endl
                     << "returning radius for C12");
          return positionRMS[6][12];
        }
      } else if(A < 19) {
        const G4double theRadiusParameter = getRadiusParameter(t, A, Z);
        const G4double theDiffusenessParameter = getSurfaceDiffuseness(t, A, Z);
        // The formula yields the nuclear RMS radius based on the parameters of
        // the nuclear-density function
        return 1.581*theDiffusenessParameter*
          (2.+5.*theRadiusParameter)/(2.+3.*theRadiusParameter);
      } else {
        INCL_ERROR("getNuclearRadius: No radius for nucleus A = " << A << " Z = " << Z << std::endl);
        return 0.0;
      }
    }

    G4double getLargestNuclearRadius(const G4int A, const G4int Z) {
      return Math::max(getNuclearRadius(Proton, A, Z), getNuclearRadius(Neutron, A, Z));
    }

    G4double getRadiusParameter(const ParticleType t, const G4int A, const G4int Z) {
// assert(A>0 && Z>=0 && Z<=A);
      if(A >= 28) {
        // phenomenological radius fit
        G4double r0 = (2.745e-4 * A + 1.063) * std::pow(A, 1.0/3.0);
        if(t==Neutron)
          r0 += neutronSkinThickness;
        return r0;
      } else if(A < 6 && A >= 2) {
        if(Z<clusterTableZSize) {
          const G4double thisRMS = positionRMS[Z][A];
          if(thisRMS>0.0)
            return thisRMS;
          else {
            INCL_DEBUG("getRadiusParameter: Radius for nucleus A = " << A << " Z = " << Z << " is not available" << std::endl
                       << "returning radius for C12");
            return positionRMS[6][12];
          }
        } else {
          INCL_DEBUG("getRadiusParameter: Radius for nucleus A = " << A << " Z = " << Z << " is not available" << std::endl
                     << "returning radius for C12");
          return positionRMS[6][12];
        }
      } else if(A < 28 && A >= 6) {
        return mediumRadius[A-1];
        //      return 1.581*mediumDiffuseness[A-1]*(2.+5.*mediumRadius[A-1])/(2.+3.*mediumRadius[A-1]);
      } else {
        INCL_ERROR("getRadiusParameter: No radius for nucleus A = " << A << " Z = " << Z << std::endl);
        return 0.0;
      }
    }

    G4double getMaximumNuclearRadius(const ParticleType t, const G4int A, const G4int Z) {
      const G4double XFOISA = 8.0;
      if(A >= 19) {
        return getNuclearRadius(t,A,Z) + XFOISA * getSurfaceDiffuseness(t,A,Z);
      } else if(A < 19 && A >= 6) {
        return 5.5 + 0.3 * (G4double(A) - 6.0)/12.0;
      } else if(A >= 2) {
        return getNuclearRadius(t, A, Z) + 4.5;
      } else {
        INCL_ERROR("getMaximumNuclearRadius : No maximum radius for nucleus A = " << A << " Z = " << Z << std::endl);
        return 0.0;
      }
    }

    G4double getSurfaceDiffuseness(const ParticleType t, const G4int A, const G4int Z) {
      if(A >= 28) {
        G4double a = 1.63e-4 * A + 0.510;
        if(t==Neutron)
          a += neutronSkinAdditionalDiffuseness;
        return a;
      } else if(A < 28 && A >= 19) {
        return mediumDiffuseness[A-1];
      } else if(A < 19 && A >= 6) {
        return mediumDiffuseness[A-1];
      } else if(A < 6 && A >= 2) {
        INCL_ERROR("getSurfaceDiffuseness: was called for A = " << A << " Z = " << Z << std::endl);
        return 0.0;
      } else {
        INCL_ERROR("getSurfaceDiffuseness: No diffuseness for nucleus A = " << A << " Z = " << Z << std::endl);
        return 0.0;
      }
    }

    G4double getMomentumRMS(const G4int A, const G4int Z) {
// assert(Z>=0 && A>=0 && Z<=A);
      return getFermiMomentum(A,Z) * Math::sqrtThreeFifths;
    }

    G4double getSeparationEnergyINCL(const ParticleType t, const G4int /*A*/, const G4int /*Z*/) {
      if(t==Proton)
        return theINCLProtonSeparationEnergy;
      else if(t==Neutron)
        return theINCLNeutronSeparationEnergy;
      else {
        INCL_ERROR("ParticleTable::getSeparationEnergyINCL : Unknown particle type." << std::endl);
        return 0.0;
      }
    }

    G4double getSeparationEnergyReal(const ParticleType t, const G4int A, const G4int Z) {
      // Real separation energies for all nuclei
      if(t==Proton)
        return (*getTableParticleMass)(Proton) + (*getTableMass)(A-1,Z-1) - (*getTableMass)(A,Z);
      else if(t==Neutron)
        return (*getTableParticleMass)(Neutron) + (*getTableMass)(A-1,Z) - (*getTableMass)(A,Z);
      else {
        INCL_ERROR("ParticleTable::getSeparationEnergyReal : Unknown particle type." << std::endl);
        return 0.0;
      }
    }

    G4double getSeparationEnergyRealForLight(const ParticleType t, const G4int A, const G4int Z) {
      // Real separation energies for light nuclei, fixed values for heavy nuclei
      if(Z<clusterTableZSize && A<clusterTableASize)
        return getSeparationEnergyReal(t, A, Z);
      else
        return getSeparationEnergyINCL(t, A, Z);
    }

    G4double getProtonSeparationEnergy() { return protonSeparationEnergy; }

    G4double getNeutronSeparationEnergy() { return neutronSeparationEnergy; }

    void setProtonSeparationEnergy(const G4double s) { protonSeparationEnergy = s; }

    void setNeutronSeparationEnergy(const G4double s) { neutronSeparationEnergy  = s; }

    std::string getElementName(const G4int Z) {
      if(Z<1) {
        INCL_WARN("getElementName called with Z<1" << std::endl);
        return elementTable[0];
      } else if(Z<elementTableSize)
        return elementTable[Z];
      else
        return getIUPACElementName(Z);
    }

    std::string getIUPACElementName(const G4int Z) {
      std::stringstream elementStream;
      elementStream << Z;
      std::string elementName = elementStream.str();
      std::transform(elementName.begin(), elementName.end(), elementName.begin(), intToIUPAC);
      elementName[0] = std::toupper(elementName.at(0));
      return elementName;
    }

    G4int parseElement(std::string pS) {
      // Normalize the element name
      std::transform(pS.begin(), pS.end(), pS.begin(), ::tolower);
      pS[0] = ::toupper(pS[0]);

      const std::string *iter = std::find(elementTable, elementTable+elementTableSize, pS);
      if(iter != elementTable+elementTableSize)
        return iter - elementTable;
      else
        return ParticleTable::parseIUPACElement(pS);
    }

    G4int parseIUPACElement(std::string const &s) {
      // Normalise to lower case
      std::string elementName(s);
      std::transform(elementName.begin(), elementName.end(), elementName.begin(), ::tolower);
      // Return 0 if the element name contains anything but IUPAC digits
      if(elementName.find_first_not_of(elementIUPACDigits)!=std::string::npos)
        return 0;
      std::transform(elementName.begin(), elementName.end(), elementName.begin(), iupacToInt);
      std::stringstream elementStream(elementName);
      G4int Z;
      elementStream >> Z;
      return Z;
    }

    IsotopicDistribution const &getNaturalIsotopicDistribution(const G4int Z) {
      return getNaturalIsotopicDistributions()->getIsotopicDistribution(Z);
    }

    G4int drawRandomNaturalIsotope(const G4int Z) {
      return getNaturalIsotopicDistributions()->drawRandomIsotope(Z);
    }

    G4double getFermiMomentumConstant(const G4int /*A*/, const G4int /*Z*/) {
      return PhysicalConstants::Pf;
    }

    G4double getFermiMomentumConstantLight(const G4int A, const G4int Z) {
// assert(Z>0 && A>0 && Z<=A);
      if(Z<clusterTableZSize && A<clusterTableASize) {
        const G4double rms = momentumRMS[Z][A];
        return ((rms>0.) ? rms : momentumRMS[6][12]) * Math::sqrtFiveThirds;
      } else
        return getFermiMomentumConstant(A,Z);
    }

    G4double getFermiMomentumMassDependent(const G4int A, const G4int /*Z*/) {
// assert(A>0);
      static const G4double alphaParam = 259.416; // MeV/c
      static const G4double betaParam  = 152.824; // MeV/c
      static const G4double gammaParam = 9.5157E-2;
      return alphaParam - betaParam*std::exp(-gammaParam*((G4double)A));
    }

    G4double getRPCorrelationCoefficient(const ParticleType t) {
// assert(t==Proton || t==Neutron);
      return rpCorrelationCoefficient[t];
    }

    G4double getNeutronSkinThickness() { return neutronSkinThickness; }

    G4double getNeutronSkinAdditionalDiffuseness() { return neutronSkinAdditionalDiffuseness; }

    G4ThreadLocal G4double effectiveDeltaDecayThreshold = 0.;
    G4ThreadLocal NuclearMassFn getTableMass = NULL;
    G4ThreadLocal ParticleMassFn getTableParticleMass = NULL;
    G4ThreadLocal SeparationEnergyFn getSeparationEnergy = NULL;
    G4ThreadLocal FermiMomentumFn getFermiMomentum = NULL;

  } // namespace ParticleTable
} // namespace G4INCL

