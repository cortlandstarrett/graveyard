/* $Id: vresource.h,v 1.93 1997/07/24 22:16:59 sean Exp $ */

/************************************************************

    vresource.h
    C Interface to the Resource Manager

    (c) Copyright Visix Software  1993
    All rights reserved

************************************************************/

#ifndef vresourceINCLUDED
#define vresourceINCLUDED 1

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstdioINCLUDED		/* for FILE */
#include vstdioHEADER
#endif

#ifndef  vstddefINCLUDED	/* for size_t */
#include vstddefHEADER
#endif

#ifndef  vstdINCLUDED		/* for vbyte, vbool */
#include vstdHEADER
#endif

#ifndef  vexINCLUDED
#include vexHEADER
#endif

#ifndef  vfixedINCLUDED
#include vfixedHEADER
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vfsINCLUDED
#include vfsHEADER
#endif

#ifndef  vscrapINCLUDED
#include vscrapHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * CONSTANTS AND MACRO DEFINITIONS * * * * * * * * * *
 */

#define	vresourceMAX_FILES	127	/* max # of resource files open */

#define vresourceNULL		((vresource) 0L)	/* No resource	*/
#define vresourceTAG_NULL	((const vname *) 0L)	/* No tag 	*/

#define	vresourceUNTYPED	0	/* untyped placeholder 		*/
#define	vresourceDICT		1	/* set of tagged components 	*/
#define	vresourceARRAY		2	/* array of a particular type 	*/
#define	vresourceTAG		3	/* symbolic tag 		*/
#define	vresourceINTEGER	4	/* integer 			*/
#define	vresourceFIXED		5	/* fixed point quantity 	*/
#define	vresourceFLOAT		6	/* floating point quantity 	*/
#define	vresourceSTRING		7	/* character string 		*/
#define	vresourceCHAR		8	/* character 			*/
#define	vresourceBOOLEAN	9	/* boolean value 		*/
#define	vresourceOPAQUE		10	/* uninterpreted block of bytes */

/* Bit flags for resource manager options */

enum
{
  vresourceCREATE_ORIGINAL = 0x0,	/* Create version 1.x files	*/
  vresourceCREATE_CURRENT  = 0x1,	/* Create current files		*/
  _vresourceCREATE_MASK    = 0x1,	/* Mask for creation type	*/
  vresourceOPEN_LOCKED 	   = 0x0,      	/* Open files with DENY modes   */
  vresourceOPEN_SHARED     = 0x2,       /* Open files without DENY modes */
  _vresourceOPEN_MASK      = 0x2      	/* Mask for open mode           */
};

enum
{
  vresourceNO_FILE	= vFALSE,
  vresourceBTREE_FILE,
  vresourceCHUNK_FILE
};

/*
 * * * * * * * * * TYPE AND STRUCTURE DEFINITIONS * * * * * * * * * *
 */

typedef unsigned long 	 	 vresource;
typedef unsigned long 		 vresourceID;

/*
 * * * * * * * * * RESOURCE MANAGER FUNCTION PROTOTYPES * * * * * * * * * *
 */

void		vresourceStartup(void);


/*
 * Functions which control the Resource Manager:
 */

int		vresourceSetOptions(int options);
int	     	vresourceGetOptions(void);

/*
 * Functions to open resource files:
 */

vresource	vresourceOpenFile(const vfsPath *fileName, int typeAccess);
vresource	vresourceOpenInternal(const void *data);
vresource	vresourceOpenBuffer(const vbyte *data, size_t size);
int		vresourceTestFile(const vfsPath *fileName);

/*
 * Functions to create resource files:
 */

vresource	vresourceCreateFile(const vfsPath *fileName, vfsMode mode);
vresource	vresourceCreateMemFromFile(const vfsPath *pathname);
vresource	vresourceCreateFileFromMem(vresource res,
					   const vfsPath *pathname,
					   vfsMode mode);
vresource	vresourceCreateMem(void);

/*
 * Functions to copy resource files:
 */

void		vresourceCopyCompact(vresource fromRes, vresource toRes);
void 		vresourceCopy(vresource fromRes, vresource toRes);

/* 
 * Functions to close and destroy resource files:
 */

void		vresourceCloseFile(vresource res);
void		vresourceDestroyMem(vresource res);

/*
 * Miscellaneous file-related operations:
 */

void		vresourceFlush(vresource res);
void		vresourceWriteDefinition(vresource res, vfsFile *stream,
					 const vchar *prefix);
vfsFile		*vresourceGetFile(vresource res);
size_t		vresourceGetDataSize(vresource res);
void		vresourceGetData(vresource res, vbyte *buffer);
void		vresourceDump(vresource res, FILE *stream);

/*
 * Functions to create scalar resources:
 */

vresource	vresourceMake(vresource res, const vname *tag);
vresource	vresourceCreate(vresource res, const vname *tag, int type);

/*
 * Functions to create array resources:
 */

vresource	vresourceMakeArray(vresource res, const vname *tag, 
				   int componentType, size_t initialSize);
vresource	vresourceCreateArray(vresource res, const vname *tag,
				     int componentType, size_t initialSize);

/*
 * Function to create an array element:
 */

vresource	vresourceCreateAt(vresource res, size_t idx, int type);

/*
 * Functions to remove scalar resources and elements of array resources:
 */

void		vresourceRemove(vresource res, const vname *tag);
void		vresourceRemoveAt(vresource res, size_t idx);
void 		vresourceRemoveIfExists(vresource res, const vname *tag);

/*
 * Functions to retrieve resources:
 */

vresource	vresourceGet(vresource res, const vname *tag);
const vname	*vresourceGetTag(vresource res, const vname *tag);
int		vresourceGetInteger(vresource res, const vname *tag);
vfixed		vresourceGetFixed(vresource res, const vname *tag);
double		vresourceGetFloat(vresource res, const vname *tag);
vstr		*vresourceGetString(vresource res, const vname *tag);
vscribe		*vresourceScribeString(vresource res, const vname *tag);
void		vresourceGetStringBuf(vresource res, const vname *tag, 
				      size_t offset, vchar *buffer,
				      size_t maxLength, size_t *length);
vbool		vresourceGetBoolean(vresource res, const vname *tag);
vbyte		*vresourceGetOpaque(vresource res, const vname *tag,
				    size_t *length);
vchar		vresourceGetChar(vresource res, const vname *tag);
vscrap 		*vresourceGetScrap(vresource res, const vname *tag);

/*
 * Functions to conditionally retrieve resources:
 */

vbool		vresourceTestGet(vresource res, const vname *tag,
				 vresource *value);
vbool		vresourceTestGetTag(vresource res, const vname *tag,
				    const vname **value);
vbool		vresourceTestGetInteger(vresource res, const vname *tag,
					int *value);
vbool		vresourceTestGetFixed(vresource res, const vname *tag, 
				      vfixed *value);
vbool		vresourceTestGetFloat(vresource res, const vname *tag,
				      double *value);
vbool		vresourceTestGetString(vresource res, const vname *tag,
				       vstr **value);
vbool		vresourceTestScribeString(vresource res, const vname *tag,
					vscribe **value);
vbool		vresourceTestGetStringBuf(vresource res, const vname *tag,
					  size_t offset, vchar *buffer,
					  size_t maxLength, size_t *length);
vbool		vresourceTestGetBoolean(vresource res, const vname *tag,
					vbool *value);
vbool		vresourceTestGetOpaque(vresource res, const vname *tag,
				       vbyte **buffer, size_t *length);
vbool		vresourceTestGetChar(vresource res, const vname *tag,
				     vchar *value);
vbool		vresourceTestGetScrap(vresource res, const vname *tag,
				      vscrap **scrap);

/*
 * Functions to retrieve elements of array resources:
 */

vresource	vresourceGetAt(vresource res, size_t idx);
const		vname *vresourceGetTagAt(vresource res, size_t idx);
int		vresourceGetIntegerAt(vresource res, size_t idx);
vfixed		vresourceGetFixedAt(vresource res, size_t idx);
double		vresourceGetFloatAt(vresource res, size_t idx);
vstr		*vresourceGetStringAt(vresource res, size_t idx);
vscribe		*vresourceScribeStringAt(vresource res, size_t idx);
void		vresourceGetStringBufAt(vresource res, size_t idx,
					size_t offset, vchar *buffer,
					size_t maxLength, size_t *length);
vbool		vresourceGetBooleanAt(vresource res, size_t idx);
void		vresourceGetOpaqueAt(vresource res, size_t idx, size_t offset,
				     vbyte **buffer, size_t maxLength,
				     size_t *length);
vchar		vresourceGetCharAt(vresource res, size_t idx);
vscrap 		*vresourceGetScrapAt(vresource res, size_t idx);

/*
 * Functions to set scalar resources:
 */

void		vresourceSetTag(vresource res, const vname *tag,
				const vname *value);
void		vresourceSetInteger(vresource res, const vname *tag,
				    int value);
void		vresourceSetFixed(vresource res, const vname *tag,
				  vfixed value);
void		vresourceSetFloat(vresource res, const vname *tag,
				  double value);
void		vresourceSetString(vresource res, const vname *tag,
				   const vchar *value);
void		vresourceSetStringScribed(vresource res, const vname *tag,
					  vscribe *value);
void		vresourceSetStringBuf(vresource res, const vname *tag,
				      const vchar *buffer, size_t length);
void		vresourceSetBoolean(vresource res, const vname *tag,
				    int value);
void		vresourceSetOpaque(vresource res, const vname *tag,
				   const vbyte *value, size_t length);
void		vresourceSetChar(vresource res, const vname *tag, int value);
void		vresourceSetScrap(vresource res, const vname *tag, 
				  vscrap *scrap);

/*
 * Functions to set elements of array resources:
 */

void		vresourceSetTagAt(vresource res, size_t idx,
				  const vname *value);
void		vresourceSetIntegerAt(vresource res, size_t idx, int value);
void		vresourceSetFixedAt(vresource res, size_t idx, vfixed value);
void		vresourceSetFloatAt(vresource res, size_t idx, double value);
void		vresourceSetStringAt(vresource res, size_t idx,
				     const vchar *value);
void		vresourceSetStringAtScribed(vresource res, size_t idx,
					    vscribe *value);
void		vresourceSetStringBufAt(vresource res, size_t idx,
					const vchar *buffer, size_t length);
void		vresourceSetBooleanAt(vresource res, size_t idx, int value);
void		vresourceSetOpaqueAt(vresource res, size_t idx,
				     const vbyte *value, size_t length);
void		vresourceSetCharAt(vresource res, size_t idx, int value);
void 		vresourceSetScrapAt(vresource res, size_t idx, vscrap *value);


/*
 * Functions to insert a new element into an array resource:
 */

vresource	vresourceInsertAt(vresource res, size_t idx, int type);
void		vresourceInsertIntegerAt(vresource res, size_t idx, int value);
void		vresourceInsertFloatAt(vresource res, size_t idx,
				       double value);
void		vresourceInsertTagAt(vresource res, size_t idx,
				     const vname *value);
void		vresourceInsertFixedAt(vresource res, size_t idx,
				       vfixed value);
void 		vresourceInsertBooleanAt(vresource res, size_t idx, int value);
void 		vresourceInsertCharAt(vresource res, size_t idx, int value);

void		vresourceRelocateAt(vresource res, size_t fromIndex, 
				    size_t toIndex);

/*
 * Functions to locate resources:
 */

vresource	vresourceGetParent(vresource res);
void		vresourceFind(vresource res,
			      vresource *foundRes, const vname **foundTag);
void		vresourceFindArray(vresource res, vresource *foundRes,
				   const vname **foundTag, size_t *foundIdx);

/*
 * Operations on dictionary resources:
 */

const vname	*vresourceGetNthTag(vresource res, size_t idx);
size_t		vresourceCountComponents(vresource res);

/*
 * Convenience operations on resources and rectangles:
 */

void 		vresourceLoadInitRect(vrect *rect, vresource res);
void 		vresourceStoreRect(const vrect *rect, vresource res);
void 		vresourceLoadInitRectFloat(vrectFloat *rect, vresource res);
void 		vresourceStoreRectFloat(const vrectFloat *rect, vresource res);
vrect 		*vresourceLoadRects(vresource res, int *count);
void 		vresourceStoreRects(const vrect *rects, int count,
				    vresource res);
vrectLong	*vresourceLoadLongRects(vresource res, int *count);
void 		vresourceStoreLongRects(const vrectLong *rects, int count,
					vresource res);
/*
 * Operations on resources and path objects:
 */

void		vresourceStorePath(vfsPath *path, vresource res);
vfsPath		*vresourceLoadPath(vresource res);

/*
 * Miscellaneous operations on resources:
 */

int 		vresourceGetType(vresource res, const vname *tag);
void		vresourceRename(vresource res, const vname *oldtag,
				const vname *newtag);
vresource	vresourceGetRoot(vresource res);
size_t		vresourceGetSize(vresource res);
size_t		vresourceGetLength(vresource res);

/*
 * Miscellaneous operations on arrays:
 */

int 		vresourceGetArrayType(vresource res);
void		vresourceSetArraySize(vresource res, size_t newSize);

/*
 * Operations on resource IDs:
 */

vresourceID	vresourceGetID(vresource res);
vresource	vresourceGetByID(vresource resfile, vresourceID id);

/*
 * Resource scraps:
 */

vresource vresourceGetScrapResource(vscrap *scrap);

vresource vresourceGetArrayScrapResource(vscrap *scrap);
size_t vresourceGetArrayScrapIndex(vscrap *scrap);

/*
 * Deprecated entry points:
 * (don't use these)
 */

int		vresourceType(vresource res); 
int		vresourceArrayType(vresource res);	
vresource	vresourceGetNthComponent(vresource res, size_t n,
					 const vname **tag);
void		vresourceGetArray(vresource res, const vname *tag,
				  void **value, size_t *length);
vbool		vresourceTestGetArray(vresource res, const vname *tag,
				      void **value, size_t *length);

/*
 * * * * * * * * * P_R_I_V_A_T_E FUNCTION PROTOTYPES * * * * * * * * * *
 */

int _vresourceGetIsNewFromResource(vresource resource);
int _vresourceGetIsNewFromOptions(void);
int _vresourceGetIsNewFromFile(const vfsPath *path);
int _vresourceGetIsNewFromMemory(const vbyte *memory);
int _vresourceGetIsNewFromScrap(vscrap *scrap);
int _vresourceGetIsNewFromInternal(const void *data);

/*
 * * * * * * * * * * * Compatibility Magic * * * * * * * * * * * * 
 */

#ifndef vresourceUSE_OLD_RESOURCE_MANAGER
#define vresourceUSE_OLD_RESOURCE_MANAGER	0
#endif

#ifndef vresourceUSE_NEW_RESOURCE_MANAGER
#define vresourceUSE_NEW_RESOURCE_MANAGER	1
#endif

#if (vresourceUSE_OLD_RESOURCE_MANAGER && vresourceUSE_NEW_RESOURCE_MANAGER)

struct _vresourceFuncsBlock
{
  vresource	(*openFile)(const vfsPath *fileName, int typeAccess);
  vresource	(*openInternal)(const void *data);
  
  vresource	(*createFile)(const vfsPath *fileName, vfsMode mode);
  vresource 	(*createMem)(void);
  vresource	(*createMemFromFile)(const vfsPath *pathname);
  vresource	(*createFileFromMem)(vresource res, const vfsPath *pathname, 
				     vfsMode mode);

  void		(*copyCompact)(vresource from, vresource to);

  void		(*closeFile)(vresource res);
  void		(*destroyMem)(vresource res);

  void 		(*flush)(vresource res);
  void		(*writeDefinition)(vresource res, vfsFile *stream, 
				   const vchar *prefix);
  vfsFile	*(*getFile)(vresource res);
  void		(*dump)(vresource res, FILE *stream);

  vresource	(*make)(vresource res, const vname *tag);
  vresource	(*createRes)(vresource res, const vname *tag, int type);
  
  vresource 	(*makeArray)(vresource res, const vname *tag,
			     int componentType, size_t initialSize);
  vresource 	(*createArray)(vresource res, const vname *tag,
			       int componentType, size_t initialSize);

  vresource	(*createAt)(vresource res, size_t idx, int type);
  
  void		(*remove)(vresource res, const vname *tag);
  void		(*removeAt)(vresource res, size_t idx);

  vresource	(*get)(vresource res, const vname *tag);
  const vname	*(*getTag)(vresource res, const vname *tag);
  int		(*getInteger)(vresource res, const vname *tag);
  vfixed	(*getFixed)(vresource res, const vname *tag);
  double	(*getFloat)(vresource res, const vname *tag);
  vscribe	*(*scribeString)(vresource res, const vname *tag);
  void		(*getStringBuf)(vresource res, const vname *tag, 
				size_t offset, vchar *buffer,
				size_t maxLength, size_t *length);
  vbool		(*getBoolean)(vresource res, const vname *tag);
  vbyte		*(*getOpaque)(vresource res, const vname *tag,
			      size_t *length);
  vchar		(*getChar)(vresource res, const vname *tag);
  void		(*getArray)(vresource res, const vname *tag,
			    void **value, size_t *length);
  vscrap 	*(*getScrap)(vresource res, const vname *tag);
  
  vbool		(*testGet)(vresource res, const vname *tag,
			   vresource *value);
  vbool		(*testGetTag)(vresource res, const vname *tag,
			      const vname **value);
  vbool		(*testGetInteger)(vresource res, const vname *tag,
				  int *value);
  vbool		(*testGetFixed)(vresource res, const vname *tag, 
				vfixed *value);
  vbool		(*testGetFloat)(vresource res, const vname *tag,
				double *value);
  vbool		(*testGetString)(vresource res, const vname *tag,
				 vstr **value);
  vbool		(*testScribeString)(vresource res, const vname *tag,
				    vscribe **value);
  vbool		(*testGetStringBuf)(vresource res, const vname *tag,
				    size_t offset, vchar *buffer,
				    size_t maxLength, size_t *length);
  vbool		(*testGetBoolean)(vresource res, const vname *tag,
				  vbool *value);
  vbool		(*testGetOpaque)(vresource res, const vname *tag,
				 vbyte **buffer, size_t *length);
  vbool		(*testGetChar)(vresource res, const vname *tag,
			       vchar *value);
  vbool		(*testGetArray)(vresource res, const vname *tag,
				void **value, size_t *length);
  vbool		(*testGetScrap)(vresource res, const vname *tag,
				vscrap **scrap);
  
  vresource	(*getAt)(vresource res, size_t idx);
  const	vname 	*(*getTagAt)(vresource res, size_t idx);
  int		(*getIntegerAt)(vresource res, size_t idx);
  vfixed	(*getFixedAt)(vresource res, size_t idx);
  double	(*getFloatAt)(vresource res, size_t idx);
  vscribe	*(*scribeStringAt)(vresource res, size_t idx);
  void		(*getStringBufAt)(vresource res, size_t idx,
				  size_t offset, vchar *buffer,
				  size_t maxLength, size_t *length);
  vbool		(*getBooleanAt)(vresource res, size_t idx);
  void		(*getOpaqueAt)(vresource res, size_t idx, size_t offset,
			       vbyte **buffer, size_t maxLength,
			       size_t *length);
  vchar		(*getCharAt)(vresource res, size_t idx);
  vscrap 	*(*getScrapAt)(vresource res, size_t idx);
  
  void		(*setTag)(vresource res, const vname *tag,
			  const vname *value);
  void		(*setInteger)(vresource res, const vname *tag,
			      int value);
  void		(*setFixed)(vresource res, const vname *tag,
			    vfixed value);
  void		(*setFloat)(vresource res, const vname *tag,
			    double value);
  void		(*setStringScribed)(vresource res, const vname *tag,
				    vscribe *value);
  void		(*setStringBuf)(vresource res, const vname *tag,
				const vchar *buffer, size_t length);
  void		(*setBoolean)(vresource res, const vname *tag,
			      int value);
  void		(*setOpaque)(vresource res, const vname *tag,
			     const vbyte *value, size_t length);
  void		(*setChar)(vresource res, const vname *tag, int value);
  void		(*setScrap)(vresource res, const vname *tag, 
			    vscrap *scrap);
  
  void		(*setTagAt)(vresource res, size_t idx,
			    const vname *value);
  void		(*setIntegerAt)(vresource res, size_t idx, int value);
  void		(*setFixedAt)(vresource res, size_t idx, vfixed value);
  void		(*setFloatAt)(vresource res, size_t idx, double value);
  void		(*setStringAtScribed)(vresource res, size_t idx,
				      vscribe *value);
  void		(*setStringBufAt)(vresource res, size_t idx,
				  const vchar *buffer, size_t length);
  void		(*setBooleanAt)(vresource res, size_t idx, int value);
  void		(*setOpaqueAt)(vresource res, size_t idx,
			       const vbyte *value, size_t length);
  void		(*setCharAt)(vresource res, size_t idx, int value);
  void 		(*setScrapAt)(vresource res, size_t idx, vscrap *value);
  
  
  vresource	(*insertAt)(vresource res, size_t idx, int type);
  void		(*insertTagAt)(vresource res, size_t idx,
			       const vname *value);
  void		(*insertIntegerAt)(vresource res, size_t idx, int value);
  void		(*insertFixedAt)(vresource res, size_t idx,
				 vfixed value);
  void		(*insertFloatAt)(vresource res, size_t idx,
				 double value);
  void 		(*insertBooleanAt)(vresource res, size_t idx, int value);
  void 		(*insertCharAt)(vresource res, size_t idx, int value);
  
  void		(*find)(vresource res,
			vresource *foundRes, const vname **foundTag);
  void		(*findArray)(vresource res, vresource *foundRes,
			     const vname **foundTag, size_t *foundIdx);
  
  size_t	(*countComponents)(vresource res);
  vresource	(*getNthComponent)(vresource res, size_t n,
				   const vname **tag);
  const vname  *(*getNthTag)(vresource res, size_t n); 
  
  void		(*rename)(vresource res, const vname *oldtag,
			  const vname *newtag);

  vresource	(*getParent)(vresource res);
  vresource	(*getRoot)(vresource res);
  size_t	(*getSize)(vresource res);
  size_t	(*getLength)(vresource res);
  
  int		(*getType)(vresource res, const vname *tag); 
  int		(*getArrayType)(vresource res);	
  void		(*setArraySize)(vresource res, size_t newSize);
  
  vresourceID	(*getID)(vresource res);
  vresource	(*getByID)(vresource resfile, vresourceID id);

  vresource 	(*getScrapResource)(vscrap *scrap);

  vresource 	(*getArrayScrapResource)(vscrap *scrap);
  size_t 	(*getArrayScrapIndex)(vscrap *scrap);

};
  
extern vportLINK const struct _vresourceFuncsBlock _vresourceFuncs[];

#define _vresourceGetIsNewFromResource(r) \
    (((r)&0x80000000u)!=0)

#define _vresourceGetFuncsFromID(r) \
    _vresourceFuncs[_vresourceGetIsNewFromResource(r)]
#define _vresourceGetFuncsFromOptions() \
    _vresourceFuncs[_vresourceGetIsNewFromOptions()]
#define _vresourceGetFuncsFromFile(p) \
    _vresourceFuncs[_vresourceGetIsNewFromFile(p)]
#define _vresourceGetFuncsFromMemory(m) \
    _vresourceFuncs[_vresourceGetIsNewFromMemory(m)]
#define _vresourceGetFuncsFromScrap(s) \
    _vresourceFuncs[_vresourceGetIsNewFromScrap(s)]
#define _vresourceGetFuncsFromInternal(d) \
    _vresourceFuncs[_vresourceGetIsNewFromInternal(d)]

#define vresourceOpenFile(f,a) \
    (*_vresourceGetFuncsFromFile(f).openFile)(f, a)

#define vresourceOpenInternal(d) \
    (*_vresourceGetFuncsFromInternal(d).openInternal)(d)

#define vresourceCreateFile(f, m) \
    (*_vresourceGetFuncsFromOptions().createFile)(f, m)
#define vresourceCreateMem() \
    (*_vresourceGetFuncsFromOptions().createMem)()
#define vresourceCreateMemFromFile(f) \
    (*_vresourceGetFuncsFromFile(f).createMemFromFile)(f)
#define vresourceCreateFileFromMem(r,p,m) \
    (*_vresourceGetFuncsFromID(r).createFileFromMem)(r,p,m)

#define vresourceCopyCompact(f, t) \
    (*_vresourceFuncs[_vresourceGetIsNewFromResource(f) \
		      ||_vresourceGetIsNewFromResource(t)].copyCompact)(f, t)

#define vresourceCloseFile(r) \
    (*_vresourceGetFuncsFromID(r).closeFile)(r)
#define vresourceDestroyMem(r) \
    (*_vresourceGetFuncsFromID(r).destroyMem)(r)

#define vresourceFlush(r) \
    (*_vresourceGetFuncsFromID(r).flush)(r)
#define vresourceWriteDefinition(r,s,p) \
    (*_vresourceGetFuncsFromID(r).writeDefinition)(r,s,p)
#define vresourceGetFile(r) \
    (*_vresourceGetFuncsFromID(r).getFile)(r)
#define vresourceDump(r,s) \
    (*_vresourceGetFuncsFromID(r).dump)(r,s)

#define vresourceMake(r,t) \
    (*_vresourceGetFuncsFromID(r).make)(r,t)
#define vresourceCreate(r,t,tp) \
    (*_vresourceGetFuncsFromID(r).createRes)(r,t,tp)

#define vresourceMakeArray(r,t,tp,n) \
    (*_vresourceGetFuncsFromID(r).makeArray)(r,t,tp,n)
#define vresourceCreateArray(r,t,tp,n) \
    (*_vresourceGetFuncsFromID(r).createArray)(r,t,tp,n)

#define vresourceCreateAt(r,n,tp) \
    (*_vresourceGetFuncsFromID(r).createAt)(r,n,tp)

#define vresourceRemove(r,t) \
    (*_vresourceGetFuncsFromID(r).remove)(r,t)
#define vresourceRemoveAt(r,i) \
    (*_vresourceGetFuncsFromID(r).removeAt)(r,i)

#define vresourceGet(r,t) \
    (*_vresourceGetFuncsFromID(r).get)(r,t)
#define vresourceGetTag(r,t) \
    (*_vresourceGetFuncsFromID(r).getTag)(r,t)
#define vresourceGetInteger(r,t) \
    (*_vresourceGetFuncsFromID(r).getInteger)(r,t)
#define vresourceGetFixed(r,t) \
    (*_vresourceGetFuncsFromID(r).getFixed)(r,t)
#define vresourceGetFloat(r,t) \
    (*_vresourceGetFuncsFromID(r).getFloat)(r,t)
#define vresourceScribeString(r,t) \
    (*_vresourceGetFuncsFromID(r).scribeString)(r,t)
#define vresourceGetStringBuf(r,t,o,b,m,l) \
    (*_vresourceGetFuncsFromID(r).getStringBuf)(r,t,o,b,m,l)
#define vresourceGetBoolean(r,t) \
    (*_vresourceGetFuncsFromID(r).getBoolean)(r,t)
#define vresourceGetOpaque(r,t,l) \
    (*_vresourceGetFuncsFromID(r).getOpaque)(r,t,l)
#define vresourceGetChar(r,t) \
    (*_vresourceGetFuncsFromID(r).getChar)(r,t)
#define vresourceGetArray(r,t,v,l) \
    (*_vresourceGetFuncsFromID(r).getArray)(r,t,v,l)
#define vresourceGetScrap(r,t) \
    (*_vresourceGetFuncsFromID(r).getScrap)(r,t)

#define vresourceTestGet(r,t,v) \
    (*_vresourceGetFuncsFromID(r).testGet)(r,t,v)
#define vresourceTestGetTag(r,t,v) \
    (*_vresourceGetFuncsFromID(r).testGetTag)(r,t,v)
#define vresourceTestGetInteger(r,t,v) \
    (*_vresourceGetFuncsFromID(r).testGetInteger)(r,t,v)
#define vresourceTestGetFixed(r,t,v) \
    (*_vresourceGetFuncsFromID(r).testGetFixed)(r,t,v)
#define vresourceTestGetFloat(r,t,v) \
    (*_vresourceGetFuncsFromID(r).testGetFloat)(r,t,v)
#define vresourceTestGetString(r,t,v) \
    (*_vresourceGetFuncsFromID(r).testGetString)(r,t,v)
#define vresourceTestScribeString(r,t,v) \
    (*_vresourceGetFuncsFromID(r).testScribeString)(r,t,v)
#define vresourceTestGetStringBuf(r,t,o,b,m,l) \
    (*_vresourceGetFuncsFromID(r).testGetStringBuf)(r,t,o,b,m,l)
#define vresourceTestGetBoolean(r,t,v) \
    (*_vresourceGetFuncsFromID(r).testGetBoolean)(r,t,v)
#define vresourceTestGetOpaque(r,t,v,l) \
    (*_vresourceGetFuncsFromID(r).testGetOpaque)(r,t,v,l)
#define vresourceTestGetChar(r,t,v) \
    (*_vresourceGetFuncsFromID(r).testGetChar)(r,t,v)
#define vresourceTestGetArray(r,t,v,l) \
    (*_vresourceGetFuncsFromID(r).testGetArray)(r,t,v,l)
#define vresourceTestGetScrap(r,t,v) \
    (*_vresourceGetFuncsFromID(r).testGetScrap)(r,t,v)

#define vresourceGetAt(r,i) \
    (*_vresourceGetFuncsFromID(r).getAt)(r,i)
#define vresourceGetTagAt(r,i) \
    (*_vresourceGetFuncsFromID(r).getTagAt)(r,i)
#define vresourceGetIntegerAt(r,i) \
    (*_vresourceGetFuncsFromID(r).getIntegerAt)(r,i)
#define vresourceGetFixedAt(r,i) \
    (*_vresourceGetFuncsFromID(r).getFixedAt)(r,i)
#define vresourceGetFloatAt(r,i) \
    (*_vresourceGetFuncsFromID(r).getFloatAt)(r,i)
#define vresourceScribeStringAt(r,i) \
    (*_vresourceGetFuncsFromID(r).scribeStringAt)(r,i)
#define vresourceGetStringBufAt(r,i,o,b,m,l) \
    (*_vresourceGetFuncsFromID(r).getStringBufAt)(r,i,o,b,m,l)
#define vresourceGetBooleanAt(r,i) \
    (*_vresourceGetFuncsFromID(r).getBooleanAt)(r,i)
#define vresourceGetOpaqueAt(r,i,o,b,m,l) \
    (*_vresourceGetFuncsFromID(r).getOpaqueAt)(r,i,o,b,m,l)
#define vresourceGetCharAt(r,i) \
    (*_vresourceGetFuncsFromID(r).getCharAt)(r,i)
#define vresourceGetScrapAt(r,i) \
    (*_vresourceGetFuncsFromID(r).getScrapAt)(r,i)

#define vresourceSetTag(r,t,v) \
    (*_vresourceGetFuncsFromID(r).setTag)(r,t,v)
#define vresourceSetInteger(r,t,v) \
    (*_vresourceGetFuncsFromID(r).setInteger)(r,t,v)
#define vresourceSetFixed(r,t,v) \
    (*_vresourceGetFuncsFromID(r).setFixed)(r,t,v)
#define vresourceSetFloat(r,t,v) \
    (*_vresourceGetFuncsFromID(r).setFloat)(r,t,v)
#define vresourceSetStringScribed(r,t,v) \
    (*_vresourceGetFuncsFromID(r).setStringScribed)(r,t,v)
#define vresourceSetStringBuf(r,t,b,l) \
    (*_vresourceGetFuncsFromID(r).setStringBuf)(r,t,b,l)
#define vresourceSetBoolean(r,t,v) \
    (*_vresourceGetFuncsFromID(r).setBoolean)(r,t,v)
#define vresourceSetOpaque(r,t,v,l) \
    (*_vresourceGetFuncsFromID(r).setOpaque)(r,t,v,l)
#define vresourceSetChar(r,t,v) \
    (*_vresourceGetFuncsFromID(r).setChar)(r,t,v)
#define vresourceSetScrap(r,t,v) \
    (*_vresourceGetFuncsFromID(r).setScrap)(r,t,v)

#define vresourceSetTagAt(r,i,v) \
    (*_vresourceGetFuncsFromID(r).setTagAt)(r,i,v)
#define vresourceSetIntegerAt(r,i,v) \
    (*_vresourceGetFuncsFromID(r).setIntegerAt)(r,i,v)
#define vresourceSetFixedAt(r,i,v) \
    (*_vresourceGetFuncsFromID(r).setFixedAt)(r,i,v)
#define vresourceSetFloatAt(r,i,v) \
    (*_vresourceGetFuncsFromID(r).setFloatAt)(r,i,v)
#define vresourceSetStringAtScribed(r,i,v) \
    (*_vresourceGetFuncsFromID(r).setStringAtScribed)(r,i,v)
#define vresourceSetStringBufAt(r,i,b,l) \
    (*_vresourceGetFuncsFromID(r).setStringBufAt)(r,i,b,l)
#define vresourceSetBooleanAt(r,i,v) \
    (*_vresourceGetFuncsFromID(r).setBooleanAt)(r,i,v)
#define vresourceSetOpaqueAt(r,i,v,l) \
    (*_vresourceGetFuncsFromID(r).setOpaqueAt)(r,i,v,l)
#define vresourceSetCharAt(r,i,v) \
    (*_vresourceGetFuncsFromID(r).setCharAt)(r,i,v)
#define vresourceSetScrapAt(r,i,v) \
    (*_vresourceGetFuncsFromID(r).setScrapAt)(r,i,v)

#define vresourceInsertAt(r,i,v) \
    (*_vresourceGetFuncsFromID(r).insertAt)(r,i,v)
#define vresourceInsertTagAt(r,i,v) \
    (*_vresourceGetFuncsFromID(r).insertTagAt)(r,i,v)
#define vresourceInsertIntegerAt(r,i,v) \
    (*_vresourceGetFuncsFromID(r).insertIntegerAt)(r,i,v)
#define vresourceInsertFixedAt(r,i,v) \
    (*_vresourceGetFuncsFromID(r).insertFixedAt)(r,i,v)
#define vresourceInsertFloatAt(r,i,v) \
    (*_vresourceGetFuncsFromID(r).insertFloatAt)(r,i,v)
#define vresourceInsertBooleanAt(r,i,v) \
    (*_vresourceGetFuncsFromID(r).insertBooleanAt)(r,i,v)
#define vresourceInsertCharAt(r,i,v) \
    (*_vresourceGetFuncsFromID(r).insertCharAt)(r,i,v)

#define vresourceFind(r,fr,ft) \
    (*_vresourceGetFuncsFromID(r).find)(r,fr,ft)
#define vresourceFindArray(r,fr,ft,fi) \
    (*_vresourceGetFuncsFromID(r).findArray)(r,fr,ft,fi)

#define vresourceCountComponents(r) \
    (*_vresourceGetFuncsFromID(r).countComponents)(r)
#define vresourceGetNthComponent(r,n,t) \
    (*_vresourceGetFuncsFromID(r).getNthComponent)(r,n,t)
#define vresourceGetNthTag(r,n) \
    (*_vresourceGetFuncsFromID(r).getNthTag)(r,n)

#define vresourceRename(r,ot,nt) \
    (*_vresourceGetFuncsFromID(r).rename)(r,ot,nt)

#define vresourceGetParent(r) \
    (*_vresourceGetFuncsFromID(r).getParent)(r)
#define vresourceGetRoot(r) \
    (*_vresourceGetFuncsFromID(r).getRoot)(r)
#define vresourceGetSize(r) \
    (*_vresourceGetFuncsFromID(r).getSize)(r)
#define vresourceGetLength(r) \
    (*_vresourceGetFuncsFromID(r).getLength)(r)

#define vresourceGetType(r, t) \
    (*_vresourceGetFuncsFromID(r).getType)(r, t)
#define vresourceGetArrayType(r) \
    (*_vresourceGetFuncsFromID(r).getArrayType)(r)
#define vresourceSetArraySize(r,n) \
    (*_vresourceGetFuncsFromID(r).setArraySize)(r,n)

#define	vresourceGetID(r) \
    (*_vresourceGetFuncsFromID(r).getID)(r)
#define	vresourceGetByID(r,i) \
    (*_vresourceGetFuncsFromID(r).getByID)(r,i)

#define vresourceGetScrapResource(s) \
    (*_vresourceGetFuncsFromScrap(s).getScrapResource)(s)

#define vresourceGetArrayScrapResource(s) \
    (*_vresourceGetFuncsFromScrap(s).getArrayScrapResource)(s)
#define vresourceGetArrayScrapIndex(s) \
    (*_vresourceGetFuncsFromScrap(s).getArrayScrapIndex)(s)

#else

#define _vresourceGetIsNewFromResource(r)  vresourceUSE_NEW_RESOURCE_MANAGER
#define _vresourceGetIsNewFromOptions()	   vresourceUSE_NEW_RESOURCE_MANAGER
#define _vresourceGetIsNewFromFile(p)	   vresourceUSE_NEW_RESOURCE_MANAGER
#define _vresourceGetIsNewFromMemory(m)	   vresourceUSE_NEW_RESOURCE_MANAGER
#define _vresourceGetIsNewFromScrap(s)	   vresourceUSE_NEW_RESOURCE_MANAGER
#define _vresourceGetIsNewFromInternal(d)  vresourceUSE_NEW_RESOURCE_MANAGER

#endif


#if vportLIFETIME

enum
{
  _vresourceLIFETIME_OPEN,
  _vresourceLIFETIME_CLOSE
};

typedef void (*_vresourceLifetimeProc)(vresource res, int message);

_vresourceLifetimeProc _vresourceGetLifetimeProc();
void _vresourceSetLifetimeProc(_vresourceLifetimeProc lifetimeProc);

extern vportLINK _vresourceLifetimeProc _vresourceCurrentLifetimeProc;

#endif


/*
 * * * * * * * * * FUNCTIONS IMPLEMENTED AS MACROS * * * * * * * *
 */

#define vresourceGetString(res,tag) \
    vstrCloneScribed(vresourceScribeString((res),(tag)))
#define vresourceGetStringAt(res,index) \
    vstrCloneScribed(vresourceScribeStringAt((res),(index)))

#define vresourceSetString(res,tag,value) \
    vresourceSetStringScribed((res),(tag),vcharScribe(value))
#define vresourceSetStringAt(res,index,value) \
    vresourceSetStringAtScribed((res),(index),vcharScribe(value))

#define vresourceType(res) \
    vresourceGetType(res, NULL)
#define vresourceArrayType(res) \
    vresourceGetArrayType(res)


vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vresourceINCLUDED */
