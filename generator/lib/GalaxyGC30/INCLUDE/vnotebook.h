/* $Id: vnotebook.h,v 1.36 1997/11/19 22:12:26 gregt Exp $ */

/************************************************************

    vnotebook.h
    C Interface to notebooks

    (c) Copyright Visix Software  1994
    All rights reserved
    
************************************************************/

#ifndef vnotebookINCLUDED
#define vnotebookINCLUDED

#ifndef vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef vcontainerINCLUDED
#include vcontainerHEADER
#endif

#ifndef vbuttonINCLUDED
#include vbuttonHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

#define vnotebookDEFAULT	-1

enum{
  vnotebookID_ATTRIBUTE_NEW_PAGE     	= vcontainerNEXT_ID_ATTRIBUTE,
  vnotebookID_ATTRIBUTE_MAJOR_TAB_CHANGE,
  vnotebookID_ATTRIBUTE_MINOR_TAB_CHANGE,
  vnotebookNEXT_ID_ATTRIBUTE
};

/*
 *  Notebook Tab Positions
 */
enum{
  vnotebookTABSET_RIGHT	 		= 0,
  vnotebookTABSET_LEFT	 		,
  vnotebookTABSET_BOTTOM		,
  vnotebookTABSET_TOP
};

/*
 *  Notebook Tab Types
 */
enum{
  vnotebookTABS_NONE			= 0,
  vnotebookTABS_PAGE			,
  vnotebookTABS_MAJOR			,
  vnotebookTABS_MAJOR_AND_MINOR		
};

/*
 *  Which TabSet constant
 */
enum{
  vnotebookMAJOR_TABSET			= 0,
  vnotebookMINOR_TABSET
};

/*
 *  Which button constant
 */
enum{
  vnotebookNEXT_PAGE_BUTTON	   	= 0,
  vnotebookPREVIOUS_PAGE_BUTTON
};

/*
 *  Folio justification
 */
enum{
  vnotebookFOLIO_JUSTIFY_RIGHT		= 0,
  vnotebookFOLIO_JUSTIFY_CENTER		,
  vnotebookFOLIO_JUSTIFY_LEFT
};

/*
 *  Vertical Tabs
 */
enum{
  vnotebookVERTICAL_TABS_NORMAL		= 0,
  vnotebookVERTICAL_TABS_ROTATED
};

/*
 *  Tab Set Button Placement
 */
enum{
  vnotebookTABSET_BUTTONS_SEPARATE  	= 0,
  vnotebookTABSET_BUTTONS_ADJACENT
};

/*
 *  Binding style settings
 */
enum{
  vnotebookBINDING_PERFECT	     	= 0,
  vnotebookBINDING_SPIRAL		
};

/*
 *  Tab style settings
 */
enum{
  vnotebookTAB_STYLE_RECT		= 0,
  vnotebookTAB_STYLE_ROUND_RECT		,
  vnotebookTAB_STYLE_BEVELED		
};

/*
 *  Style values
 */
enum{
  vnotebookSTYLE_MAJOR_TABSET_SIDE		= 0x00000001,
  vnotebookSTYLE_MINOR_TABSET_SIDE		= 0x00000002,
  vnotebookSTYLE_TABS				= 0x00000004,
  vnotebookSTYLE_FOLIO				= 0x00000008,
  vnotebookSTYLE_FOLIO_JUSTIFY			= 0x00000010,
  vnotebookSTYLE_PAGE_BUTTONS			= 0x00000020,
  vnotebookSTYLE_MULTILINE_TABS			= 0x00000040,
  vnotebookSTYLE_TAB_STYLE			= 0x00000080,
  vnotebookSTYLE_VERTICAL_TABS			= 0x00000100,
  vnotebookSTYLE_PAGES_WRAP			= 0x00000200,
  vnotebookSTYLE_PAGE_BORDERS			= 0x00000400,
  vnotebookSTYLE_BINDING			= 0x00000800,
  vnotebookSTYLE_PAGE_COUNT			= 0x00001000,
  vnotebookSTYLE_PAGE_STEP			= 0x00002000,
  vnotebookSTYLE_BINDING_SIZE			= 0x00004000,
  vnotebookSTYLE_PAGE_INSET			= 0x00008000,
  vnotebookSTYLE_PAGE_INSET_BORDER		= 0x00010000,
  vnotebookSTYLE_TABSET_BUTTONS_CENTERED	= 0x00020000,
  vnotebookSTYLE_TABSET_BUTTONS_PLACEMENT	= 0x00040000,
  vnotebookSTYLE_TABSET_PARTIAL_TABS		= 0x00080000,
  vnotebookSTYLE_TAB_SPACING			= 0x00100000,
  vnotebookSTYLE_TAB_INSET_X		       	= 0x00200000,
  vnotebookSTYLE_TAB_INSET_Y			= 0x00400000,
  vnotebookSTYLE_TAB_SELECT_RAISE		= 0x00800000,
  vnotebookSTYLE_TAB_SELECT_RESIZE		= 0x01000000,
  vnotebookSTYLE_FOLIO_BUTTON_MARGIN		= 0x02000000,
  vnotebookSTYLE_BUTTON_MARGIN			= 0x04000000,
  vnotebookSTYLE_BUTTON_BORDER_MARGIN		= 0x08000000,
  vnotebookNUM_STYLES				= 28
};

enum {
  vnotebookNEXT_SELECT				= vcontainerNEXT_SELECT
};

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vnotebookClass		 vnotebookClass;
typedef struct vnotebookSectionClass	 vnotebookSectionClass;
typedef struct vnotebookPageClass	 vnotebookPageClass;
typedef struct vnotebookTabClass	 vnotebookTabClass;
typedef struct vnotebookStyleClass	 vnotebookStyleClass;

typedef struct vnotebook		 vnotebook;
typedef struct vnotebookPage		 vnotebookPage;
typedef struct vnotebookSection		 vnotebookSection;
typedef struct vnotebookTab		 vnotebookTab;
typedef struct vnotebookStyle		 vnotebookStyle;

typedef void (*vnotebookNoteProc)(
    vnotebook     	*notebook,
    vevent          	*event
    );

typedef void (*vnotebookPageNoteProc)(
    vnotebookPage       *page,
    vevent              *event
    );

typedef void (*vnotebookSectionNoteProc)(
    vnotebookSection    *section,
    vevent              *event
    );

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vnotebookStartup(
    void
    );


vnotebookClass *vnotebookGetDefaultClass(
    void
    );

vnotebookStyle *vnotebookGetClassStyle(
    vnotebookClass		*clas
    );

vnotebook *vnotebookCreateOfClass(
    vnotebookClass  		*clas
    );

vnotebook *vnotebookCreate(
    void
    );

vnotebook *vnotebookClone(
    vnotebook			*notebook
    );

void vnotebookDestroy( 
    vnotebook 			*notebook 
    );

void vnotebookInitOfClass(
    vnotebook			*notebook,
    vnotebookClass		*clas
    );

void vnotebookInit(
    vnotebook			*notebook
    );

void vnotebookCopy(
    vnotebook			*src,
    vnotebook			*dest
    );

void vnotebookCopyInit(
    vnotebook             	*src,
    vnotebook              	*dest
    );

vnotebook *vnotebookLoad(
    vresource              	 resource
    );

void vnotebookLoadInit(
    vnotebook              	*notebook,
    vresource                    resource
    );

void vnotebookStore(
    vnotebook                     *notebook,
    vresource                      resource
    );

vnotebookClass *vnotebookGetClass(
    vnotebook		*notebook
    );

vdialogItem *vnotebookGetItem(
    vnotebook		*notebook
    );

vcontainer *vnotebookGetContainer(
    vnotebook		*notebook
    );

vnotebookNoteProc vnotebookGetNotify(
    vnotebook        	*notebook
    );

const void *vnotebookGetData(
    vnotebook		*notebook
    );

vnotebookPage *vnotebookGetCurrentPage(
    vnotebook		*notebook
    );

vnotebookPage *vnotebookDetermineCurrentPage(
    vnotebook		*notebook
    );

void vnotebookSetCurrentPage(
    vnotebook		*notebook,
    vnotebookPage	*page
    );

void vnotebookGetCurrentPageNumber(
    vnotebook		*notebook,
    int			*pageNum,
    int			*total
    );

vnotebookSection *vnotebookGetSection(
    vnotebook		*notebook
    );

vdialogItem *vnotebookGetMinorTabSet(
    vnotebook		*notebook
    );

vdialogItem *vnotebookGetMajorTabSet(
    vnotebook		*notebook
    );

vnotebookStyle *vnotebookGetStyle(
    vnotebook		*notebook
    );

void vnotebookSetNotify(
    vnotebook        	*notebook,
    vnotebookNoteProc    noteProc
    );

void vnotebookSetData(
    vnotebook		*notebook,
    const void		*data
    );

void vnotebookSetStyle(
    vnotebook		*notebook,
    vnotebookStyle	*style
    );

void vnotebookSetStyleOwned(
    vnotebook		*notebook,
    vnotebookStyle	*style
    );

void vnotebookGetFolioSize(
    vnotebook		*notebook,
    int			*w,
    int			*h
    );

void vnotebookChangedStyle(
    vnotebook		*notebook
    );

void vnotebookDetermineStyle(
    vnotebook		*notebook,
    vnotebookStyle	*style,
    int			 whichSettings
    );

void vnotebookCalcFolioRect(
    vnotebook		*notebook,
    vrect		*rect
    );

void vnotebookDrawFolio(
    vnotebook		*notebook,
    vrect		*rect
    );

void vnotebookDrawFolioWith(
    vnotebook		*notebook,
    vrect		*rect,
    vdrawcontext        *context
    );

void vnotebookGetPageButtonSize(
    vnotebook		*notebook,
    int			*w,
    int			*h
    );

void vnotebookCalcPageButtonRects(
    vnotebook		*notebook,
    vrect		*nextRect,
    vrect		*prevRect
    );

void vnotebookRecalc(
    vnotebook		*notebook
    );

void vnotebookCalcPageRect(
    vnotebook		*notebook,
    vrect		*rect 
    );

void vnotebookCalcPageRectAt(
    vnotebook		*notebook,
    int			 page,
    vrect		*rect
    );

void vnotebookDrawBinder(
    vnotebook		*notebook
    );

void vnotebookDrawBinderWith(
    vnotebook		*notebook,
    vdrawcontext        *context
    );

void vnotebookDrawPageAt(
    vnotebook		*notebook,
    int			 pageNum,
    vrect		*rect
    );

void vnotebookDrawPageAtWith(
    vnotebook		*notebook,
    int			 pageNum,
    vrect		*rect,
    vdrawcontext        *context
    );

void vnotebookAppendPage( 
    vnotebook		*notebook,
    vnotebookPage	*page
    );

vnotebookPage *vnotebookRemovePage(
    vnotebook		*notebook,
    vnotebookPage	*page
    );

int vnotebookGetPageCount( 
    vnotebook		*notebook
    );

vnotebookPage *vnotebookGetPageAt(
    vnotebook		*notebook,
    int			 index
    );

vnotebookPage *vnotebookFindPage(
    vnotebook		*notebook,
    const vname		*name
    );

int vnotebookGetPageIndex(
    vnotebook		*notebook,
    vnotebookPage	*page
    );

void vnotebookSetPageIndex(
    vnotebook		*notebook,
    vnotebookPage	*page,
    int			 index
    );

void vnotebookGetTabSetSize(
    vnotebook		*notebook,
    vdialogItem		*tabset,
    int			*w,
    int			*h
    );

void vnotebookCalcTabSetRect(
    vnotebook		*notebook,
    vdialogItem		*tabset,
    vrect		*rect
    );

void vnotebookRecalcTabSetTabs(
    vnotebook		*notebook,
    vdialogItem		*tabset
    );

void vnotebookAddTabSetTab(
    vnotebook		*notebook,
    vdialogItem		*tabset,
    vnotebookTab	*tab
    );

vnotebookTab *vnotebookRemoveTabSetTab(
    vnotebook		*notebook,
    vdialogItem		*tabset,
    vnotebookTab	*tab
    );

int vnotebookGetTabSetTabCount(
    vnotebook		*notebook,
    vdialogItem		*tabset
    );

vnotebookTab *vnotebookGetTabSetTabAt(
    vnotebook		*notebook,
    vdialogItem		*tabset,
    int			 index
    );

void vnotebookGetMaxTabSetTabSize(
    vnotebook		*notebook,
    vdialogItem		*tabset,
    int			*w,
    int			*h
    );

vrect *vnotebookGetTabSetClipRects( 
    vnotebook 		*notebook, 
    vdialogItem		*tabset,
    int			*rectCount
    );

void vnotebookSetTabSetTabSelected(
    vnotebook		*notebook,
    vdialogItem		*tabset,
    vnotebookTab	*tab
    );

void vnotebookScrollTabSetTabIntoView(
    vnotebook		*notebook,
    vdialogItem		*tabset,
    vnotebookTab	*tab
    );

void vnotebookCalcTabSetTabRect(
    vnotebook		*notebook,
    vdialogItem		*tabset,
    vnotebookTab	*tab,
    vrect		*rect
    );

/*
 *  Sections
 */

vnotebookSectionClass *vnotebookGetDefaultSectionClass(
    void
    );

vnotebookSection *vnotebookCreateSectionOfClass(
    vnotebookSectionClass  		*clas
    );

vnotebookSection *vnotebookCreateSection(
    void
    );

vnotebook *vnotebookCloneSection(
    vnotebookSection			*section
    );

void vnotebookDestroySection( 
    vnotebookSection 			*section 
    );

void vnotebookInitSectionOfClass(
    vnotebookSection			*section,
    vnotebookSectionClass		*clas
    );

void vnotebookInitSection(
    vnotebookSection			*section
    );

void vnotebookCopySection(
    vnotebookSection			*src,
    vnotebookSection			*dest
    );

void vnotebookCopyInitSection(
    vnotebookSection             	*src,
    vnotebookSection              	*dest
    );

vnotebookSection *vnotebookLoadSection(
    vresource              	 resource
    );

void vnotebookLoadInitSection(
    vnotebookSection            *section,
    vresource                    resource
    );

void vnotebookStoreSection(
    vnotebookSection              *section,
    vresource                      resource
    );

vnotebookSectionClass *vnotebookGetSectionClass(
    vnotebookSection		*section
    );

vdialogItem *vnotebookGetSectionItem(
    vnotebookSection		*section
    );

vnotebookPage *vnotebookGetSectionPage(
    vnotebookSection		*section
    );

vcontainer *vnotebookGetSectionContainer(
    vnotebookSection		*section
    );

vnotebookPage *vnotebookGetSectionCurrentPage(
    vnotebookSection		*section
    );

vnotebookSectionNoteProc vnotebookGetSectionNotify(
    vnotebookSection        	*section
    );

const void *vnotebookGetSectionData(
    vnotebookSection		*section
    );

void vnotebookSetSectionNotify(
    vnotebookSection        	*section,
    vnotebookSectionNoteProc	 noteProc
    );

void vnotebookSetSectionData(
    vnotebookSection		*section,
    const void			*data
    );

void vnotebookSetSectionCurrentPage(
    vnotebookSection		*section,
    vnotebookPage	     	*page
    );

vnotebookPage *vnotebookGetSectionFirstPage(
    vnotebookSection	*section
    );

vnotebookPage *vnotebookGetSectionLastPage(
    vnotebookSection	*section
    );

vnotebookPage *vnotebookGetSectionNextPage(
    vnotebookSection	*section
    );

vnotebookPage *vnotebookGetSectionPreviousPage(
    vnotebookSection	*section
    );

void vnotebookSetSectionFirstPage(
    vnotebookSection	*section
    );

void vnotebookSetSectionLastPage(
    vnotebookSection	*section
    );

void vnotebookSetSectionNextPage(
    vnotebookSection	*section
    );

void vnotebookSetSectionPreviousPage(
    vnotebookSection	*section
    );

int vnotebookCalcSectionPageNumbers(
    vnotebookSection	*section,
    int			 start
    );

void vnotebookAppendSectionPage( 
    vnotebookSection  	*section,
    vnotebookPage	*Page
    );

vnotebookPage *vnotebookRemoveSectionPage( 
    vnotebookSection  	*section,
    vnotebookPage	*Page
    );

int vnotebookGetSectionPageCount( 
    vnotebookSection	*section
    );

vnotebookPage *vnotebookGetSectionPageAt(
    vnotebookSection   	*section,
    int			 index
    );

vnotebookPage *vnotebookFindSectionPage(
    vnotebookSection  	*section,
    const vname		*name
    );

int vnotebookGetSectionPageIndex(
    vnotebookSection  	*section,
    vnotebookPage	*page
    );

void vnotebookSetSectionPageIndex(
    vnotebookSection  	*section,
    vnotebookPage	*page,
    int			 index
    );

/*
 *  Pages
 */

vnotebookPageClass *vnotebookGetDefaultPageClass(
    void
    );

vnotebookPage *vnotebookCreatePageOfClass(
    vnotebookPageClass  		*clas
    );

vnotebookPage *vnotebookCreatePage(
    void
    );

vnotebookPage *vnotebookClonePage(
    vnotebookPage			*page
    );

void vnotebookDestroyPage( 
    vnotebookPage 			*page 
    );

void vnotebookInitPageOfClass(
    vnotebookPage			*page,
    vnotebookPageClass			*clas
    );

void vnotebookInitPage(
    vnotebookPage			*page
    );

void vnotebookCopyPage(
    vnotebookPage			*src,
    vnotebookPage			*dest
    );

void vnotebookCopyInitPage(
    vnotebookPage             	*src,
    vnotebookPage              	*dest
    );

vnotebookPage *vnotebookLoadPage(
    vresource              	 resource
    );

void vnotebookLoadInitPage(
    vnotebookPage              	*page,
    vresource                    resource
    );

void vnotebookStorePage(
    vnotebookPage                     *page,
    vresource                      resource
    );

int vnotebookGetPageNumber(
    vnotebookPage	*page
    );

void vnotebookSetPageNumber(
    vnotebookPage	*page,
    int			 number
    );

vnotebookPageClass *vnotebookGetPageClass( 
    vnotebookPage	*page
    );

vdialogItem *vnotebookGetPageItem( 
    vnotebookPage	*page
    );

vcontainer *vnotebookGetPageContainer( 
    vnotebookPage	*page
    );

vnotebookPageNoteProc vnotebookGetPageNotify(
    vnotebookPage        	*page
    );

const void *vnotebookGetPageData(
    vnotebookPage   	*page
    );

int vnotebookPageIsValid(
    vnotebookPage    	*page
    );

int vnotebookPageIsNotebook(
    vnotebookPage    	*page
    );

int vnotebookPageIsSection(
    vnotebookPage   	*page
    );

vnotebook *vnotebookDeterminePageNotebook( 
    vnotebookPage 	*page 
    );

vnotebookSection *vnotebookGetPageSection( 
    vnotebookPage 	*page 
    );

vnotebookTab *vnotebookCreatePageTab(
    vnotebookPage	*page
    );

vnotebookTab *vnotebookGetPageTab(
    vnotebookPage    	*page
    );

void vnotebookSetPageNotify(
    vnotebookPage        	*page,
    vnotebookPageNoteProc	 noteProc
    );

void vnotebookSetPageData(
    vnotebookPage   	*page,
    const void		*data
    );

void vnotebookSetPageTab(
    vnotebookPage	*page,
    vnotebookTab	*tab
    );

int vnotebookPageIsSelected( 
    vnotebookPage    	*page
    );

void vnotebookSetPageCurrent(
    vnotebookPage   	*page
    );

void vnotebookDrawPageBorder(
    vnotebookPage	*page,
    const vrect		*rect
    );

void vnotebookDrawPageBorderWith(
    vnotebookPage	*page,
    const vrect		*rect,
    vdrawcontext        *context
    );

void vnotebookDrawPageContent(
    vnotebookPage	*page,
    const vrect		*rect
    );

void vnotebookDrawPageContentWith(
    vnotebookPage	*page,
    const vrect		*rect,
    vdrawcontext        *context
    );

void vnotebookCalcPageContentRect(
    vnotebookPage	*page,
    vrect		*rect
    );

void vnotebookGetPageContentMinSize(
    vnotebookPage	*page,
    int			*w,
    int			*h
    );

void vnotebookGetPageContentNaturalSize(
    vnotebookPage	*page,
    int			*w,
    int			*h
    );

void vnotebookGetPageBorderSizes( 
    vnotebookPage 	*page, 
    int		     	*top,
    int			*left,
    int			*bottom,
    int			*right
    );

void vnotebookGetPageDecorationSizes( 
    vnotebookPage 	*page, 
    int		     	*top,
    int			*left,
    int			*bottom,
    int			*right
    );


/*
 *  vnotebookTab
 */

vnotebookTabClass *vnotebookGetDefaultTabClass(
    void
    );

vnotebookTab *vnotebookCreateTabOfClass(
    vnotebookTabClass		*clas
    );

vnotebookTab *vnotebookCreateTab(
    void
    );

vnotebookTab *vnotebookCloneTab(
    vnotebookTab	*tab
    );

void vnotebookInitTabOfClass( 
    vnotebookTab 	*tab,
    vnotebookTabClass 	*clas
    );

void vnotebookInitTab( 
    vnotebookTab 	*tab
    );

void vnotebookCopyTab( 
    vnotebookTab 	*src,
    vnotebookTab     	*dest
    );

void vnotebookCopyInitTab( 
    vnotebookTab 	*src,
    vnotebookTab     	*dest
    );

void vnotebookSetTabTabSet(
    vnotebookTab   	*tab,
    vdialogItem		*tabset
    );
    
void vnotebookDestroyTab( 
    vnotebookTab 	*tab
    );

vnotebookTab *vnotebookLoadTab(
    vresource		 resource
    );

void vnotebookLoadInitTab(
    vnotebookTab	*tab,
    vresource		 resource
    );

void vnotebookStoreTab(
    vnotebookTab	*tab,
    vresource		 resource
    );

vnotebookPage *vnotebookGetTabPage(
    vnotebookTab      	*tab
    );

vdialogItem *vnotebookGetTabTabSet(
    vnotebookTab      	*tab
    );

const void *vnotebookGetTabData(
    vnotebookTab	*tab
    );

vnotebookTabClass *vnotebookGetTabClass(
    vnotebookTab	*tab
    );

vdialogItem *vnotebookGetTabItem(
    vnotebookTab	*tab
    );

const vchar *vnotebookGetTabTitle(
    vnotebookTab	*tab
    );

void vnotebookSetTabTitle(
    vnotebookTab     	*tab,
    const vchar		*title
    );

void vnotebookSetTabTitleScribed(
    vnotebookTab     	*tab,
    vscribe		*scribe
    );

void vnotebookSetTabData(
    vnotebookTab	*tab,
    const void		*data
    );

void vnotebookSetTabImage(
    vnotebookTab     	*tab,
    vimage		*image
    );

void vnotebookSetTabImageOwned(
    vnotebookTab	*tab,
    vimage		*image
    );

void vnotebookSetTabImageMask(
    vnotebookTab	*tab,
    int			 mask
    );

void vnotebookSetTabImageNone(
    vnotebookTab     	*tab,
    int			 value
    );

int vnotebookGetTabImageNone(
    vnotebookTab	*tab
    );

int vnotebookIsTabImageMask( 
    vnotebookTab	*tab
    );

vimage *vnotebookGetTabImage(
    vnotebookTab	*tab
    );

vfont *vnotebookDetermineTabFont(
    vnotebookTab	*tab
    );

vimage *vnotebookDetermineTabImage(
    vnotebookTab	*tab,
    int			*isMask
    );

void vnotebookDrawTabContent(
    vnotebookTab	*tab,
    vrect 		*rect
    );

void vnotebookDrawTabContentWith(
    vnotebookTab	*tab,
    vrect 		*rect,
    vdrawcontext        *context
    );

void vnotebookDrawTabBorder(
    vnotebookTab    	*tab
    );

void vnotebookDrawTabBorderWith(
    vnotebookTab    	*tab,
    vdrawcontext        *context
    );

void vnotebookGetTabContentSize(
    vnotebookTab    	*tab,
    int			*w,
    int			*h
    );

/*
 *  vnotebookStyle 
 */

vnotebookStyleClass *vnotebookGetDefaultStyleClass(
    void
    );

vnotebookStyle *vnotebookCreateStyleOfClass(
    vnotebookStyleClass    	*clas
    );

vnotebookStyle *vnotebookCreateStyle(
    void
    );

void vnotebookInitStyleOfClass(
    vnotebookStyle	     	*style,
    vnotebookStyleClass		*clas
    );

void vnotebookInitStyle(
    vnotebookStyle	*style
    );

vnotebookStyle *vnotebookCloneStyle(
    vnotebookStyle	*style
    );

void vnotebookCopyStyle(
    vnotebookStyle	*src,
    vnotebookStyle	*dest
    );

void vnotebookCopyInitStyle(
    vnotebookStyle	*src,
    vnotebookStyle	*dest
    );

void vnotebookDestroyStyle(
    vnotebookStyle	*style
    );

void vnotebookStoreStyle(
    vnotebookStyle	*style,
    vresource		 resource
    );

void vnotebookLoadInitStyle(
    vnotebookStyle	*style,
    vresource		 resource 
    );

vnotebookStyle *vnotebookLoadStyle(
    vresource		 resource
    );

int vnotebookStyleIsEmpty(
    vnotebookStyle	*style
    );

vnotebookStyleClass *vnotebookGetStyleClass(
    vnotebookStyle	*style
    );

vobject *vnotebookGetStyleObject(
    vnotebookStyle	*style
    );

vloadable *vnotebookGetStyleLoadable(
    vnotebookStyle	*style
    );

int vnotebookGetStyleScalarValue(
    vnotebookStyle	*style,
    int			 whichValue
    );

void vnotebookSetStyleScalarValue(
    vnotebookStyle	*style,
    int			 whichValue,
    int			 value
    );

int vnotebookGetStyleMajorTabSetSide( 
    vnotebookStyle 	*style 
    );

int vnotebookGetStyleMinorTabSetSide( 
    vnotebookStyle 	*style 
    );

int vnotebookGetStyleTabs(
    vnotebookStyle 	*style 
    );

int vnotebookGetStyleTabStyle( 
    vnotebookStyle 	*style 
    );

int vnotebookGetStyleVerticalTabs( 
    vnotebookStyle 	*style 
    );

int vnotebookGetStyleFolio( 
    vnotebookStyle 	*style 
    );

int vnotebookGetStyleFolioJustification( 
    vnotebookStyle 	*style 
    );

int vnotebookGetStylePageButtons( 
    vnotebookStyle 	*style 
    );

int vnotebookGetStylePageBorders(
    vnotebookStyle 	*style 
    );

int vnotebookGetStylePagesWrap(
    vnotebookStyle 	*style 
    );

int vnotebookGetStyleBinding(
    vnotebookStyle 	*style 
    );

int vnotebookGetStyleBindingSize(
    vnotebookStyle 	*style 
    );

int vnotebookGetStylePageCount(
    vnotebookStyle 	*style 
    );

int vnotebookGetStylePageStep(
    vnotebookStyle 	*style 
    );

int vnotebookGetStylePageInset(
    vnotebookStyle 	*style 
    );

int vnotebookGetStylePageInsetBorder(
    vnotebookStyle 	*style 
    );

int vnotebookGetStyleTabSetButtonsCentered(
    vnotebookStyle 	*style 
    );

int vnotebookGetStyleTabSetButtonsPlacement(
    vnotebookStyle 	*style
    );

int vnotebookGetStyleTabSetPartialTabs(
    vnotebookStyle 	*style 
    );

int vnotebookGetStyleTabSpacing(
    vnotebookStyle 	*style 
    );

int vnotebookGetStyleTabInsetX(
    vnotebookStyle 	*style 
    );

int vnotebookGetStyleTabInsetY(
    vnotebookStyle 	*style 
    );

int vnotebookGetStyleTabSelectRaise(
    vnotebookStyle 	*style 
    );

int vnotebookGetStyleTabSelectResize(
    vnotebookStyle 	*style 
    );

int vnotebookGetStyleFolioButtonMargin(
    vnotebookStyle 	*style 
    );

int vnotebookGetStyleButtonMargin(
    vnotebookStyle 	*style 
    );

int vnotebookGetStyleButtonBorderMargin(
    vnotebookStyle 	*style 
    );


void vnotebookSetStyleMajorTabSetSide( 
    vnotebookStyle 	*style, 
    int 		 value 
    );

void vnotebookSetStyleMinorTabSetSide(
    vnotebookStyle 	*style, 
    int 		 value 
    );

void vnotebookSetStyleTabs(
    vnotebookStyle 	*style, 
    int 		 value 
    );

void vnotebookSetStyleTabStyle(
    vnotebookStyle 	*style, 
    int 		 value 
    );

void vnotebookSetStyleVerticalTabs(
    vnotebookStyle 	*style, 
    int 		 value 
    );

void vnotebookSetStyleFolio(
    vnotebookStyle 	*style, 
    int 		 value 
    );

void vnotebookSetStyleFolioJustification(
    vnotebookStyle 	*style, 
    int 		 value 
    );

void vnotebookSetStylePageButtons(
    vnotebookStyle 	*style, 
    int 		 value 
    );

void vnotebookSetStylePageBorders(
    vnotebookStyle 	*style, 
    int 		 value 
    );

void vnotebookSetStylePagesWrap(
    vnotebookStyle 	*style, 
    int 		 value 
    );

void vnotebookSetStyleBinding(
    vnotebookStyle 	*style, 
    int 		 value 
    );

void vnotebookSetStyleBindingSize(
    vnotebookStyle 	*style, 
    int 		 value 
    );

void vnotebookSetStylePageCount(
    vnotebookStyle 	*style, 
    int 		 value 
    );

void vnotebookSetStylePageStep(
    vnotebookStyle 	*style, 
    int 		 value 
    );

void vnotebookSetStylePageInset(
    vnotebookStyle 	*style, 
    int 		 value 
    );

void vnotebookSetStylePageInsetBorder(
    vnotebookStyle 	*style, 
    int 		 value 
    );

void vnotebookSetStyleTabSetButtonsCentered(
    vnotebookStyle 	*style, 
    int 		 value 
    );

void vnotebookSetStyleTabSetButtonsPlacement(
    vnotebookStyle 	*style, 
    int 		 value 
    );

void vnotebookSetStyleTabSetPartialTabs(
    vnotebookStyle 	*style, 
    int 		 value 
    );

void vnotebookSetStyleTabSpacing(
    vnotebookStyle 	*style, 
    int 		 value  
    );

void vnotebookSetStyleTabInsetX(
    vnotebookStyle 	*style, 
    int 		 value  
    );

void vnotebookSetStyleTabInsetY(
    vnotebookStyle 	*style, 
    int 		 value  
    );

void vnotebookSetStyleTabSelectRaise(
    vnotebookStyle 	*style, 
    int 		 value  
    );

void vnotebookSetStyleTabSelectResize(
    vnotebookStyle 	*style, 
    int 		 value  
    );

void vnotebookSetStyleFolioButtonMargin(
    vnotebookStyle 	*style, 
    int 		 value  
    );

void vnotebookSetStyleButtonMargin(
    vnotebookStyle 	*style, 
    int 		 value  
    );

void vnotebookSetStyleButtonBorderMargin(
    vnotebookStyle 	*style, 
    int 		 value  
    );


/*
 * deprecated functions
 */

void vnotebookDeletePage(
    vnotebook		*notebook,
    vnotebookPage	*page
    );

void vnotebookDeleteSectionPage( 
    vnotebookSection  	*section,
    vnotebookPage	*Page
    );

void vnotebookDeleteTabSetTab(
    vnotebook		*notebook,
    vdialogItem		*tabset,
    vnotebookTab	*tab
    );

/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum{
  _vnotebookPAGE_BUTTONS    		= 0x000100,
  _vnotebookFOLIO		 	= 0x000200,
  _vnotebookPAGE_TABS			= 0x000400,

  _vnotebookMAJOR_TABS			= 0x000800,
  _vnotebookMINOR_TABS			= 0x001000,
  _vnotebookTABSET_VERTICAL_TEXT	= 0x002000,
  _vnotebookMULTILINE_TABS		= 0x004000,
  _vnotebookDRAW_PAGE_BORDERS		= 0x008000,
  _vnotebookPAGES_WRAP			= 0x010000,
  _vnotebookSTYLE_OWNED			= 0x100000
};

enum{
  _vnotebookSECTION_MAJOR_TABS		= 0x0001,
  _vnotebookSECTION_MINOR_TABS		= 0x0002,
  _vnotebookSECTION_PAGE_TABS		= 0x0004
};

enum{
  _vnotebookMAJOR_TAB_MASK		= 0x00000C,
  _vnotebookMINOR_TAB_MASK		= 0x000030,
  _vnotebookTAB_MASK			= 0x000003,
  _vnotebookTABS_MASK			= 0x001C00,
  _vnotebookFOLIO_JUST_MASK		= 0x000003
};

enum{
  _vnotebookTAB_IMAGE_OWNED		= 0x0001,
  _vnotebookTAB_IMAGE_MASK		= 0x0002,
  _vnotebookTAB_NO_IMAGE		= 0x0004
};

enum{
  _vnotebookPAGE_SELECTED		= 0x0001
};

/*  vnotebookFlags
 *
 *                4               3               2               1
 *  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 *								---
 *  1-2 - folio just flags
 *  3-4 - major tab side
 *  5-6 - minor tab side
 *  7-8 - not used
 *  9   - page button flag
 * 10   - folio flag
 * 11   - page tabs flag
 * 12   - major tabs flag
 * 13   - minor tabs flag
 * 14   - vertical text on tabs flag
 * 15   - multiline tabs
 * 16   - page borders
 * 17   - pages wrap
 */

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct _vnotebookTabSetClass	 _vnotebookTabSetClass;
typedef struct _vnotebookTabSet		 _vnotebookTabSet;

struct vnotebookStyle{
  vobject		 object;
  unsigned long		 flags;
  unsigned long		 defaults;
  vbyte			 bindSize;
  vbyte			 pageCount;
  vbyte			 pageStep;
  vbyte		     	 pageInset;
  vbyte			 pageInsetBorder;
  vbyte			 tabGap;
  vbyte			 tabInsetX;
  vbyte			 tabInsetY;
  vbyte			 tabRaise;
  vbyte			 tabSelectOffset;
  vbyte			 folioButtonMargin;
  vbyte			 buttonMargin;
  vbyte			 buttonBorderMargin;
};

#define vnotebookSTYLE_CLASS(SUPER, STYLE)		 	\
  vobjectCLASS(SUPER, STYLE)

struct vnotebookStyleClass{
  vnotebookSTYLE_CLASS( vnotebookStyleClass, vnotebookStyle );
};

struct vnotebookTab{
  vdialogItem		 item;
  unsigned short	 flags;
  short			 contentW;
  short		 	 contentH;
  vnotebookPage		*page;
  vdialogItem		*tabset;
};

#define vnotebookTAB_CLASS(SUPER, TAB, NOTIFY)		 	\
  vdialogITEM_CLASS(SUPER, TAB, NOTIFY);		        \
  vclassMETHOD(vnotebookDRAW_TAB_BORDER, (TAB *tab));		\
  vclassMETHOD(vnotebookDRAW_TAB_BORDER_WITH,                   \
	       (TAB *tab, vdrawcontext *context));		\
  vclassMETHOD(vnotebookDRAW_TAB_CONTENT, 			\
	       (TAB *tab, vrect *rect));			\
  vclassMETHOD(vnotebookDRAW_TAB_CONTENT_WITH, 			\
	       (TAB *tab, vrect *rect, vdrawcontext *context)); \
  vclassMETHOD(vnotebookGET_TAB_CONTENT_SIZE, 			\
	       (TAB *tab, int *w, int *h))

struct vnotebookTabClass{
  vnotebookTAB_CLASS( vnotebookTabClass, vnotebookTab, vdialogItemNoteProc );
};

struct vnotebookPage{
  vcontainer		 	 container;
  unsigned short		 flags;
  vnotebookTab			*tab;
  short			 	 pageNum;
};

struct vnotebookSection{
  vnotebookPage		 page;
  unsigned int      	 flags;
  short			 numPages;
  short 	       	 totalPages;
};

#define vnotebookPageCLASS(SUPER, PAGE, TAB, NOTIFY)		\
  vcontainerCLASS(SUPER, PAGE, NOTIFY);				\
  vclassMETHOD(vnotebookSELECT_PAGE, (PAGE *page));		\
  vclassMETHOD(vnotebookUNSELECT_PAGE, (PAGE *page));		\
  vclassMETHOD_RET(vnotebookPAGE_IS_VALID, int, (PAGE *page));	\
  vclassMETHOD_RET(vnotebookCREATE_PAGE_TAB, TAB *, 		\
		   (PAGE *page));				\
  vclassMETHOD(vnotebookCALC_PAGE_CONTENT_RECT,			\
	       (PAGE *page, vrect *rect));			\
  vclassMETHOD(vnotebookDRAW_PAGE_CONTENT, 			\
	       (PAGE *page, const vrect *rect));		\
  vclassMETHOD(vnotebookDRAW_PAGE_CONTENT_WITH, 		\
	       (PAGE *page, const vrect *rect, vdrawcontext *context)); \
  vclassMETHOD(vnotebookDRAW_PAGE_BORDER, 			\
	       (PAGE *page, const vrect *rect));		\
  vclassMETHOD(vnotebookDRAW_PAGE_BORDER_WITH, 			\
	       (PAGE *page, const vrect *rect, vdrawcontext *context)); \
  vclassMETHOD(vnotebookGET_PAGE_CONTENT_MIN_SIZE, 		\
	       (PAGE *page, int *w, int *h));			\
  vclassMETHOD(vnotebookGET_PAGE_CONTENT_NATURAL_SIZE, 		\
	       (PAGE *page, int *w, int *h));			\
  vclassMETHOD(vnotebookGET_PAGE_BORDER_SIZES, 			\
	       (PAGE *page, int *top, int *left, 		\
		int *bot, int *rt));				\
  vclassMETHOD(vnotebookGET_PAGE_DECORATION_SIZES, 		\
	       (PAGE *page, int *top, int *left, 		\
		int *bot, int *rt));				\
  vclassMETHOD_RET(vnotebookPAGE_HAS_BORDER, int, (PAGE *page))
  

struct vnotebookPageClass{
  vnotebookPageCLASS( vnotebookPageClass, vnotebookPage, vnotebookTab,
		      vnotebookPageNoteProc );
};

#define vnotebookSectionCLASS(SUPER, SECTION, TAB, NOTIFY)  \
  vnotebookPageCLASS(SUPER, SECTION, TAB, NOTIFY)

struct vnotebookSectionClass{
  vnotebookSectionCLASS( vnotebookSectionClass, vnotebookSection, 
			 vnotebookTab, vnotebookSectionNoteProc );
};

struct vnotebook{
  vnotebookSection	 section;
  unsigned int		 flags;
  vrect			 folioRect;
  vrect			 pageRect;
  vnotebookStyle       	*style;
  short			 offsetX, offsetY;
  short			 bindPageCount;
  vbutton		*nextPageBtn;
  vbutton		*prevPageBtn;
  vdialogItem     	*majorTabs;
  vdialogItem   	*minorTabs;
  vdialogItem		*focusItem;
};

#define vnotebookCLASS(SUPER, NOTEBOOK, NOTIFY, TABSET, TAB)	        \
  vnotebookSectionCLASS(SUPER, NOTEBOOK, TAB, NOTIFY);		        \
  vclassVARIABLE(vnotebookCLASS_STYLE, vnotebookStyle *);		\
  vclassMETHOD(vnotebookSET_STYLE, 					\
	       (NOTEBOOK *notebook, vnotebookStyle *style));		\
  vclassMETHOD(vnotebookCHANGED_STYLE, (NOTEBOOK *notebook));		\
  vclassMETHOD(vnotebookDETERMINE_STYLE,				\
	       (NOTEBOOK *notebook, vnotebookStyle *style, int which));	\
  vclassMETHOD(vnotebookGET_FOLIO_SIZE, 				\
	       (NOTEBOOK *notebook, int *w, int *h));			\
  vclassMETHOD(vnotebookCALC_FOLIO_RECT, 				\
	       (NOTEBOOK *notebook, vrect *rect));			\
  vclassMETHOD(vnotebookDRAW_FOLIO, 					\
	       (NOTEBOOK *notebook, vrect *rect));			\
  vclassMETHOD(vnotebookDRAW_FOLIO_WITH,				\
	       (NOTEBOOK *notebook, vrect *rect, vdrawcontext *contetext));\
  vclassMETHOD(vnotebookGET_PAGE_BUTTON_SIZE, 				\
	       (NOTEBOOK *notebook, int *w, int *h));			\
  vclassMETHOD(vnotebookCALC_PAGE_BUTTON_RECTS, 			\
	       (NOTEBOOK *notebook, vrect *nextRect, vrect *prevRect));	\
  vclassMETHOD_RET(vnotebookCREATE_PAGE_BUTTON, vbutton *,		\
		   (NOTEBOOK *notebook, int whichBtn));			\
  vclassMETHOD(vnotebookRECALC, (NOTEBOOK *notebook));			\
  vclassMETHOD(vnotebookCALC_PAGE_RECT, 				\
	       (NOTEBOOK *notebook, vrect *rect));			\
  vclassMETHOD(vnotebookDRAW_BINDER, (NOTEBOOK *notebook));		\
  vclassMETHOD(vnotebookDRAW_BINDER_WITH,                               \
	       (NOTEBOOK *notebook, vdrawcontext *context));		\
  vclassMETHOD(vnotebookDRAW_PAGE_AT, 					\
	       (NOTEBOOK *notebook, int pageNum, vrect *rect));		\
  vclassMETHOD(vnotebookDRAW_PAGE_AT_WITH,				\
	       (NOTEBOOK *notebook, int pageNum,                        \
		vrect *rect, vdrawcontext *context));		        \
  vclassMETHOD(vnotebookRECALC_TABSET_TABS,				\
	       (NOTEBOOK *notebook, TABSET *tabset));			\
  vclassMETHOD(vnotebookGET_TABSET_SIZE, 				\
	       (NOTEBOOK *notebook, TABSET *tabset, int *w, int *h));   \
  vclassMETHOD(vnotebookCALC_TABSET_RECT,				\
	       (NOTEBOOK *notebook, TABSET *tabset, vrect *rect));	\
  vclassMETHOD(vnotebookGET_MAX_TABSET_TAB_SIZE, 			\
	       (NOTEBOOK *notebook, TABSET *tabset, int *w, int *h));	\
  vclassMETHOD_RET(vnotebookCREATE_TABSET, TABSET *,			\
		   (NOTEBOOK *notebook, int whichTabs));		\
  vclassMETHOD(vnotebookADD_TABSET_TAB,					\
	       (NOTEBOOK *notebook, TABSET *tabset, TAB *tab));		\
  vclassMETHOD_RET(vnotebookREMOVE_TABSET_TAB, TAB *,			\
	       (NOTEBOOK *notebook, TABSET *tabset, TAB *tab));		\
  vclassMETHOD(/* deprecated */ vnotebookDELETE_TABSET_TAB,		\
	       (NOTEBOOK *notebook, TABSET *tabset, TAB *tab));		\
  vclassMETHOD_RET(vnotebookGET_TABSET_TAB_COUNT, int,			\
		   (NOTEBOOK *notebook, TABSET *tabset));		\
  vclassMETHOD_RET(vnotebookGET_TABSET_TAB_AT, TAB *,			\
		   (NOTEBOOK *notebook, TABSET *tabset, int index));	\
  vclassMETHOD_RET(vnotebookGET_TABSET_CLIP_RECTS, vrect *,		\
		   (NOTEBOOK *notebook, TABSET *tabset, 		\
		    int *rectCount));					\
  vclassMETHOD(vnotebookSET_TABSET_TAB_SELECTED, 			\
	       (NOTEBOOK *notebook, TABSET *tabset, TAB *tab));		\
  vclassMETHOD(vnotebookSCROLL_TABSET_TAB_INTO_VIEW, 			\
	       (NOTEBOOK *notebook, TABSET *tabset, TAB *tab));		\
  vclassMETHOD(vnotebookCALC_TABSET_TAB_RECT, 				\
	       (NOTEBOOK *notebook, TABSET *tabset, 			\
		TAB *tab, vrect *rect))

struct vnotebookClass{
  vnotebookCLASS( vnotebookClass, vnotebook, vnotebookNoteProc, 
		  vdialogItem, vnotebookTab );
};

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

int _vnotebookGetTabs(
    vnotebook			*notebook
    );

vbool _vnotebookDetermineTabImageIsMask(
    vnotebookTab	*tab
    );

/*
 *  vnotebookTabSet
 */

_vnotebookTabSetClass *_vnotebookGetDefaultTabSetClass(
    void
    );

void _vnotebookSetTabSetNotebook( 
    _vnotebookTabSet	*tabset,
    vnotebook		*owner
    );

void _vnotebookSetTabSetType( 
    _vnotebookTabSet	*tabset,
    int			 value
    );

vrect *_vnotebookGetTabSetRects( 
    _vnotebookTabSet 		*tabset, 
    int 			*rectCount 
    );


/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 *  Styles
 */

#define vnotebookGetStyleClass( t ) \
  ( (vnotebookStyleClass *) vobjectGetClass( (vobject *) t ) )
#define vnotebookGetStyleObject( t ) \
  vportBASE_OBJECT(t, object)
#define vnotebookGetStyleLoadable( t ) \
  ( vobjectGetLoadable( vnotebookGetStyleObject( t ) ) )

#define vnotebookCreateStyleOfClass(t) \
    ((vnotebookStyle *) vloadableCreateOfClass((vloadableClass*)(t)))
#define vnotebookCreateStyle() \
    vnotebookCreateStyleOfClass( vnotebookGetDefaultStyleClass() )
#define vnotebookDestroyStyle( t ) \
    vloadableDestroy( vnotebookGetStyleLoadable( t ) )
#define vnotebookCloneStyle(n) \
    ((vnotebookStyle *) vloadableClone((vloadable *) n))
#define vnotebookInitStyleOfClass(n, c) \
    vloadableInitOfClass((vloadable *) (n), (vloadableClass *)(c))
#define vnotebookInitStyle(n) \
    vnotebookInitStyleOfClass(n, vnotebookGetDefaultStyleClass())
#define vnotebookCopyInitStyle(n, t) \
    vloadableCopyInit((vloadable *) (n), (vloadable *) (t))
#define vnotebookCopyStyle( s, d ) \
    vloadableCopy( vnotebookGetStyleLoadable( s ), vnotebookGetStyleLoadable( d ) )
#define vnotebookLoadStyle(r) \
    ((vnotebookStyle *) vloadableLoad(r))
#define vnotebookLoadInitStyle(n, r) \
    vloadableLoadInit((vloadable *)(n), r)
#define vnotebookStoreStyle( t, r ) \
    vloadableStore( vnotebookGetStyleLoadable( t ), r )


/*
 *  Tabs 
 */

#define vnotebookGetTabClass( t ) \
  ( (vnotebookTabClass *) vdialogGetItemClass( (vdialogItem *) t ) )
#define vnotebookGetTabItem( t )	( vportBASE_OBJECT( ( t ), item ) )

#define vnotebookCreateTabOfClass(t) \
    ((vnotebookTab *) vdialogCreateItemOfClass((vdialogItemClass*)(t)))
#define vnotebookCreateTab() \
    vnotebookCreateTabOfClass(vnotebookGetDefaultTabClass())
#define vnotebookDestroyTab( t ) \
    vdialogDestroyItem( vnotebookGetTabItem( t ) )
#define vnotebookCloneTab(n) \
    ((vnotebookTab*)vdialogCloneItem((vdialogItem *) n))
#define vnotebookInitTabOfClass(n, c) \
    vdialogInitItemOfClass((vdialogItem *) (n), (vnotebookTabClass*)(c))
#define vnotebookInitTab(n) \
    vnotebookInitTabOfClass(n, vnotebookGetDefaultTabClass())
#define vnotebookCopyInitTab(n, t) \
    vdialogCopyInitItem((vdialogItem *) (n), (vdialogItem *) (t))
#define vnotebookCopyTab( s, d ) \
    vdialogCopyItem( vnotebookGetTabItem( s ), vnotebookGetTabItem( d ) )
#define vnotebookLoadTab(r) \
    ((vnotebookTab*) vdialogLoadItem(r))
#define vnotebookLoadInitTab(n, r) \
    vdialogLoadInitItem((vdialogItem *)(n), r)
#define vnotebookStoreTab( t, r ) \
    vdialogStoreItem( vnotebookGetTabItem( t ), r )
#define vnotebookGetTabData( t ) \
    vdialogGetItemData(vnotebookGetTabItem(t))
#define vnotebookSetTabData( t, d ) \
    vdialogSetItemData( vnotebookGetTabItem( t ), d )


#define vnotebookGetTabPage( t )      	( (t)->page )
#define vnotebookGetTabTabSet( t )      ( (t)->tabset )
#define vnotebookGetTabImage( t ) \
  (vdialogGetItemImage(vnotebookGetTabItem(t)))

#define vnotebookSetTabTitle( t, s ) \
  (vdialogSetItemTitle(vnotebookGetTabItem(t), s))
#define vnotebookSetTabTitleScribed( t, s ) \
  (vdialogSetItemTitleScribed(vnotebookGetTabItem(t), s))

#define vnotebookSetTabImage( t, i ) \
  (vdialogSetItemImage(vnotebookGetTabItem(t), i))
#define vnotebookSetTabImageOwned( t, i ) \
  (vdialogSetItemImageOwned(vnotebookGetTabItem(t), i))
#define vnotebookSetTabImageMask( t, v ) \
  (vdialogSetItemImageMask(vnotebookGetTabItem(t), v))

#define vnotebookIsTabImageMask( t ) \
  ( ((t)->flags & _vnotebookTAB_IMAGE_MASK) != 0 )
#define vnotebookGetTabImageNone( t ) \
  ( ((t)->flags & _vnotebookTAB_NO_IMAGE) != 0 )

#define vnotebookSetTabTabSet( t, ts )  ( (t)->tabset = (ts) )

/*
 *  Pages
 */

#define vnotebookGetPageClass( n ) \
  ( (vnotebookPageClass *) vcontainerGetClass( (vcontainer *) n ) )

#define vnotebookGetPageContainer( p ) \
  ( vportBASE_OBJECT( ( p ), container ) )
#define vnotebookGetPageItem( p ) \
  vcontainerGetItem( vnotebookGetPageContainer( p ) )

#define vnotebookCreatePageOfClass(p) \
    ((vnotebookPage*) vdialogCreateItemOfClass((vdialogItemClass*)(p)))
#define vnotebookCreatePage() \
    vnotebookCreatePageOfClass(vnotebookGetDefaultPageClass())
#define vnotebookDestroyPage( p ) \
    vdialogDestroyItem( vnotebookGetPageItem( p ) )
#define vnotebookClonePage(p) \
    ((vnotebookPage*)vdialogCloneItem((vdialogItem *) p))
#define vnotebookInitPageOfClass(p, c) \
    vdialogInitItemOfClass((vdialogItem *) (p), (vnotebookPageClass*)(c))
#define vnotebookInitPage(p) \
    vnotebookInitPageOfClass(p, vnotebookGetDefaultPageClass())
#define vnotebookCopyInitPage(p, t) \
    vdialogCopyInitItem((vdialogItem *) (p), (vdialogItem *) (t))
#define vnotebookCopyPage( p, d ) \
    vdialogCopyItem( vnotebookGetPageItem( p ), \
		     vnotebookGetPageItem( d ) )
#define vnotebookLoadPage(r) \
    ((vnotebookPage *) vdialogLoadItem(r))
#define vnotebookLoadInitPage(p, r) \
    vdialogLoadInitItem((vdialogItem *)(p), r)
#define vnotebookStorePage( p, r ) \
    vdialogStoreItem( vnotebookGetPageItem( p ), r )
#define vnotebookGetPageData( p ) \
    vdialogGetItemData( vnotebookGetPageItem( p ) )
#define vnotebookSetPageData( p, d ) \
    vdialogSetItemData( vnotebookGetPageItem( p ), d )

#define vnotebookPageIsNotebook( i ) \
  ( vclassIsKindOf( vdialogGetItemClass( (vdialogItem *) i ), \
		    vnotebookGetDefaultClass() ) )
#define vnotebookPageIsSection( i ) \
  ( vclassIsKindOf( vdialogGetItemClass( (vdialogItem *) i ), \
		    vnotebookGetDefaultSectionClass() ) )

#define vnotebookGetPageTab( n )	( (n)->tab )

#define vnotebookGetPageNumber( p )	( (p)->pageNum )
#define vnotebookSetPageNumber( p, n )	( (p)->pageNum = n )

#define vnotebookGetPageIndex( n, p ) \
  ( vcontainerGetItemIndex( (vcontainer *) n, (vdialogItem *) p ) )
#define vnotebookGetPageCount( n ) \
  ( vcontainerGetItemCount( (vcontainer *) n ) )
#define vnotebookGetPageAt( n, i ) \
  ( (vnotebookPage *) vcontainerGetItemAt( (vcontainer *) n, i ) )
#define vnotebookFindPage( n, t ) \
  ( (vnotebookPage *) vcontainerFindItem( (vcontainer *) n, t ) )
#define vnotebookSetPageIndex( n, p, i ) \
  ( vcontainerSetItemIndex( (vcontainer *) n, (vdialogItem *) p, i ) )
#define vnotebookAppendPage( n, p ) \
  ( vcontainerAppendItem( (vcontainer *) n, (vdialogItem *) p ) )
#define vnotebookRemovePage( n, p ) \
  ( (vnotebookPage *) vcontainerRemoveItem( (vcontainer *) n, \
					    (vdialogItem *) p ) )
#define vnotebookDeletePage( n, p ) \
  ( vcontainerDeleteItem( (vcontainer *) n, (vdialogItem *) p ) )

#define vnotebookGetPageNotify(b) \
  ((vnotebookPageNoteProc)vdialogGetItemNotify(vnotebookGetPageItem(b)))
#define vnotebookSetPageNotify(b, n) \
  vdialogSetItemNotify((vdialogItem *)(b), (vdialogItemNoteProc)(n))

#define vnotebookPageIsSelected(p) \
  (((p)->flags & _vnotebookPAGE_SELECTED) != 0)

/*
 *  Sections
 */

#define vnotebookGetSectionClass( n ) \
  ( (vnotebookSectionClass *) vobjectGetClass( (vobject *) n ) )

#define vnotebookGetSectionPage( s ) \
  ( vportBASE_OBJECT( ( s ), page ) )
#define vnotebookGetSectionContainer( s ) \
  vnotebookGetPageContainer( vnotebookGetSectionPage( s ) )
#define vnotebookGetSectionItem( s ) \
  vcontainerGetItem( vnotebookGetSectionContainer( s ) )

#define vnotebookCreateSectionOfClass(p) \
    ((vnotebookSection*) vdialogCreateItemOfClass((vdialogItemClass*)(p)))
#define vnotebookCreateSection() \
    vnotebookCreateSectionOfClass(vnotebookGetDefaultSectionClass())
#define vnotebookDestroySection( s ) \
    vdialogDestroyItem( vnotebookGetSectionItem( s ) )
#define vnotebookCloneSection(p) \
    ((vnotebookSection*)vdialogCloneItem((vdialogItem *) p))
#define vnotebookInitSectionOfClass(p, c) \
    vdialogInitItemOfClass((vdialogItem *) (p), (vnotebookSectionClass*)(c))
#define vnotebookInitSection(p) \
    vnotebookInitSectionOfClass(p, vnotebookGetDefaultSectionClass())
#define vnotebookCopyInitSection(p, t) \
    vdialogCopyInitItem((vdialogItem *) (p), (vdialogItem *) (t))
#define vnotebookCopySection( s, d ) \
    vdialogCopyItem( vnotebookGetSectionItem( s ), \
		     vnotebookGetSectionItem( d ) )
#define vnotebookLoadSection(r) \
    ((vnotebookSection *) vdialogLoadItem(r))
#define vnotebookStoreSection( s, r ) \
    vdialogStoreItem( vnotebookGetSectionItem( s ), r )
#define vnotebookLoadInitSection(p, r) \
    vdialogLoadInitItem((vdialogItem *)(p), r)
#define vnotebookGetSectionData( n ) \
    (vdialogGetItemData(vnotebookGetSectionItem((n))))
#define vnotebookSetSectionData( s, d ) \
    vdialogSetItemData( vnotebookGetSectionItem( s ), d )

#define vnotebookGetSectionCurrentPage( s )	\
  ((vnotebookPage *) vcontainerGetSelection( (vcontainer *) s ))
#define vnotebookSetSectionCurrentPage( s, i ) \
  vcontainerSetSelection( vnotebookGetSectionContainer( s ), \
			  (vdialogItem *) (i) )

#define vnotebookGetSectionPageIndex( s, p ) \
  ( vcontainerGetItemIndex( (vcontainer *) s, (vdialogItem *) p ) )
#define vnotebookGetSectionPageCount( n ) \
  ( vcontainerGetItemCount( (vcontainer *) n ) )
#define vnotebookGetSectionPageAt( n, i ) \
  ( (vnotebookPage *) vcontainerGetItemAt( (vcontainer *) n, i ) )
#define vnotebookFindSectionPage( n, t ) \
  ( (vnotebookPage *) vcontainerFindItem( (vcontainer *) n, t ) )
#define vnotebookSetSectionPageIndex( n, p, i ) \
  ( vcontainerSetItemIndex( (vcontainer *) n, (vdialogItem *) p, i ) )
#define vnotebookAppendSectionPage( s, p ) \
  ( vcontainerAppendItem( (vcontainer *) s, (vdialogItem *) p ) )
#define vnotebookRemoveSectionPage( s, p ) \
  ( (vnotebookPage *) vcontainerRemoveItem( (vcontainer *) s, \
					    (vdialogItem *) p ) )
#define vnotebookDeleteSectionPage( s, p ) \
  ( vcontainerDeleteItem( (vcontainer *) s, (vdialogItem *) p ) )

#define vnotebookGetSectionNotify(s) \
  ((vnotebookSectionNoteProc)vdialogGetItemNotify(vnotebookGetSectionItem(s)))
#define vnotebookSetSectionNotify(s, n) \
  vdialogSetItemNotify((vdialogItem *)(s), (vdialogItemNoteProc)(n))

/*
 *  Notebooks
 */

#define vnotebookGetClass( n ) \
  ( (vnotebookClass *) vcontainerGetClass( (vcontainer *) n ) )

#define vnotebookGetSection( n ) \
  ( vportBASE_OBJECT( ( n ), section ) )
#define vnotebookGetContainer( n ) \
  vnotebookGetSectionContainer( vnotebookGetSection( n ) )
#define vnotebookGetItem( n ) \
  vcontainerGetItem( vnotebookGetContainer( n ) )

#define vnotebookCreateOfClass(n) \
    ((vnotebook*) vdialogCreateItemOfClass((vdialogItemClass*)(n)))
#define vnotebookCreate() \
    vnotebookCreateOfClass(vnotebookGetDefaultClass())
#define vnotebookDestroy( n ) \
    vdialogDestroyItem( vnotebookGetItem( n ) )
#define vnotebookClone(n) \
    ((vnotebook*)vdialogCloneItem((vdialogItem *) n))
#define vnotebookInitOfClass(n, c) \
    vdialogInitItemOfClass((vdialogItem *) (n), (vnotebookClass*)(c))
#define vnotebookInit(n) \
    vnotebookInitOfClass(n, vnotebookGetDefaultClass())
#define vnotebookCopyInit(n, t) \
    vdialogCopyInitItem((vdialogItem *) (n), (vdialogItem *) (t))
#define vnotebookCopy( n, d ) \
    vdialogCopyItem( vnotebookGetItem( n ), vnotebookGetItem( d ) )
#define vnotebookLoad(r) \
    ((vnotebook*) vdialogLoadItem(r))
#define vnotebookLoadInit(n, r) \
    vdialogLoadInitItem((vdialogItem *)(n), r)
#define vnotebookStore( n, r ) \
    vdialogStoreItem( vnotebookGetItem( n ), r )
#define vnotebookGetData( n ) \
    (vdialogGetItemData(vnotebookGetItem((n))))
#define vnotebookSetData( n, d ) \
    vdialogSetItemData( vnotebookGetItem( n ), d )

#define vnotebookGetCurrentPage( n ) \
  ( vnotebookGetSectionCurrentPage( vnotebookGetSection( n ) ) )
#define vnotebookSetCurrentPage( n, d ) \
  ( vnotebookSetSectionCurrentPage( vnotebookGetSection( n ), d ) )

#define _vnotebookGetMajorTabSide( n ) \
  ( ((n)->flags >> 2) & _vnotebookTAB_MASK )
#define _vnotebookGetMinorTabSide( n ) \
  ( ((n)->flags >> 4) & _vnotebookTAB_MASK )
#define _vnotebookGetFolioJustification( n ) \
  ( ((n)->flags & _vnotebookFOLIO_JUST_MASK ) )

#define _vnotebookHasPageButtons( n ) \
  ( ((n)->flags & _vnotebookPAGE_BUTTONS) != 0 )
#define _vnotebookHasFolio( n ) \
  ( ((n)->flags & _vnotebookFOLIO) != 0 )

#define _vnotebookGetDrawPageBorders( n ) \
  ( ((n)->flags & _vnotebookDRAW_PAGE_BORDERS) != 0 )

#define _vnotebookHasRotatedTextOnVerticalTabs( n ) \
  ( (n)->flags & _vnotebookTABSET_VERTICAL_TEXT )

#define _vnotebookHasPageWrap( n ) \
  ( (n)->flags & _vnotebookPAGES_WRAP )

#define vnotebookGetNotify(b) \
  ((vnotebookNoteProc)vdialogGetItemNotify(vnotebookGetItem(b)))
#define vnotebookSetNotify(b, n) \
  vdialogSetItemNotify((vdialogItem *)(b), (vdialogItemNoteProc)(n))

#define vnotebookGetMajorTabSet( n )	( (n)->majorTabs )
#define vnotebookGetMinorTabSet( n )	( (n)->minorTabs )

#define vnotebookGetStyle( n )		( (n)->style )


/*
 *  Styles
 */

#define vnotebookGetStyleMajorTabSetSide( s ) \
  vnotebookGetStyleScalarValue( s, vnotebookSTYLE_MAJOR_TABSET_SIDE )
#define vnotebookGetStyleMinorTabSetSide( s ) \
  vnotebookGetStyleScalarValue( s, vnotebookSTYLE_MINOR_TABSET_SIDE )
#define vnotebookGetStyleTabs( s ) \
  vnotebookGetStyleScalarValue( s, vnotebookSTYLE_TABS )
#define vnotebookGetStyleFolio( s ) \
  vnotebookGetStyleScalarValue( s, vnotebookSTYLE_FOLIO )
#define vnotebookGetStyleFolioJustification( s ) \
  vnotebookGetStyleScalarValue( s, vnotebookSTYLE_FOLIO_JUSTIFY )
#define vnotebookGetStylePageButtons( s ) \
  vnotebookGetStyleScalarValue( s, vnotebookSTYLE_PAGE_BUTTONS )
#define vnotebookGetStyleTabStyle( s ) \
  vnotebookGetStyleScalarValue( s, vnotebookSTYLE_TAB_STYLE )
#define vnotebookGetStyleVerticalTabs( s ) \
  vnotebookGetStyleScalarValue( s, vnotebookSTYLE_VERTICAL_TABS )
#define vnotebookGetStylePagesWrap( s ) \
  vnotebookGetStyleScalarValue( s, vnotebookSTYLE_PAGES_WRAP )
#define vnotebookGetStylePageBorders( s ) \
  vnotebookGetStyleScalarValue( s, vnotebookSTYLE_PAGE_BORDERS )
#define vnotebookGetStyleBinding( s ) \
  vnotebookGetStyleScalarValue( s, vnotebookSTYLE_BINDING )
#define vnotebookGetStylePageCount( s ) \
  vnotebookGetStyleScalarValue( s, vnotebookSTYLE_PAGE_COUNT )
#define vnotebookGetStylePageStep( s ) \
  vnotebookGetStyleScalarValue( s, vnotebookSTYLE_PAGE_STEP )
#define vnotebookGetStyleBindingSize( s ) \
  vnotebookGetStyleScalarValue( s, vnotebookSTYLE_BINDING_SIZE )
#define vnotebookGetStylePageInset( s ) \
  vnotebookGetStyleScalarValue( s, vnotebookSTYLE_PAGE_INSET )
#define vnotebookGetStylePageInsetBorder( s ) \
  vnotebookGetStyleScalarValue( s, vnotebookSTYLE_PAGE_INSET_BORDER )
#define vnotebookGetStyleTabSetButtonsCentered( s ) \
  vnotebookGetStyleScalarValue( s, vnotebookSTYLE_TABSET_BUTTONS_CENTERED )
#define vnotebookGetStyleTabSetButtonsPlacement( s ) \
  vnotebookGetStyleScalarValue( s, vnotebookSTYLE_TABSET_BUTTONS_PLACEMENT )
#define vnotebookGetStyleTabSetPartialTabs( s ) \
  vnotebookGetStyleScalarValue( s, vnotebookSTYLE_TABSET_PARTIAL_TABS )
#define vnotebookGetStyleTabSpacing( s ) \
  vnotebookGetStyleScalarValue( s, vnotebookSTYLE_TAB_SPACING )
#define vnotebookGetStyleTabInsetX( s ) \
  vnotebookGetStyleScalarValue( s, vnotebookSTYLE_TAB_INSET_X )
#define vnotebookGetStyleTabInsetY( s ) \
  vnotebookGetStyleScalarValue( s, vnotebookSTYLE_TAB_INSET_Y )
#define vnotebookGetStyleTabSelectRaise( s ) \
  vnotebookGetStyleScalarValue( s, vnotebookSTYLE_TAB_SELECT_RAISE )
#define vnotebookGetStyleTabSelectResize( s ) \
  vnotebookGetStyleScalarValue( s, vnotebookSTYLE_TAB_SELECT_RESIZE )
#define vnotebookGetStyleFolioButtonMargin( s ) \
  vnotebookGetStyleScalarValue( s, vnotebookSTYLE_FOLIO_BUTTON_MARGIN )
#define vnotebookGetStyleButtonMargin( s ) \
  vnotebookGetStyleScalarValue( s, vnotebookSTYLE_BUTTON_MARGIN )
#define vnotebookGetStyleButtonBorderMargin( s ) \
  vnotebookGetStyleScalarValue( s, vnotebookSTYLE_BUTTON_BORDER_MARGIN )

#define vnotebookSetStyleMajorTabSetSide( s, v ) \
  vnotebookSetStyleScalarValue( s, vnotebookSTYLE_MAJOR_TABSET_SIDE, v )
#define vnotebookSetStyleMinorTabSetSide( s, v ) \
  vnotebookSetStyleScalarValue( s, vnotebookSTYLE_MINOR_TABSET_SIDE, v )
#define vnotebookSetStyleTabs( s, v ) \
  vnotebookSetStyleScalarValue( s, vnotebookSTYLE_TABS, v )
#define vnotebookSetStyleFolio( s, v ) \
  vnotebookSetStyleScalarValue( s, vnotebookSTYLE_FOLIO, v )
#define vnotebookSetStyleFolioJustification( s, v ) \
  vnotebookSetStyleScalarValue( s, vnotebookSTYLE_FOLIO_JUSTIFY, v )
#define vnotebookSetStylePageButtons( s, v ) \
  vnotebookSetStyleScalarValue( s, vnotebookSTYLE_PAGE_BUTTONS, v )
#define vnotebookSetStyleTabStyle( s, v ) \
  vnotebookSetStyleScalarValue( s, vnotebookSTYLE_TAB_STYLE, v )
#define vnotebookSetStyleVerticalTabs( s, v ) \
  vnotebookSetStyleScalarValue( s, vnotebookSTYLE_VERTICAL_TABS, v )
#define vnotebookSetStylePagesWrap( s, v ) \
  vnotebookSetStyleScalarValue( s, vnotebookSTYLE_PAGES_WRAP, v )
#define vnotebookSetStylePageBorders( s, v ) \
  vnotebookSetStyleScalarValue( s, vnotebookSTYLE_PAGE_BORDERS, v )
#define vnotebookSetStyleBinding( s, v ) \
  vnotebookSetStyleScalarValue( s, vnotebookSTYLE_BINDING, v )
#define vnotebookSetStylePageCount( s, v ) \
  vnotebookSetStyleScalarValue( s, vnotebookSTYLE_PAGE_COUNT, v )
#define vnotebookSetStylePageStep( s, v ) \
  vnotebookSetStyleScalarValue( s, vnotebookSTYLE_PAGE_STEP, v )
#define vnotebookSetStyleBindingSize( s, v ) \
  vnotebookSetStyleScalarValue( s, vnotebookSTYLE_BINDING_SIZE, v )
#define vnotebookSetStylePageInset( s, v ) \
  vnotebookSetStyleScalarValue( s, vnotebookSTYLE_PAGE_INSET, v )
#define vnotebookSetStylePageInsetBorder( s, v ) \
  vnotebookSetStyleScalarValue( s, vnotebookSTYLE_PAGE_INSET_BORDER, v )
#define vnotebookSetStyleTabSetButtonsCentered( s, v ) \
  vnotebookSetStyleScalarValue( s, vnotebookSTYLE_TABSET_BUTTONS_CENTERED, v )
#define vnotebookSetStyleTabSetButtonsPlacement( s, v ) \
  vnotebookSetStyleScalarValue( s, vnotebookSTYLE_TABSET_BUTTONS_PLACEMENT, v )
#define vnotebookSetStyleTabSetPartialTabs( s, v ) \
  vnotebookSetStyleScalarValue( s, vnotebookSTYLE_TABSET_PARTIAL_TABS, v )
#define vnotebookSetStyleTabSpacing( s, v ) \
  vnotebookSetStyleScalarValue( s, vnotebookSTYLE_TAB_SPACING, v )
#define vnotebookSetStyleTabInsetX( s, v ) \
  vnotebookSetStyleScalarValue( s, vnotebookSTYLE_TAB_INSET_X, v )
#define vnotebookSetStyleTabInsetY( s, v ) \
  vnotebookSetStyleScalarValue( s, vnotebookSTYLE_TAB_INSET_Y, v )
#define vnotebookSetStyleTabSelectRaise( s, v ) \
  vnotebookSetStyleScalarValue( s, vnotebookSTYLE_TAB_SELECT_RAISE, v )
#define vnotebookSetStyleTabSelectResize( s, v ) \
  vnotebookSetStyleScalarValue( s, vnotebookSTYLE_TAB_SELECT_RESIZE, v )
#define vnotebookSetStyleFolioButtonMargin( s, v ) \
  vnotebookSetStyleScalarValue( s, vnotebookSTYLE_FOLIO_BUTTON_MARGIN, v )
#define vnotebookSetStyleButtonMargin( s, v) \
  vnotebookSetStyleScalarValue( s, vnotebookSTYLE_BUTTON_MARGIN, v )
#define vnotebookSetStyleButtonBorderMargin( s, v ) \
  vnotebookSetStyleScalarValue( s, vnotebookSTYLE_BUTTON_BORDER_MARGIN, v )

/*
 *  Miscellaneous
 */

#define _vnotebookCreateDefaultTabSet()	\
  ( (_vnotebookTabSet *) vobjectCreateOfClass( _vnotebookGetDefaultTabSetClass() ) )



/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

/*
 *  Page
 */

#define vnotebookPageIsValid( p ) \
  vclassSend( vnotebookGetPageClass( p ), vnotebookPAGE_IS_VALID, (p) )
#define vnotebookCreatePageTab( p ) \
  vclassSend( vnotebookGetPageClass( p ), vnotebookCREATE_PAGE_TAB, (p) )

#define vnotebookCalcPageContentRect( p, r ) \
  vclassSend( vnotebookGetPageClass( p ), vnotebookCALC_PAGE_CONTENT_RECT, (p, r) )
#define vnotebookDrawPageContent( p, r ) \
  vclassSend( vnotebookGetPageClass( p ), vnotebookDRAW_PAGE_CONTENT, (p, r) )
#define vnotebookDrawPageContentWith( p, r, c ) \
  vclassSend( vnotebookGetPageClass( p ), vnotebookDRAW_PAGE_CONTENT_WITH, \
	      (p, r, c) )
#define vnotebookDrawPageBorder( p, r ) \
  vclassSend( vnotebookGetPageClass( p ), vnotebookDRAW_PAGE_BORDER, (p, r) )
#define vnotebookDrawPageBorderWith( p, r, c ) \
  vclassSend( vnotebookGetPageClass( p ), vnotebookDRAW_PAGE_BORDER_WITH,   \
	      (p, r, c) )


#define vnotebookGetPageContentMinSize( p, w, h ) \
  vclassSend( vnotebookGetPageClass( p ), vnotebookGET_PAGE_CONTENT_MIN_SIZE, (p, w, h) )
#define vnotebookGetPageContentNaturalSize( p, w, h ) \
  vclassSend( vnotebookGetPageClass( p ), vnotebookGET_PAGE_CONTENT_NATURAL_SIZE, (p, w, h) )

#define vnotebookGetPageBorderSizes( p, t, l, b, r ) \
  vclassSend( vnotebookGetPageClass( p ), vnotebookGET_PAGE_BORDER_SIZES, (p, t, l, b, r) )
#define vnotebookGetPageDecorationSizes( p, t, l, b, r ) \
  vclassSend( vnotebookGetPageClass( p ), vnotebookGET_PAGE_DECORATION_SIZES, (p, t, l, b, r) )

/*
 *  Tab
 */

#define vnotebookGetTabContentSize( t, w, h ) \
  vclassSend( vnotebookGetTabClass( t ), vnotebookGET_TAB_CONTENT_SIZE, (t, w, h) )
#define vnotebookDrawTabContent( t, r ) \
  vclassSend( vnotebookGetTabClass( t ), vnotebookDRAW_TAB_CONTENT, (t, r) )
#define vnotebookDrawTabContentWith( t, r,c  ) \
  vclassSend( vnotebookGetTabClass( t ), vnotebookDRAW_TAB_CONTENT_WITH, \
	      (t, r, c) )
#define vnotebookDrawTabBorder( t ) \
  vclassSend( vnotebookGetTabClass( t ), vnotebookDRAW_TAB_BORDER, (t) )
#define vnotebookDrawTabBorderWith( t, c ) \
  vclassSend( vnotebookGetTabClass( t ), vnotebookDRAW_TAB_BORDER_WITH, (t, c) )

/*
 *  Section
 */

/*
 *  Notebook
 */

#define vnotebookRecalc( n ) \
  vclassSend( vnotebookGetClass( n ), vnotebookRECALC, (n) )

#define vnotebookDrawBinder( n ) \
  vclassSend( vnotebookGetClass( n ), vnotebookDRAW_BINDER, (n) )
#define vnotebookDrawBinderWith( n, c ) \
  vclassSend( vnotebookGetClass( n ), vnotebookDRAW_BINDER_WITH, (n, c) )
#define vnotebookDrawPageAt( n, i, r ) \
  vclassSend( vnotebookGetClass( n ), vnotebookDRAW_PAGE_AT, (n, i, r) )
#define vnotebookDrawPageAtWith( n, i, r, c ) \
  vclassSend( vnotebookGetClass( n ), vnotebookDRAW_PAGE_AT_WITH, (n, i, r, c) )

#define vnotebookGetPageButtonSize( n, w, h ) \
  vclassSend( vnotebookGetClass( n ), vnotebookGET_PAGE_BUTTON_SIZE, (n, w, h) )
#define vnotebookCalcPageButtonRects( n, x, p ) \
  vclassSend( vnotebookGetClass( n ), vnotebookCALC_PAGE_BUTTON_RECTS, (n, x, p) )

#define vnotebookGetFolioSize( n, w, h ) \
  vclassSend( vnotebookGetClass( n ), vnotebookGET_FOLIO_SIZE, (n, w, h) )
#define vnotebookCalcFolioRect( n, r ) \
  vclassSend( vnotebookGetClass( n ), vnotebookCALC_FOLIO_RECT, (n, r) )
#define vnotebookDrawFolio( n, r ) \
  vclassSend( vnotebookGetClass( n ), vnotebookDRAW_FOLIO, (n, r) )
#define vnotebookDrawFolioWith( n, r, c ) \
  vclassSend( vnotebookGetClass( n ), vnotebookDRAW_FOLIO_WITH, (n, r, c) )

#define vnotebookCalcPageRect( n, r ) \
  vclassSend( vnotebookGetClass( n ), vnotebookCALC_PAGE_RECT, (n, r) )

#define vnotebookGetTabSetSize( n, t, w, h ) \
  vclassSend( vnotebookGetClass( n ), vnotebookGET_TABSET_SIZE, (n, t, w, h) )
#define vnotebookCalcTabSetRect( n, t, r ) \
  vclassSend( vnotebookGetClass( n ), vnotebookCALC_TABSET_RECT, (n, t, r) )

#define vnotebookRecalcTabSetTabs( n, t ) \
  vclassSend( vnotebookGetClass( n ), vnotebookRECALC_TABSET_TABS, (n, t) )

#define vnotebookGetMaxTabSetTabSize( n, t, w, h ) \
  vclassSend( vnotebookGetClass( n ), vnotebookGET_MAX_TABSET_TAB_SIZE, (n, t, w, h) )

#define vnotebookGetTabSetTabAt( n, t, i ) \
  vclassSend( vnotebookGetClass( n ), vnotebookGET_TABSET_TAB_AT, (n, t, i) )
#define vnotebookAddTabSetTab( n, t, tab ) \
  vclassSend( vnotebookGetClass( n ), vnotebookADD_TABSET_TAB, (n, t, tab) )
#define vnotebookRemoveTabSetTab( n, t, tab ) \
  vclassSend( vnotebookGetClass( n ), vnotebookREMOVE_TABSET_TAB, (n, t, tab) )
#define vnotebookDeleteTabSetTab( n, t, tab ) \
  ( (void) vnotebookRemoveTabSetTab( n, t, tab ) )
#define vnotebookGetTabSetTabCount( n, t ) \
  vclassSend( vnotebookGetClass( n ), vnotebookGET_TABSET_TAB_COUNT, (n, t) )
#define vnotebookGetTabSetClipRects( n, t, c ) \
  vclassSend( vnotebookGetClass( n ), vnotebookGET_TABSET_CLIP_RECTS, (n, t, c) )

#define vnotebookSetTabSetTabSelected( n, ts, t ) \
  vclassSend( vnotebookGetClass( n ), vnotebookSET_TABSET_TAB_SELECTED, (n, ts, t) )
#define vnotebookScrollTabSetTabIntoView( n, ts, t ) \
  vclassSend( vnotebookGetClass( n ), vnotebookSCROLL_TABSET_TAB_INTO_VIEW, (n, ts, t) )
#define vnotebookCalcTabSetTabRect( n, ts, t, r ) \
  vclassSend( vnotebookGetClass( n ), vnotebookCALC_TABSET_TAB_RECT, (n, ts, t, r) )

#define vnotebookChangedStyle( n ) \
  vclassSend( vnotebookGetClass( n ), vnotebookCHANGED_STYLE, (n) )
#define vnotebookSetStyle( n, s ) \
  vclassSend( vnotebookGetClass( n ), vnotebookSET_STYLE, (n, s) )
#define vnotebookDetermineStyle( n, s, w ) \
  vclassSend( vnotebookGetClass( n ), vnotebookDETERMINE_STYLE, (n, s, w) )

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vnotebookINCLUDED */

