// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: faccb3.cxx,v 1.2 1999-12-15 14:48:47 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
/* 
	This is version 4.5 of XVT-Architect.
	This file was automatically generated by XVT-Architect,
	Do not modify its contents.
*/

#include "factory.h"
#include "XVTPwr.h"
#include "AppDef.h"
#include PwrGen_i
#include "facdec.h"
#include "classes.h"
#include "defines.h"
#include "faccb.h"
#define _PA_REF(x) x=x

void _Init_GUI_faccb3() { }

void* C_CTaskWin1004_GUI_DEFAULT(const PAFactory* theFactory, CObjectRWC* theData)
{
	_PA_REF(theFactory);
	_PA_REF(theData);
	CTaskWin* anInstance = NULL;
	return anInstance;
}

void I_CTaskWin1004_GUI_DEFAULT(const PAFactory* theFactory, CObjectRWC* theData, CDataMembers* theDataMembers)
{
	_PA_REF(theFactory);
	_PA_REF(theData);
	_PA_REF(theDataMembers);
	CTaskWin* anInstance = PtrCast(CTaskWin, theData);
	if (!anInstance) return;

	
	IPAFactoryView(anInstance, "", NULLcmd, NULLcmd, TRUE, TRUE, FALSE, TOPSTICKY|LEFTSTICKY, FALSE, FALSE);
	
	
	anInstance->SetBackgroundDrawing(FALSE);
	
	
}

CFactoryElement _CTaskWin1004DEFAULT(&GUIFactory, CTaskWin1004, 20044, 2, C_CTaskWin1004_GUI_DEFAULT, I_CTaskWin1004_GUI_DEFAULT, CTaskDoc1003, 0, 1, 1, 0);

void* C_CMenuButton1063_GUI_DEFAULT(const PAFactory* theFactory, CObjectRWC* theData)
{
	_PA_REF(theFactory);
	_PA_REF(theData);
	CSubview* anEnclosure = PtrCast( CSubview, theData );
	CMenuButton *anInstance = new CMenuButton( anEnclosure, CRect((UNITS)3, (UNITS)3, (UNITS)26, (UNITS)26), M_FILE_SAVE );
	return anInstance;
}

void I_CMenuButton1063_GUI_DEFAULT(const PAFactory* theFactory, CObjectRWC* theData, CDataMembers* theDataMembers)
{
	_PA_REF(theFactory);
	_PA_REF(theData);
	_PA_REF(theDataMembers);
	CMenuButton* anInstance = PtrCast(CMenuButton, theData);
	if (!anInstance) return;

	
	IPAFactoryView(anInstance, "", NULLcmd, NULLcmd, TRUE, TRUE, FALSE, TOPSTICKY|LEFTSTICKY, FALSE, FALSE);
	
	
	anInstance->SetTogglable( FALSE );
	CImage anImage(1000);
	CPicture* aPicture = new CPicture( anInstance, CPoint((UNITS)0, (UNITS)0), anImage );
	_PA_REF(aPicture);
	anInstance->SetCommands( NULLcmd, NULLcmd, SAVE_LOG_INcmd, SAVE_LOG_OUTcmd );
	anInstance->SizeToFit();
	
	
}

CFactoryElement _CMenuButton1063DEFAULT(&GUIFactory, CMenuButton1063, 20126, 3, C_CMenuButton1063_GUI_DEFAULT, I_CMenuButton1063_GUI_DEFAULT, LogBar, 0, 1, 13, 0);

void* C_CMenuButton1078_GUI_DEFAULT(const PAFactory* theFactory, CObjectRWC* theData)
{
	_PA_REF(theFactory);
	_PA_REF(theData);
	CSubview* anEnclosure = PtrCast( CSubview, theData );
	CMenuButton *anInstance = new CMenuButton( anEnclosure, CRect((UNITS)128, (UNITS)3, (UNITS)151, (UNITS)26), PAUSEcmd );
	return anInstance;
}

void I_CMenuButton1078_GUI_DEFAULT(const PAFactory* theFactory, CObjectRWC* theData, CDataMembers* theDataMembers)
{
	_PA_REF(theFactory);
	_PA_REF(theData);
	_PA_REF(theDataMembers);
	CMenuButton* anInstance = PtrCast(CMenuButton, theData);
	if (!anInstance) return;

	
	IPAFactoryView(anInstance, "", NULLcmd, NULLcmd, TRUE, TRUE, FALSE, TOPSTICKY|LEFTSTICKY, FALSE, FALSE);
	
	
	anInstance->SetTogglable( FALSE );
	CImage anImage(1005);
	CPicture* aPicture = new CPicture( anInstance, CPoint((UNITS)0, (UNITS)0), anImage );
	_PA_REF(aPicture);
	anInstance->SetCommands( NULLcmd, NULLcmd, PAUSE_INcmd, PAUSE_OUTcmd );
	anInstance->SizeToFit();
	
	
}

CFactoryElement _CMenuButton1078DEFAULT(&GUIFactory, CMenuButton1078, 20126, 3, C_CMenuButton1078_GUI_DEFAULT, I_CMenuButton1078_GUI_DEFAULT, LogBar, 0, 1, 13, 5);

void* C_execButton_GUI_DEFAULT(const PAFactory* theFactory, CObjectRWC* theData)
{
	_PA_REF(theFactory);
	_PA_REF(theData);
	CSubview* anEnclosure = PtrCast( CSubview, theData );
	CMenuButton *anInstance = new CMenuButton( anEnclosure, CRect((UNITS)660, (UNITS)3, (UNITS)683, (UNITS)26), EXECUTEcmd );
	return anInstance;
}

void I_execButton_GUI_DEFAULT(const PAFactory* theFactory, CObjectRWC* theData, CDataMembers* theDataMembers)
{
	_PA_REF(theFactory);
	_PA_REF(theData);
	_PA_REF(theDataMembers);
	CMenuButton* anInstance = PtrCast(CMenuButton, theData);
	if (!anInstance) return;

	
	IPAFactoryView(anInstance, "", NULLcmd, NULLcmd, TRUE, FALSE, FALSE, TOPSTICKY|LEFTSTICKY, FALSE, FALSE);
	
	
	anInstance->SetTogglable( FALSE );
	CImage anImage(1009);
	CPicture* aPicture = new CPicture( anInstance, CPoint((UNITS)0, (UNITS)0), anImage );
	_PA_REF(aPicture);
	anInstance->SetCommands( NULLcmd, NULLcmd, EXECUTE_INcmd, EXECUTE_OUTcmd );
	anInstance->SizeToFit();
	
	
}

CFactoryElement _execButtonDEFAULT(&GUIFactory, execButton, 20126, 3, C_execButton_GUI_DEFAULT, I_execButton_GUI_DEFAULT, LogBar, 0, 1, 13, 10);

void* C_DropArea_GUI_DEFAULT(const PAFactory* theFactory, CObjectRWC* theData)
{
	_PA_REF(theFactory);
	_PA_REF(theData);
	CSubview* anEnclosure = PtrCast( CSubview, theData );
	CScroller* anInstance = new CScroller(anEnclosure, CRect((UNITS)0, (UNITS)255, (UNITS)966, (UNITS)710));

	return anInstance;
}

void I_DropArea_GUI_DEFAULT(const PAFactory* theFactory, CObjectRWC* theData, CDataMembers* theDataMembers)
{
	_PA_REF(theFactory);
	_PA_REF(theData);
	_PA_REF(theDataMembers);
	CScroller* anInstance = PtrCast(CScroller, theData);
	if (!anInstance) return;

	
	IPAFactoryView(anInstance, "", NULLcmd, NULLcmd, TRUE, TRUE, FALSE, TOPSTICKY|RIGHTSTICKY|LEFTSTICKY|BOTTOMSTICKY, FALSE, FALSE);
	
	
	anInstance->SetScrollingOrigin( CPoint((UNITS)0, (UNITS)0));
	anInstance->SetVirtualFrame((UNITS)0, (UNITS)0);
	
	anInstance->IScroller(FALSE,FALSE,TRUE, (UNITS)8, (UNITS)80,anInstance->IsVisible(), anInstance->GetGlue());
	
}

CFactoryElement _DropAreaDEFAULT(&GUIFactory, DropArea, 20017, 3, C_DropArea_GUI_DEFAULT, I_DropArea_GUI_DEFAULT, G4Win, 0, 1, 5, 4);

