/* $Id: pref.c,v 1.4 1994/09/23 17:56:03 thomas Exp $ */

/************************************************************

    preferences.c
    C Source to Microdraw

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/
 
/*----------------------------------------------------------------------------
 * The following Sample Code is provided for your reference purposes in
 * connection with your use of the Galaxy Application Environment (TM) software
 * product which you have licensed from Visix Software, Inc. ("Visix").
 * The Sample code is provided to you without any warranty of any kind
 * whatsoever and you agree to be responsible for the use and/or incorporation
 * of the Sample Code into any software product you develop. You agree to fully
 * and completely indemnify and hold Visix harmless from any and all loss,
 * claim, liability or damages with respect to your use of the Sample Code.
 *
 * Subject to the foregoing, you are permitted to copy, modify, and
 * distribute the Sample Code for any purpose and without fee,
 * provided that (i) a copyright notice in the form of "Copyright
 * 1992, 1993, 1994 Visix Software Inc., 11440 Commerce Park Drive,
 * Reston, VA 22091. All Rights Reserved" appears in all copies, (ii)
 * both the copyright notice and this permission notice appear in
 * supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 ---------------------------------------------------------------------------*/

#define vdebugTAG "vmdrawPreferences"

#include "micdraw.h"

vmdrawPreferenceData          vmdrawPreferences;
vmdrawTemplatePreferenceData  vmdrawTemplatePreferences;

/*
 * _vmdrawReadPreferences
 */
static void _vmdrawReadPreferences(
    vresource		resource
    )
{
    int		x;

    /* Auto Save Information */

    if (vresourceTestGetInteger
	(resource, vnameInternGlobalLiteral("AutoActions"), &x))
	vmdrawPreferences.numAutoActions = x;
    if (vresourceTestGetInteger
	(resource, vnameInternGlobalLiteral("AutoMinutes"), &x))
	vmdrawPreferences.numAutoMinutes = x;

    /* Max Undos */

    if (vresourceTestGetInteger
	(resource, vnameInternGlobalLiteral("MaxUndos"), &x))
	vmdrawPreferences.maxUndos = x;

    /* Options */

    if (vresourceTestGetInteger
	(resource, vnameInternGlobalLiteral("Options"), &x))
	vmdrawPreferences.options = x;

    vmdrawLoadTemplate(resource, &vmdrawTemplatePreferences);
}

/*
 * vmdrawLoadTemplate
 */
void vmdrawLoadTemplate(
    vresource           		resource,
    vmdrawTemplatePreferenceData		*prefs
    )
{
    vresource   res, templateRes;
    int		x;
    double	y;

    if (vresourceTestGet(resource, vnameInternGlobalLiteral("Template"),
			 &templateRes)) {

        if (vresourceTestGet(templateRes, vname_Rect, &res))
            vresourceLoadInitRect(&prefs->newDocumentRect, res);;

        /* Grid */

        res = vresourceGet(templateRes, vdomain_Grid);

        prefs->grid.xSpacing= vresourceGetIntegerAt(res, 0);
        prefs->grid.ySpacing= vresourceGetIntegerAt(res, 1);
        prefs->grid.xSkew   = vresourceGetIntegerAt(res, 2);
        prefs->grid.ySkew   = vresourceGetIntegerAt(res, 3);

	/* Scale */

	if (vresourceTestGetFloat	
	    (templateRes, vnameInternGlobalLiteral("Scale"), &y))
	    prefs->scale = y; 

	/* View Settings */

	if (vresourceTestGetInteger	
	    (templateRes, vnameInternGlobalLiteral("ViewSetting"), &x))
	    prefs->viewSettings = x; 

	/* Align Option */

	if (vresourceTestGetInteger	
	    (templateRes, vnameInternGlobalLiteral("AlignOption"), &x))
	    prefs->alignOption = x;

	/* Document Width/Height */

	if (vresourceTestGetInteger(templateRes, vname_Width, &x))
	    prefs->documentWidth = x; 
	if (vresourceTestGetInteger(templateRes, vname_Height, &x))
	    prefs->documentHeight = x; 
    }
}

/*
 * vmdrawStoreTemplate
 */
void vmdrawStoreTemplate(
    vresource           		resource,
    vmdrawTemplatePreferenceData	*prefs
    )
{
    vresource   templateRes, res;

    /*
     * Store the template document
     */

    templateRes = vresourceMake(resource,
                                vnameInternGlobalLiteral("Template"));

    vresourceStoreRect(&prefs->newDocumentRect,
                       vresourceMake(templateRes, vname_Rect));

    /* Grid */

    res = vresourceCreateArray(templateRes, vdomain_Grid, vresourceINTEGER, 4);

    vresourceSetIntegerAt(res, 0, prefs->grid.xSpacing);
    vresourceSetIntegerAt(res, 1, prefs->grid.ySpacing);
    vresourceSetIntegerAt(res, 2, prefs->grid.xSkew);
    vresourceSetIntegerAt(res, 3, prefs->grid.ySkew);

    /* Scale */

    vresourceSetFloat(templateRes, vnameInternGlobalLiteral("Scale"),
		      (double) prefs->scale);

    /* View Settings */

    vresourceSetInteger(templateRes, vnameInternGlobalLiteral("ViewSetting"),
			prefs->viewSettings);

    /* Align Option */

    vresourceSetInteger(templateRes, vnameInternGlobalLiteral("AlignOption"),
			prefs->alignOption);

    /* Document Width/Height */

    vresourceSetInteger(templateRes, vname_Width,
			prefs->documentWidth);
    vresourceSetInteger(templateRes, vname_Height,
			prefs->documentHeight);
}

/*
 * vmdrawPreferencesStartup
 *
 * Read in preditor preferences
 */
void vmdrawPreferencesStartup()
{
   /*
    * Initialize preferences to default values
    */

    _vmdrawReadPreferences(vresourceGet(vmdrawResFile, vname_Preferences));

    /*
     * Now read in any user-defined preferences
     */

    if (vmdrawUserPrefFile != vresourceNULL)
        _vmdrawReadPreferences(vmdrawUserPrefFile);
}

/*
 * vmdrawPreferencesShutdown
 *
 * Vmdraw preferences back to pref file
 */
void vmdrawPreferencesShutdown()
{
    if (vmdrawUserPrefFile == vresourceNULL)
        return;

    /* Auto Save Information */

    vresourceSetInteger(vmdrawUserPrefFile, 
			vnameInternGlobalLiteral("AutoActions"),
			vmdrawPreferences.numAutoActions);
    vresourceSetInteger(vmdrawUserPrefFile, 
			vnameInternGlobalLiteral("AutoMinutes"),	
			vmdrawPreferences.numAutoMinutes);

    /* Max Undos */

    vresourceSetInteger(vmdrawUserPrefFile, 
			vnameInternGlobalLiteral("MaxUndos"),
			vmdrawPreferences.maxUndos);

    /* Options */

    vresourceSetInteger(vmdrawUserPrefFile, 
			vnameInternGlobalLiteral("Options"),
			vmdrawPreferences.options);

    vmdrawStoreTemplate(vmdrawUserPrefFile, &vmdrawTemplatePreferences);
}
