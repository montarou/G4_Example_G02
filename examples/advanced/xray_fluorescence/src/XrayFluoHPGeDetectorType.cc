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
// $Id: XrayFluoHPGeDetectorType.cc
// GEANT4 tag $Name:
//
// Author: Alfonso Mantero (Alfonso.Mantero@ge.infn.it)
//
// History:
// -----------
//  16 Jul 2003  Alfonso Mantero Created
//
// -------------------------------------------------------------------

#include "XrayFluoHPGeDetectorType.hh"
#include "XrayFluoDataSet.hh"
#include "G4DataVector.hh"
#include "G4LogLogInterpolation.hh"
#include "G4ios.hh"
#include <g4std/fstream>
#include <g4std/strstream>
#include "G4UnitsTable.hh"
#include "Randomize.hh"


XrayFluoHPGeDetectorType::XrayFluoHPGeDetectorType():
  detectorMaterial("HPGe"),efficiencySet(0)
{
  LoadResponseData("response");

  LoadEfficiencyData("efficienza");

 
}
XrayFluoHPGeDetectorType::~XrayFluoHPGeDetectorType()
{
  std::map<G4int,G4DataVector*,G4std::less<G4int> >::iterator pos;

  for (pos = energyMap.begin(); pos != energyMap.end(); pos++)
    {
      G4DataVector* dataSet = (*pos).second;
      delete dataSet;
      dataSet = 0;
    }
  for (pos = dataMap.begin(); pos != dataMap.end(); pos++)
    {
      G4DataVector* dataSet = (*pos).second;
      delete dataSet;
      dataSet = 0;
    }
}
G4String XrayFluoHPGeDetectorType::GetDetectorMaterial()
{
  return detectorMaterial;
}

XrayFluoHPGeDetectorType* XrayFluoHPGeDetectorType::instance = 0;

XrayFluoHPGeDetectorType* XrayFluoHPGeDetectorType::GetInstance()

{
  if (instance == 0)
    {
      instance = new XrayFluoHPGeDetectorType;
     
    }
  return instance;
}

G4double XrayFluoHPGeDetectorType::ResponseFunction(G4double energy)
{
 

  G4double eMin = 1* keV;
  G4double eMax = 10*keV; 
  G4double value = 0.;
  G4double efficiency = 1.;
  
  const XrayFluoDataSet* dataSet = efficiencySet;
  G4int id = 0;
  
  G4double random = G4UniformRand();
 
  if (energy>=eMin && energy <=eMax)
    {
      G4double infEnergy = (G4int)(energy/keV)* keV;
      
      G4double supEnergy = ((G4int)(energy/keV) + 1)*keV;
            
      G4double infData = GetInfData(energy, random, 0);// 0 is not used
      
      G4double supData = GetSupData(energy,random, 0); // 0 is not used
      
      value = (log10(infData)*log10(supEnergy/energy) +
	       log10(supData)*log10(energy/infEnergy)) / 
	log10(supEnergy/infEnergy);
      value = pow(10,value);
    }
  else if (energy<eMin)
    { 
      G4double infEnergy = eMin;
      G4double supEnergy = eMin/keV +1*keV;
 
      G4double infData = GetInfData(eMin, random, 0);
      G4double supData = GetSupData(eMin,random, 0);
      value = (log10(infData)*log10(supEnergy/eMin) +
	       log10(supData)*log10(eMin/infEnergy)) / 
	log10(supEnergy/infEnergy);
      value = pow(10,value);
      value = value-eMin+ energy;


    }
 else if (energy>eMax)
    { 
      G4double infEnergy = eMax/keV - 1. *keV;
      G4double supEnergy = eMax;
 
      G4double infData = GetInfData(eMax, random, 0);
      G4double supData = GetSupData(eMax,random, 0);
      value = (log10(infData)*log10(supEnergy/eMax) +
	       log10(supData)*log10(eMax/infEnergy)) / 
	log10(supEnergy/infEnergy);
      value = pow(10,value);
      value = value+energy- eMax;
    }
  G4double  RandomNum = G4UniformRand(); 
  
  efficiency = dataSet->FindValue(value,id);
  if ( RandomNum>efficiency )
    {
      value = 0.;
    }
 
  return value;
}
G4double XrayFluoHPGeDetectorType::GetInfData(G4double energy, G4double random, G4int)
{
  G4double value = 0.;
  G4int zMin = 1;
  G4int zMax = 10; 
  
  G4int Z = ((G4int)(energy/keV));
  
  if (Z<zMin) {Z=zMin;}
  if (Z>zMax) {Z=zMax;}
  
  if (Z >= zMin && Z <= zMax)
    {
      G4std::map<G4int,G4DataVector*,G4std::less<G4int> >::const_iterator pos;
      pos = energyMap.find(Z);
      G4std::map<G4int,G4DataVector*,G4std::less<G4int> >::const_iterator posData;
      posData = dataMap.find(Z);
      if (pos!= energyMap.end())
	{
	  G4DataVector energySet = *((*pos).second);
	  G4DataVector dataSet = *((*posData).second);
	  G4int nData = energySet.size();
	  
	  G4double partSum = 0;
	  G4int index = 0;
	  
	  while (random> partSum)
	    {
	      partSum += dataSet[index];
	      index++;
	    }
	  
	  
	  if (index >= 0 && index < nData)
	    {
	      value = energySet[index];
	      
	    }
	  
	}
    }
  return value;

}
G4double XrayFluoHPGeDetectorType::GetSupData(G4double energy, G4double random, G4int)
{
  G4double value = 0.;
  G4int zMin = 1;
  G4int zMax = 10;
  G4int Z = ((G4int)(energy/keV)+1);
  
  if (Z<zMin) {Z=zMin;}
  if (Z>zMax) {Z=zMax;}
  if (Z >= zMin && Z <= zMax)
    {
      G4std::map<G4int,G4DataVector*,G4std::less<G4int> >::const_iterator pos;
      pos = energyMap.find(Z);
      G4std::map<G4int,G4DataVector*,G4std::less<G4int> >::const_iterator posData;
      posData = dataMap.find(Z);
      if (pos!= energyMap.end())
	{
	  G4DataVector energySet = *((*pos).second);
	  G4DataVector dataSet = *((*posData).second);
	  G4int nData = energySet.size();
	  G4double partSum = 0;
	  G4int index = 0;
	  
	  while (random> partSum)
	    {
	      partSum += dataSet[index];
	      index++;
	    }
	  
	  
	  if (index >= 0 && index < nData)
	    {
	      value = energySet[index];
	    }
	}
    }
  return value;

}
void XrayFluoHPGeDetectorType::LoadResponseData(G4String fileName)
{
  char nameChar[100] = {""};
  G4std::ostrstream ost(nameChar, 100, G4std::ios::out);
  
  
  ost << fileName<<".dat";
  
  G4String name(nameChar);
  
  char* path = getenv("XRAYDATA");
  
  G4String pathString(path);
  G4String dirFile = pathString + "/" + name;
  G4std::ifstream file(dirFile);
  G4std::filebuf* lsdp = file.rdbuf();
  
  if (! (lsdp->is_open()) )
    {
      G4String excep = "XrayFluoHPGeDetectorType - data file: " + dirFile + " not found";
      G4Exception(excep);
	}
  G4double a = 0;
  G4int k = 1;
  G4int s = 0;
  
  G4int Z = 1;
  G4DataVector* energies = new G4DataVector;
  G4DataVector* data = new G4DataVector;

  do
    {
      file >> a;
      G4int nColumns = 2;
      if (a == -1)
	{
	  if (s == 0)
	    {
	      // End of a  data set
	      energyMap[Z] = energies;
	      dataMap[Z] = data;
	      // Start of new shell data set
	      energies = new G4DataVector;
	      data = new G4DataVector;
	      Z++;	    
	    }      
	  s++;
	  if (s == nColumns)
	    {
	      s = 0;
	    }
	}
      else if (a == -2)
	{
	  // End of file; delete the empty vectors 
	  //created when encountering the last -1 -1 row
	  delete energies;
	  delete data;
	  
	}
      else
	{
	  // 1st column is energy
	  if(k%nColumns != 0)
	    {	
	      G4double e = a * keV;
	      energies->push_back(e);
	      k++;
	    }
	  else if (k%nColumns == 0)
	    {
	      // 2nd column is data
	      
	      data->push_back(a);
	      k = 1;
	    }
	}
    } while (a != -2); // end of file
  file.close();    
}

void XrayFluoHPGeDetectorType::LoadEfficiencyData(G4String fileName)
{

  char* path = getenv("XRAYDATA");
  G4String dirFile;
  if (path) {
    G4String pathString(path);
    dirFile = pathString + "/" + fileName;
  }
  else{ dirFile = fileName;}
  
  G4VDataSetAlgorithm* interpolation4 = new G4LogLogInterpolation();
  efficiencySet = new XrayFluoDataSet(1,dirFile,interpolation4,keV,1);
  delete interpolation4; 
}

