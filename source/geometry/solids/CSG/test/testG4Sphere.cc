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
// $Id: testG4Sphere.cc,v 1.7 2002-08-10 13:40:51 grichine Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
// G4Sphere Test File
//
// o Basic asserts on each function +
//   awkward cases for tracking / geom algorithms
//
// o Add tests on dicovering bugs in G4Sphere.cc...
//
// History:
// 28.03.95 P.Kent Initial version
// 20.10.96 V.Grichine Final modifications to commit

#include "G4ios.hh"
#include <assert.h>
#include <math.h>
#include "globals.hh"
#include "geomdefs.hh"

#include "ApproxEqual.hh"

#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4AffineTransform.hh"
#include "G4VoxelLimits.hh"
#include "G4Sphere.hh"

//const G4double kApproxEqualTolerance = kCarTolerance;

// Return true if the double check is approximately equal to target
//
// Process:
//
// Return true is difference < kApproxEqualTolerance

//G4bool ApproxEqual(const G4double check,const G4double target)
//{
//    return (fabs(check-target)<kApproxEqualTolerance) ? true : false ;
//}

// Return true if the 3vector check is approximately equal to target
//G4bool ApproxEqual(const G4ThreeVector& check, const G4ThreeVector& target)
//{
//    return (ApproxEqual(check.x(),target.x())&&
//	   ApproxEqual(check.y(),target.y())&&
//	    ApproxEqual(check.z(),target.z()))? true : false;
//}

///////////////////////////////////////////////////////////////////
//
// Dave's auxiliary function

const G4String OutputInside(const EInside a)
{
	switch(a) 
        {
		case kInside:  return "Inside"; 
		case kOutside: return "Outside";
		case kSurface: return "Surface";
	}
	return "????";
}



int main(void)
{
    G4double Dist;
    G4ThreeVector pzero(0,0,0),px(30,0,0),py(0,30,0),pz(0,0,30);
    G4ThreeVector Pmx(-30,0,0),pmy(0,-30,0),pmz(0,0,-30);
    G4ThreeVector pbigx(100,0,0),pbigy(0,100,0),pbigz(0,0,100);
    G4ThreeVector pbigmx(-100,0,0),pbigmy(0,-100,0),pbigmz(0,0,-100);

    G4ThreeVector ponrmin1(45,0,0),ponrmax1(50,0,0),ponzmax(0,0,50),
	    ponrmin2(45/sqrt(2.),45/sqrt(2.),0),
            ponrmin3(0,0,-45),ponrminJ(0,0,-300),ponrmaxJ(0,0,-500),
	    ponrmax2(50/sqrt(2.),50/sqrt(2.),0);
    G4ThreeVector ponphi1(48/sqrt(2.),-48/sqrt(2.),0),
	          ponphi2(48/sqrt(2.),48/sqrt(2.),0),
	          pInPhi(48*0.866,-24,0),
	          pOverPhi(-48/sqrt(2.),48/sqrt(2.),0);
    G4ThreeVector pontheta1(0,48*sin(pi/4),48*cos(pi/4)),
	    pontheta2(0,48*sin(pi/4),-48*cos(pi/4));

    G4ThreeVector ptestphi1(-100,-45/sqrt(2.),0),
	    ptestphi2(-100,45/sqrt(2.),0);

    G4ThreeVector ptesttheta1(0,48/sqrt(2.),100),
	    ptesttheta2(0,48/sqrt(2.),-100);

    G4ThreeVector vx(1,0,0),vy(0,1,0),vz(0,0,1);
    G4ThreeVector vmx(-1,0,0),vmy(0,-1,0),vmz(0,0,-1);
    G4ThreeVector vxy(1/sqrt(2.),1/sqrt(2.),0),vmxmy(-1/sqrt(2.),-1/sqrt(2.),0);
    G4ThreeVector vxmy(1/sqrt(2.),-1/sqrt(2.),0),vmxy(-1/sqrt(2.),1/sqrt(2.),0);
    G4ThreeVector v345exit1(-0.8,0.6,0),v345exit2(0.8,0.6,0),
	          v345exit3(0.6,0.8,0);
    G4ThreeVector norm,*pNorm;
    G4bool *pgoodNorm,goodNorm,calcNorm=true;

    pNorm=&norm;
    pgoodNorm=&goodNorm;

    G4Sphere s1("Solid G4Sphere",0,50,0,twopi,0,pi);
    G4Sphere s2("Spherical Shell",45,50,0,twopi,0,pi);
    G4Sphere s3("Band (theta segment)",45,50,0,twopi,pi/4,halfpi);
    G4Sphere s32("Band (theta segment2)",45,50,0,twopi,0,pi/4);
    G4Sphere s33("Band (theta segment1)",45,50,0,twopi,pi*3/4,pi/4);
    G4Sphere s34("Band (theta segment)",4,50,0,twopi,pi/4,halfpi);
    G4Sphere s4("Band (phi segment)",45,50,-pi/4,halfpi,0,twopi);
    //    G4cout<<"s4.fSPhi = "<<s4.GetSPhi()<<G4endl;
    G4Sphere s5("Patch (phi/theta seg)",45,50,-pi/4,halfpi,pi/4,halfpi);
    G4Sphere s6("John example",300,500,0,5.76,0,pi) ; 
    G4Sphere s7("sphere7",1400.,1550.,0.022321428571428572,0.014642857142857141,
	                  1.5631177553663251,0.014642857142857141    );
    G4Sphere s8("sphere",278.746*mm, 280.0*mm, 0.0*degree, 360.0*degree,
		                               0.0*degree, 90.0*degree);

    G4Sphere b216("b216", 1400.0, 1550.0, 
                  0.022321428571428572, 
		  0.014642857142857141,
                  1.578117755366325,
                  0.014642857142867141);

    G4Sphere s9("s9",0*mm,410*mm,0*degree,360*degree,90*degree,90*degree);


G4ThreeVector p216(1549.9518578505142,1.2195415370970153,-12.155289555510985), 
              v216(-0.61254821852534425,-0.51164551429243466,-0.60249775741147549);


 G4ThreeVector s9p(384.8213314370455*mm,
	       134.264386151667*mm,
	       -44.56026800002064*mm);

 G4ThreeVector s9v(-0.6542770611918751,
		   -0.0695116921641141,
		   -0.7530535517814154);

#ifdef NDEBUG
    G4Exception("FAIL: *** Assertions must be compiled in! ***");
#endif

    //////////////// Check name /////////////////////////

    assert(s1.GetName()=="Solid G4Sphere");


    // Some user application cases

    Dist = s4.DistanceToOut(ponrmin3,vmz,calcNorm,pgoodNorm,pNorm) ;
    G4cout<<"s4.DistanceToOut(ponrmin3,vmz,calcNorm,pgoodNorm,pNorm) = "<<Dist
        <<G4endl ;
    Dist = s6.DistanceToOut(ponrminJ,vmz,calcNorm,pgoodNorm,pNorm) ;
    G4cout<<"s6.DistanceToOut(ponrminJ,vmz,calcNorm,pgoodNorm,pNorm) = "<<Dist
        <<G4endl ;
    Dist = s6.DistanceToOut(ponrmaxJ,vmz,calcNorm,pgoodNorm,pNorm) ;
    G4cout<<"s6.DistanceToOut(ponrmaxJ,vmz,calcNorm,pgoodNorm,pNorm) = "<<Dist
        <<G4endl ;

    Dist = s7.DistanceToOut(G4ThreeVector(1399.984667238032,
                                             5.9396696802500299,
                                            -2.7661927818688308),
                            G4ThreeVector(0.50965504781062942,
                                         -0.80958849145715217,
                                          0.29123565499656401),
                                        calcNorm,pgoodNorm,pNorm) ;
    G4cout<<"s7.DistanceToOut(shereP,sphereV,calcNorm,pgoodNorm,pNorm) = "<<Dist
        <<G4endl ;

    Dist = s7.DistanceToIn(G4ThreeVector(1399.984667238032,
                                             5.9396696802500299,
                                            -2.7661927818688308),
                            G4ThreeVector(0.50965504781062942,
                                         -0.80958849145715217,
                                          0.29123565499656401)) ;
    G4cout<<"s7.DistanceToIn(shereP,sphereV,calcNorm,pgoodNorm,pNorm) = "<<Dist
        <<G4endl ;


    
// Check G4Sphere::Inside

    EInside inside = s7.Inside(G4ThreeVector(1399.984667238032,
                                             5.9396696802500299,
                                            -2.7661927818688308)  ) ;
    G4cout<<"s7.Inside(G4ThreeVector(1399.98466 ... = "
          <<OutputInside(inside)<<G4endl ;

    inside = s8.Inside(G4ThreeVector(-249.5020724528353*mm,
					       26.81253142743162*mm,
                                              114.8988524453591*mm  )  ) ;
    G4cout<<"s8.Inside(G4ThreeVector(-249.5020 ... = "
          <<OutputInside(inside)<<G4endl ;
    inside = b216.Inside(p216);
    G4cout<<"b216.Inside(p216) = "
          <<OutputInside(inside)<<G4endl ;
    inside = s1.Inside(pz);
    G4cout<<"s1.Inside(pz) = "
          <<OutputInside(inside)<<G4endl ;

    inside = s9.Inside(s9p);
    G4cout<<"s9.Inside(s9p) = "
          <<OutputInside(inside)<<G4endl ;
    assert(s1.Inside(pzero)==kInside);
    // assert(s1.Inside(pz)==kInside);
    assert(s2.Inside(pzero)==kOutside);
    assert(s2.Inside(ponrmin2)==kSurface);
    assert(s2.Inside(ponrmax2)==kSurface);
    assert(s3.Inside(pontheta1)==kSurface);
    assert(s3.Inside(pontheta2)==kSurface);
    assert(s4.Inside(ponphi1)==kSurface);
    assert(s4.Inside(ponphi1)==kSurface);
    assert(s4.Inside(pOverPhi)==kOutside);
    assert(s4.Inside(pInPhi)==kInside);
    assert(s5.Inside(pbigz)==kOutside);

// Checking G4Sphere::SurfaceNormal
    norm=s1.SurfaceNormal(ponrmax1);
    assert(ApproxEqual(norm,vx));

// Checking G4Sphere::DistanceToOut(P)
    Dist=s1.DistanceToOut(pzero);
    assert(ApproxEqual(Dist,50));
    Dist=s1.DistanceToOut(ponrmax1);
    assert(ApproxEqual(Dist,0));

// Checking G4Sphere::DistanceToOut(p,v)


        Dist=s1.DistanceToOut(pz,vz,calcNorm,pgoodNorm,pNorm);
	G4cout<<"Dist=s1.DistanceToOut(pz,vz) = "<<Dist<<G4endl;

     Dist=s1.DistanceToOut(ponrmax1,vx,calcNorm,pgoodNorm,pNorm);
     *pNorm=pNorm->unit();
     assert(ApproxEqual(Dist,0)&&*pgoodNorm&&ApproxEqual(*pNorm,vx));

     Dist=s2.DistanceToOut(ponrmin1,vx,calcNorm,pgoodNorm,pNorm);
     *pNorm=pNorm->unit();
     assert(ApproxEqual(Dist,5)&&*pgoodNorm&&ApproxEqual(*pNorm,vx));

     Dist=s2.DistanceToOut(ponrmax2,vx,calcNorm,pgoodNorm,pNorm);
     assert(ApproxEqual(Dist,0)&&*pgoodNorm&&ApproxEqual(*pNorm,vxy));

    Dist=s1.DistanceToOut(pzero,vx,calcNorm,pgoodNorm,pNorm);
    assert(ApproxEqual(Dist,50)&&ApproxEqual(pNorm->unit(),vx)&&*pgoodNorm);
    Dist=s1.DistanceToOut(pzero,vmx,calcNorm,pgoodNorm,pNorm);
    assert(ApproxEqual(Dist,50)&&ApproxEqual(pNorm->unit(),vmx)&&*pgoodNorm);
    Dist=s1.DistanceToOut(pzero,vy,calcNorm,pgoodNorm,pNorm);
    assert(ApproxEqual(Dist,50)&&ApproxEqual(pNorm->unit(),vy)&&*pgoodNorm);
    Dist=s1.DistanceToOut(pzero,vmy,calcNorm,pgoodNorm,pNorm);
    assert(ApproxEqual(Dist,50)&&ApproxEqual(pNorm->unit(),vmy)&&*pgoodNorm);
    Dist=s1.DistanceToOut(pzero,vz,calcNorm,pgoodNorm,pNorm);
    assert(ApproxEqual(Dist,50)&&ApproxEqual(pNorm->unit(),vz)&&*pgoodNorm);
    Dist=s1.DistanceToOut(pzero,vmz,calcNorm,pgoodNorm,pNorm);
    assert(ApproxEqual(Dist,50)&&ApproxEqual(pNorm->unit(),vmz)&&*pgoodNorm);
    Dist=s1.DistanceToOut(pzero,vxy,calcNorm,pgoodNorm,pNorm);
    assert(ApproxEqual(Dist,50)&&ApproxEqual(pNorm->unit(),vxy)&&*pgoodNorm);

    Dist=s4.DistanceToOut(ponphi1,vx,calcNorm,pgoodNorm,pNorm);
    //assert(ApproxEqual(Dist,0)&&ApproxEqual(pNorm->unit(),vmxmy)&&*pgoodNorm);
    Dist=s4.DistanceToOut(ponphi2,vx,calcNorm,pgoodNorm,pNorm);
    // assert(ApproxEqual(Dist,0)&&ApproxEqual(pNorm->unit(),vmxy)&&*pgoodNorm);
    Dist=s3.DistanceToOut(pontheta1,vz,calcNorm,pgoodNorm,pNorm);
    // assert(ApproxEqual(Dist,0)&&ApproxEqual(pNorm->unit(),vy)&&*pgoodNorm);
    Dist=s32.DistanceToOut(pontheta1,vmz,calcNorm,pgoodNorm,pNorm);
    //assert(ApproxEqual(Dist,0)&&ApproxEqual(pNorm->unit(),vmy)&&*pgoodNorm);
    Dist=s32.DistanceToOut(pontheta1,vz,calcNorm,pgoodNorm,pNorm);
    //assert(ApproxEqual(Dist,50)&&ApproxEqual(pNorm->unit(),vz)&&*pgoodNorm);
    Dist=s1.DistanceToOut(pzero,vmz,calcNorm,pgoodNorm,pNorm);
    assert(ApproxEqual(Dist,50)&&ApproxEqual(pNorm->unit(),vmz)&&*pgoodNorm);
    Dist=s1.DistanceToOut(pzero,vxy,calcNorm,pgoodNorm,pNorm);
    assert(ApproxEqual(Dist,50)&&ApproxEqual(pNorm->unit(),vxy)&&*pgoodNorm);
    
    
        Dist=s2.DistanceToOut(ponrmin1,vxy,calcNorm,pgoodNorm,pNorm);
	//        G4cout<<"Dist=s2.DistanceToOut(pormin1,vxy) = "<<Dist<<G4endl;

    Dist=s2.DistanceToOut(ponrmax1,vmx,calcNorm,pgoodNorm,pNorm);
    //    G4cout<<"Dist=s2.DistanceToOut(ponxside,vmx) = "<<Dist<<G4endl;
    Dist=s2.DistanceToOut(ponrmax1,vmxmy,calcNorm,pgoodNorm,pNorm);
    //    G4cout<<"Dist=s2.DistanceToOut(ponxside,vmxmy) = "<<Dist<<G4endl;
    Dist=s2.DistanceToOut(ponrmax1,vz,calcNorm,pgoodNorm,pNorm);
    //    G4cout<<"Dist=s2.DistanceToOut(ponxside,vz) = "<<Dist<<G4endl;

    //    Dist=s2.DistanceToOut(pbigx,vx,calcNorm,pgoodNorm,pNorm);
    //    G4cout<<"Dist=s2.DistanceToOut(pbigx,vx) = "<<Dist<<G4endl;
    //    Dist=s2.DistanceToOut(pbigx,vxy,calcNorm,pgoodNorm,pNorm);
    //    G4cout<<"Dist=s2.DistanceToOut(pbigx,vxy) = "<<Dist<<G4endl;
    //    Dist=s2.DistanceToOut(pbigx,vz,calcNorm,pgoodNorm,pNorm);
    //    G4cout<<"Dist=s2.DistanceToOut(pbigx,vz) = "<<Dist<<G4endl;

    Dist=b216.DistanceToOut(p216,v216,calcNorm,pgoodNorm,pNorm);
    G4cout<<"b216.DistanceToOut(p216,v216,... = "<<Dist<<G4endl;

    Dist=s9.DistanceToOut(s9p,s9v,calcNorm,pgoodNorm,pNorm);
    G4cout<<"s9.DistanceToOut(s9p,s9v,... = "<<Dist<<G4endl;

     
// Checking G4Sphere::DistanceToIn(P)
    Dist=s2.DistanceToIn(pzero);
    assert(ApproxEqual(Dist,45));
    Dist=s1.DistanceToIn(ponrmax1);
    assert(ApproxEqual(Dist,0));

// Checking G4Sphere::DistanceToIn(P,V)
    Dist=s1.DistanceToIn(ponzmax,vz);
    G4cout<<"s1.DistanceToIn(ponzmax,vz) = "<<Dist<<G4endl;
    Dist=s1.DistanceToIn(pbigy,vy);
    assert(Dist==kInfinity);
    Dist=s1.DistanceToIn(pbigy,vmy);
    assert(ApproxEqual(Dist,50));

    Dist=s2.DistanceToIn(pzero,vy);
    assert(ApproxEqual(Dist,45));
    Dist=s2.DistanceToIn(pzero,vmy);
    assert(ApproxEqual(Dist,45));
    Dist=s2.DistanceToIn(ponrmin1,vx);
    //    G4cout<<"s2.DistanceToIn(ponmin1,vx) = "<<Dist<<G4endl;
    assert(Dist==0);
    Dist=s2.DistanceToIn(ponrmin1,vmx);
    assert(ApproxEqual(Dist,90));

    Dist=s2.DistanceToIn(ponrmin2,vx);
    assert(Dist==0);
    Dist=s2.DistanceToIn(ponrmin2,vmx);
    assert(ApproxEqual(Dist,90/sqrt(2.)));


    Dist=s3.DistanceToIn(ptesttheta1,vmz);
    //    G4cout<<"s3.DistanceToIn(ptesttheta1,vmz) = "<<Dist<<G4endl;
    assert(ApproxEqual(Dist,100-48/sqrt(2.)));
    Dist=s3.DistanceToIn(pontheta1,vz);
    //    G4cout<<"s3.DistanceToIn(pontheta1,vz) = "<<Dist<<G4endl;
    assert(Dist==kInfinity);
    Dist=s3.DistanceToIn(pontheta1,vmz);
    assert(Dist==0);
    Dist=s3.DistanceToIn(pontheta2,vz);
    //    G4cout<<"s3.DistanceToIn(pontheta2,vz) = "<<Dist<<G4endl;
    assert(Dist==0);
    Dist=s3.DistanceToIn(pontheta2,vmz);
    assert(Dist==kInfinity);
    Dist=s32.DistanceToIn(pontheta1,vz);
    //    G4cout<<"s32.DistanceToIn(pontheta1,vz) = "<<Dist<<G4endl;
    assert(Dist==0);
    Dist=s32.DistanceToIn(pontheta1,vmz);
    //    G4cout<<"s32.DistanceToIn(pontheta1,vmz) = "<<Dist<<G4endl;
    assert(Dist==kInfinity);
    Dist=s33.DistanceToIn(pontheta2,vz);
    //    G4cout<<"s33.DistanceToIn(pontheta2,vz) = "<<Dist<<G4endl;
    assert(Dist==kInfinity);
    Dist=s33.DistanceToIn(pontheta2,vmz);
    //    G4cout<<"s33.DistanceToIn(pontheta2,vmz) = "<<Dist<<G4endl;
    assert(Dist==0);

     Dist=s4.DistanceToIn(pbigy,vmy);
     assert(Dist==kInfinity);
     Dist=s4.DistanceToIn(pbigz,vmz);
     assert(ApproxEqual(Dist,50));
     Dist=s4.DistanceToIn(pzero,vy);
     assert(Dist==kInfinity);
     Dist=s4.DistanceToIn(pzero,vx);
     assert(ApproxEqual(Dist,45));

     Dist=s4.DistanceToIn(ptestphi1,vx);
     assert(ApproxEqual(Dist,100+45/sqrt(2.)));
     Dist=s4.DistanceToIn(ponphi1,vmxmy);
     assert(Dist==kInfinity);
     Dist=s4.DistanceToIn(ponphi1,vxy);
     //     G4cout<<"s4.DistanceToIn(ponphi1,vxy) = "<<Dist<<G4endl;
     assert(ApproxEqual(Dist,0));

     Dist=s4.DistanceToIn(ptestphi2,vx);
     assert(ApproxEqual(Dist,100+45/sqrt(2.)));
     Dist=s4.DistanceToIn(ponphi2,vmxy);
     assert(Dist==kInfinity);
     Dist=s4.DistanceToIn(ponphi2,vxmy);
     //     G4cout<<"s4.DistanceToIn(ponphi2,vxmy) = "<<Dist<<G4endl;
     assert(ApproxEqual(Dist,0));

     Dist=s3.DistanceToIn(pzero,vx);
     assert(ApproxEqual(Dist,45));
     Dist=s3.DistanceToIn(ptesttheta1,vmz);
     assert(ApproxEqual(Dist,100-48/sqrt(2.)));
     Dist=b216.DistanceToIn(p216,v216);
     G4cout<<"b216.DistanceToIn(p216,v216) = "<<Dist<<G4endl;

     ///////////////////////////////////////////////////////////////////////////


// CalculateExtent
    G4VoxelLimits limit;		// Unlimited
    G4RotationMatrix noRot;
    G4AffineTransform origin;
    G4double min,max;
    assert(s1.CalculateExtent(kXAxis,limit,origin,min,max));
    assert(min<=-50&&max>=50);
    assert(s1.CalculateExtent(kYAxis,limit,origin,min,max));
    assert(min<=-50&&max>=50);
    assert(s1.CalculateExtent(kZAxis,limit,origin,min,max));
    assert(min<=-50&&max>=50);

    assert(s2.CalculateExtent(kXAxis,limit,origin,min,max));
    assert(min<=-50&&max>=50);
    assert(s2.CalculateExtent(kYAxis,limit,origin,min,max));
    assert(min<=-50&&max>=50);
    assert(s2.CalculateExtent(kZAxis,limit,origin,min,max));
    assert(min<=-50&&max>=50);

    assert(s3.CalculateExtent(kXAxis,limit,origin,min,max));
    assert(min<=-50&&max>=50);
    assert(s3.CalculateExtent(kYAxis,limit,origin,min,max));
    assert(min<=-50&&max>=50);
    assert(s3.CalculateExtent(kZAxis,limit,origin,min,max));
    assert(min<=-50/sqrt(2.)&&max>=50/sqrt(2.));
    
    G4ThreeVector pmxmymz(-100,-110,-120);
    G4AffineTransform tPosOnly(pmxmymz);
    assert(s1.CalculateExtent(kXAxis,limit,tPosOnly,min,max));
    assert(min<=-150&&max>=-50);
    assert(s1.CalculateExtent(kYAxis,limit,tPosOnly,min,max));
    assert(min<=-160&&max>=-60);
    assert(s1.CalculateExtent(kZAxis,limit,tPosOnly,min,max));
    assert(min<=-170&&max>=-70);

    assert(s3.CalculateExtent(kXAxis,limit,tPosOnly,min,max));
    assert(min<=-150&&max>=-50);
    assert(s3.CalculateExtent(kYAxis,limit,tPosOnly,min,max));
    assert(min<=-160&&max>=-60);
    assert(s3.CalculateExtent(kZAxis,limit,tPosOnly,min,max));
    assert(min<=-170+50/sqrt(2.)&&max>=-70-50/sqrt(2.));
    
    G4RotationMatrix r90Z;
    r90Z.rotateZ(halfpi);
    G4AffineTransform tRotZ(r90Z,pzero);
    assert(s1.CalculateExtent(kXAxis,limit,tRotZ,min,max));
    assert(min<=-50&&max>=50);
    assert(s1.CalculateExtent(kYAxis,limit,tRotZ,min,max));
    assert(min<=-50&&max>=50);
    assert(s1.CalculateExtent(kZAxis,limit,tRotZ,min,max));
    assert(min<=-50&&max>=50);

    assert(s2.CalculateExtent(kXAxis,limit,tRotZ,min,max));
    assert(min<=-50&&max>=50);
    assert(s2.CalculateExtent(kYAxis,limit,tRotZ,min,max));
    assert(min<=-50&&max>=50);
    assert(s2.CalculateExtent(kZAxis,limit,tRotZ,min,max));
    assert(min<=-50&&max>=50);

    assert(s3.CalculateExtent(kXAxis,limit,tRotZ,min,max));
    assert(min<=-50&&max>=50);
    assert(s3.CalculateExtent(kYAxis,limit,tRotZ,min,max));
    assert(min<=-50&&max>=50);
    assert(s3.CalculateExtent(kZAxis,limit,tRotZ,min,max));
    assert(min<=-50/sqrt(2.)&&max>=50/sqrt(2.));
    
// Check that clipped away
    G4VoxelLimits xClip;
    xClip.AddLimit(kXAxis,-100,-60);
    assert(!s1.CalculateExtent(kXAxis,xClip,origin,min,max));

// Assert clipped to volume
    G4VoxelLimits allClip;
    allClip.AddLimit(kXAxis,-5,+5);
    allClip.AddLimit(kYAxis,-5,+5);
    allClip.AddLimit(kZAxis,-5,+5);
    G4RotationMatrix genRot;
    genRot.rotateX(pi/6);
    genRot.rotateY(pi/6);
    genRot.rotateZ(pi/6);
    G4AffineTransform tGen(genRot,vx);
    assert(s1.CalculateExtent(kXAxis,allClip,tGen,min,max));
    assert(min<=-5&&max>=5);
    assert(s1.CalculateExtent(kYAxis,allClip,tGen,min,max));
    assert(min<=-5&&max>=5);
    assert(s1.CalculateExtent(kZAxis,allClip,tGen,min,max));
    assert(min<=-5&&max>=5);

    assert(s2.CalculateExtent(kXAxis,allClip,tGen,min,max));
    assert(min<=-5&&max>=5);
    assert(s2.CalculateExtent(kYAxis,allClip,tGen,min,max));
    assert(min<=-5&&max>=5);
    assert(s2.CalculateExtent(kZAxis,allClip,tGen,min,max));
    assert(min<=-5&&max>=5);
    
    s34.CalculateExtent(kXAxis,allClip,tGen,min,max);
    // G4cout<<"s34.CalculateExtent(kXAxis,allClip,tGen,min,max)"<<G4endl ;
    // G4cout<<"min = "<<min<<"   max = "<<max<<G4endl ;

    s34.CalculateExtent(kYAxis,allClip,tGen,min,max);
    // G4cout<<"s3.CalculateExtent(kYAxis,allClip,tGen,min,max)"<<G4endl ;
    // G4cout<<"min = "<<min<<"   max = "<<max<<G4endl ;

    s34.CalculateExtent(kZAxis,allClip,tGen,min,max);
    //  G4cout<<"s34.CalculateExtent(kZAxis,allClip,tGen,min,max)"<<G4endl ;
    //  G4cout<<"min = "<<min<<"   max = "<<max<<G4endl ;
    assert(s34.CalculateExtent(kXAxis,allClip,tGen,min,max));
    assert(min<=-5&&max>=5);
    assert(s34.CalculateExtent(kYAxis,allClip,tGen,min,max));
    assert(min<=-5&&max>=5);
    assert(s34.CalculateExtent(kZAxis,allClip,tGen,min,max));
    assert(min<=-5&&max>=5);

// Test z clipping ok
    for (G4double zTest=-100;zTest<100;zTest+=9)
	{
	    G4VoxelLimits zTestClip;
	    zTestClip.AddLimit(kZAxis,-kInfinity,zTest);
	    if (zTest<-50)
		{
		    assert(!s1.CalculateExtent(kZAxis,zTestClip,origin,min,max));
		    assert(!s2.CalculateExtent(kZAxis,zTestClip,origin,min,max));
		}
	    else
		{
		    assert(s1.CalculateExtent(kZAxis,zTestClip,origin,min,max));
		    assert(s2.CalculateExtent(kZAxis,zTestClip,origin,min,max));
		    G4double testMin=-50;
		    G4double testMax=(zTest<50) ? zTest : 50;
		    assert (ApproxEqual(min,testMin)
			    &&ApproxEqual(max,testMax));
		}
	}

// Test y clipping ok
    for (G4double xTest=-100;xTest<100;xTest+=9)
	{
	    G4VoxelLimits xTestClip;
	    xTestClip.AddLimit(kXAxis,-kInfinity,xTest);
	    if (xTest<-50)
		{
		    assert(!s1.CalculateExtent(kYAxis,xTestClip,origin,min,max));
		}
	    else
		{
		   assert(s1.CalculateExtent(kYAxis,xTestClip,origin,min,max));
// Calc max y coordinate
		   G4double testMax=(xTest<0) ? sqrt(50*50-xTest*xTest) : 50;
		   assert (ApproxEqual(min,-testMax)
			   &&ApproxEqual(max,testMax));
		}
	}

// Test x clipping ok
    for (G4double yTest=-100;yTest<100;yTest+=9)
	{
	    G4VoxelLimits yTestClip;
	    yTestClip.AddLimit(kYAxis,-kInfinity,yTest);
	    if (yTest<-50)
		{
		    assert(!s1.CalculateExtent(kXAxis,yTestClip,origin,min,max));
		}
	    else
		{
		   assert(s1.CalculateExtent(kXAxis,yTestClip,origin,min,max));
// Calc max y coordinate
		   G4double testMax=(yTest<0) ? sqrt(50*50-yTest*yTest) : 50;
		   assert (ApproxEqual(min,-testMax)
			   &&ApproxEqual(max,testMax));
		}
	}

	return 0;

}











