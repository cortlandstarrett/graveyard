/* $Id: pref.c,v 1.1 1994/03/30 23:07:58 dimitri Exp $ */

/************************************************************

    preferences.c
    C Source to xwrite

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/
 
#include "micwrite.h"

#if vdebugDEBUG
#define vdebugTAG "xwritePref"
#endif

writePreferenceData          writePreferences;
writeTemplatePreferenceData  writeTemplatePreferences;

/*
 * _writeReadPreferences
 */
static void _writeReadPreferences(
    vresource		resource
    )
{ 
    vresource   res;
    writeStyle	*scan;

    /* Write Preferences are read here */

    if (vresourceTestGet(resource, 
                         vnameInternGlobalLiteral("Global Style List"), 
                         &res)) {

        writeDestroyStyleList(&writeStyleList);
	writeStyleCount = 0;

	writeStyleList = scan = writeLoadStyleList(res);

	while (scan != NULL) {
            
	    writeStyleCount++;

            if (scan->name == write_Normal)
                writeNormalStyle = scan;

            scan = scan->next;
        }
    }

    /* Load up the global style list */

    writeLoadTemplate(resource, &writeTemplatePreferences);
}

/*
 * writeLoadTemplate
 */
void writeLoadTemplate(
    vresource           	resource,
    writeTemplatePreferenceData	*prefs
    )
{
    vresource   res, templateRes;
    int		x;

    if (vresourceTestGet(resource, vnameInternGlobalLiteral("Template"),
			 &templateRes)) {

        if (vresourceTestGet(templateRes, vname_Rect, &res))
            vresourceLoadInitRect(&prefs->newDocumentRect, res);;

	if (vresourceTestGetInteger(templateRes, vname_Flags, &x))
	    prefs->flags = x;

        /* Load the template style list here */
    }
}

/*
 * writeStoreTemplate
 */
void writeStoreTemplate(
    vresource           	resource,
    writeTemplatePreferenceData	*prefs
    )
{
    vresource   templateRes;

    /*
     * Store the template
     */

    templateRes = vresourceMake(resource,
                                vnameInternGlobalLiteral("Template"));

    vresourceStoreRect(&prefs->newDocumentRect,
                       vresourceMake(templateRes, vname_Rect));

    vresourceSetInteger(templateRes, vname_Flags,
			prefs->flags);

    /* Store the style list here */
}

/*
 * writePreferencesStartup
 *
 * Read in preditor preferences
 */
void writePreferencesStartup()
{
    writeTemplatePreferences.styleList = NULL;

    /*
     * Initialize preferences to default values
     */

    _writeReadPreferences(vresourceGet(writeResFile, vname_Preferences));

    /*
     * Now read in any user-defined preferences
     */

    if (writeUserPrefFile != vresourceNULL)
        _writeReadPreferences(writeUserPrefFile);
}

/*
 * writePreferencesShutdown
 *
 * Write preferences back to pref file
 */
void writePreferencesShutdown()
{
    vresource		res;

    if (writeUserPrefFile == vresourceNULL)
        return;

    /*
     * Store the global style list
     */

    res = vresourceCreate(writeUserPrefFile, 
			  vnameInternGlobalLiteral("Global Style List"), 
			  vresourceDICT);

    writeStoreStyleList(writeStyleList, res);

    writeDestroyStyleList(&writeStyleList);

    writeStoreTemplate(writeUserPrefFile, &writeTemplatePreferences);
}
