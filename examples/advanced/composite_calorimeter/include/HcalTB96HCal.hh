///////////////////////////////////////////////////////////////////////////////
// File: HcalTB96HCal.hh
// Date: 08/00 
// Modifications: 
// Description: Equipped to construct the geometry of the hadron calorimeter
///////////////////////////////////////////////////////////////////////////////
#ifndef HcalTB96HCal_h
#define HcalTB96HCal_h 1

#include "CMSDetector.hh"

class HcalTB96HCal: public CMSDetector {
public:
  //Constructor and Destructor
  HcalTB96HCal(const G4String &name);
  virtual ~HcalTB96HCal();

  //Get Methods
  G4String getGenMat()                    const {return genMaterial;}
  double   getDy_2Cal()                   const {return dy_2Cal;}
  double   getDx_2Cal()                   const {return dx_2Cal;}
  double   getXposCal()                   const {return xposCal;}
  G4String getBoxMat()                    const {return boxMaterial;}
  int      getNBox()                      const {return nBox;}
  double   getDy_2Box()                   const {return dy_2Box;}
  double   getDx_2Box()                   const {return dx_2Box;}
  double   getWallThickBox()              const {return wallThickBox;}
  double   getXposBox(unsigned int i)     const {return xposBox[i];}
  int      getNLayerScnt()                const {return nLayerScnt;}
  int      getTypeScnt(unsigned int i)    const {return typeLayerScnt[i];}
  int      getMotherScnt(unsigned int i)  const {return mothLayerScnt[i];}
  double   getXposScnt(unsigned int i)    const {return xposLayerScnt[i];}
  int      getNLayerAbs()                 const {return nLayerAbs;}
  int      getTypeAbs(unsigned int i)     const {return typeLayerAbs[i];}
  int      getMotherAbs(unsigned int i)   const {return mothLayerAbs[i];}
  double   getXposAbs(unsigned int i)     const {return xposLayerAbs[i];}
  G4String getAbsMat()                    const {return absMaterial;}
  int      getNAbsorber()                 const {return nAbsorber;}
  double   getDy_2Abs(     )              const {return dy_2Absorber;}
  double   getDx_2Abs(unsigned int i)     const {return dx_2Absorber[i];}
  G4String getScntMat()                   const {return scntMaterial;}
  G4String getWrapMat()                   const {return wrapMaterial;}
  G4String getPlasMat()                   const {return plasMaterial;}
  int      getNScintillator()             const {return nScintillator;}
  double   getDy_2ScntLay(unsigned int i) const {return dy_2ScntLayer[i];}
  double   getDx_2ScntLay(unsigned int i) const {return dx_2ScntLayer[i];}
  double   getDx_2Wrap(unsigned int i)    const {return dx_2Wrapper[i];}
  double   getDx_2FrontP(unsigned int i)  const {return dx_2FrontPlastic[i];}
  double   getDx_2BackP(unsigned int i)   const {return dx_2BackPlastic[i];}
  double   getDx_2Scnt(unsigned int i)    const {return dx_2Scintillator[i];}

protected:
  virtual int readFile();
  virtual void constructDaughters();

private:
  G4String genMaterial;            //General material
  double   dy_2Cal;                //Half width     of the Hcal 
  double   dx_2Cal;                //Half thickness of the Hcal
  double   xposCal;                //Position in mother

  G4String boxMaterial;            //Material of boxes
  int      nBox;                   //Number of boxes
  double   dy_2Box;                //Half width     of the Boxes
  double   dx_2Box;                //Half thickness of the Boxes
  double   wallThickBox;           //Wall thickness of the boxes
  double*  xposBox;                //Position in mother

  int      nLayerScnt;             //Number of scintillator layers
  int*     typeLayerScnt;          //Layer type
  int*     mothLayerScnt;          //Mother type
  double*  xposLayerScnt;          //Position in mother

  int      nLayerAbs;              //Number of absorber     layers
  int*     typeLayerAbs;           //Layer type
  int*     mothLayerAbs;           //Mother type
  double*  xposLayerAbs;           //Position in mother

  G4String absMaterial;            //Material of absorbers
  int      nAbsorber;              //Number of absorber types
  double   dy_2Absorber;           //Half width     of the absorbers
  double*  dx_2Absorber;           //Half thickness of the absorbers

  G4String scntMaterial;           //Material of Scintillator
  G4String wrapMaterial;           //Material of Wrapper
  G4String plasMaterial;           //Material of plastic cover
  int      nScintillator;          //Number of scintillator types
  double*  dy_2ScntLayer;          //Half width     of scintillator layers
  double*  dx_2ScntLayer;          //Half thickness of scintillator layers
  double*  dx_2Wrapper;            //Half thickness of wrappers
  double*  dx_2FrontPlastic;       //Half thickness of front plastic
  double*  dx_2BackPlastic;        //Half thickness of back  plastic
  double*  dx_2Scintillator;       //Half thickness of scintillators
};

#endif
