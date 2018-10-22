/* $Id: vtimestamp.h,v 1.33 1997/10/10 21:41:07 robert Exp $ */

/************************************************************

    vtimestamp.h

    C Interface file for the Timestamp Library

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vtimestampINCLUDED
#define vtimestampINCLUDED 1

#ifndef  vportINCLUDED          /* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef  vclientINCLUDED
#include vclientHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * * * * * PUBLIC TYPES * * * * * * * * * * * * * *
 */

typedef struct vtimestamp vtimestamp;
struct vtimestamp {
    long                        sec;
    unsigned long               nsec;
};



/*
 * * * * * * * * * * * * * PUBLIC CONSTANTS * * * * * * * * * * * * * *
 */

#define vtimestampSECOND        (1000000000L)
#define vtimestampMILLISECOND   (1000000L)
#define vtimestampMICROSECOND   (1000L)


/*
 * * * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * * *
 */

void            vtimestampStartup       (void                    );

void            vtimestampInit          (vtimestamp             *timestamp);
vtimestamp      vtimestampGetNow        (void                    );
vtimestamp      vtimestampGetRecent     (void                    );
vtimestamp      vtimestampGetRaw        (void                    );

void            vtimestampSet           (vtimestamp             *timestamp,
                                         long                    seconds,
                                         unsigned long           nanoseconds);
void            vtimestampSetSeconds    (vtimestamp             *timestamp,
                                         long                    seconds);
void            vtimestampSetNanoseconds(vtimestamp             *timestamp,
                                         unsigned long           nanoseconds);

long            vtimestampGetSeconds    (vtimestamp              timestamp);
unsigned long   vtimestampGetNanoseconds(vtimestamp              timestamp);

vbool           vtimestampGreaterThan   (vtimestamp              t1,
                                         vtimestamp              t2);
vbool           vtimestampLessThan      (vtimestamp              t1,
                                         vtimestamp              t2);
vbool           vtimestampEqualTo       (vtimestamp              t1,
                                         vtimestamp              t2);

int             vtimestampCompare       (vtimestamp              t1,
                                         vtimestamp              t2);

vtimestamp      vtimestampAdd           (vtimestamp              timestamp,
                                         long                    seconds,
                                         unsigned long           nanoseconds);
vtimestamp      vtimestampSubtract      (vtimestamp              timestamp,
                                         long                    seconds,
                                         unsigned long           nanoseconds);
void            vtimestampDiffer        (vtimestamp              t1,
                                         vtimestamp              t2,
                                         long                   *seconds,
                                         unsigned long          *nanoseconds);

vbool           vtimestampValidate      (const vtimestamp        t);
void            vtimestampAssert        (const vtimestamp        t);
void            vtimestampHandledAssert (const vtimestamp        t,
                                         vdebugAssertionHandler  h,
                                         void                   *data);

/* platform specific */

vtimestamp      vtimestampFromMacTicks  (long                    ticks);
long            vtimestampToMacTicks    (vtimestamp              timestamp);

/* deprecated */

vtimestamp      vtimestampMake          (long                    seconds,
                                         unsigned long           nanoseconds);


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */


/*
 * * * * * * * * * * PRIVATE exported variables * * * * * * * * * *
 */


/*
 * * * * * * * * * * PRIVATE exported prototypes * * * * * * * * * *
 */

void            _vtimestampHandledAssert(const vtimestamp t,
                                         vdebugAssertionHandler h, void *data,
                                         const char *tag, const char *file,
                                         int line);


/*
 * * * * * * * * * * PRIVATE function macro definitions * * * * * * * * * *
 */
#define vtimestampInit(t)               ((t)->sec = 0, (t)->nsec = 0)

#define vtimestampHandledAssert(t, h, d) _vtimestampHandledAssert(t, h, d, \
                                                 vdebugTAG, __FILE__, __LINE__)

#if (vdebugDEBUG)
#define vtimestampAssert(t)             vtimestampHandledAssert((t), NULL,NULL)
#else
#define vtimestampAssert(t)             ((void)0)
#endif

#define vtimestampSet(t, s, ns)         (vtimestampAssert(*(t)), \
                                         ((t)->sec = (s)), \
                                         vdebugAssert((ns)<vtimestampSECOND), \
                                         ((t)->nsec = (ns)))
#define vtimestampSetSeconds(t, s)      (vtimestampAssert(*(t)), \
                                         ((t)->sec = (s)))
#define vtimestampSetNanoseconds(t, ns) (vtimestampAssert(*(t)), \
                                         vdebugAssert((ns)<vtimestampSECOND), \
                                         ((t)->nsec = (ns)))

#define vtimestampGetSeconds(t)         (vtimestampAssert(t), (t).sec)
#define vtimestampGetNanoseconds(t)     (vtimestampAssert(t), (t).nsec)

#define vtimestampGreaterThan(t1,t2)    (vtimestampAssert(t1), \
                                         vtimestampAssert(t2), \
                                         (t1).sec > (t2).sec || \
                                         ((t1).sec == (t2).sec && \
                                          (t1).nsec > (t2).nsec))
#define vtimestampLessThan(t1,t2)       (vtimestampAssert(t1), \
                                         vtimestampAssert(t2), \
                                         (t1).sec < (t2).sec || \
                                         ((t1).sec == (t2).sec && \
                                          (t1).nsec < (t2).nsec))
#define vtimestampEqualTo(t1,t2)        (vtimestampAssert(t1), \
                                         vtimestampAssert(t2), \
                                         (t1).sec==(t2).sec && \
                                         (t1).nsec==(t2).nsec)


vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vtimestampINCLUDED */

/*
 * Local Variables:
 * c-argdecl-indent:                4
 * c-brace-imaginary-offset:        0
 * c-brace-offset:                 -4
 * c-continued-brace-offset:        0
 * c-continued-statement-offset:    4
 * c-extra-brace-offset:            0
 * c-file-offsets:                ((block-open . -))
 * c-file-style:                   "BSD"
 * c-indent-level:                  4
 * c-label-offset:                 -4
 * indent-tabs-mode:                nil
 * tab-width:                       4
 * End:
 */

