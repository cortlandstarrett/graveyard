/* $Id: das1.c,v 1.4 1995/05/01 19:12:41 abstine Exp $
 *
 * The following Sample Code is provided for your reference purposes in
 * connection with your use of the Galaxy Application Environment (TM) software
 * product which you have licensed from Visix Software, Inc. ("Visix").
 * The Sample code is provided to you without any warranty of any kind
 * whatsoever and you agree to be responsible for the use and/or incorporation
 * of the Sample Code into any software product you develop. You agree to fully
 * and completely indemnify and hold Visix harmless from any and all loss,
 * claim, liability or damages with respect to your use of the Sample Code.  
 *
 * Subject to the foregoing, you are permitted to copy, modify, and distribute
 * the Sample Code for any purpose and without fee, provided that (i) a
 * copyright notice in the in the form of "Copyright 1994 Visix Software
 * Inc., 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved"
 * appears in all copies, (ii) both the copyright notice and this permission
 * notice appear in supporting documentation and (iii) you are a valid
 * licensee of Galaxy Application Environment.
 */
/*
 * das1.c:
 *
 *	This is a sample program illustrating the Service Manager.
 *	An analogous sample program that illustrates the Communication Manager
 *	can be found in comm.c.
 *	(NOTE:  the two versions do not talk to each other.)
 *
 *	This application acts as both a provider and a consumer.  The provider
 *	listens for sessions, creating a dialog for each session.  The
 *	consumer establishes a session with another provider, and has a window
 *	open for it.
 *
 *	This application uses preferences to specify the port, transport, and
 *	location of the provider.  These can be specified on the
 *	command line (where applicable) as
 *		-Transport <transport> -Port <port> -Location <location>.
 *	To talk on the same machine, only the Port needs to be specified.
 *
 *	The provider picks a port and displays it in a main dialog.  You must
 *	start up a provider before a sender.  Both applications can be
 *	quit using the "Quit" button in the main dialog.
 */
#include  <vport.h>
#ifndef  vserviceINCLUDED
#include  vserviceHEADER	/* for provider	*/
#endif
#ifndef  vsessionINCLUDED
#include  vsessionHEADER	/* for consumer and provider */
#endif

#ifndef  vcommINCLUDED
#include  vcommHEADER		/* to initialize for Transport preference */
#endif
#ifndef  vresourceINCLUDED
#include  vresourceHEADER
#endif
#ifndef  vapplicationINCLUDED
#include  vapplicationHEADER
#endif
#ifndef  vinstINCLUDED
#include  vinstHEADER
#endif
#ifndef  vdialogINCLUDED
#include  vdialogHEADER
#endif
#ifndef  vtextitemINCLUDED
#include  vtextitemHEADER
#endif
#ifndef  vbuttonINCLUDED
#include  vbuttonHEADER
#endif

#ifndef  veventINCLUDED
#include  veventHEADER
#endif
#ifndef  vprefINCLUDED
#include  vprefHEADER
#endif
#ifndef  vstdlibINCLUDED
#include  vstdlibHEADER
#endif


static vsignature	*_signatureDumpString;


/*---------------------------------------------------------------------------*\
    static void  exampleMainDialogNotify
       note: 	no changes
\*---------------------------------------------------------------------------*/
static void
exampleMainDialogNotify(
    vdialog		*dialog,
    vevent		*event
    )
{
    int		type;
    type = veventGetType(event);
    if ((type == veventWINDOW_STATE) && veventIsClose(event))
	veventStopProcessing();
}  /**  end  exampleMainDialogNotify  **/


/*---------------------------------------------------------------------------*\
    static void  exampleQuitNotify
       note: 	no changes
\*---------------------------------------------------------------------------*/
static void
exampleQuitNotify(
    vdialogItem		*item,
    vevent		*event
    )
{
    veventStopProcessing();
}  /**  end  exampleQuitNotify  **/



/*---------------------------------------------------------------------------*\
    vdialog  *exampleConstructMainDialog
       does  :  Sets labels in main dialog from channel address
       note  : 	use preferences instead of address
\*---------------------------------------------------------------------------*/
void
exampleConstructMainDialog(
    vdialog		*dialog,
    vservice		*service
    )
{
    const vname		*name;
    vdialogItem		*item;
    vscribe		*scribeLocation, *scribeTransport, *scribePort;
    
    /**  set location, transport, port items
     **/
    scribeLocation  = vserviceFindAttributeScribe(service, vsession_Location);
    scribeTransport = vserviceFindAttributeScribe(service, vsession_Transport);
    scribePort      = vserviceFindAttributeScribe(service, vsession_Port);

    /**  from here on is the same sans dialog title
     **/
    name  = vnameInternGlobalLiteral("labelLocation");
    item  = vdialogFindItem(dialog, name);
    vdialogSetItemTitleScribed(item, scribeLocation);

    name  = vnameInternGlobalLiteral("labelTransport");
    item  = vdialogFindItem(dialog, name);
    vdialogSetItemTitleScribed(item, scribeTransport);

    name = vnameInternGlobalLiteral("labelPort");
    item = vdialogFindItem(dialog, name);
    vdialogSetItemTitleScribed(item, scribePort);

    name = vnameInternGlobalLiteral("Quit");
    item = vdialogFindItem(dialog, name);
    vdialogSetItemNotify(item, exampleQuitNotify);


    if (scribeLocation == NULL)
	scribeLocation = vcharScribeLiteral("<NULL>");
    if (scribeTransport == NULL)
	scribeTransport = vcharScribeLiteral("<NULL>");
    if (scribePort == NULL)
	scribePort = vcharScribeLiteral("<NULL>");

    vdialogSetTitleScribed(dialog,
			   vcharScribeLiteral("vservice Send/Receive Demo"));
    vdialogSetNotify(dialog, exampleMainDialogNotify);
}  /**  end  exampleConstructMainDialog  **/
 


/*---------------------------------------------------------------------------*\
    static void  exampleSendDialogNotify
       note: 	no changes
\*---------------------------------------------------------------------------*/
static void
exampleSendDialogNotify(
    vdialog		*dialog,
    vevent		*event
    )
{
    int		type;
    vsession   *session;

    type = veventGetType(event);
    if ((type == veventWINDOW_STATE) && veventIsClose(event))
        if ((session = (vsession *)vdialogGetData(dialog)))
	    vsessionEnd(session);
    
}  /**  end  exampleSendDialogNotify  **/



/*---------------------------------------------------------------------------*\
    static void  exampleSendNotify
        note:  this does *not* assume similar character sets or architectures
\*---------------------------------------------------------------------------*/
static void
exampleSendNotify(
    vdialogItem		*item,
    vevent		*event
    )
{
    vdialog		*dialog;
    const vname		*name;
    vtextitem		*textitem;
    vstr		*s;
    vsession		*session;
    vsessionStatement	*statement;

    /**  this block is the same
     **/
    dialog = (vdialog *)vobjectGetParent(vdialogGetItemObject(item));
    session = (vsession *)vdialogGetData(dialog);
    name = vnameInternGlobalLiteral("textitemInput");
    textitem = (vtextitem *)vdialogFindItem(dialog, name);
    s = vtextitemGetTextAsString(textitem);

    /**  this block is DAS specific
     **/
    statement = vsessionCreateStatement();
    vsessionSetStatementSignature(statement, _signatureDumpString);
    vsessionSetStatementSession(statement, session);
    vsessionSetStatementArgs(statement, s);
    vsessionSendStatement(statement);
    vsessionDestroyStatement(statement);

    vstrDestroy(s);
}  /**  end  exampleSendNotify  **/



/*---------------------------------------------------------------------------*\
    static void  exampleCloseNotify
       note: 	these are similar
\*---------------------------------------------------------------------------*/
static void
exampleCloseNotify(
    vdialogItem		*item,
    vevent		*event
    )
{
    vdialog	*dialog;
    vsession    *session;

    dialog = (vdialog *)vobjectGetParent(vdialogGetItemObject(item));
    if ((session = (vsession *)vdialogGetData(dialog)))
        vsessionEnd(session);
}  /**  end  exampleCloseNotify  **/



/*---------------------------------------------------------------------------*\
    vdialog  *exampleConstructSendDialog
       does  :  Sets title and data
\*---------------------------------------------------------------------------*/
void
exampleConstructSendDialog(
    vdialog		*dialog,
    vsession		*session
    )
{
    const vname		*name;
    vdialogItem		*item;
    vscribe		*scribeLocation;
    vscribe		*scribeTransport;
    vscribe		*scribePort;

    vsessionSetData(session, dialog);
    vdialogSetData(dialog, session);

    scribeLocation  = vsessionFindAttributeScribe(session, vsession_Location);
    scribeTransport = vsessionFindAttributeScribe(session, vsession_Transport);
    scribePort      = vsessionFindAttributeScribe(session, vsession_Port);


    /**  from here on is the same sans dialog title
     **/
    name = vnameInternGlobalLiteral("Close");
    item = vdialogFindItem(dialog, name);
    vdialogSetItemNotify(item, exampleCloseNotify);
    
    name = vnameInternGlobalLiteral("Send");
    item = vdialogFindItem(dialog, name);
    vdialogSetItemNotify(item, exampleSendNotify);

    
    if (scribeLocation == NULL)
	scribeLocation = vcharScribeLiteral("<NULL>");
    if (scribeTransport == NULL)
	scribeTransport = vcharScribeLiteral("<NULL>");
    if (scribePort == NULL)
	scribePort = vcharScribeLiteral("<NULL>");
    
    vdialogSetTitleScribed(dialog,
			   vcharScribeFormatLiteral("DAS Demo: %S/%S/%S",
				scribeLocation, scribeTransport, scribePort));
    vdialogSetNotify(dialog, exampleSendDialogNotify);
}  /**  end  exampleConstructSendDialog  **/
 


/*---------------------------------------------------------------------------*\
    static void  exampleShowMessage
       note: 	no changes
\*---------------------------------------------------------------------------*/
static void
exampleShowMessage(
    vdialog	*dialog,
    vchar	*s
    )
{
    const vname	*name;
    vtextitem	*textitem;
    
    name = vnameInternGlobalLiteral("textitemReceived");
    textitem = (vtextitem *)vdialogFindItem(dialog, name);
    vtextitemSetText(textitem, s);
}  /**  end  exampleShowMessage  **/


/*---------------------------------------------------------------------------*\
    static vscrap  *exampleSessionNotify
       note: 	vsession specific function
\*---------------------------------------------------------------------------*/
static void
exampleSessionNotify(
    vsession		*session,
    vsessionEvent	*event
    )
{
    vresource		 resRoot;
    vresource		 res;
    const vname		*name;
    vdialog		*dialog;

    switch (vsessionGetEventCode(event))
    {
	case  vsessionEVENT_BEGIN:
	    /**  similar to vcommOPEN code
	     **/
	    resRoot = vapplicationGetResources(vapplicationGetCurrent());
	    name = vnameInternGlobalLiteral("dialogTalk");
	    res = vresourceGet(resRoot, name);
	    dialog = vdialogLoad(res);
	    vsessionSetData(session, dialog);
	    exampleConstructSendDialog(dialog, session);
	    vdialogOpen(dialog);
	    break;
	    
	case  vsessionEVENT_END:
	    /**  similar to vcommCLOSE code
	     **/
	    dialog = vsessionGetData(session);
	    vdialogSetData(dialog,NULL);
	    vobjectDestroyLater(vdialogGetObject(dialog));
	    break;

	case  vsessionEVENT_CANNOT_BEGIN:
	    break;

	default:
	    break;
    }  /**  end switch  **/
}  /**  end  exampleSessionNotify  **/



/*---------------------------------------------------------------------------*\
    static vscrap  *exampleHandleDumpPrimitive
       note: 	vservice specific function
\*---------------------------------------------------------------------------*/
static vscrap
*exampleHandleDumpPrimitive(
    vservicePrimitive	*prim,
    vsession		*session,
    vscrap		*scrapArgs
    )
{
    vstr	*s;

    vserviceGetPrimitiveArgs(prim, scrapArgs, &s);
    exampleShowMessage(vsessionGetData(session), s);
    vstrDestroy(s);

    return  NULL;
}  /**  end exampleHandleDumpPrimitive  **/



/*---------------------------------------------------------------------------*\
    static vservice  *exampleCreateService
       note: 	vservice specific function
\*---------------------------------------------------------------------------*/
static vservice
*exampleCreateService()
{
    vservice 		*service;
    vservicePrimitive	*prim;

    service = vserviceCreate();
    vsessionSetNotify(vserviceGetTemplateSession(service),
		      exampleSessionNotify);

    prim = vserviceCreatePrimitive();
    vserviceSetPrimitiveSignature(prim, _signatureDumpString);
    vserviceSetPrimitiveHandler(prim, exampleHandleDumpPrimitive);
    vserviceAddPrimitiveOwned(service, prim);
    return service;
}



int
main(int argc, char *argv[])
{
    vresource		 resRoot;
    vresource		 res;
    int			 bConnect;
    vfsPath		*path;
    const vchar		*sPref;
    const vname		*name;
    vstr		*sEmpty;
    vdialog		*dialogMain;
    vservice		*service;
    vsession		*session;

    /**  initialize preferences	(same)
     **/
    vprefStoreScribed(vcharScribeLiteral("Port"),
		      vcharScribeLiteral(" "));
    vprefStoreScribed(vcharScribeLiteral("Transport"),
		      vcharScribeLiteral(" "));
    vprefStoreScribed(vcharScribeLiteral("Location"),
		      vcharScribeLiteral(" "));

    vprefSetArgs(argc, argv);


    vcommRegisterAllDrivers();	/* for specifying Transport preference */

    /**  initialize managers for loading resources  (same)
     **/
    (void)vdialogGetDefaultClass();
    (void)vbuttonGetDefaultClass();
    (void)vtextitemGetDefaultClass();

    sEmpty = vstrCloneScribed(vcharScribeLiteral(" "));


    /**  initialize signatures  (DAS specific)
     **/
    _signatureDumpString = vsignatureCreate();
    vsignatureSetTag(_signatureDumpString, vnameInternGlobalLiteral("dump"));
    vsignatureConstructArgs(_signatureDumpString,
			    vdatatagGetString(),
			    NULL);

    /**  start service  (vservice specific)
     **  allow Transport preference to determine transport
     **/
    service = exampleCreateService();
    sPref = vprefLoadScribed(vcharScribeLiteral("Transport"));
    if (vcharCompare(sPref, sEmpty) != 0)
	vserviceSetAttributeTag(service, vsession_Transport,
				vnameInternGlobal(sPref));
    vserviceEnable(service);


    /**  initialize main dialog  (same sans types to Construct dialog)
     **/
    path = vinstFindSameResourceScribed(vcharScribeLiteral("sendstr.vr"));
    resRoot = vresourceOpenFile(path, vfsOPEN_READ_ONLY);
    vapplicationSetResources(vapplicationGetCurrent(), resRoot);
    name = vnameInternGlobalLiteral("dialogMain");
    res = vresourceGet(resRoot, name);
    dialogMain = vdialogLoad(res);
    exampleConstructMainDialog(dialogMain, service);
    vdialogOpen(dialogMain);


    /**  establish session with specified provider, if any  (DAS specific)
     **/
    bConnect = FALSE;
    session = vsessionCreate();

    sPref = vprefLoadScribed(vcharScribeLiteral("Transport"));
    if (vcharCompare(sPref, sEmpty) != 0)
	vsessionSetAttribute(session, vsession_Transport,
			     vdatatagGetTag(), vnameInternGlobal(sPref));

    sPref = vprefLoadScribed(vcharScribeLiteral("Location"));
    if (vcharCompare(sPref, sEmpty) != 0)
	vsessionSetAttribute(session, vsession_Location,
			     vdatatagGetString(), sPref);

    sPref = vprefLoadScribed(vcharScribeLiteral("Port"));
    if (vcharCompare(sPref, sEmpty) != 0) {
	vsessionSetAttribute(session, vsession_Port,
			     vdatatagGetString(), sPref);
	bConnect = TRUE;
    }
    vstrDestroy(sEmpty);
    
    if (bConnect) {
	vsessionSetService(session, service);
	vsessionSetNotify(session, exampleSessionNotify);
	vsessionSetDestroyWhenInactive(session, TRUE);
	vsessionBegin(session);
    }
    else
	vsessionDestroy(session);


    veventProcess();


    /**  cleanup application  (similar)
     **/
    vserviceDisable(service);
    vserviceDestroy(service);
    vdialogDestroy(dialogMain);
    vfsDestroyPath(path);
    vsignatureDestroy(_signatureDumpString);

    exit(EXIT_SUCCESS);
    return  EXIT_FAILURE;
}  /**  end  main  **/
