/* $Id: vhelpref.h,v 1.7 1997/11/06 19:39:50 robert Exp $ */

/* -----------------------------------------------------------------------
 *
 *  vhelpref.h
 *
 *  Programming interface to the vhelpref
 *
 *  (c) Copyright Visix Software
 *  All rights reserved
 *
 * -----------------------------------------------------------------------
 */

#ifndef vhelprefINCLUDED
#define vhelprefINCLUDED	1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vinstanceINCLUDED
#include vinstanceHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vurlINCLUDED
#include vurlHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct	vhelpref			vhelpref;
typedef struct	vhelprefClass			vhelprefClass;       

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * Creation/Destruction/Class Management
 */
vhelprefClass *vhelprefGetDefaultClass(void);

vhelprefClass *vhelprefGetClass(
    vhelpref	*helpref
    );

vhelpref *vhelprefCreateOfClass(
    vhelprefClass	*helprefClass
    );

vhelpref *vhelprefCreate(
   void
   );

void vhelprefInit(
    vhelpref		*helpref
   );

vhelpref *vhelprefDestroy(
    vhelpref		*helpref
    );			

vhelpref *vhelprefInitOfClass(
   vhelpref		*helpref,
   vhelprefClass	*clas
   );

vinstance *vhelprefGetInstance(
    vhelpref		*helpref
    );

/*
 * Class specific API.
 */

void vhelprefSetNestedContextStringOwned(
    vhelpref		*helpref,
    vchar	       **context,
    int			 count
    );

void vhelprefSetNestedContextString(
    vhelpref		*helpref,
    const vchar	       **context,
    int			 count
    );

void vhelprefSetContextString(
    vhelpref		*helpref,
    const vchar		*context
    );

void vhelprefSetContextStringScribed(
    vhelpref		*helpref,
    vscribe		*context
    );

void vhelprefGetContextString(
    vhelpref		 *helpref,
    const vchar	       ***context,
    int			 *count
    );

void vhelprefSetURLOwned(
    vhelpref		*helpref,
    vurl	        *url
    );

const vurl *vhelprefGetURL(
    vhelpref		*helpref
    );
  
/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vhelpref {
    vinstance		  instance;
    unsigned short	  flags;
    vurl		 *url;
    const vchar		**context;
    int			  count;
};

#define vhelprefCLASS(SUPER, HELPREF)			        	\
    vinstanceCLASS(SUPER, HELPREF);				        \
    vclassMETHOD(vhelprefSET_NESTED_CONTEXT_STRING,		        \
		 (HELPREF *helpref, const vchar **context, int count));	\
    vclassMETHOD(vhelprefSET_NESTED_CONTEXT_STRING_OWNED,	        \
		 (HELPREF *helpref, vchar **context, int count));	\
    vclassMETHOD(vhelprefSET_CONTEXT_STRING_SCRIBED,		        \
		 (HELPREF *helpref, vscribe *context));			\
    vclassMETHOD(vhelprefSET_URL_OWNED,					\
		 (HELPREF *helpref, vurl *url))	       

struct vhelprefClass {
    vhelprefCLASS(vhelprefClass, vhelpref);
};

/*
 * Flag values.
 */
enum 
{
    _vhelprefCONTEXT_OWNED	= 0x0001,
    _vhelprefCONTEXT_VSTR	= 0x0002
};

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */
#define vhelprefGetInstance(r)		vportBASE_OBJECT((r), instance)
#define vhelprefGetClass(r)						\
    ((vhelprefClass*)vinstanceGetClass(vhelprefGetInstance(r)))
#define vhelprefCreateOfClass(r) 					\
    ((vhelpref *)vinstanceCreateOfClass((vinstanceClass*)(r)))
#define vhelprefInitOfClass(r, c) 					\
    vinstanceInitOfClass(vhelprefGetInstance(r), (vinstanceClass*)(c))
#define vhelprefCreate() 						\
    vhelprefCreateOfClass(vhelprefGetDefaultClass())
#define vhelprefInit(r)							\
    vhelprefInitOfClass(r, vhelprefGetDefaultClass())
#define vhelprefDestroy(d) 						\
    vinstanceDestroy(vhelprefGetInstance(d))

#define vhelprefGetURL(r)		(r)->url

#define vhelprefSetContextString(r, c)					\
    vhelprefSetContextStringScribed(r, vcharScribe(c))

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */
#define vhelprefSetNestedContextString(r, s, c)				\
    vclassSend(vhelprefGetClass(r), 					\
	       vhelprefSET_NESTED_CONTEXT_STRING, (r, s, c))
#define vhelprefSetNestedContextStringOwned(r, s, c)			\
    vclassSend(vhelprefGetClass(r), 					\
	       vhelprefSET_NESTED_CONTEXT_STRING_OWNED, (r, s, c))
#define vhelprefSetContextStringScribed(r, c)				\
    vclassSend(vhelprefGetClass(r), 					\
	       vhelprefSET_CONTEXT_STRING_SCRIBED, (r, c))
#define vhelprefSetURLOwned(r, s)					\
    vclassSend(vhelprefGetClass(r), 					\
	       vhelprefSET_URL_OWNED, (r, s))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vhelprefINCLUDED */

