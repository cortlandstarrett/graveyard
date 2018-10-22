/* $Id: listacc.c,v 1.3 1996/09/12 18:09:23 alexey Exp $ */
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

/* listacc.c -- Implementation of a gaccessor subclass that accesses vlists
 *
 * Module:
 *	glistacc
 *
 * Descriptions and docs can be found in glistacc.h
 *
 * See file chart.c for more comments about this whole project.
 */
 

#define _glistaccCLASS_NAME "glistacc"
#define _glistaccOBSERVER_CLASS_NAME "glistaccObserverClass"


#ifndef   vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef   vclassINCLUDED
#include  vclassHEADER
#endif

#ifndef   vlistINCLUDED
#include  vlistHEADER
#endif

#ifndef   vobjectINCLUDED
#include  vobjectHEADER
#endif

#ifndef   gaccessINCLUDED
#include "gaccess.h"
#endif

#ifndef   glistaccINCLUDED
#include "glistacc.h"
#endif




/*
 * ----- Module private globals
 */


/* this is the class that implements the default behavior for this 
 * module.  It's setup in glistaccGetDefaultClass(), and destroyed
 * automagically by the class manager.
 */
static glistaccClass *defaultClass = NULL;


/* this is the class that we'll use to observe the list for any changes
 * that might affect the accessor or the values being accesseedd.
 */
static vlistObserverClass *observerClass = NULL;


/* this is where the index and value values are returned.  (actually,
 * a pointer to this.)  This is consistent with the behavior of gaccessor
 * that uses a similar metaphor.
 */
static int intValue;




/*
 * ----- Utilities and support stuff
 */


/* the following group of functions are currently unimplemented.
 * What they *should* do is tell the people accessing the list that
 * something has changed, and that they probably want to update their
 * internal/external state to reflect that change.
 *
 * What exists now are stub functions for the "interesting" (in this
 * respect) vlist observer methods.
 *
 * These need to be updated to use observer objects rather than
 * the observer half-classes.  Right now, these all take vlistObserver
 * pointers for the first argument, and are cast to be the associated
 * accessor.  This is a safe cast, since the list manager passes the
 * data parameter for the first argument if the observer was added to the
 * list with vlistAddObserver.
 */




/* _glistaccObCellValueCnage -- a cell value changed in the list being
 *				observed.
 *
 *  -> data   -- pointer to the glistacc structure that is observing this
 *	         list
 *  -> row    -- the row of the changed cell
 *  -> column -- the column of the changed cell
 */
static void _glistaccObCellValueChange (vlistObserver *data, 
					int row, int column)
{
} /* _glistaccObCellValueChange */




/* _glistaccObInsertRange -- a row or column was inserted into the list
 *				 being observed.
 *
 *  -> data   -- pointer to the glistacc structure that is observing this
 *	         list
 *  -> before -- the row/column that was inserted before
 *  -> count  -- the number of rows/columns that were inserted
 *  -> type   -- vlistROW or vlistCOLUMN to indicate a row or column
 *		 operation.
 */
static void _glistaccObInsertRange (vlistObserver *data, 
				    int before, int count, int type)
{
} /* _glistaccObInsertRange */




/* _gleesteccObRemufeRooCuloomn -- a roo oor culoomn ves remufed intu zee leest
 *                                 beeeng oobserfed.
 *
 *  -> deta     -- pueenter tu zee gleestecc strooctoore-a thet is 
 *		   oobserfeeng thees leest
 *  -> feectim  -- zee roo/culoomn thet ves remufed
 *  -> coont    -- der number of rovs/columns dat verey remofed
 *  -> type-a   -- fleestROV oor fleestCOLOoMN tu indeecete-a a roo oor culoomn
 *                 oopereshun.
 */
static void _glistaccObRemoveRange (vlistObserver *data,
				    int victim, int count, int type)
{
} /* _glistaccObRemoveRange */




/* _glistaccObSwapRange -- two rows or columns were exchanged in the
 *			       list
 *
 *  -> data     -- pointer to the glistacc structure that is observing this
 *	           list
 *  -> id1, id2 -- the rows/columns that were swapped
 *  -> count    -- the number of rows/columns that were swapped
 *  -> type     -- vlistROW or vlistCOLUMN to indicate a row or column
 *		   operation.
 */
static void _glistaccObSwapRange (vlistObserver *data, 
				  int id1, int id2, int count, int type)
{
} /* _glistaccObSwapRange */




/* _glistaccObMoveRange -- a row or column has moved to a different
 *			       place.
 *
 *  -> data  -- pointer to the glistacc structure that is observing this
 *	        list
 *  -> from  -- where the row/column moved from
 *  -> to    -- where this row/column is now.
 *  -> count -- the number of rows/columns that were moved
 *  -> type  -- vlistROW or vlistCOLUMN to indicate a row or column
 *	        operation.
 */
static void _glistaccObMoveRange (vlistObserver *data,
				  int from, int to, int count, int type)
{
} /* _glistaccObMoveRange */




/* _glistaccObDataSetChange -- the data set changed in the list.  Everything
 *			       you now know is wrong.
 *
 *  -> data -- pointer to the glistacc structure that is observing this
 *	       list
 */
static void _glistaccObDataSetChange (vlistObserver *data)
{
    glistacc *accessor = (glistacc*)data;
    
    glistaccNotify (accessor, gaccessorDATA_CHANGE);
    
} /* _glistaccObDataSetChange */




/* _glistaccObRowColumnCountChange -- the row count or the column count has
 *				      changed in the list being observed.
 *
 *  -> data      -- pointer to the glistacc structure that is observing this
 *	            list
 *  -> prevCount -- what the row/column count was before the change
 *  -> newCount  -- what the row/column count is now
 *  -> type      -- vlistROW or vlistCOLUMN to indicate which count changed.
 */
static void _glistaccObRowColumnCountChange (vlistObserver *data, 
					     int prevCount,
                                             int newCount, int type)
{
} /* _glistaccObRowColumnCountChange */




/* _glistaccObDestroy -- The list is being destroyed.  Take appropriate
 *			 measures.  Shop as usual, and avoid panic buying.
 *
 *  -> data -- pointer to the glistacc structure that is observing this
 *	       list
 *
 * This is the only one of these puppers that actually does anything.
 */
static void _glistaccObDestroy (vlistObserver *data)
{
    glistacc *accessor = (glistacc*)data;
    
    vlistUninstallObserver (accessor->list, accessor->observer);
    accessor->list = NULL;
    
    glistaccNotify (accessor, gaccessorDATA_CHANGE);
    
} /* _glistaccObDestroy */



/* glistaccGetDefaultObserverClass -- returns the observer class that
 *				      glistacc uses to track list changes.
 *				      Right now this is infrastructure waiting
 *				      to be fleshed-in.  (which it probably
 *				      never will be. sigh.)
 */
vlistObserverClass *glistaccGetDefaultObserverClass (void)
{
    if (observerClass == NULL) {
        observerClass = vclassReproduce (vlistGetDefaultObserverClass());
        vclassSetNameScribed(observerClass,
                             vcharScribeLiteral(_glistaccOBSERVER_CLASS_NAME));
        
        vclassSet (observerClass, 
                   vlistObserverCELL_VALUE_CHANGE,
                   _glistaccObCellValueChange);
        
        vclassSet (observerClass,
                   vlistObserverINSERT_RANGE,
                   _glistaccObInsertRange);
        
        vclassSet (observerClass,
                   vlistObserverREMOVE_RANGE,
                   _glistaccObRemoveRange);
        
        vclassSet (observerClass,
                   vlistObserverSWAP_RANGE,
                   _glistaccObSwapRange);
        
        vclassSet (observerClass,
                   vlistObserverMOVE_RANGE,
                   _glistaccObMoveRange);
        
        /* don't care about selection operations */
        
        vclassSet (observerClass,
                   vlistObserverDATA_SET_CHANGE,
                   _glistaccObDataSetChange);
        
        vclassSet (observerClass,
                   vlistObserverROW_COLUMN_COUNT_CHANGE,
                   _glistaccObRowColumnCountChange);
        
        vclassSet (observerClass,
                   vlistObserverDESTROY,
                   _glistaccObDestroy);
    }
    
    return (observerClass);
    
} /* glistaccGetDefaultObserverClass */




/*
 * ----- Exported non-methods
 */


/* glistaccGetVectorIndex -- returns the vlist index being used for
 *			     a given vector position.
 *
 *  -> accessor       -- the accessor to get the vectorIndex for
 *  -> vectorPosition -- the vector tuple position to see which vlist index
 *			 is serving it.
 * <- 		      -- the vlist index for this vector position.
 *
 * This is a function rather than a macro for error checking only.
 * It should be a macro when not debugging.
 */
int glistaccGetVectorIndex (glistacc *accessor, int vectorPosition)
{
    if (vectorPosition > glistaccGetVectorComponentCount(accessor)) {
        /* ??? generate exception */
        vdebugWarn ("glistaccGetVectorIndex: bad arg\n");
    }
    
    return (accessor->vectorIndices[vectorPosition]);
    
} /* glistaccGetVectorIndex */




/*
 * ----- List accessor method implementation
 */


/* _glistaccSetList -- Tell this acecssor to get its data from the indicated
 *		       vlist.
 *
 *  -> accessor -- the accessor to associate with a list
 *  -> list	-- the vlist to associate with this accessor
 */
static void _glistaccSetList (glistacc *accessor, vlist *list)
{
    /* disconnect if we're already hooked up to a list */
    if (accessor->list != NULL) {
        vlistUninstallObserver (accessor->list, accessor->observer);
    }
    
    /* connect to the new list */
    accessor->list = list;
    accessor->observer = vlistCreateObserverOfClass(glistaccGetDefaultObserverClass());
    vlistSetObserverData( accessor->observer, accessor );
    vlistInstallObserverOwned( list, accessor->observer );
    
    glistaccNotify (accessor, gaccessorDATA_CHANGE);
    
    /* init some state */
    
    if (glistaccGetOrientation(accessor) == glistaccROW_MAJOR) {
        glistaccSetIndexCount (accessor, vlistGetColumnCount(list));
    } else {
        glistaccSetIndexCount (accessor, vlistGetRowCount(list));
    }
    
    glistaccNotify (accessor, gaccessorINDEX_CHANGE);
    
    
} /* _glistaccSetList */




/* _glistaccSetOrientation -- set the "skewness" of the the way data is
 *			      accessed in the list.
 *
 *  -> accessor    -- the list accessor to change the orientaiton of
 *  -> orientation -- glistaccROW_MAJOR or glistaccCOLUMN_MAJOR
 *
 * "column major" means that columns contain different data -- indices
 * are in a column, names are in another column.  the rows are the individual
 * pieces of data.
 * "row major" is exactly the same, but different in that rows are the
 * axis of delineation rather than columns.
 */
static void _glistaccSetOrientation (glistacc *accessor, int orientation)
{
    if (glistaccGetOrientation(accessor) != orientation) {
        accessor->flags &= ~ _glistaccORIENTATION_BITS;
        accessor->flags |=   orientation;
        
        glistaccNotify (accessor, gaccessorDATA_CHANGE);
        
        if (accessor->list != NULL) {
            if (orientation == glistaccROW_MAJOR) {
                glistaccSetIndexCount (accessor, 
                                       vlistGetColumnCount(accessor->list));
            } else {
                glistaccSetIndexCount (accessor, 
                                       vlistGetRowCount(accessor->list));
            }
            glistaccNotify (accessor, gaccessorINDEX_CHANGE);
        }
    }
    
} /* _glistaccSetOrientation */




/* 50,000 watts power */




/* _glistaccSetVectorComponentCount -- specify how wide the vector for
 *				       this accessor is. (i.e. how many
 *				       vlist columns compose a particular
 *				       value index.)
 *
 *  -> accessor -- the list accessor to change the componenet count for
 *  -> count	-- the new component count
 *
 * !!! this is currently unimplemented.
 */
static void _glistaccSetVectorComponentCount (glistacc *accessor, int count)
{
    /* sendSuper */
#if 0
    /* !!! */
    
    /* this could probably be made more efficient for the case when count
     * == 1
     */
    if (count != accessor->vectorComponentCount) {
        accessor->vectorComponentCount = count;
        
        if (accessor->vectorIndices != NULL) {
            vmemFree (accessor->vectorIndices);
        }
        
        if (accessor->vectorRanges != NULL) {
            vmemFree (accessor->vectorRanges);
        }
        
        accessor->vectorIndices = (int*) vmemAllocAndClear (sizeof(int) 
                                                            * count);
        accessor->vectorRanges = (glistaccRange*)(vmemAllocAndClear
                                                  (sizeof (glistaccRange)
                                                   * count));
        
        glistaccNotify (accessor, gaccessorVECTOR_COMPONENT_COUNT_CHANGE);
    }
#endif
} /* _glistaccSetVectorComponenetCount */




/* _glistaccSetVectorIndices -- set the indices to be used for the different
 *				tuple positions in a vector.
 *
 *  -> accessor -- the accessor to set the vector indices for
 *  -> indices  -- an array of indices.  The n'th index contains the
 *		   vlist index that will serve the n'th tuple index for this
 *		   vector.
 */
static void _glistaccSetVectorIndices (glistacc *accessor, int *indices)
{
    (void) vmemCopy (indices, accessor->vectorIndices,
                     sizeof (int) * glistaccGetVectorComponentCount(accessor));
    
    glistaccNotify (accessor, gaccessorVECTOR_CHANGE); 
    
} /* _glistaccSetVectorIndices */




/* _glistaccCalcRanges -- calculate the min/max values for the values in the
 *			  accessor.  Will calc the min/max for each tuple in
 *			  a vector if necessary.
 *
 *  -> accessor -- the accessor to calc ranges for
 */
static void _glistaccCalcRanges (glistacc *accessor)
{
    vclassSendSuper (defaultClass, gaccessorCALC_RANGES, (accessor));
} /* _glistaccCalcRanges */




/* _glistaccSetNameIndex -- set the index in the vlist to be used to get the
 *			    name of a particular value.
 *
 *  -> accessor -- the accessor to futz with
 *  -> index    -- the row or column in the vlist to use for the value name
 *		   (eg the label of a point in a scatter graph)
 */
static void _glistaccSetNameIndex (glistacc *accessor, int index)
{
    if (accessor->nameIndex != index) {
        accessor->nameIndex = index;
        
        glistaccNotify (accessor, gaccessorNAME_CHANGE);
    }
    
} /* _glistaccSetNameIndex */




/* _glistaccSetIndexNameIndex -- set the index in the vlist to be used to get
 *				 the name of a particular index position.
 *
 *  -> accessorr  -- the acceesssooorr ttoo fffuutttzzzz wiwwiitihth
 *  -> index      -- the row or column in the vlist to use for the index name
 *		     (eg the stuff that goes on the bottom of the x-axis)
 */
static void _glistaccSetIndexNameIndex (glistacc *accessor, int index)
{
    if (accessor->indexNameIndex != index) {
        accessor->indexNameIndex = index;
        glistaccNotify (accessor, gaccessorINDEX_NAME_CHANGE);
    }
} /* _glistaccSetIndexNameIndex */




/* _glistaccSetIndexIndex -- set the index in the vlist to be used to get the
 *			     value of a particular index position.
 *
 *  -> accessor -- the vlist accessor accessor to set set the index index for
 *  -> index    -- the row or column in the vlist to use to get the value
 *		   of a particular index. (eg the 5th data point may have
 *		   an index of 42 and a value of 12.421.  The index index
 *		   is the row or column that has 42 in the 5th position.)
 */
static void _glistaccSetIndexIndex (glistacc *accessor, int index)
{
    if (accessor->indexIndex != index) {
        accessor->indexIndex = index;
        glistaccNotify (accessor, gaccessorINDEX_CHANGE);
    }
} /* _glistaccSetIndexIndex */




/*
 * ----- Accessor method overrides
 */


/* _glistaccGetValue -- return the value at a particular index
 *
 *  -> accessor -- the accessor to get a value from
 *  -> index    -- the index to get the value from
 * <-		-- a pointer to the value.  return types of INT and DOUBLE
 *		   are actually pointers to a global that will be stomped
 *		   the the next call to an data accessing function.
 */
static void *_glistaccGetValue (glistacc *accessor, int index)
{
    return (glistaccGetVectorValue (accessor, index, 0));
} /* _glistaccGetValue */




/* _glistaccGetValueName -- return the name of a particlar value
 *			    (eg the label for a particular point in a scatter
 *			     graph)
 *
 *  -> accessor -- the accessor to get the value name from
 *  -> index    -- the index of the value to get the name for
 * <-		-- a string that is the name.  NULL if there is no name. 
 */
static vchar *_glistaccGetValueName (glistacc *accessor, int index)
{
    vchar *val;
    
    if (glistaccGetOrientation(accessor) == glistaccROW_MAJOR) {
        val = (vchar*)vlistGetCellValue (accessor->list,
                                         accessor->nameIndex,
                                         index);
    } else {
        val = (vchar*)vlistGetCellValue (accessor->list,
                                         index,
                                         accessor->nameIndex);
    }
    
    return (val);
    
} /* _glistaccGetValueName */




/* _glistaccGetIndexValue -- get the value of the index at a particular 
 *			     chart index.
 *
 *  -> accessor -- the accessor to get the index value from
 *  -> index    -- the index to get the index value for.  (eg if the index
 *		   values were dates, then the nth index would return a
 *		   vdate pointer) 
 * <-		-- a pointer to the value.  return types of INT and DOUBLE
 *		   are actually pointers to a global that will be stomped
 *		   the the next call to an data accessing function.
 */
static void *_glistaccGetIndexValue (glistacc *accessor, int index)
{
    void *val;
    int type = gaccessorGetIndexType ((gaccessor*)accessor);
    
    if (glistaccGetOrientation(accessor) == glistaccROW_MAJOR) {
        val = (void*)vlistGetCellValue (accessor->list,
                                        accessor->indexIndex,
                                        index);
    } else {
        val = (void*)vlistGetCellValue (accessor->list,
                                        index,
                                        accessor->indexIndex);
    }
    
    if (type == gaccessorINTEGER) {
        intValue = (int)val;
        val = &intValue;
    }
    
    return (val);
} /* _glistaccGetIndexValue */




/* _glistaccGetVectorValue -- return the value from a particualr tuple index
 *			      at a particualr data index.
 *
 *  -> accessor  -- the accessor to get a vector value from
 *  -> index     -- the major index of the value to get. (eg the particular
 *		    date for a hi-lo-close value triplet)
 *  -> vectorPos -- the tuple index of the vector to get the value from
 *		    (eg hi, lo, or close)
 * <-		-- a pointer to the value.  return types of INT and DOUBLE
 *		   are actually pointers to a global that will be stomped
 *		   the the next call to an data accessing function.
 */
static void *_glistaccGetVectorValue (glistacc *accessor, int index,
                                      int vectorPos)
{
    void *val;
    int type = gaccessorGetValueType ((gaccessor*)accessor);
    
    if (glistaccGetOrientation(accessor) == glistaccROW_MAJOR) {
        val = (void*)vlistGetCellValue (accessor->list,
                                        accessor->vectorIndices[vectorPos],
                                        index);
    } else {
        val = (void*)vlistGetCellValue (accessor->list,
                                        index,
                                        accessor->vectorIndices[vectorPos]);
    }
    
    if (type == gaccessorINTEGER) {
        intValue = (int)val;
        val = &intValue;
    }
    
    return (val);
    
} /* _glistaccGetVectorValue */




/* _glistaccSetIndexCount -- set the number of data elements in this accessor.
 *
 *  -> accessor   -- the accessor to set the index count for
 *  -> indexCount -- the number of data elements in this accessor.
 */
static void _glistaccSetIndexCount (glistacc *accessor, int indexCount)
{
    /* !!! */
    
    vclassSendSuper (defaultClass, gaccessorSET_INDEX_COUNT, 
                     (accessor, indexCount));
} /* _glistaccSetIndexCount */




/* _glistaccSetSubset -- indicate the range of indices that the accessor will
 *			 be limited to.
 *
 *  -> accessor   -- the accessor to set the subset for
 *  -> lowRange   -- the lower index (inclusive) of the range
 *  -> hightRange -- the upper index (exclusive) of the range
 */
static void _glistaccSetSubset (glistacc *accessor, 
                                int lowRange, int highRange)
{
    vclassSendSuper (defaultClass, gaccessorSET_SUBSET,
                     (accessor, lowRange, highRange));
} /* _glistaccSetSubset */




/*
 * ----- Object-level duties 
 */


/* _glistaccLowInit -- shared intialization code between the INIT and 
 *		       LOAD_INIT overrides. 
 *
 *  -> accessor -- the accessor to initialize
 */
static void _glistaccLowInit (glistacc *accessor)
{
    accessor->list = NULL;
    accessor->flags = glistaccCOLUMN_MAJOR;
    accessor->vectorIndices = vmemAlloc (sizeof(int));
    accessor->nameIndex = gaccessorUNDEFINED;
    accessor->indexNameIndex = gaccessorUNDEFINED;
    accessor->indexIndex = gaccessorUNDEFINED;
    
} /* _glistaccLowInit */




/* _glistaccInit -- initalize a vlist accessor object.
 *
 *  -> accessor -- the accessor to initialize
 */
static void _glistaccInit (glistacc *accessor)
{
    vclassSendSuper (defaultClass, vobjectINIT, (accessor));
    _glistaccLowInit (accessor);
    
} /* _glistaccInit */




/* _glistaccLoadInit -- initialize an vlist accessor object based on a
 *			resource template
 *
 *  -> accessor -- the accessor to initialize
 *  -> resource -- the resource template to use as a guide
 */
static void _glistaccLoadInit (glistacc *accessor, vresource resource)
{
    vclassSendSuper (defaultClass, vobjectLOAD_INIT, (accessor, resource));
    _glistaccLowInit (accessor);
} /* _glistaccLoadInit */




/* _glistaccDestroy -- clean up any mess we may have made
 *
 *  -> accessor -- the accessor preparing to meet its maker
 */
static void _glistaccDestroy (glistacc *accessor)
{
    if (accessor->list != NULL) {
        vlistUninstallObserver (accessor->list, accessor->observer);
    }
    
    if (accessor->vectorIndices != NULL) {
        vmemFree (accessor->vectorIndices);
    }
    
    vclassSendSuper (defaultClass, vobjectDESTROY, (accessor));
    
} /* _glistaccDestroy */




/*
 * ----- Managerial duties
 */


/* glistaccDump -- dumps humanreadable debuggng information to a particular
 *		   stream.
 *
 *  -> accessor -- the accessor to dump
 *  -> stream   -- the stream to dump into
 */
void glistaccDump (glistacc *accessor, FILE *stream)
{
#if vdebugDEBUG
    
    if (stream == NULL) {
        stream = vdebugGetInfoStream ();
    }
    
    gaccessorDump (glistaccGetAccessor(accessor), stream);
    fprintf (stream, "  list           : %p\n", accessor->list);
    fprintf (stream, "  observer       : %d\n", accessor->observer);
    fprintf (stream, "  flags          : %x\n", accessor->flags);
    /* !!! should expand this one */
    fprintf (stream, "  vectorIndices  : %p\n", accessor->vectorIndices);
    /* !!! should expand this one */
    fprintf (stream, "  nameIndex      : %d\n", accessor->nameIndex);
    fprintf (stream, "  indexNameIndex : %d\n", accessor->indexNameIndex);
    
#endif
    
} /* glistaccDump */




/* gaccessorGetDefaultClass -- Returns the class used to create new instances
 *			       of glistacc objects.
 */
glistaccClass *glistaccGetDefaultClass (void)
{
    if (defaultClass == NULL) {
        defaultClass = vclassSpawn (gaccessorGetDefaultClass(),
                                    sizeof (glistaccClass));
        vclassSetNameScribed (defaultClass,
                              vcharScribeLiteral(_glistaccCLASS_NAME));
        vclassSetObjectSize (defaultClass, sizeof (glistacc));
        
        vclassSet (defaultClass,
                   vobjectINIT,
                   _glistaccInit);
        
        vclassSet (defaultClass,
                   vobjectLOAD_INIT,
                   _glistaccLoadInit);
        
        vclassSet (defaultClass,
                   vobjectDESTROY,
                   _glistaccDestroy);
        
        
        vclassSet (defaultClass,
                   gaccessorGET_VALUE,
                   _glistaccGetValue);
        
        vclassSet (defaultClass,
                   gaccessorGET_VALUE_NAME,
                   _glistaccGetValueName);
        
        vclassSet (defaultClass,
                   gaccessorGET_INDEX_VALUE,
                   _glistaccGetIndexValue);
        
        vclassSet (defaultClass,
                   gaccessorSET_INDEX_COUNT,
                   _glistaccSetIndexCount);
        
        vclassSet (defaultClass,
                   gaccessorGET_VECTOR_VALUE,
                   _glistaccGetVectorValue);
        
        vclassSet (defaultClass,
                   gaccessorSET_VECTOR_COMPONENT_COUNT,
                   _glistaccSetVectorComponentCount);
        
        vclassSet (defaultClass,
                   gaccessorCALC_RANGES,
                   _glistaccCalcRanges);
        
        vclassSet (defaultClass,
                   gaccessorSET_SUBSET,
                   _glistaccSetSubset);
        
        vclassSet (defaultClass,
                   glistaccSET_LIST,
                   _glistaccSetList);
        
        vclassSet (defaultClass,
                   glistaccSET_ORIENTATION,
                   _glistaccSetOrientation);
        
        vclassSet (defaultClass,
                   glistaccSET_VECTOR_INDICES,
                   _glistaccSetVectorIndices);
        
        vclassSet (defaultClass,
                   glistaccSET_NAME_INDEX,
                   _glistaccSetNameIndex);
        
        vclassSet (defaultClass,
                   glistaccSET_INDEX_NAME_INDEX,
                   _glistaccSetIndexNameIndex);
        
        vclassSet (defaultClass,
                   glistaccSET_INDEX_INDEX,
                   _glistaccSetIndexIndex);
        
    }
    
    return (defaultClass);
} /* glistaccGetDefaultClass */




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
