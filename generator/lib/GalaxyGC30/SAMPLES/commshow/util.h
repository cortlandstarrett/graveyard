/* $Id: util.h,v 1.4 1997/05/27 15:21:47 paul Exp $ */

#ifndef _commtestUtilINCLUDED
#define _commtestUtilINCLUDED 1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vnameINCLUDED
#include vnameHEADER
#endif

#ifndef vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef vcontainerINCLUDED
#include vcontainerHEADER
#endif

#ifndef vtextitemINCLUDED
#include vtextitemHEADER
#endif

#ifndef vcolorINCLUDED
#include vcolorHEADER
#endif

vdialogItem *_utilFindItem(vdialog *dialog, const vname *tag);
vdialogItem *_utilFindContainerItem(vcontainer *container, const vname *tag);
void         _utilSetUpTextItemClasses(void);
void         _utilSetTextAsScribe(vtextitem *textitem, vscribe *scribe);
vcolor      *_utilForeground(vdialogItem *ditem);

#define _utilForeground(i)                                                  \
    vwindowDetermineForeground(vdialogGetWindow(vdialogDetermineItemDialog(i)))

#endif
