///////////////////////////////////////////////////////////////////////////////
// File: GeometryConfiguration.cc
// Author: I. Gonzalez, 2/98
// Date: 03/98 I. Gonzalez
// Modifications: 24/03/98 I.G.
//                03/05/99 I.G. Added sensitive behaviour
//                16/12/99 I.G. Updated for STL.  Needs revision!!! 
//                02/05/00 I.G. S.B. Use local file if available
///////////////////////////////////////////////////////////////////////////////

#include "GeometryConfiguration.hh"

#include <fstream>

//Comment/Uncomment next line to hide/show debug information
//#define debug


GeometryConfiguration * GeometryConfiguration::instance = 0;

GeometryConfiguration* GeometryConfiguration::getInstance(){
  if (!instance) 
    instance = new GeometryConfiguration;
  return instance;
}


int GeometryConfiguration::getConstructFlag(const G4String& n) /*const*/ {
  int flag = -1;
  GeometryConfIterator it = theConfiguration.find(n);

  if (it != theConfiguration.end())
    flag = (*it).second.ConstructFlag;
  else {
    cerr << "ERROR: In GeometryConfiguration::getConstructFlag(const G4String& n)" 
	 << endl 
	 << "       " << n << " not found in configuration file" << endl;
  }

  return flag;
}

G4String GeometryConfiguration::getFileName(const G4String& n) /*const*/ {
  G4String fn;
  GeometryConfIterator it = theConfiguration.find(n);

  if (it != theConfiguration.end())
    fn = (*it).second.FileName;
  else {
    cerr << "ERROR: In GeometryConfiguration::getConstructFlag(const G4String& n)" 
	 << endl 
	 << "       " << n << " not found in configuration file" << endl;
  }

  return fn;
}

GeometryConfiguration::GeometryConfiguration():
  theConfiguration() {

  ///////////////////////////////////////////////////////////////
  // Open the file
  G4String pathName = getenv("OSCAR_CONFPATH");
  G4String fileenv  = getenv("OSCAR_GEOMETRYCONF");
  if (!pathName || !fileenv) {
    cerr << "ERROR: OSCAR_GEOMETRYCONF and/or OSCAR_CONFPATH not set" << endl
	 << "       Set them to the geometry configuration file/path" << endl;
    exit(-2);
  }

  cout << " ==> Opening file " << fileenv << "..." << endl;
  ifstream is;
  bool ok = openGeomFile(is, pathName, fileenv);
  if (!ok)
    exit(-1);

  G4String name;
  GCInfo gcinfo;

  while (is) {
    readName(is, name);
    readName(is, gcinfo.FileName);
    is >> gcinfo.ConstructFlag >> jump;
#ifdef debug
    cout << "GeometryConfiguration constructor: Read \"" << name << "\" \"" 
	 << gcinfo.FileName << "\"" << tab << gcinfo.ConstructFlag << endl;
#endif
    theConfiguration[name] = gcinfo;
  }

  

  ///////////////////////////////////////////////////////////////
  // Close the file  
  is.close();
  cout << " <== Closed file " << fileenv << endl;
}
