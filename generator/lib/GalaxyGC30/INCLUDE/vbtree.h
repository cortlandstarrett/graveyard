/* $Id: vbtree.h,v 1.25 1996/04/19 20:05:35 chris Exp $ */

/************************************************************

    vresource.h
    C Interface to the B-Tree Manager

    (c) Copyright Visix Software  1992
    All rights reserved

************************************************************/

#ifndef vbtreeINCLUDED
#define vbtreeINCLUDED 1

/* Galaxy headers */

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vsystypesINCLUDED
#include vsystypesHEADER
#endif

#ifndef  vstdioINCLUDED
#include vstdioHEADER
#endif

#ifndef  vstdINCLUDED
#include vstdHEADER
#endif

#ifndef  vexINCLUDED
#include vexHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vfsINCLUDED
#include vfsHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * CONSTANTS AND MACRO DEFINITIONS * * * * * * * * * *
 */

#define VBTREE_STANDALONE 	0	/* 1 for standalone (non-vfs) code */

/*
 * * * * * * P_R_I_V_A_T_E CONSTANTS AND MACRO DEFINITIONS * * * * * *
 */

/* action codes for vbtreeScan() call */

enum {
    _vbtreeMARK		= 1,
    _vbtreeFIRST	= 2,
    _vbtreeLAST		= 3,
    _vbtreeNEXT		= 4,
    _vbtreePREV		= 5
};

/*
 * * * * * * * * * TYPE AND STRUCTURE DEFINITIONS * * * * * * * * * *
 */

typedef unsigned long 	 vbtree;		/* Visible form of a B-Tree */
typedef vexException	 vbtreeException;
typedef vbtreeException	 vbtreeNotClosedException;

/*
 * * * * * * * P_R_I_V_A_T_E TYPE AND STRUCTURE DEFINITIONS * * * * * *
 */

typedef struct {			/* Variable length piece of data */
    vbyte	*data;
    size_t	size;
} _vbtreeChunk;

/*
 * * * * * * * * * RESOURCE MANAGER FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * Functions to open, close and create B-Trees:
 */

vbtree		vbtreeCreate(size_t pageSize);

#if VBTREE_STANDALONE
vbtree		vbtreeCreateFile(const char *fileName, int mode,
				 size_t pageSize, vbyte *magic);
#else
vbtree		vbtreeCreateFile(const vfsPath *fileName, vfsMode mode,
				 size_t pageSize, vbyte *magic);

#endif

#if VBTREE_STANDALONE
vbtree		vbtreeOpenFile(const char *fileName, int typeAccess,
			       vbyte *magic);
#else
vbtree		vbtreeOpenFile(const vfsPath *fileName, int typeAccess,
			       vbyte *magic);
#endif

vbtree		vbtreeCreateMemFromFile(const vfsPath *fileName,
					vbyte *magic);
vbtree		vbtreeCreateFileFromMem(vbtree tree, const vfsPath *fileName,
					vfsMode mode, vbyte *magic);

vbtree		vbtreeOpenInternal(const void *data);
void		vbtreeClose(vbtree tree);

/*
 * Functions to copy B-Trees:
 */

void		vbtreeCopyCompact(vbtree fromTree, vbtree toTree);

/*
 * Functions to insert and retrieve records via key:
 */

void		vbtreePut(vbtree tree, vbyte *key, size_t keyLength,
			  vbyte *data, size_t dataLength);
vbool		vbtreeGet(vbtree tree, vbyte *key, size_t keyLength,
			  vbyte **data, size_t *dataLength);
/* 
 * Function to delete records:
 */

vbool		vbtreeRemove(vbtree tree, vbyte *key, size_t keyLength);

/*
 * Miscellaneous operations on B-Trees:
 */

void		vbtreeFlush (vbtree tree);
vbool		vbtreeIsWritable(vbtree tree);
void		vbtreeWriteDefinition(vbtree tree, vfsFile *stream,
				      const vchar *name);
vfsFile		*vbtreeGetFile(vbtree tree);

/*
 * Debugging functions:
 */

void vbtreeDump(vbtree tree, FILE *stream);

/*
 * Exceptions:
 */

vbtreeException 		*vbtreeGetException(void);
vbtreeNotClosedException	*vbtreeGetNotClosedException(void);

const vexClass			*vbtreeGetExceptionClass(void);
const vexClass			*vbtreeGetNotClosedExceptionClass(void);

/*
 * Deprecated functions: 
 */

vbtree		vbtreeCreateMem(void);

/*
 * Private:
 */

#define vbtreeGetException() \
((vbtreeException *) vexGetExceptionOfClass(vbtreeGetExceptionClass()))

#define vbtreeGetNotClosedException() \
((vbtreeNotClosedException *) \
 vexGetExceptionOfClass(vbtreeGetNotClosedExceptionClass()))

/*
 * * * * * * * * * P_R_I_V_A_T_E FUNCTION PROTOTYPES * * * * * * * * * *
 */

vbool		_vbtreeScan(vbtree tree, _vbtreeChunk *key,
			    _vbtreeChunk *data, unsigned long flags);

/*
 * * * * * * * * * FUNCTIONS IMPLEMENTED AS MACROS * * * * * * * *
 */

#define	vbtreeCreate(pageSize) \
  	       		(vbtreeOpenFile(NULL, vfsOPEN_READ_WRITE, NULL))
#define	vbtreeCreateMem() \
  			(vbtreeOpenFile(NULL, vfsOPEN_READ_WRITE, NULL))

vportEND_CPLUSPLUS_EXTERN_C

#endif	/* vbtreeINCLUDED */

