// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: factory.cxx,v 1.2 1999-12-15 14:48:48 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
/* 
	This is version 4.5 of XVT-Architect.
	This file was automatically generated by XVT-Architect,
	Do not modify its contents.
*/

#include "factory.h"
#include "faccmd.h"


CGUIFactory GUIFactory;

int CGUIFactory::itIsInitialized = 0;

extern void _Init_GUI_faccb0();
extern void _Init_GUI_faccb1();
extern void _Init_GUI_faccb2();
extern void _Init_GUI_faccb3();
extern void _Init_GUI_faccb4();

CGUIFactory::CGUIFactory(void)
: PAFactory(itIsInitialized)
{
	itIsInitialized = 1;
	_Init_GUI_faccb0();
	_Init_GUI_faccb1();
	_Init_GUI_faccb2();
	_Init_GUI_faccb3();
	_Init_GUI_faccb4();
}

CGUIFactory& CGUIFactory::operator[](CGUIFactory::LayerID theLayer)
{
	PAFactory::operator[]((long) theLayer);
	return *this;
}

void CGUIFactory::SetDefaultLayer(CGUIFactory::LayerID theLayer)
{
	PAFactory::SetDefaultLayer((long) theLayer);
}

CGUIFactory::LayerID CGUIFactory::GetDefaultLayer(void) const
{
	return (CGUIFactory::LayerID) PAFactory::GetDefaultLayer();
}

long CGUIFactory::GetLayerBase(CGUIFactory::LayerID theLayerID)
{
	switch(theLayerID) {
		case DEFAULT: return DEFAULT_BASE;
	}
	return 0;
}

