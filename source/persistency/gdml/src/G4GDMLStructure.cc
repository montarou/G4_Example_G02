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
// $Id: G4GDMLStructure.cc,v 1.29 2007-12-11 09:57:34 ztorzsok Exp $
// GEANT4 tag $ Name:$
//
// class G4GDMLStructure Implementation
//
// Original author: Zoltan Torzsok, November 2007
//
// --------------------------------------------------------------------

#include "G4GDMLStructure.hh"

EAxis G4GDMLStructure::directionRead(const xercesc::DOMElement* const element) {

   G4double x = 0.0;
   G4double y = 0.0;
   G4double z = 0.0;

   const xercesc::DOMNamedNodeMap* const attributes = element->getAttributes();
   XMLSize_t attributeCount = attributes->getLength();

   for (XMLSize_t attribute_index=0;attribute_index<attributeCount;attribute_index++) {

      xercesc::DOMNode* attribute_node = attributes->item(attribute_index);

      if (attribute_node->getNodeType() != xercesc::DOMNode::ATTRIBUTE_NODE) continue;

      const xercesc::DOMAttr* const attribute = dynamic_cast<xercesc::DOMAttr*>(attribute_node);   

      const G4String attName = xercesc::XMLString::transcode(attribute->getName());
      const G4String attValue = xercesc::XMLString::transcode(attribute->getValue());

      if (attName=="x") x = eval.Evaluate(attValue); else
      if (attName=="y") y = eval.Evaluate(attValue); else
      if (attName=="z") z = eval.Evaluate(attValue);
   }

   if (x == 1.0 && y == 0.0 && z == 0.0) return kXAxis; else
   if (x == 0.0 && y == 1.0 && z == 0.0) return kYAxis; else
   if (x == 0.0 && y == 0.0 && z == 1.0) return kZAxis;

   G4Exception("GDML: Only directions along axes are supported!");

   return kUndefined;
}

void G4GDMLStructure::divisionvolRead(const xercesc::DOMElement* const element,G4LogicalVolume* pMother) {

   G4double unit = 1.0;
   G4double width = 0.0;
   G4double offset = 0.0;
   G4int number = 0;
   G4String volumeref;
   EAxis axis = kUndefined;

   const xercesc::DOMNamedNodeMap* const attributes = element->getAttributes();
   XMLSize_t attributeCount = attributes->getLength();

   for (XMLSize_t attribute_index=0;attribute_index<attributeCount;attribute_index++) {

      xercesc::DOMNode* attribute_node = attributes->item(attribute_index);

      if (attribute_node->getNodeType() != xercesc::DOMNode::ATTRIBUTE_NODE) continue;

      const xercesc::DOMAttr* const attribute = dynamic_cast<xercesc::DOMAttr*>(attribute_node);   

      const G4String attName = xercesc::XMLString::transcode(attribute->getName());
      const G4String attValue = xercesc::XMLString::transcode(attribute->getValue());

      if (attName=="unit") unit = eval.Evaluate(attValue); else
      if (attName=="width") width = eval.Evaluate(attValue); else
      if (attName=="offset") offset = eval.Evaluate(attValue); else
      if (attName=="number") number = eval.EvaluateInteger(attValue); else
      if (attName=="axis") {
      
         if (attValue=="kXAxis") axis = kXAxis; else
         if (attValue=="kYAxis") axis = kYAxis; else
         if (attValue=="kZAxis") axis = kZAxis; else
         if (attValue=="kRho") axis = kRho; else
         if (attValue=="kPhi") axis = kPhi;
      }
   }

   width *= unit;
   offset *= unit;

   for (xercesc::DOMNode* iter = element->getFirstChild();iter != 0;iter = iter->getNextSibling()) {

      if (iter->getNodeType() != xercesc::DOMNode::ELEMENT_NODE) continue;

      const xercesc::DOMElement* const child = dynamic_cast<xercesc::DOMElement*>(iter);

      const G4String tag = xercesc::XMLString::transcode(child->getTagName());

      if (tag=="volumeref") volumeref = refRead(child);
   }

   G4LogicalVolume* pLogical = getVolume(GenerateName(volumeref));

   new G4PVDivision("",pLogical,pMother,axis,number,width,offset);
}

G4LogicalVolume* G4GDMLStructure::fileRead(const xercesc::DOMElement* const element) {

   G4String name;
   G4String volname;

   const xercesc::DOMNamedNodeMap* const attributes = element->getAttributes();
   XMLSize_t attributeCount = attributes->getLength();

   for (XMLSize_t attribute_index=0;attribute_index<attributeCount;attribute_index++) {

      xercesc::DOMNode* attribute_node = attributes->item(attribute_index);

      if (attribute_node->getNodeType() != xercesc::DOMNode::ATTRIBUTE_NODE) continue;

      const xercesc::DOMAttr* const attribute = dynamic_cast<xercesc::DOMAttr*>(attribute_node);   

      const G4String attName = xercesc::XMLString::transcode(attribute->getName());
      const G4String attValue = xercesc::XMLString::transcode(attribute->getValue());

      if (attName=="name") name = attValue; else
      if (attName=="volname") volname = attValue;
   }

   G4GDMLStructure structure; // We create a new structure with a new evaluator
   
   structure.Parse(name);

   return structure.getVolume(structure.GenerateName(volname));
}

void G4GDMLStructure::loopRead(const xercesc::DOMElement* const element) {

   G4String var;
   G4String from;
   G4String to;
   G4String step;

   const xercesc::DOMNamedNodeMap* const attributes = element->getAttributes();
   XMLSize_t attributeCount = attributes->getLength();

   for (XMLSize_t attribute_index=0;attribute_index<attributeCount;attribute_index++) {

      xercesc::DOMNode* attribute_node = attributes->item(attribute_index);

      if (attribute_node->getNodeType() != xercesc::DOMNode::ATTRIBUTE_NODE) continue;

      const xercesc::DOMAttr* const attribute = dynamic_cast<xercesc::DOMAttr*>(attribute_node);   

      const G4String attribute_name = xercesc::XMLString::transcode(attribute->getName());
      const G4String attribute_value = xercesc::XMLString::transcode(attribute->getValue());

      if (attribute_name=="var") var  = attribute_value; else
      if (attribute_name=="from") from = attribute_value; else
      if (attribute_name=="to") to = attribute_value; else
      if (attribute_name=="step") step = attribute_value;
   }

   eval.checkVariable(var);

   G4int _var = eval.EvaluateInteger(var );
   G4int _from = eval.EvaluateInteger(from);
   G4int _to = eval.EvaluateInteger(to  );
   G4int _step = eval.EvaluateInteger(step);
   
   if (!from.empty()) _var = _from;

   while (_var <= _to) {
   
      eval.setVariable(var,_var);
      structureRead(element);

      _var += _step;
   }
}

void G4GDMLStructure::physvolRead(const xercesc::DOMElement* const element,G4LogicalVolume *mother) {

   G4LogicalVolume* logvol = 0;

   G4ThreeVector position;
   G4ThreeVector rotation;
   G4ThreeVector scale(1.0,1.0,1.0);

   for (xercesc::DOMNode* iter = element->getFirstChild();iter != 0;iter = iter->getNextSibling()) {

      if (iter->getNodeType() != xercesc::DOMNode::ELEMENT_NODE) continue;

      const xercesc::DOMElement* const child = dynamic_cast<xercesc::DOMElement*>(iter);

      const G4String tag = xercesc::XMLString::transcode(child->getTagName());

      if (tag=="file") logvol = fileRead(child); else
      if (tag=="volumeref") logvol = getVolume(GenerateName(refRead(child))); else
      if (tag=="position") position = positionRead(child); else
      if (tag=="rotation") rotation = rotationRead(child); else
      if (tag=="scale") scale = scaleRead(child); else
      if (tag=="positionref") position = *getPosition(GenerateName(refRead(child))); else
      if (tag=="rotationref") rotation = *getRotation(GenerateName(refRead(child))); else
      if (tag=="scaleref") scale = *getScale(GenerateName(refRead(child)));
   }

   G4RotationMatrix Rot;

   Rot.rotateX(rotation.x());
   Rot.rotateY(rotation.y());
   Rot.rotateZ(rotation.z());
   
   G4Transform3D transform(Rot.inverse(),position);
   transform = transform*G4Scale3D(scale.x(),scale.y(),scale.z());

   G4ReflectionFactory::Instance()->Place(transform,"",logvol,mother,false,0);
}

G4double G4GDMLStructure::quantityRead(const xercesc::DOMElement* const element) {

   G4double value = 0.0;
   G4double unit = 1.0;

   const xercesc::DOMNamedNodeMap* const attributes = element->getAttributes();
   XMLSize_t attributeCount = attributes->getLength();

   for (XMLSize_t attribute_index=0;attribute_index<attributeCount;attribute_index++) {

      xercesc::DOMNode* attribute_node = attributes->item(attribute_index);

      if (attribute_node->getNodeType() != xercesc::DOMNode::ATTRIBUTE_NODE) continue;

      const xercesc::DOMAttr* const attribute = dynamic_cast<xercesc::DOMAttr*>(attribute_node);   

      const G4String attName = xercesc::XMLString::transcode(attribute->getName());
      const G4String attValue = xercesc::XMLString::transcode(attribute->getValue());

      if (attName=="value") value = eval.Evaluate(attValue);
      if (attName=="unit") unit = eval.Evaluate(attValue);
   }

   return value*unit;
}

void G4GDMLStructure::replicate_along_axisRead(const xercesc::DOMElement* const element,G4double& width,G4double& offset,EAxis& axis) {

   for (xercesc::DOMNode* iter = element->getFirstChild();iter != 0;iter = iter->getNextSibling()) {

      if (iter->getNodeType() != xercesc::DOMNode::ELEMENT_NODE) continue;

      const xercesc::DOMElement* const child = dynamic_cast<xercesc::DOMElement*>(iter);

      const G4String tag = xercesc::XMLString::transcode(child->getTagName());

      if (tag=="width") width = quantityRead(child); else
      if (tag=="offset") offset = quantityRead(child); else
      if (tag=="direction") axis = directionRead(child);
   }
}

void G4GDMLStructure::replicavolRead(const xercesc::DOMElement* const element,G4LogicalVolume* pMother) {

   G4int numb = 0;

   const xercesc::DOMNamedNodeMap* const attributes = element->getAttributes();
   XMLSize_t attributeCount = attributes->getLength();

   for (XMLSize_t attribute_index=0;attribute_index<attributeCount;attribute_index++) {

      xercesc::DOMNode* attribute_node = attributes->item(attribute_index);

      if (attribute_node->getNodeType() != xercesc::DOMNode::ATTRIBUTE_NODE) continue;

      const xercesc::DOMAttr* const attribute = dynamic_cast<xercesc::DOMAttr*>(attribute_node);   

      const G4String attName = xercesc::XMLString::transcode(attribute->getName());
      const G4String attValue = xercesc::XMLString::transcode(attribute->getValue());

      if (attName=="numb") numb = eval.EvaluateInteger(attValue);
   }

   G4double width;
   G4double offset;
   EAxis axis;

   G4LogicalVolume* pLogical = 0;

   for (xercesc::DOMNode* iter = element->getFirstChild();iter != 0;iter = iter->getNextSibling()) {

      if (iter->getNodeType() != xercesc::DOMNode::ELEMENT_NODE) continue;

      const xercesc::DOMElement* const child = dynamic_cast<xercesc::DOMElement*>(iter);

      const G4String tag = xercesc::XMLString::transcode(child->getTagName());

      if (tag=="volumeref") pLogical = getVolume(GenerateName(refRead(child))); else
      if (tag=="replicate_along_axis") replicate_along_axisRead(child,width,offset,axis);
   }

   new G4PVReplica("",pLogical,pMother,axis,numb,width,offset);
}

void G4GDMLStructure::volumeRead(const xercesc::DOMElement* const element) {

   G4String name;

   G4VSolid* solidPtr = 0;
   G4Material* materialPtr = 0;

   XMLCh *name_attr = xercesc::XMLString::transcode("name");
   name = xercesc::XMLString::transcode(element->getAttribute(name_attr));
   xercesc::XMLString::release(&name_attr);

   for (xercesc::DOMNode* iter = element->getFirstChild();iter != 0;iter = iter->getNextSibling()) {

      if (iter->getNodeType() != xercesc::DOMNode::ELEMENT_NODE) continue;

      const xercesc::DOMElement* const child = dynamic_cast<xercesc::DOMElement*>(iter);

      const G4String tag = xercesc::XMLString::transcode(child->getTagName());

      if (tag=="materialref") materialPtr = getMaterial(GenerateName(refRead(child))); else
      if (tag=="solidref") solidPtr = getSolid(GenerateName(refRead(child)));
   }

   volume_contentRead(element,new G4LogicalVolume(solidPtr,materialPtr,GenerateName(name),0,0,0));
}

void G4GDMLStructure::volume_contentRead(const xercesc::DOMElement* const element,G4LogicalVolume* volumePtr) {

   for (xercesc::DOMNode* iter = element->getFirstChild();iter != 0;iter = iter->getNextSibling()) {

      if (iter->getNodeType() != xercesc::DOMNode::ELEMENT_NODE) continue;

      const xercesc::DOMElement* const child = dynamic_cast<xercesc::DOMElement*>(iter);
  
      const G4String tag = xercesc::XMLString::transcode(child->getTagName());

      if (tag=="loop") volume_loopRead(child,volumePtr); else
      if (tag=="paramvol") paramvolRead(child,volumePtr); else
      if (tag=="physvol") physvolRead(child,volumePtr); else
      if (tag=="replicavol") replicavolRead(child,volumePtr); else
      if (tag=="divisionvol") divisionvolRead(child,volumePtr);
   }
}

void G4GDMLStructure::volume_loopRead(const xercesc::DOMElement* const element,G4LogicalVolume* volumePtr) {

   G4String var;
   G4String from;
   G4String to;
   G4String step;

   const xercesc::DOMNamedNodeMap* const attributes = element->getAttributes();
   XMLSize_t attributeCount = attributes->getLength();

   for (XMLSize_t attribute_index=0;attribute_index<attributeCount;attribute_index++) {

      xercesc::DOMNode* attribute_node = attributes->item(attribute_index);

      if (attribute_node->getNodeType() != xercesc::DOMNode::ATTRIBUTE_NODE) continue;

      const xercesc::DOMAttr* const attribute = dynamic_cast<xercesc::DOMAttr*>(attribute_node);   

      const G4String attribute_name = xercesc::XMLString::transcode(attribute->getName());
      const G4String attribute_value = xercesc::XMLString::transcode(attribute->getValue());

      if (attribute_name=="var") var  = attribute_value; else
      if (attribute_name=="from") from = attribute_value; else
      if (attribute_name=="to") to = attribute_value; else
      if (attribute_name=="step") step = attribute_value;
   }

   eval.checkVariable(var);

   G4int _var  = eval.EvaluateInteger(var);
   G4int _from = eval.EvaluateInteger(from);
   G4int _to   = eval.EvaluateInteger(to);
   G4int _step = eval.EvaluateInteger(step);
   
   if (!from.empty()) _var = _from;

   while (_var <= _to) {
   
      eval.setVariable(var,_var);
      volume_contentRead(element,volumePtr);

      _var += _step;
   }
}

void G4GDMLStructure::structureRead(const xercesc::DOMElement* const element) {

   for (xercesc::DOMNode* iter = element->getFirstChild();iter != 0;iter = iter->getNextSibling()) {

      if (iter->getNodeType() != xercesc::DOMNode::ELEMENT_NODE) continue;

      const xercesc::DOMElement* const child = dynamic_cast<xercesc::DOMElement*>(iter);

      const G4String tag = xercesc::XMLString::transcode(child->getTagName());

      if (tag=="loop") loopRead(child); else
      if (tag=="volume") volumeRead(child); else      
      G4Exception("GDML: Unknown tag in structure: "+tag);
   }
}

G4LogicalVolume* G4GDMLStructure::getVolume(const G4String& ref) const {

   G4LogicalVolume *volumePtr = G4LogicalVolumeStore::GetInstance()->GetVolume(ref,false);

   if (!volumePtr) G4Exception("GDML: Referenced volume '"+ref+"' was not found!");

   return volumePtr;
}
