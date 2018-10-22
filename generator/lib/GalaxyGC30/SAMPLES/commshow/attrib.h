/* $Id: attrib.h,v 1.4 1997/02/20 18:31:09 david Exp $ */

#ifndef _commtestAttribINCLUDED
#define _commtestAttribINCLUDED 1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vdialogINCLUDED
#include vdialogHEADER
#endif

/*
 * possible values of second argument to _attribLocatorUpdate()
 */
enum {
     _REMOTE_LOCATOR    =  0x0001,
     _LOCAL_LOCATOR     =  0x0002,
     _BOTH_LOCATOR      =  0x0003,
     _CLEAR_LOCATOR     =  0x0004
 };

typedef void (*_commtestQueryFunc)(
    vdialog                        *dialog,
    const vname                    *name
    );

typedef void (*_commtestLocatorQueryFunc)(
    vdialog                        *dialog,
    const vname                    *name,
    int                             sel
    );

typedef struct _commtestAttributes _commtestAttributes;
struct _commtestAttributes
{
    const char                      *name;
    _commtestQueryFunc               queryFunc;
};

typedef struct _commtestLocatorAttributes _commtestLocatorAttributes;
struct _commtestLocatorAttributes
{
    const char                      *name;
    _commtestLocatorQueryFunc        queryFunc;
};

void _attribSetupCommandSpace(vdialog *dialog);
void _attribUpdate(vdialog *dialog);
void _attribLocatorUpdate(vdialog *dialog, int sel);

#endif
