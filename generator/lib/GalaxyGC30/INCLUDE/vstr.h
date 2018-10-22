/* $Id: vstr.h,v 1.40 1994/02/19 23:34:05 chad Exp $ */

/******************************************
 * vstr.h
 * 
 * Dynamic string header file for String Manager
 * 
 * Part of Galaxy Application Environment
 *
 * Copyright (C) 1992-1993 Visix Software Inc.
 * All rights reserved.
 ******************************************/

#ifndef vstrINCLUDED
#define vstrINCLUDED 1

/*
 * Include any other files this header depends upon
 */

#ifndef  vportINCLUDED			/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vsystypesINCLUDED		/* for size_t */
#include vsystypesHEADER
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


vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * * * * * Types * * * * * * * * * * * * * *
 */

typedef vchar vstr;

/*
 * * * * * * * * * * * * * Function Prototypes * * * * * * * * * * * * * *
 */

vstr *vstrCreate(
    void
    );

vstr *vstrCreateSized(
    size_t  	    	    	length
    );
void vstrDestroy(
    vstr    	    	    	*string
    );

size_t vstrGetSize(
    const vstr 	    	    	*string
    );

vstr *vstrSetSize(
    vstr    	    	    	*string,
    size_t  	    	    	newSize
    );

vstr *vstrSetSizeMangle(
    vstr    	    	    	*string,
    size_t  	    	    	newSize
    );

vstr *vstrClone(
    const vchar     	    	*string
    );

vstr *vstrCloneScribed(
    vscribe 	    	    	*scribe
    );

vstr *vstrCopy(
    const vchar     	    	*source,
    vstr    	    	    	*dest
    );

vstr *vstrCopyScribed(
    vscribe 	    	    	*scribe,
    vstr    	    	    	*dest
    );

vstr *vstrCopyMulti(
    const vchar     	    	*string1,
    ... /* , 	    	    	    	*/
    /* NULL, 	    	    	    	*/
    /* vstr 	    	    	*dest   */
    );
vstr *vstrCopyMultiScribed(
    vscribe *scribe1, 
    ... /* , 	    	    	    	*/
    /* NULL,	    	    	    	*/
    /* vstr 	    	    	*dest	*/
    );

vstr *vstrAppend(
    vstr    	    	    	*string,
    const vchar     	    	*appendString
    );

vstr *vstrAppendScribed(
    vstr    	    	    	*string,
    vscribe 	    	    	*appendString
    );

vstr *vstrConcatenate(
    vstr    	    	    	*string,
    const vchar     	    	*concatenateString
    );

vstr *vstrConcatenateScribed(
    vstr    	    	    	*string,
    vscribe 	    	    	*concatenateScribe
    );

vscribe *vstrScribe(
    vstr    	    	    	*string
    );

#if vdebugDEBUG

vstr *vstrCreateDebug(
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vstr *vstrCreateSizedDebug(
    size_t  	    	    	size, 
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vstr *vstrSetSizeDebug(
    vstr    	    	    	*string,
    size_t  	    	    	newSize,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vstr *vstrSetSizeMangleDebug(
    vstr    	    	    	*string,
    size_t  	    	    	newSize,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vstr *vstrCloneDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vstr *vstrCloneScribedDebug(
    vscribe 	    	    	*scribe,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vstr *vstrCopyDebug(
    const vchar     	    	*source,
    vstr    	    	    	*dest,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vstr *vstrCopyScribedDebug(
    vscribe 	    	    	*scribe,
    vstr    	    	    	*dest,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vstr *vstrAppendDebug(
    vstr    	    	    	*dest,
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vstr *vstrAppendScribedDebug(
    vstr    	    	    	*dest,
    vscribe 	    	    	*scribe,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vstr *vstrConcatenateDebug(
    vstr    	    	    	*dest,
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );
vstr *vstrConcatenateScribedDebug(
    vstr    	    	    	*dest,
    vscribe 	    	    	*scribe,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

#endif

/*
 * * * * * * * * * * * * * * * Function MACROs * * * * * * * * * * * * * * *
 */

#if vdebugDEBUG


#define vstrCreate() \
    vstrCreateDebug(vmemTAG, __FILE__, __LINE__)
#define vstrCreateSized(n) \
    vstrCreateSizedDebug((n), vmemTAG, __FILE__, __LINE__)

#define vstrSetSize(s,n) \
    vstrSetSizeDebug((s), (n), vmemTAG, __FILE__, __LINE__)
#define vstrSetSizeMangle(s,n) \
    vstrSetSizeMangleDebug((s), (n), vmemTAG, __FILE__, __LINE__)
	
#define vstrClone(s) \
    vstrCloneDebug((s), vmemTAG, __FILE__, __LINE__)
#define vstrCloneScribed(s) \
    vstrCloneScribedDebug((s), vmemTAG, __FILE__, __LINE__)

#define vstrCopy(s,d) \
    vstrCopyDebug((s), (d), vmemTAG, __FILE__, __LINE__)
#define vstrCopyScribed(s,d) \
    vstrCopyScribedDebug((s), (d), vmemTAG, __FILE__, __LINE__)

#define vstrAppend(d,s) \
    vstrAppendDebug((d), (s), vmemTAG, __FILE__, __LINE__)
#define vstrAppendScribed(d,s) \
    vstrAppendScribedDebug((d), (s), vmemTAG, __FILE__, __LINE__)

#define vstrConcatenate(d,s) \
    vstrConcatenateDebug((d), (s), vmemTAG, __FILE__, __LINE__)
#define vstrConcatenateScribed(d,s) \
    vstrConcatenateScribedDebug((d), (s), vmemTAG, __FILE__, __LINE__)


#define vstrCreateDebug(t, f, l) \
    vstrCreateSizedDebug(0, t, f, l)

#define vstrCopyDebug(_s, _d, t, f, l) \
    vstrCopyScribedDebug(vcharScribe(_s), (_d), t, f, l)
#define vstrCloneDebug(_s, t, f, l) \
    vstrCopyDebug((_s), NULL, t, f, l)
#define vstrCloneScribedDebug(_s, t, f, l) \
    vstrCopyScribedDebug((_s), NULL, t, f, l)
#define vstrAppendDebug(_d, _s, t, f, l) \
    vstrAppendScribedDebug((_d), vcharScribe(_s), t, f, l)
#define vstrConcatenateDebug(_d, _s, t, f, l) \
    vstrConcatenateScribedDebug((_d), vcharScribe(_s), t, f, l)

#else

#define vstrCreate() \
    vstrCreateSized(0)

#define vstrCopy(_s, _d) \
    vstrCopyScribed(vcharScribe(_s), (_d))
#define vstrClone(_s) \
    vstrCopy((_s), NULL)
#define vstrCloneScribed(_s) \
    vstrCopyScribed((_s), NULL)
#define vstrAppend(_d, _s) \
    vstrAppendScribed((_d), vcharScribe(_s))
#define vstrConcatenate(_d, _s) \
    vstrConcatenateScribed((_d), vcharScribe(_s))

#endif

vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vstrINCLUDED */
    
