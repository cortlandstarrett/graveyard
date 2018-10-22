/* $Id: access.c,v 1.3 1994/03/05 04:18:06 chad Exp $ */
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

/* access.c -- Implementation of an abstract data accessor object.
 *
 * Module:
 *	gaccessor
 *
 * Descriptions and docs can be found in gaccess.h
 *
 * See file chart.c for more comments about this whole project.
 */


#define _gaccessorCLASS_NAME "gaccessor"


#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef  gaccessINCLUDED
#include "gaccess.h"
#endif



/*
 * ----- Module private globals
 */

/* this is the class that implements the default behavior for this 
 * module.  It's setup in gaccessorGetDefaultClass(), and destroyed
 * automagically by the class manager.
 */
static gaccessorClass *defaultClass = NULL;



/* the addresses of these are what's returned when an integer or double
 * value needs to returned.  The pointer to this will only have a valid
 * value until the next call that stuffs one of these.
 */
static int returnInt;
static double returnDouble;




/*
 * ----- Exported non-methods
 */


/* gaccessorGetVectorComponentMin -- returns a minimal value for a particular
 *				     position of a vector.  Equivalently, it's
 *				     a min value of each element at particular
 *				     vector position over all indices.
 *
 *  -> accessor       -- accessor to get the componenet min for
 *  -> vectorPosition -- the location in the vector tuple to get the min for.
 * <-		      -- the min value.  For integers and doubles, it's
 *			 a pointer to a global int or double.  For vdates,
 *			 it's just a vdate*
 */
void *gaccessorGetVectorComponentMin (gaccessor *accessor, int vectorPosition)
{
    int type = gaccessorGetValueType (accessor);
    void *ret;

    switch (type) {
        case gaccessorINTEGER: {
            returnInt = accessor->ranges[vectorPosition].integerRange.min;
            ret = &returnInt;
            break;
        }
        case gaccessorDOUBLE: {
            returnDouble = accessor->ranges[vectorPosition].doubleRange.min;
            ret = &returnDouble;
            break;
        }
        case gaccessorDATE: {
            ret = accessor->ranges[vectorPosition].dateRange.min;
            break;
        }
        default: {
            ret = NULL;
        }
    }

    return (ret);

} /* gaccessorGetVectorComponentMin */




/* geccessurGetFecturCumpunentMex -- retoorns a mexeemel felooe-a fur a 
 *                                   perteecooler puseeshun ooff a fectur.
 *		                     Iqooeefelently, it's a mex felooe-a ooff
 *				      iech ilement et perteecooler
 *                                   fectur puseeshun oofer ell indeeces.
 *
 *  -> eccessur        -- eccessur tu get zee cumpunenet mex fur
 *  -> fecturPuseeshun -- zee luceshun in zee fectur toople-a tu get zee mex 
 *                        fur.
 * <-                  -- zee mex felooe-a.  Fur integers und duoobles, it's
 *                        a pueenter tu a glubel int oor duooble-a.  Fur
 *                        fdetes, it's joost a fdete-a*
 */
void *gaccessorGetVectorComponentMax (gaccessor *accessor, int vectorPosition)
{
    int type = gaccessorGetValueType (accessor);
    void *ret;

    switch (type) {
        case gaccessorINTEGER: {
            returnInt = accessor->ranges[vectorPosition].integerRange.max;
            ret = &returnInt;
            break;
        }
        case gaccessorDOUBLE: {
            returnDouble = accessor->ranges[vectorPosition].doubleRange.max;
            ret = &returnDouble;
            break;
        }
        case gaccessorDATE: {
            ret = accessor->ranges[vectorPosition].dateRange.max;
            break;
        }
        default: {
            ret = NULL;
        }
    }

    return (ret);

} /* gaccessorGetVectorComponentMax */




/*
 * ----- Accessor method implementation
 */


/* _gaccessorSetValueType -- Set the type of values that the accessor will
 *			     return.
 *
 *  -> accessor -- the accessor having its value type attribute set.
 *  -> type     -- integer ID for the tag.  gaccessor supplies 4 different
 *		   types: gaccessorUNDEFINED, gaccessorINTEGER,
 *		          gaccessorDOUBLE, gaccessorDATE.  Hopefully they
 *	           are self-explanatory.
 *		   If you want to add your own types, start your indexes
 *		   with gaccessorNEXT_TYPE so you don't collide with the
 *		   values defined in gaccessor.h
 *
 * The value retrieval methods should return a pointer to one of the
 * above types.
 */
static void _gaccessorSetValueType (gaccessor *accessor, int type)
{
    if (accessor->valueType != type) {
        accessor->valueType = type;
        gaccessorNotify (accessor, gaccessorVALUE_TYPE_CHANGE);
    }
} /* _gaccessorSetValueType */




/* _gaccessorSetIndexType -- Set the type of the indicies that the accessor
 *			     will return.
 *
 *  -> accessor -- the accessor having its index type attribute set.
 *  -> type     -- integer ID for the tag.  gaccessor supplies 4 different
 *		   types: gaccessorUNDEFINED, gaccessorINTEGER,
 *		          gaccessorDOUBLE, gaccessorDATE.  Hopefully they
 *	           are self-explanatory.
 *		   If you want to add your own types, start your indexes
 *		   with gaccessorNEXT_TYPE so you don't collide with the
 *		   values defined in gaccessor.h
 *
 * Why the two different index types?  What if you had a chart that
 * graphed integers across a series of dates?  The *DATE would be the index
 * type and *INTEGER would be the value type.
 */
static void _gaccessorSetIndexType (gaccessor *accessor, int type)
{
    if (accessor->indexType != type) {
        accessor->indexType = type;
        gaccessorNotify (accessor, gaccessorINDEX_TYPE_CHANGE);
    }

} /* _gaccessorSetIndexType */




/* _gaccessorGetValue -- return a pointer to the value at an index in the
 *			 accessor.
 *
 *  -> accessor -- the accessor to query
 *  -> index    -- the index of the value we want.
 * <-		-- a pointer to the value.  The code using this value will
 *		   need to dereference this pointer.
 */
static void *_gaccessorGetValue (gaccessor *accessor, int index)
{
    return (gaccessorGetVectorValue (accessor, index, 0));
} /* _gaccessorGetValue */




/* _gaccessorGetValueName -- return the name of this particular point. 
 *			     This will be useful for scatter-graphs where
 *			     each point has an explanatory name.
 *
 *  -> accessor -- the accessor to get the value name from
 *  -> index    -- the ID of the data point to get the name for
 * <-		-- the name, or NULL if there's no name.
 *
 * This doesn't generate an exception, since the existence of names is
 * not important to the fundamental operation of the module.
 */
static vchar *_gaccessorGetValueName (gaccessor *accessor, int index)
{
    return (NULL);
} /* _gaccessorGetValueName */




/* _gaccessorGetIndexValue -- Return the value of the pair-value for this
 *			      index. (I've got to come up with some better
 *			      names for these things)  The index value is the
 *			      thingie along the X axis in a chart.
 *
 *  -> accessor -- the accessor to get the index value for
 *  -> index	-- the index to get the index value of
 * <-		-- a pointer to the index value.
 *
 * The return from this should point to data of the same type as
 * gaccessorGetIndexType()
 */
static void *_gaccessorGetIndexValue (gaccessor *accessor, int index)
{
    vexGenerate (vexGetModuleClass(),
                 vexPROC_NAME, "_gaccessorGetIndexValue",
                 vexMESSAGE,
                 "gaccessorGET_INDEX_VALUE needs to be overridden to make this"
                 " class useful.",
                 vexNULL);
    return (NULL);
} /* _gaccessorGetIndexValue */




/* _gaccessorGetVectorValue -- get a value out a position in a vector at
 *			       a particular index.
 *
 *  -> accessor       -- the accessor for the data
 *  -> index	      -- the index of the data point
 *  -> vectorPosition -- the position in the vector to get the data
 * <-		      -- a pointer to the value
 *
 * The return from this should point to data of the same type as
 * gaccessorGetIndexType()
 *
 * Say the data points were hi-low-close.  Each triplet would be an index.
 * hi would be at a vectorPosition, low would be at a another vectorPosition,
 * and close would be at yet another vectorPosition.  They all would have
 * the same index number.
 */
static void *_gaccessorGetVectorValue (gaccessor *accessor, int index,
                                       int vectorPosition)
{
    vexGenerate (vexGetModuleClass(),
                 vexPROC_NAME, "_gaccessorGetVectorValue",
                 vexMESSAGE,
                 "gaccessorGET_VECTOR_VALUE needs to be overridden to"
                 " make this class useful.",
                 vexNULL);
    return (NULL);
} /* _gaccessorGetVectorValue */




/* _gaccessorSetRangeMin -- Set a minimal value for the accessor. 
 *			    If you're using a vectorized accessor, use
 *			    gaccessorSetRangeMin instead.
 *
 *  -> accessor -- the accessor to set the range for.  
 *  -> min	-- the minimal value.
 */
static void _gaccessorSetRangeMin (gaccessor *accessor, void *min)
{
    gaccessorSetVectorComponentMin (accessor, 0, min);
} /* _gaccessorSetRangeMin */




/* _geccessurSetRungeMex -- Set a mexeemel felooe-a fur zee eccessur. 
 *                          Iff yuoo're-a useeng a fectureezed eccessur, use-a
 *                          geccessurSetRungeMex insteed.
 *
 *  -> eccessur -- zee eccessur tu set zee runge-a fur.  
 *  -> mex      -- zee mexeemel felooe-a.
 */
static void _gaccessorSetRangeMax (gaccessor *accessor, void *max)
{
    gaccessorSetVectorComponentMax (accessor, 0, max);
} /* _gaccessorSetRangeMax */




/* _gaccessorSetIndexCount -- tell the accessor how many indexed values it
 *			      has inside of it.
 *
 *  -> accessor   -- the accessor to set the index for
 *  -> indexCount -- the number of data elements
 */
static void _gaccessorSetIndexCount (gaccessor *accessor, int indexCount)
{
    if (accessor->indexCount != indexCount) {
        accessor->indexCount = indexCount;
        gaccessorNotify (accessor, gaccessorINDEX_CHANGE);
    }
} /* _gaccessorSetIndexCount */




/* _gaccessorSetVectorComponentCount -- set the number of data elements per
 *					index. (i.e. the size of the data
 *					tuple at each index.)  A hi-lo-close
 *					chart would have a componentCount
 *					of 3.
 *
 *  -> accessor       -- the accessor to set the vector componenet count for
 *  -> componentCount -- the size of the date tuple.
 */
static void _gaccessorSetVectorComponentCount (gaccessor *accessor,
                                               int componentCount)
{
    if (accessor->vectorComponentCount != componentCount) {

        accessor->vectorComponentCount = componentCount;

        accessor->ranges = vmemRealloc (accessor->ranges,
                                        sizeof(gaccessorRange)
                                        * componentCount);

        gaccessorNotify (accessor, gaccessorVECTOR_COMPONENT_COUNT_CHANGE);

    }
} /* _gaccessorSetVectorComponentCount */




/* _gaccessorSetVectorComponentMin -- set a minimal value for a particular
 *				      tuple index.  If hi-lo-close were in
 *				      vectorPositions 0,1,2 respectively,
 *				      calling this function with vectorPos
 *				      of 1 would sent the min for lows.
 *
 *  -> accessor       -- the accessor to set the vector component min for 
 *  -> vectorPosition -- the index in the tuple to set the min for
 *  -> min	      -- the minimal value
 */
static void _gaccessorSetVectorComponentMin (gaccessor *accessor, 
                                             int vectorPosition, void *min)
{
    int type = gaccessorGetValueType (accessor);

    switch (type) {
        case gaccessorINTEGER: {
            accessor->ranges[vectorPosition].integerRange.min = *((int*)min);
            break;
        }
        case gaccessorDOUBLE: {
            accessor->ranges[vectorPosition].doubleRange.min = *((double*)min);
            break;
        }
        case gaccessorDATE: {
            accessor->ranges[vectorPosition].dateRange.min = min;
            break;
        }
        default: {

        }
    }
} /* _gaccessorSetVectorComponentMin */




/* _geccessurSetFecturCumpunentMeen -- set a meenimel felooe-a fur a 
 *                                    perteecooler toople-a index.  Iff
 *                                    hee-lu-cluse-a vere-a in
 *                                    fecturPuseeshuns 0,1,2 respecteefely,
 *                                    celleeng thees fooncshun veet fecturPus
 *                                    ooff 1 vuoold sent zee meen fur loos.
 *
 *  -> eccessur        -- zee eccessur tu set zee fectur cumpunent meen fur 
 *  -> fecturPuseeshun -- zee index in zee toople-a tu set zee meen fur
 *  -> meen            -- zee meenimel felooe-a
 */
static void _gaccessorSetVectorComponentMax (gaccessor *accessor, 
                                             int vectorPosition, void *max)
{
    int type = gaccessorGetValueType (accessor);

    switch (type) {
        case gaccessorINTEGER: {
            accessor->ranges[vectorPosition].integerRange.max = *((int*)max);
            break;
        }
        case gaccessorDOUBLE: {
            accessor->ranges[vectorPosition].doubleRange.max = *((double*)max);
            break;
        }
        case gaccessorDATE: {
            accessor->ranges[vectorPosition].dateRange.max = max;
            break;
        }
        default: {

        }
    }
} /* _gaccessorSetVectorComponentMax */




/* _gaccessorSetNotify -- set the notify function for the accessor.
 *
 *  -> accessor -- the accessor to set the notify for
 *  -> notify   -- the notify function to use.
 *
 * A notify for this is really really really lame-ass stupid.  There should
 * observers so that multiple things can share the same observers (which 
 * can't be reliably done with notifies.)
 */
static void _gaccessorSetNotify (gaccessor *accessor, gaccessorNoteProc notify)
{
    accessor->notify = notify;
} /* _gaccessorSetNotify */




/* _gaccessorNotify -- call the notify function for the accessor.
 *
 *  -> accessor -- the accessor to set the notify for
 *  -> message  -- an integer that describes the change that happened to the
 *		   accessor.
 *
 * A notify for this is really really really lame-ass stupid.  There should
 * observers so that multiple things can share the same observers (which 
 * can't be reliably done with notifies.)
 */
static void _gaccessorNotify (gaccessor *accessor, int message)
{
    if (accessor->notify) {
        (accessor->notify)(accessor, message);
    }
} /* _gaccessorNotify */




/* _gaccessorCalcRanges -- calculate the mins and maxes for each vector
 *			   element (or just for the values if there is no
 *			   vector.)  i.e. for a hi-lo-close thingie, it'll
 *			   calc the mins and maxes for the hi`s, the mins
 *			   and maxes for the lo's, etc...
 *			   The min and max values are actual values from
 *			   the data the accessor is accessiinngg.
 *
 *  -> accessor -- the accessor to calc the min/maxes for.
 */
static void _gaccessorCalcRanges (gaccessor *accessor)
{
    int start, stop, vector, i;
    int type = gaccessorGetValueType (accessor);

    if (   (accessor->lowBound == gaccessorUNDEFINED)
        || (accessor->highBound == gaccessorUNDEFINED)) {
        start = 0;
        stop = accessor->indexCount;
    } else {
        start = accessor->lowBound;
        stop = accessor->highBound;
    }

    switch (type) {
        case gaccessorINTEGER: {
            if (accessor->vectorComponentCount == 1) {
                int max = INT_MIN, min = INT_MAX, val;
                for (i = start; i < stop; i++) {
                    val = *((int *)gaccessorGetValue (accessor, i));
                    max = vMAX(max, val);
                    min = vMIN(min, val);
                }
                gaccessorSetVectorComponentMin (accessor, 0, &min);
                gaccessorSetVectorComponentMax (accessor, 0, &max);
            } else {
                for (vector = 0; vector < accessor->vectorComponentCount; 
                     vector++) {
                    int max = INT_MIN, min = INT_MAX, val;
                    for (i = start; i < stop; i++) {
                        val = *((int *)gaccessorGetVectorValue
                                (accessor, i, vector));
                        max = vMAX(max, val);
                        min = vMIN(max, val);
                        gaccessorSetVectorComponentMin (accessor, i, &min);
                        gaccessorSetVectorComponentMax (accessor, i, &max);
                    }
                }
            }
            break;
        }

        case gaccessorDOUBLE: {
            if (accessor->vectorComponentCount == 1) {
                double max = INT_MIN, min = INT_MAX, val;
                for (i = start; i < stop; i++) {
                    val = *((double *)gaccessorGetValue (accessor, i));
                    max = vMAX(max, val);
                    min = vMIN(min, val);
                }
                gaccessorSetVectorComponentMin (accessor, 0, &min);
                gaccessorSetVectorComponentMax (accessor, 0, &max);
            } else {
                for (vector = 0; vector < accessor->vectorComponentCount; 
                     vector++) {
                    double max = INT_MIN, min = INT_MAX, val;
                    for (i = start; i < stop; i++) {
                        val = *((double *)gaccessorGetVectorValue
                                (accessor, i, vector));
                        max = vMAX(max, val);
                        min = vMIN(max, val);
                        gaccessorSetVectorComponentMin (accessor, i, &min);
                        gaccessorSetVectorComponentMax (accessor, i, &max);
                    }
                }
            }
            break;
        }

        case gaccessorDATE: {
#if vdebugDEBUG
            vexGenerate (vexGetModuleUnimplementedClass(),
                         vexPROC_NAME, "_gaccessorCalcRanges",
                         vexMESSAGE,
                         "rangeCalc for data values not implemented yet.",
                         vexNULL);
#endif            
            break;
        }

        default: {
#if vdebugDEBUG
            vexGenerate (vexGetModuleClass(),
                         vexPROC_NAME, "_gaccessorCalcRanges",
                         vexMESSAGE,
                         "unknown value type for accessor",
                         vexNULL);
#endif            
        }
    }
    
} /* _gaccessorCalcRanges */




/* _gaccessorSetSubset -- tell the accessor to only pay attention to a
 *			  (contiguous) range of values.
 *
 *  -> accessor  -- the accessor to indicate the subset for.
 *  -> lowBound  -- the index for the start of the subset
 *  -> highBound -- the index one past the end of the subset.
 *
 * i.e. if you wanted indices 5,6,7,8,9 to be a subset, you
 *      do a gaccessorSetSubset (spam, 5, 10);
 */
static void _gaccessorSetSubset (gaccessor *accessor, 
                                 int lowBound, int highBound)
{
    if (   (accessor->lowBound != lowBound)
        || (accessor->highBound != highBound)) {

        
        if (   (lowBound == gaccessorUNDEFINED)
            || (highBound == gaccessorUNDEFINED)) {
            accessor->lowBound = gaccessorUNDEFINED;
            accessor->highBound = gaccessorUNDEFINED;
        } else {
            if ((highBound - lowBound) > accessor->indexCount) {
#if vdebugDEBUG
                vexGenerate (vexGetArgRangeClass (),
                             vexPROC_NAME, "_gaccessorSetSubet",
                             vexMESSAGE,
                             "Size of indicated subset exceeds total index count",
                             vexNULL);
#endif
            }
            
            accessor->lowBound = lowBound;
            accessor->highBound = highBound;
            gaccessorNotify (accessor, gaccessorSUBSET_CHANGE);
        }
    }

} /* _gaccessorSetSubset */




/*
 * ----- Object-level duties 
 */


/* _gaccessorLowInit -- shared intialization code between the INIT and 
 *			LOAD_INIT overrides. 
 *
 *  -> accessor -- the accessor to initialize
 */
static void _gaccessorLowInit (gaccessor *accessor)
{
    accessor->valueType = gaccessorUNDEFINED;
    accessor->indexType = gaccessorUNDEFINED;
    accessor->ranges = vmemAlloc(sizeof(gaccessorRange));
    accessor->notify = (gaccessorNoteProc) NULL;
    accessor->indexCount = gaccessorUNDEFINED;
    accessor->vectorComponentCount = 1;
    accessor->lowBound = gaccessorUNDEFINED;
    accessor->highBound = gaccessorUNDEFINED;

} /* _gaccessorLowInit */




/* _gaccessorInit -- initalize an accessor object.
 *
 *  -> accessor -- the accessor to initialize
 */
static void _gaccessorInit (gaccessor *accessor)
{
    vclassSendSuper (defaultClass, vobjectINIT, (accessor));
    _gaccessorLowInit (accessor);
} /* _gaccessorInit */




/* _gaccessorLoadInit -- initialize an accessor object based on a resource
 *			 template
 *
 *  -> accessor -- the accessor to initialize
 *  -> resource -- the resource template to use as a guide
 */
static void _gaccessorLoadInit (gaccessor *accessor, vresource resource)
{
    vclassSendSuper (defaultClass, vobjectLOAD_INIT, (accessor, resource));
    _gaccessorLowInit (accessor);
} /* _gaccessorLoadInit */




/* _gaccessorDestroy -- clean up any mess we may have made
 *
 *  -> accessor -- the accessor preparing to meet its maker
 */
static void _gaccessorDestroy (gaccessor *accessor)
{
    if (accessor->ranges != NULL) {
        vmemFree (accessor->ranges);
    }

    vclassSendSuper (defaultClass, vobjectDESTROY, (accessor));

} /* _gaccessorDestroy */




/*
 * ----- Managerial duties
 */


#if vdebugDEBUG

/* _gaccessorValType -- maps the type to a human-readable char* string
 *
 *  -> type -- the type to map
 * <-	    -- human readable translation
 */
static char *_gaccessorValType (int type)
{
    char *ret;

    switch (type) {
        case gaccessorUNDEFINED: {
            ret = "Undefined";
            break;
        }

        case gaccessorINTEGER: {
            ret = "Integer";
            break;
        }

        case gaccessorDOUBLE: {
            ret = "Double";
            break;
        }

        case gaccessorDATE: {
            ret = "Date";
            break;
        }

        default: {
            ret = "Unknown";
            break;
        }
    }

    return (ret);

} /* _gaccessorValType */

#endif




/* gaccessorDump -- dumps human-readable debugging information to a particular
 *		    stream.
 *
 *  -> accessor -- the accessor to dump
 *  -> stream   -- the stream to dump it into
 */
void gaccessorDump (gaccessor *accessor, FILE *stream)
{
#if vdebugDEBUG

    if (stream == NULL) {
        stream = vdebugGetInfoStream ();
    }

    fprintf (stream, "accessor: %p (%s)\n", accessor, 
             (gaccessorGetTag(accessor) == NULL) 
             ? "no tag"
             : (char*)gaccessorGetTag(accessor));
    fprintf (stream, "   valueType: %d (%s)\n", 
             accessor->valueType, _gaccessorValType(accessor->valueType));
    fprintf (stream, "   indexType: %d (%s)\n", 
             accessor->indexType, _gaccessorValType(accessor->indexType));
    fprintf (stream, "   ranges: %p\n", accessor->ranges);
    fprintf (stream, "   notify: %p\n", accessor->notify);
    fprintf (stream, "   indexCount: %d\n", accessor->indexCount);
    fprintf (stream, "   vectorComponentCount: %d\n", 
             accessor->vectorComponentCount);
    fprintf (stream, "   lowBound: %d\n", accessor->lowBound);
    fprintf (stream, "   highBound: %d\n", accessor->highBound);

#endif

} /* gaccessrDump */




/* gaccessorGetDefaultClass -- Returns the class used to create new instances
 *			       of gaccessor objects.
 */
gaccessorClass *gaccessorGetDefaultClass (void)
{
    if (defaultClass == NULL) {

        defaultClass = vclassSpawn (vobjectGetDefaultClass(),
                                    sizeof (gaccessorClass));
        vclassSetNameScribed (defaultClass,
                              vcharScribeLiteral(_gaccessorCLASS_NAME));
        vclassSetObjectSize (defaultClass, sizeof (gaccessor));

        vclassSet (defaultClass,
                   vobjectINIT,
                   _gaccessorInit);
        
        vclassSet (defaultClass,
                   vobjectLOAD_INIT,
                   _gaccessorLoadInit);

        vclassSet (defaultClass,
                   vobjectDESTROY,
                   _gaccessorDestroy);

        vclassSet (defaultClass,
                   gaccessorSET_VALUE_TYPE,
                   _gaccessorSetValueType);

        vclassSet (defaultClass,
                   gaccessorSET_INDEX_TYPE,
                   _gaccessorSetIndexType);

        vclassSet (defaultClass,
                   gaccessorGET_VALUE,
                   _gaccessorGetValue);

        vclassSet (defaultClass,
                   gaccessorGET_VALUE_NAME,
                   _gaccessorGetValueName);
        
        vclassSet (defaultClass,
                   gaccessorSET_RANGE_MIN,
                   _gaccessorSetRangeMin);

        vclassSet (defaultClass,
                   gaccessorSET_RANGE_MAX,
                   _gaccessorSetRangeMax);

        vclassSet (defaultClass,
                   gaccessorGET_INDEX_VALUE,
                   _gaccessorGetIndexValue);

        vclassSet (defaultClass,
                   gaccessorSET_INDEX_COUNT,
                   _gaccessorSetIndexCount);

        vclassSet (defaultClass,
                   gaccessorGET_VECTOR_VALUE,
                   _gaccessorGetVectorValue);

        vclassSet (defaultClass,
                   gaccessorSET_VECTOR_COMPONENT_COUNT,
                   _gaccessorSetVectorComponentCount);

        vclassSet (defaultClass,
                   gaccessorSET_VECTOR_COMPONENT_MIN,
                   _gaccessorSetVectorComponentMin);

        vclassSet (defaultClass,
                   gaccessorSET_VECTOR_COMPONENT_MAX,
                   _gaccessorSetVectorComponentMax);

        vclassSet (defaultClass,
                   gaccessorSET_NOTIFY,
                   _gaccessorSetNotify);

        vclassSet (defaultClass,
                   gaccessorNOTIFY,
                   _gaccessorNotify);

        vclassSet (defaultClass,
                   gaccessorCALC_RANGES,
                   _gaccessorCalcRanges);

        vclassSet (defaultClass,
                   gaccessorSET_SUBSET,
                   _gaccessorSetSubset);
    }

    return (defaultClass);
} /* gaccessorGetDefaultClass */


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

