#ifdef G4VIS_BUILD_OI_DRIVER

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
// $Id: SoDetectorTreeKit.cc,v 1.7 2004-12-07 23:41:00 perl Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
/*-----------------------------HEPVis----------------------------------------*/
/*                                                                           */
/* Node:             SoDetectorTreeKit                                       */
/* Description:      Represents a single sided silicon strip detector        */
/* Author:           Joe Boudreau Nov 11 1996                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// this :
#include "HEPVis/nodekits/SoDetectorTreeKit.h"

#include <cmath>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/SoPickedPoint.h>
#include <Inventor/nodes/SoPickStyle.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodekits/SoAppearanceKit.h>
#include <Inventor/nodekits/SoNodeKitListPart.h>
#include <Inventor/nodekits/SoBaseKit.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodekits/SoSeparatorKit.h>
#include <Inventor/nodekits/SoShapeKit.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/nodes/SoUnits.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoTexture2Transform.h>

// This statement is required
SO_KIT_SOURCE(SoDetectorTreeKit) 
 
// initClass
void SoDetectorTreeKit::initClass(){
  SO_KIT_INIT_CLASS(SoDetectorTreeKit,SoBaseKit,"BaseKit");
}

// Constructor
SoDetectorTreeKit::SoDetectorTreeKit() {
  SO_KIT_CONSTRUCTOR(SoDetectorTreeKit);

  SO_NODE_ADD_FIELD(alternateRep, (NULL));

  SO_KIT_ADD_CATALOG_ENTRY     (     topSeparator,         SoSeparator, FALSE,          this,\0, FALSE);
  SO_KIT_ADD_CATALOG_ENTRY     (        pickStyle,         SoSeparator, TRUE ,  topSeparator,\0, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY     (       appearance,     SoAppearanceKit, TRUE,  topSeparator ,\0, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY     (            units,             SoUnits, TRUE,  topSeparator ,\0, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY     (        transform,         SoTransform, TRUE ,  topSeparator,\0, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY     (texture2Transform, SoTexture2Transform, TRUE,  topSeparator ,\0, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY     (        childList,            SoSwitch, FALSE,  topSeparator,\0, FALSE);
  SO_KIT_ADD_CATALOG_ENTRY     ( previewSeparator,         SoSeparator, FALSE,     childList,\0, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY     (    fullSeparator,         SoSeparator, FALSE,     childList,\0, TRUE);

  SO_KIT_INIT_INSTANCE();
  createInitialTree();
}

// Destructor
SoDetectorTreeKit::~SoDetectorTreeKit() {
}


SbBool SoDetectorTreeKit::affectsState() const {
  return FALSE;
}

void SoDetectorTreeKit::createInitialTree() {

  SoEventCallback *myCallback = new SoEventCallback();
  myCallback->addEventCallback(SoMouseButtonEvent::getClassTypeId(),
                               SoDetectorTreeKit::expand,
                               this);
  myCallback->addEventCallback(SoMouseButtonEvent::getClassTypeId(),
                               SoDetectorTreeKit::contract  ,
                               this);
  if(setPart("callbackList[0]",myCallback)==FALSE) myCallback->unref(); 

  SoSwitch *theChildList = (SoSwitch *) childList.getValue();
  theChildList->whichChild.setValue(0);
}

void SoDetectorTreeKit::expand(void *userData, SoEventCallback *eventCB){

  // Was the event previously handled? Is it the right kind?

  if (eventCB->isHandled()) return;
  const SoMouseButtonEvent *event= (SoMouseButtonEvent *) eventCB->getEvent();
  if (!SoMouseButtonEvent::isButtonPressEvent(event,SoMouseButtonEvent::BUTTON1)) return;
  if (!event->wasCtrlDown()) return;
  if (event->wasShiftDown()) return;

  // Which Detector is this being called for?
  SoDetectorTreeKit* This = (SoDetectorTreeKit *) userData;

  // Find out whether that's the one that has been picked.  
  // "This' is the lowest detector tree kit in the hierarchy.
  SoHandleEventAction *handleEventAction = eventCB->getAction();
  const SoPickedPoint *pickedPoint = handleEventAction->getPickedPoint();
  if (!pickedPoint) return;

  SoFullPath* path = (SoFullPath*)pickedPoint->getPath();
  SoNode *ancestorNode=NULL;
  for (int i=0;i<path->getLength();i++) {
    ancestorNode  = path->getNodeFromTail(i);
    if (ancestorNode->isOfType(SoDetectorTreeKit::getClassTypeId()))  break;
  }
  if (This!=ancestorNode) return;
  //  if (!ancestorNode->isOfType(SoDetectorTreeKit::getClassTypeId())) return;
 
  // Deactivate the Preview
  This->setPreview(FALSE);
  eventCB->setHandled();
     
}

void SoDetectorTreeKit::contract(void *userData, SoEventCallback *eventCB){

  // Was the event previously handled? Is it the right kind?
  if (eventCB->isHandled()) return;
  const SoMouseButtonEvent *event= (SoMouseButtonEvent *) eventCB->getEvent();
  if (!SoMouseButtonEvent::isButtonPressEvent(event,SoMouseButtonEvent::BUTTON1)) return;
  if (event->wasCtrlDown()) return;
  if (!event->wasShiftDown()) return;

  // Which Detector is this being called for?
  SoDetectorTreeKit* This = (SoDetectorTreeKit *) userData;

  // Find out whether that's the one that has been picked
  SoHandleEventAction *handleEventAction = eventCB->getAction();
  const SoPickedPoint *pickedPoint = handleEventAction->getPickedPoint();
  if (!pickedPoint) return;
 
  // Find out whether that's the one that has been picked.  
  // "This" is the lowest detector tree kit in the hierarchy.
  SoFullPath* path = (SoFullPath*)pickedPoint->getPath();
  SoNode *ancestorNode=NULL;
  SbBool firstTreeFound=FALSE;
  for (int i=0;i<path->getLength();i++) {
    ancestorNode  = path->getNodeFromTail(i);
    if (ancestorNode->isOfType(SoDetectorTreeKit::getClassTypeId())) {
      if (!firstTreeFound) {
        if (This!=ancestorNode) return;
        firstTreeFound=TRUE;
      }
      SoDetectorTreeKit *That = (SoDetectorTreeKit *) ancestorNode;
      if (!That->getPreview()) {
        That->setPreview(TRUE);
        eventCB->setHandled();
        return;
      }
    }
  }
}

void SoDetectorTreeKit::setPreview(SbBool Flag) {
  SoSwitch *theChildList = (SoSwitch *) childList.getValue();
  if (Flag) {
    theChildList->whichChild.setValue(0);
  }
  else {
    theChildList->whichChild.setValue(1);
  }
}

SbBool SoDetectorTreeKit::getPreview() const {
  SoSwitch *theChildList = (SoSwitch *) childList.getValue();
  if (theChildList->whichChild.getValue()==0) return TRUE;
  return FALSE;
}


void SoDetectorTreeKit::setPreviewAndFull() {
  SoSwitch *theChildList = (SoSwitch *) childList.getValue();
  theChildList->whichChild.setValue(SO_SWITCH_ALL);
}

SoSeparator *SoDetectorTreeKit::getPreviewSeparator() const {
  return (SoSeparator *) previewSeparator.getValue();
}

SoSeparator *SoDetectorTreeKit::getFullSeparator() const {
  return (SoSeparator *) fullSeparator.getValue();
}




// generateAlternateRep
void SoDetectorTreeKit::generateAlternateRep() {
  alternateRep.setValue(topSeparator.getValue());
}

void SoDetectorTreeKit::clearAlternateRep() {
  alternateRep.setValue(NULL);
}

#endif
