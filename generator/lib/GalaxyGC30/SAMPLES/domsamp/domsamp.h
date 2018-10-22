/* $Id: domsamp.h,v 1.9 1995/09/29 19:23:40 gregt Exp $ */

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vstringINCLUDED
#include vstringHEADER
#endif

#ifndef vpointINCLUDED
#include vpointHEADER
#endif

#ifndef vwindowINCLUDED
#include vwindowHEADER
#endif

#ifndef vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef vonfirmINCLUDED
#include vconfirmHEADER
#endif

#ifndef mydviewINCLUDED
#include "mydview.h"
#endif

typedef struct {
  size_t	length;
  vstr		*text;
} bandName;

typedef struct {
  size_t	count;
  bandName	*names;
} bandNames;

typedef struct {
  size_t	count;
  vimage	**imArray;
} imageStruct;

typedef struct
{
  vdialog	*mainDialog;
  vwindow	*coordSys;
  vconfirm	*addItems;
  vconfirm	*editGrid;
  vconfirm	*prefs;
  vconfirm	*editMatrix;
  myDomainView	*mview;
  bandNames	bands;
  imageStruct	images;
} appData;

enum {
  objRECT,
  objTRIANGLE,
  objCIRCLE,
  objTEXT,
  objIMAGE,
  objRANDOM,
  objCOUNT
};


appData *mainDialogGetAppData(vdialog *);
void mainDialogSetAppData(vdialog *, appData *);
appData *addItemsGetAppData(vconfirm *);
void addItemsSetAppData(vconfirm *, appData *);
appData *editGridGetAppData(vconfirm *);
void editGridSetAppData(vconfirm *, appData *);
appData *prefsGetAppData(vconfirm *);
void prefsSetAppData(vconfirm *, appData *);
appData *matrixGetAppData(vconfirm *);
void matrixSetAppData(vconfirm *, appData *);
appData *coordSysGetAppData(vwindow *);
void coordSysSetAppData(vwindow *, appData *);

vdialog *appDataGetMainDialog(appData *);
void appDataSetMainDialog(appData *, vdialog *);
vdomainview *appDataGetMview(appData *);
void appDataSetMview(appData *, myDomainView *);
vconfirm *appDataGetAddItemsConfirm(appData *);
void appDataSetAddItemsConfirm(appData *, vconfirm *);
vconfirm *appDataGetPrefsConfirm(appData *);
void appDataSetPrefsConfirm(appData *);
vconfirm *appDataGetEditGridConfirm(appData *);
void appDataSetEditGridConfirm(appData *, vconfirm *);
vconfirm *appDataGetEditMatrixConfirm(appData *);
void appDataSetEditMatrixConfirm(appData *, vconfirm *);
bandNames *appDataGetBands(appData *);
imageStruct *appDataGetImages(appData *);

#define mainDialogGetAppData(m)	\
	((appData *) vdialogGetData((m)))
#define mainDialogSetAppData(m, d)	\
	vdialogSetData((m), (void *) (d))
#define addItemsGetAppData(a)	\
	((appData *) vconfirmGetData((a)))
#define addItemsSetAppData(a, d)	\
	vconfirmSetData((a), (void *) (d))
#define editGridGetAppData(a)	\
	((appData *) vconfirmGetData((a)))
#define editGridSetAppData(a, d)	\
	vconfirmSetData((a), (void *) (d))
#define prefsGetAppData(p)	\
	((appData *) vconfirmGetData((p)))
#define prefsSetAppData(p, d)	\
	vconfirmSetData((p), (void *) (d))
#define matrixGetAppData(m)	\
	((appData *) vconfirmGetData((m)))
#define matrixSetAppData(m, d)	\
	vconfirmSetData((m), (void *) (d))
#define coordSysGetAppData(c)	\
	((appData *) vwindowGetData((c)))
#define coordSysSetAppData(c, d)	\
	vwindowSetData((c), (void *) (d))
#define appDataGetMainDialog(d)	\
	(d)->mainDialog
#define appDataSetMainDialog(d, m)	\
	(d)->mainDialog = (m)
#define appDataGetMview(d)	\
	(d)->mview
#define appDataSetMview(d, v)	\
	(d)->mview = (v)
#define appDataGetBands(d)	\
	(&(d)->bands)
#define appDataGetImages(d)	\
	(&(d)->images)
#define appDataGetAddItemsConfirm(d)	\
	(d)->addItems
#define appDataSetAddItemsConfirm(d, a)	\
	(d)->addItems = (a)
#define appDataGetPrefsConfirm(d)	\
	(d)->prefs
#define appDataSetPrefsConfirm(d, p)	\
	(d)->prefs = (p)
#define appDataGetEditGridConfirm(d)	\
	(d)->editGrid
#define appDataSetEditGridConfirm(d, e)	\
	(d)->editGrid = (e)
#define appDataGetEditMatrixConfirm(d)	\
	(d)->editMatrix
#define appDataSetEditMatrixConfirm(d, e)	\
	(d)->editMatrix = (e)
