/* $Id: glistacc.h,v 1.7 1996/09/12 18:09:23 alexey Exp $ */
/* The legal types make me put this in here.
 *
 * The following Sample Code is provided for your reference purposes in
 * connection with your use of the Galaxy Application Environment (TM) software
 * product which you have licensed from Visix Software, Inc. ("Visix").
 * The Sample code is provided to you without any warranty of any kind
 * whatsoever and you agree to be responsible for the use and/or incorporation
 * of the Sample Code into any software product you develop. You agree to fully
 * and completely indemnify and hold Visix harmless from any and all loss,
 * claim, liability or damages with respect to your use of the Sample Code.  
 *
 * Subject to the foregoing, you are permitted to copy, modify, and distribute
 * the Sample Code for any purpose and without fee, provided that (i) a
 * copyright notice in the form of "Copyright 1994 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 *
 * Do not taunt Happy Fun Ball
 */

/* glistacc.h -- Interface to a gaccessor subclass that accesses vlists
 *
 * Module:
 *	glistacc
 *
 * Description:
 *	See file chart.c for more comments about this whole project.
 *
 *	This module provides a subclass of the gaccessor abstract superclass
 *	which provides data accessing of info in a vlist.
 *
 * Exported Functions:
 *
 *	glistaccSetList -- associate a vlist to the accessor
 *	glistaccGetList -- the the vlist associated with this accessor
 *
 *	glistaccSetOrientation -- set the orientation of the accessing
 *			          patterns.  i.e. glistaccCOLUMN_MAJOR assumes
 *				  that the number of rows is the number
 *				  index values / that the index is in one
 *				  column and the data in other columns.
 *				  that columns are the dividing axis.
 *				  glistaccCOLUMN_MAJOR is the default.
 *	glistaccGetOrientation -- returns the orientation of list access.
 *
 *	glistaccSetVectorIndices -- set the set of columns/rows of the vlist
 *				    that will provide the data.
 *	glistaccGetVectorIndex -- return the vlist column/row that serves
 *				  a particular vector position.
 *
 *	glistaccSetNameIndex -- set the index of the column/row that contains
 *				names for values
 *	glistaccGetNameIndex -- returns the index of the column/row that
 *				contains the value names
 *
 *	glistaccSetIndexNameIndex -- set the index of the column/row that
 *				     contins names for the index.  e.g.
 *				     the index is dates and the values
 *				     are levels of spam contamination on
 *				     those dates.  The index name will be
 *				     a vchar representation of the date,
 *				     and the name will be something else.
 *	glitaccGetIndexNameIndex -- returns the index for the column/row
 *				    that serves as the index name index
 *
 *	glistaccSetIndexIndex -- set the index of the column/row of the vlist
 *				 that contains the index value.
 *	glistaccGetIndexIndex -- get the index of the column/row of the vlist
 *				 that contains the index value.
 *
 * How to use:
 *	* create it 
 *	  listacc = glistaccCreate ();
 *
 *	* associate a vlist to it. (the list should already be populated):
 *	  glistaccSetList (listacc, myList);
 *
 *	* set the vector count (if more than one)
 *	  glistaccSetVectorCount (listacc, 3);
 *
 *	* set the indices (rows/columns) that make up the vector:
 *	  int vectorPositions[3];
 *	  vectorPosition[0] = 12;  vector pos 0 is column 12 of the list
 *	  vectorPosition[1] = 42;  vector pos 1 is column 42 of the list
 *	  vectorPosition[2] = 0;   vector pos 2 is column 0 of the list
 *	  glistaccSetVectorIndices (listacc, vectorPositions);
 *	  Note that you must set the vector count before setting the indices
 *
 *	* if you have only one axis of data (i.e. a vector length of 1), you
 *	  still need to use glistaccSetVectorIndices:
 *	  int scratch = 5; use column 5 for the values
 *	  glistaccSetVectorIndices (listacc, &scratch);
 *	  This is unfortunate.  a convenience entry point should be provided.
 *
 *	* indicate which row/column contains the data point names (if any)
 *	  glistaccSetNameIndex (listacc, 5); column 5 has data point names
 *
 *	* indicate which row/column contains the names of the indices (if any)
 *	  glistaccSetIndexNameIndex (listacc, 7);
 *
 *	* use the regular gaccessor calls to access stuff. use
 *	  glistaccGetAccessor to get the accessor.
 *	  there are also convenience macros that gives glistacc prefixes
 *	  to gaccessor entry points.
 *
 * Defaults:
 *	orientation      : glistaccCOLUMN_MAJOR
 *	name index       : gaccessorUNDEFINED
 *	index name index : gaccessorUNDEFINED
 *	index index      : gaccessorUNDEFINED
 */


#ifndef glistaccINCLUDED
#define glistaccINCLUDED 1

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vdateINCLUDED
#include vdateHEADER
#endif

#ifndef  vlistINCLUDED
#include vlistHEADER
#endif

#ifndef  gaccessINCLUDED
#include "gaccess.h"
#endif



/*
 * ---------- Constant and macro definitions ----------
 */


enum {
    glistaccROW_MAJOR          = 0x0001,
    glistaccCOLUMN_MAJOR       = 0x0002,
    _glistaccORIENTATION_BITS  = glistaccROW_MAJOR | glistaccCOLUMN_MAJOR
};




/*
 * ---------- Type and structure definitions ----------
 */


typedef struct glistacc glistacc;

struct glistacc {
#if (vportBAD_CC_SCOPING)
    gaccessor         accessr;
#else
    gaccessor         accessor;
#endif
    vlist            *list;
    vlistObserver    *observer;
    short             flags;
    int		     *vectorIndices;
    int		      indexIndex;
    int		      nameIndex;
    int		      indexNameIndex;
};

#define glistaccCLASS(SUPER, ACC, NOTIFY, LIST) 			\
gaccessorCLASS(SUPER, ACC, NOTIFY); 					\
vclassMETHOD (glistaccSET_LIST,						\
              (ACC *accessor, LIST *list));				\
vclassMETHOD (glistaccSET_ORIENTATION,					\
              (ACC *accessor, int orientation));			\
vclassMETHOD (glistaccSET_VECTOR_INDICES,				\
              (ACC *accessor, int *indices));				\
vclassMETHOD (glistaccSET_NAME_INDEX,					\
              (ACC *accessor, int index));				\
vclassMETHOD (glistaccSET_INDEX_NAME_INDEX,				\
              (ACC *accessor, int index));				\
vclassMETHOD (glistaccSET_INDEX_INDEX,					\
              (ACC *accessor, int index))


typedef struct glistaccClass glistaccClass;

struct glistaccClass {
    glistaccCLASS (glistaccClass, glistacc, gaccessorNoteProc, vlist);
};




/*
 * ---------- Module Prototypes ----------
 */


void glistaccSetList (glistacc *accessor, vlist *list);
vlist *glistaccGetList (glistacc *accessor);

void glistaccSetOrientation (glistacc *accessor, int orientation);
int glistaccGetOrientation (glistacc *accessor);

void glistaccSetVectorIndices (glistacc *accessor, int *indices);
int glistaccGetVectorIndex (glistacc *accessor, int vectorPosition);

void glistaccSetNameIndex (glistacc *accessor, int nameIndex);
int glistaccGetNameIndex (glistacc *accessor);

void glistaccSetIndexNameIndex (glistacc *accessor, int indexNameIndex);
int glitaccGetIndexNameIndex (glistacc *accessor);

void glistaccSetIndexIndex (glistacc *accessor, int index);
int glistaccGetIndexIndex (glistacc *accessor);


/* conveniences */

void glistaccSetValueType (glistacc *accessor, int type);
void glistaccSetIndexType (glistacc *accessor, int type);
int glistaccGetValueType (glistacc *accessor);
int glistaccGetIndexType (glistacc *accessor);

void *glistaccGetValue (glistacc *accessor, int index);
vchar *glistaccGetValueName (glistacc *accessor, int index);

void glistaccSetRangeMin (glistacc *accessor, void *min);
void *glistaccGetRangeMin (glistacc *accessor);
void glistaccSetRangeMax (glistacc *accessor, void *max);
void *glistaccGetRangeMax (glistacc *accessor);

void *glistaccGetIndexValue (glistacc *accessor, int index);
void glistaccSetIndexCount (glistacc *accessor, int indexCount);
int glistaccGetIndexCount (glistacc *accessor);


void *glistaccGetVectorValue (glistacc *accessor, int index,
                               int vectorPosition);
void glistaccSetVectorComponentCount (glistacc *accessor, int count);
int glistaccGetVectorComponentCount (glistacc *accessor);

void glistaccSetVectorComponentMin (glistacc *accessor,
                                     int vectorPosition, void *min);
void *glistaccGetVectorComponentMin (glistacc *accessor, 
                                       int vectorPosition);
void glistaccSetVectorComponentMax (glistacc *accessor,
                                     int vectorPosition, void *max);
void *glistaccGetVectorComponentMax (glistacc *accessor,
                                       int vectorPosition);

void glistaccSetNotify (glistacc *accessor, gaccessorNoteProc notify);
void glistaccNotify (glistacc *accessor, int message);
gaccessorNoteProc glistaccGetNotify (glistacc *accessor);

void glistaccCalcRanges (glistacc *accessor);

void glistaccSetSubset (glistacc *accessor, int lowBound, int highBound);
void glistaccGetSubset (glistacc *accessor, int *lowBound, int *highBound);



/* back to the protos */

glistacc *glistaccCreate ();
glistacc *glistaccCreateOfClass ();
void glistaccDestroy (glistacc *accessor);

glistaccClass *glistaccGetDefaultClass ();
glistaccClass *glistaccGetClass (glistacc *accessor);

gaccessor *glistaccGetAccessor (glistacc *accessor);
vobject *glistaccGetObject (glistacc *accessor);

void glistaccDump (glistacc *accessor, FILE *stream);

vlistObserverClass *glistaccGetDefaultObserverClass (void);




/*
 * ---------- Functions defined as #define defines ----------
 */


#define glistaccGetList(a)	   ((a)->list)
#if (vportBAD_CC_SCOPING)
#define glistaccGetAccessor(a)     (&((a)->accessr))
#else
#define glistaccGetAccessor(a)     (&((a)->accessor))
#endif

#define glistaccGetObject(a)	   gaccessorGetObject(glistaccGetAccessor((a)))

#define glistaccGetOrientation(a)  ((a)->flags & _glistaccORIENTATION_BITS)

#define glistaccGetNameIndex(a)	   ((a)->nameIndex)
#define glistaccGetIndexNameIndex(a) ((a)->indexNameIndex)
#define glistaccGetIndexIndex(a)   ((a)->indexIndex)

#define glistaccCreate()      glistaccCreateOfClass(glistaccGetDefaultClass())
#define glistaccCreateOfClass(c)     ((glistacc*)vobjectCreateOfClass \
                                      ((vobjectClass*)(c)))
#define glistaccDestroy(a)	   vobjectDestroy(glistaccGetObject((a)))

#define glistaccGetClass(a)	   ((glistaccClass*) \
                                    gaccessorGetClass(glistaccGetAccessor \
                                                      ((a))))

#define glistaccSend(o,s,a)	vclassSend(glistaccGetClass((o)), s, a)


/* conveniences */

#define glistaccSetValueType(a,t) gaccessorSetValueType(glistaccGetAccessor \
                                                        ((a)), t)
#define glistaccSetIndexType(a,t) gaccessorSetIndexType(glistaccGetAccessor \
                                                        ((a)), t)
#define glistaccGetValueType(a) gaccessorGetValueType(glistaccGetAccessor((a)))
#define glistaccGetIndexType(a) gaccessorGetIndexType(glistaccGetAccessor((a)))

#define glistaccGetValue(a,i) gaccessorGetValue(glistaccGetAccessor((a)),i)
#define glistaccGetValueName(a,i) gaccessorGetValueName(glistaccGetAccessor \
                                                        ((a)),i)

#define glistaccSetRangeMin(a,m) gaccessorSetRangeMin(glistaccGetAccessor \
                                                      ((a)),m)
#define glistaccGetRangeMin(a) gaccessorGetRangeMin(glistaccGetAccessor((a)))
#define glistaccSetRangeMax(a,m) gaccessorSetRangeMax(glistaccGetAccessor \
                                                      ((a)),m)
#define glistaccGetRangeMax(a) gaccessorGetRangeMax(glistaccGetAccessor((a)))

#define glistaccGetIndexValue(a,i) gaccessorGetIndexValue(glistaccGetAccessor \
                                                          ((a)),i)
#define glistaccSetIndexCount(a,i) gaccessorSetIndexCount(glistaccGetAccessor \
                                                          ((a)),i)
#define glistaccGetIndexCount(a) gaccessorGetIndexCount(glistaccGetAccessor \
                                                        ((a)))

#define glistaccGetVectorValue(a,i,v) (gaccessorGetVectorValue \
                                       (glistaccGetAccessor((a)),i,v))

#define glistaccSetVectorComponentCount(a,c) (gaccessorSetVectorComponentCount\
                                              (glistaccGetAccessor((a)),c))
#define glistaccGetVectorComponentCount(a) (gaccessorGetVectorComponentCount \
                                            (glistaccGetAccessor((a))))

#define glistaccSetVectorComponentMin(a,v,m) (gaccessorSetVectorComponentMin \
                                              (glistaccGetAccessor((a)),v,m))

#define glistaccGetVectorComponentMin(a,v) (gaccessorGetVectorComponentMin \
                                            (glistaccGetAccessor((a)),v))

#define glistaccSetVectorComponentMax(a,v,m) (gaccessorSetVectorComponentMax \
                                              (glistaccGetAccessor((a)),v,m))

#define glistaccGetVectorComponentMax(a,v) (gaccessorGetVectorComponentMax \
                                            (glistaccGetAccessor((a)),v))

#define glistaccSetNotify(a,n) gaccessorSetNotify(glistaccGetAccessor((a)),n)
#define glistaccNotify(a,m) gaccessorNotify(glistaccGetAccessor((a)),(m))
#define glistaccGetNotify(a) gaccessorGetNotify(glistaccGetAccessor((a)))

#define glistaccCalcRanges(a) gaccessorCalcRanges(glistaccGetAccessor((a)))
#define glistaccSetSubset(a,h,l) gaccessorSetSubset(glistaccGetAccessor((a)), \
                                                    h,l)
#define glistaccGetSubset(a,h,l) gaccessorGetSubset(glistaccGetAccessor((a)), \
                                                    h,l)




/*
 * ---------- Functions implemented by messages ----------
 */


#define glistaccSetList(a,l) \
	glistaccSend ((a), glistaccSET_LIST, (a,l))

#define glistaccSetOrientation(a,o) \
	glistaccSend ((a), glistaccSET_ORIENTATION, (a,o))

#define glistaccSetVectorIndices(a,i) \
	glistaccSend ((a), glistaccSET_VECTOR_INDICES, (a,i))

#define glistaccSetNameIndex(a,i) \
	glistaccSend ((a), glistaccSET_NAME_INDEX, (a,i))

#define glistaccSetIndexNameIndex(a,i) \
	glistaccSend ((a), glistaccSET_INDEX_NAME_INDEX, (a,i))

#define glistaccSetIndexIndex(a,i) \
	glistaccSend ((a), glistaccSET_INDEX_INDEX, (a,i))

#endif /* #ifndef glistaccINCLUDED */


/*
 * Formatting information for emacs in c-mode
 *
 * Local Variables:
 * c-indent-level:4
 * c-continued-statement-offset:0
 * c-brace-offset:0
 * c-brace-imaginary-offset:0
 * c-argdecl-indent:0
 * c-label-offset:0
 * End:
 */
