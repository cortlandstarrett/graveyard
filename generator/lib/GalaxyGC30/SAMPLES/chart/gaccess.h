/* $Id: gaccess.h,v 1.2 1993/11/30 19:35:28 markd Exp $ */
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

/* gaccess.h -- Interface to the charting package data set accessor objects.
 *
 * Module:
 *	gaccessor
 *
 * Description:
 * 	See file chart.c for more comments about this whole project.
 *
 *	This module is homage to the truism 
 *	"Any problem can be solved with an added layer of abstraction."
 *
 *	gaccessors are an abstract way of accessing data in an array-like
 *	structure.  Users of array data will want to go through accessors so
 *	clients can have whatever representation they want underneath it.
 *
 *	You may be thinking "why this accessor stuff?  vlist does the same
 *	sort of thing, and much more!"
 *	It's that "much more" which is of question -- array accessors just
 *	don't need things like selections and swap/move/insert operations.
 *	The overhead that vlist entails isn't wanted.
 *	Also, vlist doesn't have convenient way of storing/getting scalar
 *	values -- it just thinks in pointers.
 *	Although, if I were to re-write this, I'd probably use vlists anyway
 *	and layer the api on top of it, since it does provide observers, which
 *	are much nicer than the bogus notify in here.
 *
 *	These accessors live in a basically 1-D world, with an extra dimension
 *	of auxilliary information, like data point labels, triple-values
 *	for high-low-close type data.
 *
 *	gaccessor doesn't really provide a useful accessor, and will generate
 *	exceptions if you try to get values from it.  It's necessary to 
 *	subclass (or use a pre-written subclass) to get useful work out of 
 *	this.
 *
 *	In general, values you get back will be pointers to the appropriate
 *	data type.  The value pointed to is valid until the next value
 *	accessing.  It's best to stache these values into local vars
 *	once you get them. (vdate pointers are exempt from this)
 *
 * Exported Functions:
 *	(current data types are integers, doubles, and dates)
 *
 *	gaccessorSetValueType -- Sets the data type for values the accessor
 *			         will return (Y axis)
 *	gaccessorSetIndexType -- Sets the data of the index values (X axis) 
 *	gaccessorGetValueType -- Get the value data type
 *	gaccessorGetIndexType -- Get the index data type
 *	
 *	gaccessorGetValue  -- Returns the value for a given index.  The value
 *			      you get back (which is a pointer) is only valid
 *			      until the next call to gaccessorGetValue.
 *	gaccessorGetValueName -- Returns the name for a given index.  Usually
 *				 used to label individual points in a chart
 *	
 *	gaccessorSetRangeMin -- Set a minimal value for an accessor.  This
 *				value doesn't necessarily occur in the accessor
 *	gaccessorGetRangeMin -- Returns the value set in SetRangeMin
 *	gaccessorSetRangeMax -- Set a maximal value for an accessor.  This
 *				value doesn't necessarily occur in the accessor
 *	gaccessorGetRangeMax -- Returns the value set in SetRangeMax
 *	
 *	gaccessorGetIndexValue -- Returns the value at a particular index
 *	gaccessorSetIndexCount -- Set the number of data elements in the 
 *				  accessor
 *	gaccessorGetIndexCount -- Returns the number of data elements in the
 *				  accessor
 *	
 *	gaccessorGetVectorValue -- Returns the n'th value from a tuple at
 *				   a particular index.
 *	
 *	gaccessorSetVectorComponentCount -- Set the size of the vector tuple
 *	gaccessorGetVectorComponentCount -- returnthe size of the vector tuple
 *	
 *	gaccessorSetVectorComponentMin -- Set a minimal value for n'th
 *					  element of a tuple
 *	gaccessorGetVectorComponentMin -- Return what was set in 
 *					  SetVectorComponentMin
 *	
 *	gaccessorSetVectorComponentMax -- Set a maximal value for n'th element
 *					  of a tuple
 *	gaccessorGetVectorComponentMax -- Return what was set in 
 *					  SetVectorComponentMax
 *	
 *	gaccessorSetNotify -- Set the notify function for this accessor
 *	gaccessorNotify -- Call the notify function (if there is one)
 *	gaccessorGetNotify -- Return the notify function
 *	
 *	gaccessorCalcRanges -- compute the minimum and maximum values in
 *			       the accessor (taking into account subsets)
 *			       and do a SetRangeMin/Max / 
 *			       SetVectorComponenetMin/Max with it.
 *	
 *	gaccessorSetSubset -- Designate a range of index values that the
 *			      accessor should be limited to.
 *			      The range is lower...upper-1 inclusive
 *	gaccessorGetSubset -- Return the range of index values to use when
 *			      using the accessor.  Returns a value of 
 *			      gaccessorUNDEFINED if the subset hasn't been
 *			      set yet.
 *	
 *	gaccessorGetDefaultClass -- return the class to create new accessors
 *				    from
 *	gaccessorGetClass -- Returns the class of a particular accessor
 *			     object
 *	gaccessorGetObject -- Returns the object this accessor is built on
 *	
 *	gaccessorCreate -- create a new accessor
 *	gaccessorCreateOfClass -- create a new accessor from a given class
 *	gaccessorDestroy -- send an accessor to meet its maker
 *	gaccessorSetTag -- set the object tag for an accessor.  gaccessor
 *			   makes no use of it
 *	gaccessorGetTag -- returns the objet tag for an accessor.
 *	
 *	gaccessorDump -- dump human-readable debuggage info to a stream.
 *
 *
 * How to use:
 *	* initialize the class: 
 *	  (void)gaccessorGetDefaultClass ();
 *
 *	* create a new accessor
 *	  gaccessor *accessor = gaccessorCreate ();
 *
 *	* set the value and index type
 *	  gaccessorSetValueType (accessor, gaccessorDOUBLE);
 *	  gaccessorSetIndexType (accessor, gaccessorINTEGER);
 *
 *	* auto-set the min/max for the accessor
 *	  gaccessorCalcRanges (accessor);
 *
 *	* get values from the accessor:
 *	  int *indexthing;
 *	  double *valueThing;
 *	  valueThing = gaccessorGetValue (accessor, someIndex);
 *	  indexThing = gaccessorGetIndexValue (accessor, someIndex);
 *	  \* actually use it *\
 *	  ... = *valueThing ...
 *	  ... = *indexThing ...
 *
 *	* to use contiguous sub portions of the accessor:
 *	  gaccessorSetSubset (accessor, 5, 10);
 *	  makes the accessor think in terms of elements 5,6,7,8,9
 *	  gaccessorCalcRanges() takes this into account
 *
 *	* to get the subset:
 *	  int lowBound, hiBound;
 *	  gaccessorGetSubset (accessor, &lowBound, &hiBound);
 *
 */


#ifndef gaccessINCLUDED
#define gaccessINCLUDED 1

#ifndef   vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef   vclassINCLUDED
#include  vclassHEADER
#endif

#ifndef   vdateINCLUDED
#include  vdateHEADER
#endif

#ifndef   vnameINCLUDED
#include  vnameHEADER
#endif

#ifndef   vobjectINCLUDED
#include  vobjectHEADER
#endif




/*
 * ---------- Constant and macro definitions ----------
 */


/* the different supported data types */
enum {
    gaccessorUNDEFINED  = -1,
    gaccessorINTEGER    = 1,
    gaccessorDOUBLE,
    gaccessorDATE,
    gaccessorNEXT_TYPE
};

/* notification messages */
enum {
    gaccessorVALUE_CHANGE,	  /* lightweight change */
    gaccessorVECTOR_COMPONENT_COUNT_CHANGE,
    gaccessorINDEX_CHANGE,        /* something changed with indexes */
    gaccessorNAME_CHANGE,         /* something changed with names */
    gaccessorINDEX_NAME_CHANGE,   /* something changed with index names */
    gaccessorVECTOR_CHANGE,       /* something changed with the vector */
    gaccessorVECTOR_RANGE_CHANGE, /* a min/max in a range changed */
    gaccessorDATA_CHANGE,         /* catchall for heavy-weight changes */
    gaccessorSUBSET_CHANGE,
    gaccessorINDEX_TYPE_CHANGE,
    gaccessorVALUE_TYPE_CHANGE
};




/*
 * ---------- Support structure definitions ----------
 */


/* these are how the min/max value(s) of the accessor are represented */
typedef struct gaccessorIntRange {
    int		 min;
    int		 max;
} gaccessorIntRange;

typedef struct gaccessorDoubleRange {
    double	 min;
    double	 max;
} gaccessorDoubleRange;

typedef struct gaccessorDateRange {
    vdate	*min;
    vdate	*max;
} gaccessorDateRange;

typedef union gaccessorRange {
    gaccessorIntRange	  integerRange;
    gaccessorDoubleRange  doubleRange;
    gaccessorDateRange	  dateRange;
} gaccessorRange;




/*
 * ---------- Type and structure definitions ----------
 */


typedef struct gaccessor gaccessor;

typedef void (*gaccessorNoteProc) (gaccessor *accessor, int message);

struct gaccessor {
    vobject	       object;
    int		       valueType;
    int		       indexType;
    gaccessorRange    *ranges;
    gaccessorNoteProc  notify;
    int		       indexCount;
    int		       vectorComponentCount;
    int		       lowBound, highBound; /* subset */
};


#define gaccessorCLASS(SUPER, ACC, NOTIFY)				\
vobjectCLASS (SUPER, ACC); 						\
vclassMETHOD     (gaccessorSET_VALUE_TYPE,				\
                  (ACC *accessor, int type)); 				\
vclassMETHOD     (gaccessorSET_INDEX_TYPE,				\
                  (ACC *accessor, int type)); 				\
\
vclassMETHOD_RET (gaccessorGET_VALUE, void *, 				\
                  (ACC *accessor, int index)); 				\
vclassMETHOD_RET (gaccessorGET_VALUE_NAME, vchar *, 			\
                  (ACC *accessor, int index)); 				\
\
vclassMETHOD     (gaccessorSET_RANGE_MIN,				\
                  (ACC *accessor, void *min));				\
vclassMETHOD     (gaccessorSET_RANGE_MAX,				\
                  (ACC *accessor, void *max));				\
\
vclassMETHOD_RET (gaccessorGET_INDEX_VALUE, void *,  			\
                  (ACC *accessor, int index)); 				\
vclassMETHOD     (gaccessorSET_INDEX_COUNT,				\
                  (ACC *accessor, int indexCount));			\
\
vclassMETHOD_RET (gaccessorGET_VECTOR_VALUE, void *, 			\
                  (ACC *accessor, int index, int vectorPosition)); 	\
vclassMETHOD     (gaccessorSET_VECTOR_COMPONENT_COUNT,			\
                  (ACC *accessor, int componentCount));			\
vclassMETHOD     (gaccessorSET_VECTOR_COMPONENT_MIN,			\
                  (ACC *accessor, int vectorPosition, void *min));	\
vclassMETHOD     (gaccessorSET_VECTOR_COMPONENT_MAX,			\
                  (ACC *accessor, int vectorPosition, void *max));	\
\
vclassMETHOD     (gaccessorSET_NOTIFY,					\
                  (ACC *accessor, NOTIFY notify));			\
vclassMETHOD	 (gaccessorNOTIFY,					\
                  (ACC *accessor, int message));			\
\
vclassMETHOD     (gaccessorCALC_RANGES,					\
                  (ACC *accessor));					\
\
vclassMETHOD	 (gaccessorSET_SUBSET,					\
                  (ACC *accessor, int lowBound, int highBound))


typedef struct gaccessorClass gaccessorClass;


struct gaccessorClass {
    gaccessorCLASS (gaccessorClass, gaccessor, gaccessorNoteProc);
};



/*
 * ---------- Module Prototypes ----------
 */


void gaccessorSetValueType (gaccessor *accessor, int type);
void gaccessorSetIndexType (gaccessor *accessor, int type);
int gaccessorGetValueType (gaccessor *accessor);
int gaccessorGetIndexType (gaccessor *accessor);

void *gaccessorGetValue (gaccessor *accessor, int index);
vchar *gaccessorGetValueName (gaccessor *accessor, int index);

void gaccessorSetRangeMin (gaccessor *accessor, void *min);
void *gaccessorGetRangeMin (gaccessor *accessor);
void gaccessorSetRangeMax (gaccessor *accessor, void *max);
void *gaccessorGetRangeMax (gaccessor *accessor);

void *gaccessorGetIndexValue (gaccessor *accessor, int index);
void gaccessorSetIndexCount (gaccessor *accessor, int indexCount);
int gaccessorGetIndexCount (gaccessor *accessor);


void *gaccessorGetVectorValue (gaccessor *accessor, int index,
                               int vectorPosition);
void gaccessorSetVectorComponentCount (gaccessor *accessor, int count);
int gaccessorGetVectorComponentCount (gaccessor *accessor);

void gaccessorSetVectorComponentMin (gaccessor *accessor,
                                     int vectorPosition, void *min);
void *gaccessorGetVectorComponentMin (gaccessor *accessor, 
                                       int vectorPosition);
void gaccessorSetVectorComponentMax (gaccessor *accessor,
                                     int vectorPosition, void *max);
void *gaccessorGetVectorComponentMax (gaccessor *accessor,
                                       int vectorPosition);

void gaccessorSetNotify (gaccessor *accessor, gaccessorNoteProc notify);
void gaccessorNotify (gaccessor *accessor, int message);
gaccessorNoteProc gaccessorGetNotify (gaccessor *accessor);

void gaccessorCalcRanges (gaccessor *accessor);

/* lowBound is inclusive, highBound isn't. If you wanted 10 elements,
 * lowBound would be 0, highBound would be 10. */
void gaccessorSetSubset (gaccessor *accessor, int lowBound, int highBound);
void gaccessorGetSubset (gaccessor *accessor, int *lowBound, int *highBound);

gaccessorClass *gaccessorGetDefaultClass (void);
gaccessorClass *gaccessorGetClass (gaccessor *accessor);

vobject *gaccessorGetObject (gaccessor *accessor);

gaccessor *gaccessorCreate (void);
gaccessor *gaccessorCreateOfClass (gaccessorClass *clas);
void gaccessorDestroy (gaccessor *accessor);
void gaccessorSetTag (gaccessor *accessor, const vname *tag);
const vname *gaccessorGetTag (gaccessor *accessor);

void gaccessorDump (gaccessor *accessor, FILE *stream);




/*
 * ---------- Functions defined as #define defines ----------
 */

#define gaccessorGetValueType(a)	((a)->valueType)
#define gaccessorGetIndexType(a)	((a)->indexType)

#define gaccessorGetRangeMin(a) (gaccessorGetVectorComponentMin(a,0))
#define gaccessorGetRangeMax(a) (gaccessorGetVectorComponentMax(a,0))

#define gaccessorGetIndexCount(a) ((a)->indexCount)
#define gaccessorGetVectorComponentCount(a) ((a)->vectorComponentCount)
#define gaccessorGetNotify(a)	  ((a)->notify)
#define gaccessorGetSubset(a,l,h) do { *(l) = (a)->lowBound; \
                                       *(h) = (a)->highBound; } while (0)

#define gaccessorGetObject(a)		( &((a)->object) )

#define gaccessorCreate()    gaccessorCreateOfClass(gaccessorGetDefaultClass())
#define gaccessorCreateOfClass(c) ((gaccessor*)vobjectCreateOfClass \
                                   ((vobjectClass*)(c)))

#define gaccessorDestroy(a)     vobjectDestroy(gaccessorGetObject((a)))
#define gaccessorSetTag(a,t)	vobjectSetTag(gaccessorGetObject((a)),(t))
#define gaccessorGetTag(a)	vobjectGetTag(gaccessorGetObject((a)))

#define gaccessorGetClass(a)	( (gaccessorClass*)vobjectGetClass \
                                 (gaccessorGetObject((a)))  )
#define gaccessorSend(o,s,a)	vclassSend(gaccessorGetClass((o)), s, a)




/*
 * ---------- Functions implemented by messages ----------
 */


#define gaccessorSetValueType(a,t) \
	gaccessorSend ((a), gaccessorSET_VALUE_TYPE, (a,t))

#define gaccessorSetIndexType(a,t) \
	gaccessorSend ((a), gaccessorSET_INDEX_TYPE, (a,t))

#define gaccessorGetValue(a,i) \
	gaccessorSend ((a), gaccessorGET_VALUE, (a,i))

#define gaccessorGetValueName(a,i) \
	gaccessorSend ((a), gaccessorGET_VALUE_NAME, (a,i))

#define gaccessorSetRangeMin(a,m) \
	gaccessorSend ((a), gaccessorSET_RANGE_MIN, (a,m))

#define gaccessorSetRangeMax(a,m) \
	gaccessorSend ((a), gaccessorSET_RANGE_MAX, (a,m))

#define gaccessorGetIndexValue(a,i) \
	gaccessorSend ((a), gaccessorGET_INDEX_VALUE, (a,i))

#define gaccessorSetIndexCount(a,c) \
	gaccessorSend ((a), gaccessorSET_INDEX_COUNT, (a,c))

#define gaccessorGetVectorValue(a,i,vp) \
	gaccessorSend ((a), gaccessorGET_VECTOR_VALUE, (a,i,vp))

#define gaccessorSetVectorComponentCount(a,c) \
	gaccessorSend ((a), gaccessorSET_VECTOR_COMPONENT_COUNT, (a,c))

#define gaccessorSetVectorComponentMin(a,p,m) \
	gaccessorSend ((a), gaccessorSET_VECTOR_COMPONENT_MIN, (a,p,m))

#define gaccessorSetVectorComponentMax(a,p,m) \
	gaccessorSend ((a), gaccessorSET_VECTOR_COMPONENT_MAX, (a,p,m))

#define gaccessorSetNotify(a,n) \
	gaccessorSend ((a), gaccessorSET_NOTIFY, (a,n))

#define gaccessorNotify(a,m) \
	gaccessorSend ((a), gaccessorNOTIFY, (a,m))

#define gaccessorCalcRanges(a) \
	gaccessorSend ((a), gaccessorCALC_RANGES, (a))

#define gaccessorSetSubset(a,lb,hb) \
	gaccessorSend ((a), gaccessorSET_SUBSET, (a,lb,hb))

#endif /* gaccessINCLUDED */


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
