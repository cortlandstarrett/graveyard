/* $Id: vtextmarker.h,v 1.1 1996/09/27 02:01:53 robert Exp $ */

/************************************************************

    vtextmarker.h
    C Interface to the Text Manager's marker module

    (c) Copyright Visix Software  1991
    All rights reserved

************************************************************/

#ifndef vtextmarkerINCLUDED
#define vtextmarkerINCLUDED 1

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstdINCLUDED		/* for vbool, vbyte */
#include vstdHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vobservableINCLUDED
#include vobservableHEADER
#endif

#ifndef  vtextINCLUDED
#include vtextHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vtextmarker		vtextmarker;
typedef struct vtextmarkerClass	  	vtextmarkerClass;

typedef struct vtextmarkerIterator	vtextmarkerIterator;
typedef struct vtextmarkerIteratorClass	vtextmarkerIteratorClass;

typedef struct vtextmarkerTransitionIterator
					vtextmarkerTransitionIterator;
typedef struct vtextmarkerTransitionIteratorClass
					vtextmarkerTransitionIteratorClass;

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vtextmarkerStartup(void);


vtextmarkerClass *vtextmarkerGetDefaultClass(
    void
    );

vtextmarkerClass *vtextmarkerGetClass(
    vtextmarker		*marker
    );

vobservable *vtextmarkerGetObservable(
    vtextmarker		*marker
    );

vloadable *vtextmarkerGetLoadable(
    vtextmarker		*marker
    );

vinstance *vtextmarkerGetInstance(
    vtextmarker		*marker
    );

vtextmarker *vtextmarkerCreate(
    void
    );

vtextmarker *vtextmarkerCreateOfClass(
    vtextmarkerClass	*clas
    );

void vtextmarkerInit(
    vtextmarker		*marker
    );

void vtextmarkerInitOfClass(
    vtextmarker		*marker,
    vtextmarkerClass	*clas
    );

void vtextmarkerDestroy(
    vtextmarker		*marker
    );

vtextmarker *vtextmarkerClone(
    vtextmarker 	*marker
    );

void vtextmarkerCopyInit(
    vtextmarker 	*source,
    vtextmarker 	*destination
    );

void vtextmarkerCopy(
    vtextmarker 	*source,
    vtextmarker 	*destination
    );

vtextmarker *vtextmarkerLoad(
    vresource		 resource
    );

void vtextmarkerLoadInit(
    vtextmarker 	*marker,
    vresource		 resource
    );

void vtextmarkerStore(
    vtextmarker 	*marker,
    vresource		 resource
    );

void vtextmarkerDump(
    vtextmarker 	*marker,
    FILE 		*stream
    );

vtextTag *vtextmarkerGetTextTag(
    vtextmarker		*marker
    );

void vtextmarkerSetText(
    vtextmarker		*marker,
    vtext		*text
    );

vtext *vtextmarkerGetText(
    vtextmarker		*marker
    );

void vtextmarkerSetFixed(
    vtextmarker 	*marker,
    int			 isFixed
    );

vbool vtextmarkerIsFixed(
    vtextmarker 	*marker
    );

void vtextmarkerSetRange(
    vtextmarker 	*marker,
    long		 start,
    long		 end
    );    

long vtextmarkerGetStart(
    vtextmarker		*marker
    );

long vtextmarkerGetEnd(
    vtextmarker		*marker
    );

/*
 * Marker Iterator
 */

vtextmarkerIteratorClass *vtextmarkerGetDefaultIteratorClass(
    void
    );

void vtextmarkerInitIterator(
    vtextmarkerIterator	*iterator,
    vtextselection	*selection
    );

int vtextmarkerNextIterator(
    vtextmarkerIterator	*iterator
    );

void vtextmarkerDestroyIterator(
    vtextmarkerIterator	*iterator
    );

vtextmarker *vtextmarkerGetIteratorMarker(
    vtextmarkerIterator	*iterator
    );

vtextRuler *vtextmarkerGetIteratorRuler(
    vtextmarkerIterator	*iterator
    );

vtextStyle *vtextmarkerGetIteratorStyle(
    vtextmarkerIterator	*iterator
    );


/*
 * Marker Transition Iterator
 */

vtextmarkerTransitionIteratorClass
				*vtextmarkerGetDefaultTransitionIteratorClass(
    void
    );

void vtextmarkerInitTransitionIterator(
    vtextmarkerTransitionIterator	*iterator,
    vtextselection	*selection
    );

int vtextmarkerNextTransitionIterator(
    vtextmarkerTransitionIterator	*iterator
    );

void vtextmarkerDestroyTransitionIterator(
    vtextmarkerTransitionIterator	*iterator
    );

long vtextmarkerGetTransitionIteratorPosition(
    vtextmarkerTransitionIterator	*iterator
    );

vtextselection *vtextmarkerGetTransitionIteratorSelection(
    vtextmarkerTransitionIterator	*iterator
    );


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vtextmarker {
    vobservable		 super;

    vtextTag		 tag;
    vtext		*text;
};

#define vtextmarkerCLASS(CLASS, MARKER)				\
    vobservableCLASS(CLASS, MARKER)

struct vtextmarkerClass
{
  vtextmarkerCLASS(vtextmarkerClass, vtextmarker);
};


struct vtextmarkerIterator {
    viterator		 iterator;

    vtext		*text;
    long		 start;
    long        	 end;
    vtextTagIterator     tagIterator;

    vtextmarker 	*temp;

    vtextmarker 	*current;
    vtextRuler		*ruler;
    vtextStyle		*style;
};

#define vtextmarkerITERATOR_CLASS(CLASS, ITERATOR)			\
    viteratorCLASS(CLASS, ITERATOR)

struct vtextmarkerIteratorClass
{
  vtextmarkerITERATOR_CLASS(vtextmarkerIteratorClass, vtextmarkerIterator);
};


struct vtextmarkerTransitionIterator {
    viterator			 iterator;

    vtext			*text;
    long			 start;
    long        		 end;
    vtextTagTransitionIterator   transIterator;

    long			 pos;
    vtextselection	 	*sel;
};

#define vtextmarkerTRANSITION_ITERATOR_CLASS(CLASS, ITERATOR)		\
    viteratorCLASS(CLASS, ITERATOR)

struct vtextmarkerTransitionIteratorClass
{
  vtextmarkerTRANSITION_ITERATOR_CLASS(vtextmarkerTransitionIteratorClass,
				       vtextmarkerTransitionIterator);
};


/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vtextmarkerGetObservable(s)	vportBASE_OBJECT(s, super)
#define vtextmarkerGetLoadable(s) \
    vobservableGetLoadable(vtextmarkerGetObservable(s))
#define vtextmarkerGetInstance(s) \
    vloadableGetInstance(vtextmarkerGetLoadable(s))
#define vtextmarkerGetClass(s) \
    ((vtextmarkerClass*)vloadableGetClass(vtextmarkerGetLoadable(s)))

#define vtextmarkerCreateOfClass(c) \
    ((vtextmarker *) vloadableCreateOfClass((vloadableClass *)(c)))
#define vtextmarkerCreate() \
    vtextmarkerCreateOfClass(vtextmarkerGetDefaultClass())
#define vtextmarkerInitOfClass(s,c) \
    vloadableInitOfClass(vtextmarkerGetLoadable(s), (vloadableClass *)(c))
#define vtextmarkerInit(s) \
    vtextmarkerInitOfClass((s), vtextmarkerGetDefaultClass())
#define vtextmarkerDestroy(s) \
    vloadableDestroy(vtextmarkerGetLoadable(s))

#define vtextmarkerClone(s) \
    ((vtextmarker *) vloadableClone(vtextmarkerGetLoadable(s)))
#define vtextmarkerCopy(s,t) \
    vloadableCopy(vtextmarkerGetLoadable(s), vtextmarkerGetLoadable(t))
#define vtextmarkerCopyInit(s,t) \
    vloadableCopyInitOfSubclass(vtextmarkerGetLoadable(s), \
				vtextmarkerGetLoadable(t), \
			(vloadableClass *) vtextmarkerGetDefaultClass())

#define vtextmarkerLoad(r) \
    ((vtextmarker *) vloadableLoadOfSubclass(r, \
			(vloadableClass *) vtextmarkerGetDefaultClass()))
#define vtextmarkerLoadInit(s,r) \
    vloadableLoadInitOfSubclass(vtextmarkerGetLoadable(s), (r), \
			(vloadableClass *) vtextmarkerGetDefaultClass())
#define vtextmarkerStore(s,r) \
    vloadableStore(vtextmarkerGetLoadable(s), (r))

#define vtextmarkerDump(s,f) \
    vloadableDump(vtextmarkerGetLoadable(s), (f))

#define vtextmarkerGetTextTag(m) \
    (&(m)->tag)
#define vtextmarkerSetFixed(m,f) \
    vtextSetTagFixed(&(m)->tag, f)
#define vtextmarkerIsFixed(m) \
    vtextIsTagFixed(&(m)->tag)

#define vtextmarkerSetRange(m,s,e) \
    vtextSetTagRange(&(m)->tag, s, e)
#define vtextmarkerGetStart(m) \
    vtextGetTagStart(&(m)->tag)
#define vtextmarkerGetEnd(m) \
    vtextGetTagEnd(&(m)->tag)

#define _vtextmarkerGetIteratorIterator(i) \
    vportBASE_OBJECT(i, iterator)

#define vtextmarkerNextIterator(i) \
    viteratorNext(_vtextmarkerGetIteratorIterator(i))
#define vtextmarkerDestroyIterator(i) \
    viteratorDestroy(_vtextmarkerGetIteratorIterator(i))
#define vtextmarkerGetIteratorMarker(i) \
    ((vtextmarker *) viteratorGetElement(_vtextmarkerGetIteratorIterator(i)))
#define vtextmarkerGetIteratorRuler(i) \
    ((i)->ruler)
#define vtextmarkerGetIteratorStyle(i) \
    ((i)->style)

#define _vtextmarkerGetTransitionIteratorIterator(i) \
    vportBASE_OBJECT(i, iterator)

#define vtextmarkerNextTransitionIterator(i) \
    viteratorNext(_vtextmarkerGetTransitionIteratorIterator(i))
#define vtextmarkerDestroyTransitionIterator(i) \
    viteratorDestroy(_vtextmarkerGetTransitionIteratorIterator(i))
#define vtextmarkerGetTransitionIteratorSelection(i) \
    ((vtextselection *) \
       viteratorGetElement(_vtextmarkerGetTransitionIteratorIterator(i)))
#define vtextmarkerGetTransitionIteratorPosition(i) \
    ((i)->pos)


/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */


vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vtextmarkerINCLUDED */
