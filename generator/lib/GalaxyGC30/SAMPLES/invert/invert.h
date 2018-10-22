#ifndef invertINCLUDED
#define invertINCLUDED

/* Some convenience macros */
#define R                               0
#define G                               1
#define B                               2
#define RGB                             3

/* for vwindowComplementColors's array                             */
/* invertNUM_COMPLEMENTS is the number of complement sets          */
/* invertNUM_COLORS_PER_COMPLEMENT is the number of colors per set */
#define invertNUM_COMPLEMENTS           4
#define invertNUM_COLORS_PER_COMPLEMENT 2

#define invertNUM_COMMANDS              9

/* program status bits */
#define invertOUTLINE                   1 /* outlined rubber rect   */
#define invertFILLED                    2 /* solid rubber rect      */
#define invertSOLID                     4 /* solid white background */
#define invertSTRIPED                   8 /* RGB striped background */

/* inline functions  */

/* return the white from our private store */
#define invertGetWhite()                (_globals->colors[3][0])
/* return the black from our private store */
#define invertGetBlack()                (_globals->colors[3][1])
/* return the requested color from our private store */
#define invertGetColor(x, y)            (_globals->colors[(x)][(y)])

/* return TRUE if vwindowComplementColors succeeded, FALSE otherwise */
#define invertHasComplementColors()     (_globals->hasComplementColors)
/* set the status bit appropriately based on the results of vwCC     */
#define invertEnableComplementColors()  (_globals->hasComplementColors = vTRUE)
#define invertDisableComplementColors() (_globals->hasComplementColors = vFALSE)

/* set/return the current drawing function */
#define invertGetFunction()             (_globals->currentFunction)
#define invertSetFunction(x)            (_globals->currentFunction = (x))

/* set/return the currently selected foreground option */
#define invertGetForeground()           (_globals->foregroundStatus)
#define invertSetForeground(x)          (_globals->foregroundStatus = (x))

/* set/return the currently selected background option */
#define invertGetBackground()           (_globals->backgroundStatus)
#define invertSetBackground(x)          (_globals->backgroundStatus = (x))

/* set/return a pointer to the dialog item we draw in */
#define invertGetItem()                 (_globals->content)
#define invertSetItem(x)                (_globals->content = (x))

/* setup the rubber rect */
#define invertRectSet(x, y, w, h)       (vrectSet((x), (y), (w), (h), \
                                                  &_globals->rubberRect))
/* clear the rubber rect */
#define invertRectClear()               (vrectSet(0, 0, 0, 0, \
                                                  &_globals->rubberRect))
/* set/return the width of the rubber rect */
#define invertGetRectW()                (_globals->rubberRect.w)
#define invertSetRectW(width)           (_globals->rubberRect.w = (width))
/* set/return the height of the rubber rect */
#define invertGetRectH()                (_globals->rubberRect.h)
#define invertSetRectH(height)          (_globals->rubberRect.h = (height))
/* return the x-coordinate of the rubber rect */
#define invertGetRectX()                (_globals->rubberRect.x)
/* return the y-coordinate of the rubber rect */
#define invertGetRectY()                (_globals->rubberRect.y)
/* return the rubber rect as a vrect structure */
#define invertGetRect()                 (&_globals->rubberRect)

/* update the cached rubber rect */
#define invertUpdateCache(x, y, w, h)   (vrectSet((x), (y), (w), (h), \
                                                  &_globals->cache))
/* return the currently cached rubber rect */
#define invertGetCache()                (&_globals->cache)

/* vdialogItemClass overrides */
static void contentDraw(vdialogItem *);
static int  contentHandleButtonUp(vdialogItem *, vevent *);
static int  contentHandleItemDrag(vdialogItem *, vevent *);
static int  contentHandleButtonDown(vdialogItem *, vevent *);

/* auxillary routines */
static void dialogNotify(vdialog *, vevent *);
static void drawRubberRect(short, vrect *);
static void disableComplementColors(const char *);

/* command functions */
static int useFuncXor(vcommandFunction *, vdict *);
static int useFuncInvert(vcommandFunction *, vdict *);
static int useFuncHilite(vcommandFunction *, vdict *);
static int useFuncComplement(vcommandFunction *, vdict *);
static int queryFuncComplement(vcommandFunction *, vdict *);
static int fileQuit(vcommandFunction *, vdict *);
static int backgroundStriped(vcommandFunction *, vdict *);
static int backgroundSolid(vcommandFunction *, vdict *);
static int foregroundFilled(vcommandFunction *, vdict *);
static int foregroundOutline(vcommandFunction *, vdict *);

/* application globals management functions */
static void invertInitialize(void);
static void invertDestroy(void);

/* rock to hide our global variables under  */
typedef struct _invertGlobals {
  vcolor    ***colors;              /* an array of colors to monkey with   */
  vrect        rubberRect;          /* the rect being rubberbanded         */
  vrect        cache;               /* to keep the screen consistent       */
  int          currentFunction;     /* the current drawing function        */
  short        foregroundStatus;    /* status of the foreground            */
  short        backgroundStatus;    /* status of the background            */
  vbool        hasComplementColors; /* does vwindowComplementColors() work */
  vdialogItem *content;             /* our playing field                   */
} _invertGlobals;


#endif /* invertINCLUDED */
