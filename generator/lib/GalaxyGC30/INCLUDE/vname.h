/* $Id: vname.h,v 1.82 1997/09/09 23:40:35 robert Exp $ */

/************************************************************

    vname.h

    C Interface file for the Name Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vnameINCLUDED
#define vnameINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vstdioINCLUDED
#include vstdioHEADER
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef  vexINCLUDED
#include vexHEADER
#endif

#ifndef  vmemINCLUDED
#include vmemHEADER
#endif

#ifndef  vscribeINCLUDED
#include vscribeHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vclientINCLUDED
#include vclientHEADER
#endif

#ifndef  vmutexINCLUDED
#include vmutexHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

#define vnameNULL                  (_vnamePredefs[_vnameNULL])
#define vname_Abandon              (_vnamePredefs[_vname_Abandon])
#define vname_About                (_vnamePredefs[_vname_About])
#define vname_Accelerator          (_vnamePredefs[_vname_Accelerator])
#define vname_Adjust               (_vnamePredefs[_vname_Adjust])
#define vname_Apply                (_vnamePredefs[_vname_Apply])
#define vname_Array                (_vnamePredefs[_vname_Array])
#define vname_Attribute            (_vnamePredefs[_vname_Attribute])
#define vname_Background           (_vnamePredefs[_vname_Background])
#define vname_BackgroundDeboss     (_vnamePredefs[_vname_BackgroundDeboss])
#define vname_BackgroundEmboss     (_vnamePredefs[_vname_BackgroundEmboss])
#define vname_BackgroundHilite     (_vnamePredefs[_vname_BackgroundHilite])
#define vname_Binding              (_vnamePredefs[_vname_Binding])
#define vname_Bits                 (_vnamePredefs[_vname_Bits])
#define vname_BlockCursor          (_vnamePredefs[_vname_BlockCursor])
#define vname_Border               (_vnamePredefs[_vname_Border])
#define vname_Bottom           	   (_vnamePredefs[_vname_Bottom])
#define vname_Bounds               (_vnamePredefs[_vname_Bounds])
#define vname_Cancel               (_vnamePredefs[_vname_Cancel])
#define vname_Class                (_vnamePredefs[_vname_Class])
#define vname_Classes              (_vnamePredefs[_vname_Classes])
#define vname_Clear                (_vnamePredefs[_vname_Clear])
#define vname_Close                (_vnamePredefs[_vname_Close])
#define vname_Color                (_vnamePredefs[_vname_Color])
#define vname_Colors               (_vnamePredefs[_vname_Colors])
#define vname_Command              (_vnamePredefs[_vname_Command])
#define vname_Confirm              (_vnamePredefs[_vname_Confirm])
#define vname_Content              (_vnamePredefs[_vname_Content])
#define vname_Copy                 (_vnamePredefs[_vname_Copy])
#define vname_CurrentConfirm       (_vnamePredefs[_vname_CurrentConfirm])
#define vname_Cursor               (_vnamePredefs[_vname_Cursor])
#define vname_Cut                  (_vnamePredefs[_vname_Cut])
#define vname_Data                 (_vnamePredefs[_vname_Data])
#define vname_Date                 (_vnamePredefs[_vname_Date])
#define vname_Default              (_vnamePredefs[_vname_Default])
#define vname_DefaultFocus         (_vnamePredefs[_vname_DefaultFocus])
#define vname_Defaults             (_vnamePredefs[_vname_Defaults])
#define vname_Depth                (_vnamePredefs[_vname_Depth])
#define vname_Dialog               (_vnamePredefs[_vname_Dialog])
#define vname_Dictionary           (_vnamePredefs[_vname_Dictionary])
#define vname_Direction            (_vnamePredefs[_vname_Direction])
#define vname_Disable              (_vnamePredefs[_vname_Disable])
#define vname_Disabled             (_vnamePredefs[_vname_Disabled])
#define vname_Dispatch             (_vnamePredefs[_vname_Dispatch])
#define vname_Document             (_vnamePredefs[_vname_Document])
#define vname_DocumentPath         (_vnamePredefs[_vname_DocumentPath])
#define vname_Domain               (_vnamePredefs[_vname_Domain])
#define vname_Down                 (_vnamePredefs[_vname_Down])
#define vname_Drag                 (_vnamePredefs[_vname_Drag])
#define vname_Dropsite             (_vnamePredefs[_vname_Dropsite])
#define vname_Duplicate            (_vnamePredefs[_vname_Duplicate])
#define vname_Enabled              (_vnamePredefs[_vname_Enabled])
#define vname_Event                (_vnamePredefs[_vname_Event])
#define vname_Exclusive            (_vnamePredefs[_vname_Exclusive])
#define vname_Extend               (_vnamePredefs[_vname_Extend])
#define vname_False                (_vnamePredefs[_vname_False])
#define vname_Field                (_vnamePredefs[_vname_Field])
#define vname_Flags                (_vnamePredefs[_vname_Flags])
#define vname_Flat                 (_vnamePredefs[_vname_Flat])
#define vname_Focus                (_vnamePredefs[_vname_Focus])
#define vname_Font                 (_vnamePredefs[_vname_Font])
#define vname_Foreground           (_vnamePredefs[_vname_Foreground])
#define vname_ForegroundHilite     (_vnamePredefs[_vname_ForegroundHilite])
#define vname_FormCommand          (_vnamePredefs[_vname_FormCommand])
#define vname_Format               (_vnamePredefs[_vname_Format])
#define vname_Galaxy               (_vnamePredefs[_vname_Galaxy])
#define vname_Grab                 (_vnamePredefs[_vname_Grab])
#define vname_Group                (_vnamePredefs[_vname_Group])
#define vname_Height               (_vnamePredefs[_vname_Height])
#define vname_Help                 (_vnamePredefs[_vname_Help])
#define vname_HelpMode             (_vnamePredefs[_vname_HelpMode])
#define vname_Horizontal           (_vnamePredefs[_vname_Horizontal])
#define vname_Hour                 (_vnamePredefs[_vname_Hour])
#define vname_Hypertext            (_vnamePredefs[_vname_Hypertext])
#define vname_Icon                 (_vnamePredefs[_vname_Icon])
#define vname_Image                (_vnamePredefs[_vname_Image])
#define vname_ImageMask            (_vnamePredefs[_vname_ImageMask])
#define vname_Increment            (_vnamePredefs[_vname_Increment])
#define vname_Index                (_vnamePredefs[_vname_Index])
#define vname_Issue                (_vnamePredefs[_vname_Issue])
#define vname_Item                 (_vnamePredefs[_vname_Item])
#define vname_ItemCount            (_vnamePredefs[_vname_ItemCount])
#define vname_ItemList             (_vnamePredefs[_vname_ItemList])
#define vname_Items                (_vnamePredefs[_vname_Items])
#define vname_Key                  (_vnamePredefs[_vname_Key])
#define vname_Left                 (_vnamePredefs[_vname_Left])
#define vname_Length               (_vnamePredefs[_vname_Length])
#define vname_LineWidth            (_vnamePredefs[_vname_LineWidth])
#define vname_Map                  (_vnamePredefs[_vname_Map])
#define vname_Max                  (_vnamePredefs[_vname_Max])
#define vname_MaxColumn            (_vnamePredefs[_vname_MaxColumn])
#define vname_MaxRow               (_vnamePredefs[_vname_MaxRow])
#define vname_MaxSize              (_vnamePredefs[_vname_MaxSize])
#define vname_Menu                 (_vnamePredefs[_vname_Menu])
#define vname_MenuBar              (_vnamePredefs[_vname_MenuBar])
#define vname_MenuList             (_vnamePredefs[_vname_MenuList])
#define vname_Metrics              (_vnamePredefs[_vname_Metrics])
#define vname_Min                  (_vnamePredefs[_vname_Min])
#define vname_MinSize              (_vnamePredefs[_vname_MinSize])
#define vname_Minute               (_vnamePredefs[_vname_Minute])
#define vname_Mnemonic             (_vnamePredefs[_vname_Mnemonic])
#define vname_Month                (_vnamePredefs[_vname_Month])
#define vname_Move                 (_vnamePredefs[_vname_Move])
#define vname_Name                 (_vnamePredefs[_vname_Name])
#define vname_No                   (_vnamePredefs[_vname_No])
#define vname_NumMajor             (_vnamePredefs[_vname_NumMajor])
#define vname_NumMinor             (_vnamePredefs[_vname_NumMinor])
#define vname_Objects              (_vnamePredefs[_vname_Objects])
#define vname_Off                  (_vnamePredefs[_vname_Off])
#define vname_Offset               (_vnamePredefs[_vname_Offset])
#define vname_Ok                   (_vnamePredefs[_vname_Ok])
#define vname_OldValue             (_vnamePredefs[_vname_OldValue])
#define vname_On                   (_vnamePredefs[_vname_On])
#define vname_Open                 (_vnamePredefs[_vname_Open])
#define vname_Operand              (_vnamePredefs[_vname_Operand])
#define vname_Operator             (_vnamePredefs[_vname_Operator])
#define vname_Page                 (_vnamePredefs[_vname_Page])
#define vname_Pairs                (_vnamePredefs[_vname_Pairs])
#define vname_Palette              (_vnamePredefs[_vname_Palette])
#define vname_Paper                (_vnamePredefs[_vname_Paper])
#define vname_Paste                (_vnamePredefs[_vname_Paste])
#define vname_Phrase               (_vnamePredefs[_vname_Phrase])
#define vname_Preferences          (_vnamePredefs[_vname_Preferences])
#define vname_Print                (_vnamePredefs[_vname_Print])
#define vname_Query                (_vnamePredefs[_vname_Query])
#define vname_Quit                 (_vnamePredefs[_vname_Quit])
#define vname_Rect                 (_vnamePredefs[_vname_Rect])
#define vname_Rects                (_vnamePredefs[_vname_Rects])
#define vname_Redo                 (_vnamePredefs[_vname_Redo])
#define vname_Reset                (_vnamePredefs[_vname_Reset])
#define vname_Right                (_vnamePredefs[_vname_Right])
#define vname_ScrollX              (_vnamePredefs[_vname_ScrollX])
#define vname_ScrollY              (_vnamePredefs[_vname_ScrollY])
#define vname_Second               (_vnamePredefs[_vname_Second])
#define vname_Select               (_vnamePredefs[_vname_Select])
#define vname_Selection            (_vnamePredefs[_vname_Selection])
#define vname_ShadowBottom         (_vnamePredefs[_vname_ShadowBottom])
#define vname_ShadowTop            (_vnamePredefs[_vname_ShadowTop])
#define vname_Shown                (_vnamePredefs[_vname_Shown])
#define vname_Size                 (_vnamePredefs[_vname_Size])
#define vname_Solution             (_vnamePredefs[_vname_Solution])
#define vname_Space                (_vnamePredefs[_vname_Space])
#define vname_State                (_vnamePredefs[_vname_State])
#define vname_Static               (_vnamePredefs[_vname_Static])
#define vname_Status               (_vnamePredefs[_vname_Status])
#define vname_Steps                (_vnamePredefs[_vname_Steps])
#define vname_Style                (_vnamePredefs[_vname_Style])
#define vname_SubMenu              (_vnamePredefs[_vname_SubMenu])
#define vname_SystemFont           (_vnamePredefs[_vname_SystemFont])
#define vname_Tag                  (_vnamePredefs[_vname_Tag])
#define vname_Tags                 (_vnamePredefs[_vname_Tags])
#define vname_Text                 (_vnamePredefs[_vname_Text])
#define vname_TextFlags            (_vnamePredefs[_vname_TextFlags])
#define vname_TextView             (_vnamePredefs[_vname_TextView])
#define vname_TextViewFlags        (_vnamePredefs[_vname_TextViewFlags])
#define vname_Tip                  (_vnamePredefs[_vname_Tip])
#define vname_Title                (_vnamePredefs[_vname_Title])
#define vname_Toggle               (_vnamePredefs[_vname_Toggle])
#define vname_Top                  (_vnamePredefs[_vname_Top])
#define vname_Transparency         (_vnamePredefs[_vname_Transparency])
#define vname_True                 (_vnamePredefs[_vname_True])
#define vname_Type                 (_vnamePredefs[_vname_Type])
#define vname_Undo                 (_vnamePredefs[_vname_Undo])
#define vname_Up                   (_vnamePredefs[_vname_Up])
#define vname_Value                (_vnamePredefs[_vname_Value])
#define vname_Values               (_vnamePredefs[_vname_Values])
#define vname_Vertical             (_vnamePredefs[_vname_Vertical])
#define vname_View                 (_vnamePredefs[_vname_View])
#define vname_Width                (_vnamePredefs[_vname_Width])
#define vname_Year	   	   (_vnamePredefs[_vname_Year])
#define vname_Yes	   	   (_vnamePredefs[_vname_Yes])

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef vchar                       vname;
typedef struct vnameTable           vnameTable;
typedef struct vnameTableIterator   vnameTableIterator;

typedef unsigned long (*vnameHashFunc)(
    const void                     *p
    );

typedef unsigned long (*vnameCustomHashFunc)(
    void                           *customData,
    const void                     *p
    );

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vnameStartup(
    void
    );

unsigned long vnameMakePrime(
    unsigned long                   n
    );

unsigned long vnameHashString(
    const void                     *s
    );

unsigned long vnameHashStringSized(
    const void                     *s,
    size_t		           length
    );

unsigned long vport__IMPORT vnameHash(
    const void                     *name
    );

vnameTable *vnameCreate(
    vnameHashFunc                   hashFunc
    );

vnameTable *vnameCreateCustom(
    vnameCustomHashFunc             hashFunc,
    void			   *customData
    );

void vnameInit(
    vnameTable                     *table,
    vnameHashFunc                   hashFunc
    );

void vnameInitCustom(
    vnameTable                     *table,
    vnameCustomHashFunc             hashFunc,
    void			   *customData
    );

void vnameDestroy(
    vnameTable                     *table
    );

vnameTable *vnameGetGlobalTable(
    void
    );

const vname *vnameIntern(
    vnameTable                     *table,
    const vchar                    *str
    );

const vname *vnameInternUnsafe(
    vnameTable                     *table,
    const vchar                    *str
    );

const vname *vnameInternScribed(
    vnameTable                     *table,
    vscribe                        *scribe
    );

const vname *vnameInternUnsafeScribed(
    vnameTable                     *table,
    vscribe                        *scribe
    );

const vname *vnameInternLiteral(
    vnameTable                     *table,
    const char                     *str
    );

const vname *vnameInternUnsafeLiteral(
    vnameTable                     *table,
    const char                     *str
    );

const vname *vnameInternGlobal(
    const vchar                    *str
    );

const vname *vnameInternGlobalScribed(
    vscribe                        *scribe
    );

const vname *vnameInternGlobalLiteral(
    const char                     *str
    );

const vname *vnameGet(
    vnameTable                     *table,
    const vchar                    *str
    );

const vname *vnameGetUnsafe(
    vnameTable                     *table,
    const vchar                    *str
    );

const vname *vnameGetScribed(
    vnameTable                     *table,
    vscribe                        *scribe
    );

const vname *vnameGetUnsafeScribed(
    vnameTable                     *table,
    vscribe                        *scribe
    );

const vname *vnameGetGlobal(
    const vchar                    *str
    );

const vname *vnameGetGlobalScribed(
    vscribe                        *scribe
    );

vscribe *vnameScribe(
    vnameTable                     *table,
    const vname                    *name
    );

vscribe *vnameScribeGlobal(
    const vname                    *name
    );

void vnameDump(
    vnameTable                     *table,
    FILE                           *stream
    );

void vnameSetHashSize(
    vnameTable                     *table,
    unsigned long                   hashSize
    );

void vnameSetCustomData(
    vnameTable                     *table,
    void			   *data
    );

vnameHashFunc vnameGetHashFunc(
    vnameTable                     *table
    );

vnameCustomHashFunc vnameGetCustomHashFunc(
    vnameTable                     *table
    );

void *vnameGetCustomData(
    vnameTable                     *table
    );

unsigned long vnameGetHashSize(
    vnameTable                     *table
    );

unsigned long vnameGetSize(
    vnameTable                     *table
    );

void  vnameSetTableMutex(
    vnameTable                     *table,
    vmutex		           *mutex
    );

vmutex  *vnameGetTableMutex(
    vnameTable                     *table
    );

void  vnameLockTable(
    vnameTable                     *table
    );

void  vnameUnlockTable(
    vnameTable                     *table
    );

void vnameInitTableIterator(
    vnameTableIterator             *iterator,
    vnameTable                     *table
    );

int vnameNextTableIterator(
    vnameTableIterator             *iterator
    );

void vnameDestroyTableIterator(
    vnameTableIterator             *iterator
    );

const vname *vnameGetTableIteratorName(
    vnameTableIterator             *iterator
    );

/*
 * * * * * * * * * * PUBLIC EXCEPTION INTERFACE * * * * * * * * * *
 */

typedef struct vnameArgTagException {
    vexArgException	 parent;
    const vname		*tag;
} vnameArgTagException;

void  vnameGenerateArgTag( const vname *tag );
void  vnameGenerateMessagedArgTag( const vname *tag, const char *msg );
void  vnameArgTAG( void *exception, va_list *ap );

const vexClass *vnameGetArgTagClass( void );
const vname *vnameGetArgExceptionTag( vnameArgTagException *ex );
vnameArgTagException *vnameGetArgTagException( void );

extern vportLINK const vexClass _vnameArgTagClass;

#define vnameGetArgTagClass()			\
    (&_vnameArgTagClass)
#define vnameGetArgTagException()		\
    ((vnameArgTagException *) vexGetExceptionOfClass( &_vnameArgTagClass ))
#define vnameGetArgExceptionTag( exception )	\
    ((exception)->tag)

#define vnameGenerateArgTag(tag)		\
    vexGenerate( &_vnameArgTagClass, vnameArgTAG, tag, vexNULL )

#define vnameGenerateMessagedArgTag(tag, msg)			\
    vexGenerate( &_vnameArgTagClass, vnameArgTAG,		\
		 tag, vexMESSAGE, msg, vexNULL )


/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    _vnameNULL,
    _vname_Abandon,
    _vname_About,
    _vname_Accelerator,
    _vname_Adjust,
    _vname_Apply,
    _vname_Array,
    _vname_Attribute,
    _vname_Background,
    _vname_BackgroundDeboss,
    _vname_BackgroundEmboss,
    _vname_BackgroundHilite,
    _vname_Binding,
    _vname_Bits,
    _vname_BlockCursor,
    _vname_Border,
    _vname_Bottom,
    _vname_Bounds,
    _vname_Cancel,
    _vname_Class,
    _vname_Classes,
    _vname_Clear,
    _vname_Close,
    _vname_Color,
    _vname_Colors, 
    _vname_Command,
    _vname_Confirm,
    _vname_Content,
    _vname_Copy,
    _vname_CurrentConfirm,
    _vname_Cursor,
    _vname_Cut,
    _vname_Data,
    _vname_Date,
    _vname_Default,
    _vname_DefaultFocus,
    _vname_Defaults,
    _vname_Depth,
    _vname_Dialog,
    _vname_Dictionary,
    _vname_Direction,
    _vname_Disable,
    _vname_Disabled,
    _vname_Dispatch,
    _vname_Document,
    _vname_DocumentPath,
    _vname_Domain,
    _vname_Down,
    _vname_Drag,
    _vname_Dropsite,
    _vname_Duplicate,
    _vname_Enabled,
    _vname_Event,
    _vname_Exclusive,
    _vname_Extend,
    _vname_False,
    _vname_Field,
    _vname_Flags,
    _vname_Flat,
    _vname_Focus,
    _vname_Font,
    _vname_Foreground,
    _vname_ForegroundHilite,
    _vname_FormCommand,
    _vname_Format,
    _vname_Galaxy,
    _vname_Grab,
    _vname_Group,
    _vname_Height,
    _vname_Help,
    _vname_HelpMode,
    _vname_Horizontal,
    _vname_Hour,
    _vname_Hypertext,
    _vname_Icon,
    _vname_Image,
    _vname_ImageMask,
    _vname_Increment,
    _vname_Index,
    _vname_Issue,
    _vname_Item,
    _vname_ItemCount,
    _vname_ItemList,
    _vname_Items,
    _vname_Key,
    _vname_Left,
    _vname_Length,
    _vname_LineWidth,
    _vname_Map,
    _vname_Max,
    _vname_MaxColumn,
    _vname_MaxRow,
    _vname_MaxSize,
    _vname_Menu,
    _vname_MenuBar,
    _vname_MenuList,
    _vname_Metrics,
    _vname_Min,
    _vname_MinSize,
    _vname_Minute,
    _vname_Mnemonic,
    _vname_Month,
    _vname_Move,
    _vname_Name,
    _vname_No,
    _vname_NumMajor,
    _vname_NumMinor,
    _vname_Objects,
    _vname_Off,
    _vname_Offset,
    _vname_Ok,
    _vname_OldValue,
    _vname_On,
    _vname_Open,
    _vname_Operand,
    _vname_Operator,
    _vname_Page,
    _vname_Pairs,
    _vname_Palette,
    _vname_Paper,
    _vname_Paste,
    _vname_Phrase,
    _vname_Preferences,
    _vname_Print,
    _vname_Query,
    _vname_Quit,
    _vname_Rect,
    _vname_Rects,
    _vname_Redo,
    _vname_Reset,
    _vname_Right,
    _vname_ScrollX,
    _vname_ScrollY,
    _vname_Second,
    _vname_Select,
    _vname_Selection,
    _vname_ShadowBottom,
    _vname_ShadowTop,
    _vname_Shown,
    _vname_Size,
    _vname_Solution,
    _vname_Space,
    _vname_State,
    _vname_Static,
    _vname_Status,
    _vname_Steps,
    _vname_Style,
    _vname_SubMenu,
    _vname_SystemFont,
    _vname_Tag,
    _vname_Tags,
    _vname_Text,
    _vname_TextFlags,
    _vname_TextView,
    _vname_TextViewFlags,
    _vname_Tip,
    _vname_Title,
    _vname_Toggle,
    _vname_Top,
    _vname_Transparency,
    _vname_True,
    _vname_Type,
    _vname_Undo,
    _vname_Up,
    _vname_Value,
    _vname_Values,
    _vname_Vertical,
    _vname_View,
    _vname_Width,
    _vname_Year,
    _vname_Yes,
    _vnameCOUNT
};

#define _vnameDYNAMIC_FLAG	   0x01

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct _vname               _vname;
typedef struct _vnameBuffer         _vnameBuffer;

struct vnameTable {
    _vnameBuffer                   *buffers, *bufNext, *bufMax;
    vnameHashFunc                   hashFunc;
    vnameCustomHashFunc             customHashFunc;
    void			   *customData;
    unsigned long                   hashSize;
    unsigned short		    flags;
    unsigned long                   space;
    unsigned long                   minSpace;
    const _vname                  **hash, **max;
    vmutex		           *mutex;
};

struct vnameTableIterator {
    const _vname                  **scan, **stop;
    vnameTable			  *table;
};

struct _vname {
    unsigned long                   hash;
    vchar                           str[1];
};

/*
 * * * * * * * * * * PRIVATE VARIABLE DECLARATIONS * * * * * * * * * *
 */

extern vportLINK const vname                 *_vnamePredefs[];

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

#if (vdebugDEBUG)

vnameTable *_vnameCreateDebug(
    vnameHashFunc                   hashFunc,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

vnameTable *_vnameCreateCustomDebug(
    vnameCustomHashFunc             hashFunc,
    void			   *customData,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

#endif

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#if (vdebugDEBUG)
#define vnameCreate(f) \
    _vnameCreateDebug(f, vmemTAG, __FILE__, __LINE__)
#define vnameCreateCustom(f, d) \
    _vnameCreateCustomDebug(f, d, vmemTAG, __FILE__, __LINE__)
#endif

#define vnameIntern(t, s)           vnameInternScribed(t, vcharScribe(s))
#define vnameInternUnsafeLiteral(t, s)    \
 			    vnameInternUnsafeScribed(t, vcharScribeLiteral(s))
#define vnameInternUnsafe(t, s)     vnameInternUnsafeScribed(t, vcharScribe(s))
#define vnameInternGlobal(s)        vnameInternGlobalScribed(vcharScribe(s))
#define vnameGet(t, s)              vnameGetScribed(t, vcharScribe(s))
#define vnameGetUnsafe(t, s)        vnameGetUnsafeScribed(t, vcharScribe(s))
#define vnameGetGlobal(s)           vnameGetGlobalScribed(vcharScribe(s))
#define vnameScribe(t, n)           vcharScribe(n)

#define vnameGetHashFunc(t)       ((t)->hashFunc)
#define vnameGetCustomHashFunc(t) ((t)->customHashFunc)
#define vnameGetCustomData(t)     ((t)->customData)
#define vnameSetCustomData(t,d)   ((t)->customData = (d))
#define vnameGetHashSize(t)       ((t)->hashSize)
#define vnameGetSize(t)           ((t)->hashSize-(t)->space)

#define vnameGetTableMutex(t)	  ((t)->mutex)

#define vnameLockTable(t)	  vmutexLockWithHandling((t)->mutex)
#define vnameUnlockTable(t)	  vmutexUnlockWithHandling((t)->mutex)

#define vnameGetTableIteratorName(i) ((*(i)->scan)->str)

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vnameINCLUDED */

/*
 * Formatting information for emacs
 *
 * Local Variables:
 * c-argdecl-indent:4
 * c-basic-offset:4
 * c-brace-imaginary-offset:0
 * c-brace-offset:-4
 * c-continued-brace-offset:0
 * c-continued-statement-offset:4
 * c-indent-level:4
 * c-label-offset:-2
 * tab-width:8
 * End:
 */

