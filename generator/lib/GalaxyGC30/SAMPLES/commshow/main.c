/* $Id: main.c,v 1.5 1997/05/27 15:21:47 paul Exp $ */

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vbuttonINCLUDED
#include vbuttonHEADER
#endif

#ifndef  vcontrolINCLUDED
#include vcontrolHEADER
#endif

#ifndef  vnotebookINCLUDED
#include vnotebookHEADER
#endif

#ifndef  vtextitemINCLUDED
#include vtextitemHEADER
#endif

#ifndef  vcommandINCLUDED
#include vcommandHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vkeyINCLUDED
#include vkeyHEADER
#endif

#ifndef  vmenuINCLUDED
#include vmenuHEADER
#endif

#ifndef  _commtestCommshowINCLUDED
#include "commshow.h"
#endif

#ifndef  _commtestMainINCLUDED
#include "main.h"
#endif

#ifndef  _commtestAttribINCLUDED
#include "attrib.h"
#endif

#ifndef  _commtestControlINCLUDED
#include "control.h"
#endif

#ifndef  _commtestCreateINCLUDED
#include "create.h"
#endif

#ifndef  _commtestAttribINCLUDED
#include "attrib.h"
#endif

#ifndef  _commtestUtilINCLUDED
#include "util.h"
#endif

/*************************************************************************
 * Local constant definitions.
 *************************************************************************/
enum {
    SELECT_QUIT,
    SELECT_UDP,
    SELECT_MBX,
    SELECT_TCP,
    SELECT_PIPE,
    SELECT_SHM
};

static vcommandSelectorTemplate mainCommands[] = 
{
    {"QuitCommshow",         SELECT_QUIT},
    {"UDP",                  SELECT_UDP},
    {"Mailbox",              SELECT_MBX},
    {"TCP",                  SELECT_TCP},
    {"Pipe",                 SELECT_PIPE},
    {"Shm",                  SELECT_SHM}
};


/*************************************************************************
 * Global variable definitions.
 *************************************************************************/

static vdialog          *_mainDialog;
static vresource         _rootRes;
static _commtestGlobalsStruct  _commtestGlobals;

/*************************************************************************
 * Forward declarations.
 *************************************************************************/

static int     _mainIssue(vcommandSelector *cmd, vdict *context);
static void    _commtestGlobalsInit(void);
static void    _commtestGlobalsDestroy(void);
static void    _mainNotify(vdialog *dialog, vevent *event);
static void    _quitMain(vdialog *dialog);
static void    _connectDialogNotify(vdialog *dialog, vevent *event);

/*************************************************************************
 * Module functions.
 *************************************************************************/

void
_mainStartUp(void)
{
    vresource           res;
    vcommandSpace       *space;
    vdict               *cmdDict;
    vcommandSelectorClass *mainSelectorClass;

    _utilSetUpTextItemClasses();

    _rootRes = vapplicationGetResources(vapplicationGetCurrent());
    res = vresourceGet(_rootRes, TAG("MainDialog"));
    _mainDialog = vdialogLoad(res);
    vdialogSetNotify(_mainDialog, _mainNotify);

    res = vresourceGet(_rootRes, TAG("Green Color Specification"));
    _commtestGreen = vcolorLoadIntern(res);

    _commtestGlobalsInit();

    mainSelectorClass = vclassReproduce(vcommandGetDefaultSelectorClass());
    vclassSet(mainSelectorClass, vcommandISSUE, _mainIssue);

    space = vcommandCreateSpace();
    cmdDict = vcommandCreateDictOfClassSelectorTemplates(
                   mainSelectorClass,
                   mainCommands,
                   (size_t) sizeof(mainCommands) / sizeof(mainCommands[0]));

    vcommandAddSpaceDictOwned(space, vname_Command, cmdDict);
    vwindowSetSpaceOwned(vdialogGetWindow(_mainDialog), space);

    _attribSetupCommandSpace(_mainDialog);
    _controlSetupCommandSpace(_mainDialog);

    vdialogOpen(_mainDialog);
}

/*************************************************************************/
void
_mainShutDown(void)
{
    _commtestGlobalsDestroy();

    vdialogDestroy(_mainDialog);
}


/*************************************************************************/
static int
_mainIssue(vcommandSelector *cmd, vdict *context)
{
    switch(vcommandGetSelector(cmd))
    {
	case SELECT_QUIT:
	_quitMain(_mainDialog);
	break;

	case SELECT_UDP:
	_createUDP(_mainDialog);
	break;

	case SELECT_MBX:
	_createMailbox(_mainDialog);
	break;

	case SELECT_TCP:
	_createTCP(_mainDialog);
	break;

	case SELECT_PIPE:
	_createPipe(_mainDialog);
	break;

	case SELECT_SHM:
	_createShm(_mainDialog);
	break;

	default:
	break;
    }
    return TRUE;
}


/*************************************************************************/
static void
_mainNotify(vdialog *dialog, vevent *event)
{
    if (veventIsClose(event))
	_quitMain(dialog);
}


/*************************************************************************/
static void
_quitMain(vdialog *dialog)
{
    vwindow                  *window;
    vwindowFollowerIterator   iterator; 

    /*
     * followers are not notified of close when the parent closes,
     * so do clean up here (the same clean up that is done in the
     * followers notify upon Close)
     *
     * note: don't destroy the vmenu, it's a follower too...
     */
    vwindowInitFollowerIterator(&iterator, vdialogGetWindow(dialog));
    while (vwindowNextFollowerIterator(&iterator))
    {
	window = vwindowGetFollowerIteratorWindow(&iterator);
	if (!vclassIsKindOf(vwindowGetClass(window), vmenuGetDefaultClass()))
	    _destroyBase(window);
    }

    veventStopProcessing();
}

/*************************************************************************/
static void
_connectDialogNotify(vdialog *dialog, vevent *event)
{
    if (veventIsClose(event))
	_destroyBase(vdialogGetWindow(dialog));
}

/*************************************************************************/
static void
_commtestGlobalsInit(void)
{
    vmemSet((void *) &_commtestGlobals, 0, sizeof(_commtestGlobalsStruct));
}

/*************************************************************************/
static void
_commtestGlobalsDestroy(void)
{
    if (_commtestGlobals._ControlPageTemplate != NULL)
	vnotebookDestroyPage(_commtestGlobals._ControlPageTemplate);

    if (_commtestGlobals._IPLocatorPageTemplate != NULL)
	vnotebookDestroyPage(_commtestGlobals._IPLocatorPageTemplate);

    if (_commtestGlobals._TCPAttributePageTemplate != NULL)
	vnotebookDestroyPage(_commtestGlobals._TCPAttributePageTemplate);

    if (_commtestGlobals._UDPAttributePageTemplate != NULL)
	vnotebookDestroyPage(_commtestGlobals._UDPAttributePageTemplate);

    if (_commtestGlobals._DomainLocatorPageTemplate != NULL)
	vnotebookDestroyPage(_commtestGlobals._DomainLocatorPageTemplate);

    if (_commtestGlobals._PipeAttributePageTemplate != NULL)
	vnotebookDestroyPage(_commtestGlobals._PipeAttributePageTemplate);

    if (_commtestGlobals._MbxAttributePageTemplate != NULL)
	vnotebookDestroyPage(_commtestGlobals._MbxAttributePageTemplate);

    if (_commtestGlobals._ShmLocatorPageTemplate != NULL)
	vnotebookDestroyPage(_commtestGlobals._ShmLocatorPageTemplate);

    if (_commtestGlobals._ShmAttributePageTemplate != NULL)
	vnotebookDestroyPage(_commtestGlobals._ShmAttributePageTemplate);

    if (_commtestGlobals._ConnectionDialogTemplate != NULL)
	vdialogDestroy(_commtestGlobals._ConnectionDialogTemplate);

    if (_commtestGlobals._TCPDialogTemplate != NULL)
	vdialogDestroy(_commtestGlobals._TCPDialogTemplate);

    if (_commtestGlobals._UDPDialogTemplate != NULL)
	vdialogDestroy(_commtestGlobals._UDPDialogTemplate);

    if (_commtestGlobals._PipeDialogTemplate != NULL)
	vdialogDestroy(_commtestGlobals._PipeDialogTemplate);

    if (_commtestGlobals._MbxDialogTemplate != NULL)
	vdialogDestroy(_commtestGlobals._MbxDialogTemplate);

    if (_commtestGlobals._ShmDialogTemplate != NULL)
	vdialogDestroy(_commtestGlobals._ShmDialogTemplate);
}

/*************************************************************************/
vnotebookPage *
_getControlPageTemplate(void)
{
    vresource pageRes;

    if (_commtestGlobals._ControlPageTemplate == NULL)
    {
	pageRes = vresourceGet(_rootRes, TAG("ControlPage"));
	_commtestGlobals._ControlPageTemplate = vnotebookLoadPage(pageRes);
    }
    return _commtestGlobals._ControlPageTemplate;
}

/*************************************************************************/
vnotebookPage *
_getIPLocatorPageTemplate(void)
{
    vresource pageRes;

    if (_commtestGlobals._IPLocatorPageTemplate == NULL)
    {
	pageRes = vresourceGet(_rootRes, TAG("IPLocatorPage"));
	_commtestGlobals._IPLocatorPageTemplate = vnotebookLoadPage(pageRes);
    }
    return _commtestGlobals._IPLocatorPageTemplate;
}

/*************************************************************************/
vnotebookPage *
_getTCPAttributePageTemplate(void)
{
    vresource pageRes;

    if (_commtestGlobals._TCPAttributePageTemplate == NULL)
    {
	pageRes = vresourceGet(_rootRes, TAG("TCPAttributePage"));
	_commtestGlobals._TCPAttributePageTemplate 
	    = vnotebookLoadPage(pageRes);
    }
    return _commtestGlobals._TCPAttributePageTemplate;
}

/*************************************************************************/
vnotebookPage *
_getUDPAttributePageTemplate(void)
{
    vresource pageRes;

    if (_commtestGlobals._UDPAttributePageTemplate == NULL)
    {
	pageRes = vresourceGet(_rootRes, TAG("UDPAttributePage"));
	_commtestGlobals._UDPAttributePageTemplate = 
	    vnotebookLoadPage(pageRes);
    }
    return _commtestGlobals._UDPAttributePageTemplate;
}

/*************************************************************************/
vnotebookPage *
_getDomainLocatorPageTemplate(void)
{
    vresource pageRes;

    if (_commtestGlobals._DomainLocatorPageTemplate == NULL)
    {
	pageRes = vresourceGet(_rootRes, TAG("DomainLocatorPage"));
	_commtestGlobals._DomainLocatorPageTemplate = 
	    vnotebookLoadPage(pageRes);
    }
    return _commtestGlobals._DomainLocatorPageTemplate;
}

/*************************************************************************/
vnotebookPage *
_getPipeAttributePageTemplate(void)
{
    vresource pageRes;

    if (_commtestGlobals._PipeAttributePageTemplate == NULL)
    {
	pageRes = vresourceGet(_rootRes, TAG("PipeAttributePage"));
	_commtestGlobals._PipeAttributePageTemplate = 
	    vnotebookLoadPage(pageRes);
    }
    return _commtestGlobals._PipeAttributePageTemplate;
}

/*************************************************************************/
vnotebookPage *
_getMbxAttributePageTemplate(void)
{
    vresource pageRes;

    if (_commtestGlobals._MbxAttributePageTemplate == NULL)
    {
	pageRes = vresourceGet(_rootRes, TAG("MbxAttributePage"));
	_commtestGlobals._MbxAttributePageTemplate = 
	    vnotebookLoadPage(pageRes);
    }
    return _commtestGlobals._MbxAttributePageTemplate;
}

/*************************************************************************/
vnotebookPage *
_getShmLocatorPageTemplate(void)
{
    vresource pageRes;

    if (_commtestGlobals._ShmLocatorPageTemplate == NULL)
    {
	pageRes = vresourceGet(_rootRes, TAG("ShmLocatorPage"));
	_commtestGlobals._ShmLocatorPageTemplate = 
	    vnotebookLoadPage(pageRes);
    }
    return _commtestGlobals._ShmLocatorPageTemplate;
}

/*************************************************************************/
vnotebookPage *
_getShmAttributePageTemplate(void)
{
    vresource pageRes;

    if (_commtestGlobals._ShmAttributePageTemplate == NULL)
    {
	pageRes = vresourceGet(_rootRes, TAG("ShmAttributePage"));
	_commtestGlobals._ShmAttributePageTemplate = 
	    vnotebookLoadPage(pageRes);
    }
    return _commtestGlobals._ShmAttributePageTemplate;
}

/*************************************************************************/
vdialog *
_getConnectionDialogTemplate(void)
{
    vdialog *dialog;
    vnotebook *notebook;

    if (_commtestGlobals._ConnectionDialogTemplate == NULL)
    {
	dialog = vdialogLoad(vresourceGet(_rootRes, TAG("ConnectionDialog")));
	vdialogSetNotify(dialog, _connectDialogNotify);

	notebook = (vnotebook *) vdialogFindItem(dialog, TAG("Notebook"));
	vnotebookSetStyleOwned(notebook, vnotebookCreateStyle());
	vnotebookSetStyleTabs(vnotebookGetStyle(notebook), vnotebookTABS_PAGE);

	_commtestGlobals._ConnectionDialogTemplate = dialog;
    }

    return _commtestGlobals._ConnectionDialogTemplate;
}

/*************************************************************************/
vdialog *
_getTCPDialogTemplate(void)
{
    vnotebook *notebook;

    if (_commtestGlobals._TCPDialogTemplate == NULL)
    {
	_commtestGlobals._TCPDialogTemplate = 
	    vdialogClone(_getConnectionDialogTemplate());

	notebook = (vnotebook *) 
	    vdialogFindItem(_commtestGlobals._TCPDialogTemplate,
			    TAG("Notebook"));
	vnotebookAppendPage(notebook, 
			    vnotebookClonePage(_getControlPageTemplate()));
	vnotebookAppendPage(notebook, 
			    vnotebookClonePage(_getIPLocatorPageTemplate()));
	vnotebookAppendPage(notebook, 
			   vnotebookClonePage(_getTCPAttributePageTemplate()));
    }
    return _commtestGlobals._TCPDialogTemplate;
}

/*************************************************************************/
vdialog *
_getUDPDialogTemplate(void)
{
    vnotebook *notebook;

    if (_commtestGlobals._UDPDialogTemplate == NULL)
    {
	_commtestGlobals._UDPDialogTemplate = 
	    vdialogClone(_getConnectionDialogTemplate());
	notebook = (vnotebook *) 
	    vdialogFindItem(_commtestGlobals._UDPDialogTemplate,
			    TAG("Notebook"));
	vnotebookAppendPage(notebook, 
			    vnotebookClonePage(_getControlPageTemplate()));
	vnotebookAppendPage(notebook, 
			    vnotebookClonePage(_getIPLocatorPageTemplate()));
	vnotebookAppendPage(notebook, 
		    vnotebookClonePage(_getUDPAttributePageTemplate()));
    }
    return _commtestGlobals._UDPDialogTemplate;
}

/*************************************************************************/
vdialog *
_getPipeDialogTemplate(void)
{
    vnotebook *notebook;

    if (_commtestGlobals._PipeDialogTemplate == NULL)
    {
	_commtestGlobals._PipeDialogTemplate = 
	    vdialogClone(_getConnectionDialogTemplate());
	notebook = (vnotebook *) 
	    vdialogFindItem(_commtestGlobals._PipeDialogTemplate,
			    TAG("Notebook"));
	vnotebookAppendPage(notebook, 
			    vnotebookClonePage(_getControlPageTemplate()));
	vnotebookAppendPage(notebook, 
		    vnotebookClonePage(_getDomainLocatorPageTemplate()));
	vnotebookAppendPage(notebook, 
		    vnotebookClonePage(_getPipeAttributePageTemplate()));
    }
    return _commtestGlobals._PipeDialogTemplate;
}

/*************************************************************************/
vdialog *
_getMbxDialogTemplate(void)
{
    vnotebook *notebook;

    if (_commtestGlobals._MbxDialogTemplate == NULL)
    {
	_commtestGlobals._MbxDialogTemplate = 
	    vdialogClone(_getConnectionDialogTemplate());
	notebook = (vnotebook *) 
	    vdialogFindItem(_commtestGlobals._MbxDialogTemplate,
			    TAG("Notebook"));
	vnotebookAppendPage(notebook, 
			    vnotebookClonePage(_getControlPageTemplate()));
	vnotebookAppendPage(notebook, 
		    vnotebookClonePage(_getDomainLocatorPageTemplate()));
	vnotebookAppendPage(notebook, 
		    vnotebookClonePage(_getMbxAttributePageTemplate()));
    }
    return _commtestGlobals._MbxDialogTemplate;
}

/*************************************************************************/
vdialog *
_getShmDialogTemplate(void)
{
    vnotebook *notebook;

    if (_commtestGlobals._ShmDialogTemplate == NULL)
    {
	_commtestGlobals._ShmDialogTemplate = 
	    vdialogClone(_getConnectionDialogTemplate());
	notebook = (vnotebook *) 
	    vdialogFindItem(_commtestGlobals._ShmDialogTemplate,
			    TAG("Notebook"));
	vnotebookAppendPage(notebook, 
			    vnotebookClonePage(_getControlPageTemplate()));
	vnotebookAppendPage(notebook, 
		    vnotebookClonePage(_getShmLocatorPageTemplate()));
	vnotebookAppendPage(notebook, 
		    vnotebookClonePage(_getShmAttributePageTemplate()));
    }
    return _commtestGlobals._ShmDialogTemplate;
}
