/* $Id: main.h,v 1.5 1997/05/27 15:21:47 paul Exp $ */

#ifndef _commtestMainINCLUDED
#define _commtestMainINCLUDED 1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef vnotebookINCLUDED
#include vnotebookHEADER
#endif

typedef struct
{
    vnotebookPage    *_ControlPageTemplate;
    vnotebookPage    *_IPLocatorPageTemplate;
    vnotebookPage    *_TCPAttributePageTemplate;
    vnotebookPage    *_UDPAttributePageTemplate;
    vnotebookPage    *_DomainLocatorPageTemplate;
    vnotebookPage    *_PipeAttributePageTemplate;
    vnotebookPage    *_MbxAttributePageTemplate;
    vnotebookPage    *_ShmLocatorPageTemplate;
    vnotebookPage    *_ShmAttributePageTemplate;
    vdialog          *_ConnectionDialogTemplate;
    vdialog          *_TCPDialogTemplate;
    vdialog          *_UDPDialogTemplate;
    vdialog          *_PipeDialogTemplate;
    vdialog          *_MbxDialogTemplate;
    vdialog          *_ShmDialogTemplate;
}  _commtestGlobalsStruct;

vnotebookPage *	_getControlPageTemplate(void);
vnotebookPage *	_getIPLocatorPageTemplate(void);
vnotebookPage *	_getTCPAttributePageTemplate(void);
vnotebookPage *	_getUDPAttributePageTemplate(void);
vnotebookPage *	_getDomainLocatorPageTemplate(void);
vnotebookPage *	_getPipeAttributePageTemplate(void);
vnotebookPage *	_getMbxAttributePageTemplate(void);
vnotebookPage *	_getShmLocatorPageTemplate(void);
vnotebookPage *	_getShmAttributePageTemplate(void);
vdialog *	_getConnectionDialogTemplate(void);
vdialog *	_getTCPDialogTemplate(void);
vdialog *	_getUDPDialogTemplate(void);
vdialog *	_getPipeDialogTemplate(void);
vdialog *	_getMbxDialogTemplate(void);
vdialog *	_getShmDialogTemplate(void);

void _mainStartUp(void);
void _mainShutDown(void);

#endif
