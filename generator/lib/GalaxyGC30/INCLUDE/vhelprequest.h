/* $Id: vhelprequest.h,v 1.6 1997/09/11 23:07:52 robert Exp $ */

/* -----------------------------------------------------------------------
 *
 *  vhelrequest.h
 *
 *  Programming interface to vhelprequest
 *
 *  (c) Copyright Visix Software
 *  All rights reserved
 *
 * -----------------------------------------------------------------------
 */

#ifndef vhelprequestINCLUDED
#define vhelprequestINCLUDED	1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vloadableINCLUDED
#include vloadableHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct	vhelprequest			vhelprequest;
typedef struct	vhelprequestClass		vhelprequestClass;       

/*
 * * * * * * * * * * DEPENDENT HEADERS * * * * * * * * * *
 */ 

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * Creation/Destruction/Class Management
 */
vhelprequestClass *vhelprequestGetDefaultClass(void);

vhelprequestClass *vhelprequestGetClass(
    vhelprequest	*helprequest
    );

vhelprequest *vhelprequestCreateOfClass(
    vhelprequestClass	*helprequestClass
    );

vhelprequest *vhelprequestCreate(
   void
   );

vhelprequest *vhelprequestDestroy(
    vhelprequest	*helprequest
    );			

void vhelprequestInitOfClass(
   vhelprequest		*helprequest,
   vhelprequestClass	*clas
   );

void vhelprequestInit(
    vhelprequest	*helprequest
    );

vinstance *vhelprequestGetInstance(
    vhelprequest	*helprequest
    );


/*
 * Class specific API.
 */

void vhelprequestGetCoordinates(
    vhelprequest	*helprequest,
    int			*x,
    int			*y
    );

const vname* vhelprequestGetName(
    vhelprequest	*helprequest
    );

vobject *vhelprequestGetObject(
    vhelprequest	*helprequest
    );

vinstance *vhelprequestGetHelpData(
    vhelprequest	*helprequest
    );

void vhelprequestSetCoordinates(
    vhelprequest	*helprequest,
    int			 x,
    int			 y
    );

void vhelprequestSetName(
    vhelprequest	*helprequest,
    const vname		*name
    );

void vhelprequestSetObject(
    vhelprequest	*helprequest,
    vobject		*object
    );

void vhelprequestSetHelpData(
    vhelprequest	*helprequest,
    vinstance		*helpdata
    );

void vhelprequestSetHelpDataOwned(
    vhelprequest	*helprequest,
    vinstance		*helpdata
    );

void vhelprequestSetOneTry(
    vhelprequest	*helprequest,
    vbool		 onOff
    );

void vhelprequestSetTriedOnce(
    vhelprequest	*helprequest,
    vbool		 onOff
    );

vbool vhelprequestIsOneTry(
    vhelprequest	*helprequest
    );

vbool vhelprequestIsTriedOnce(
    vhelprequest	*helprequest
    );


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vhelprequest {
    vinstance		  instance;
    unsigned short	  flags;
    const vname		 *name;
    vobject		 *object;
    int			  x;
    int			  y;
    vinstance		 *helpdata;
};

#define vhelprequestCLASS(SUPER, REQUEST)			        \
    vinstanceCLASS(SUPER, REQUEST);				        \
    vclassMETHOD(vhelprequestSET_COORDINATES,		        	\
		 (REQUEST *helprequest, int x, int y));			\
    vclassMETHOD(vhelprequestSET_NAME,		        		\
		 (REQUEST *helprequest, const vname *name));		\
    vclassMETHOD(vhelprequestSET_HELP_DATA,	        		\
		 (REQUEST *helprequest, vinstance *instance));		\
    vclassMETHOD(vhelprequestSET_HELP_DATA_OWNED,	       		\
		 (REQUEST *helprequest, vinstance *instance));		\
    vclassMETHOD(vhelprequestSET_ONE_TRY,		        	\
		 (REQUEST *helprequest, vbool onOff));			\
    vclassMETHOD(vhelprequestSET_TRIED_ONCE,		        	\
		 (REQUEST *helprequest, vbool onOff));			\
    vclassMETHOD(vhelprequestSET_OBJECT,		        	\
		 (REQUEST *helprequest, vobject *object))
    

struct vhelprequestClass {
    vhelprequestCLASS(vhelprequestClass, vhelprequest);
};


/*
 * Flag values.
 */
enum 
{
    _vhelprequestDATA_OWNED	= 0x0001,
    _vhelprequestONE_TRY	= 0x0002,
    _vhelprequestTRIED_ONCE	= 0x0004

};


/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */
#define vhelprequestGetInstance(r)     vportBASE_OBJECT((r), instance)
#define vhelprequestGetClass(r)						\
    ((vhelprequestClass*)vinstanceGetClass(vhelprequestGetInstance(r)))
#define vhelprequestCreateOfClass(r) 					\
    ((vhelprequest *)vinstanceCreateOfClass((vinstanceClass*)(r)))
#define vhelprequestInitOfClass(r, c) 					\
    vinstanceInitOfClass(vhelprequestGetInstance(r),		 	\
      (vinstanceClass*)(c))
#define vhelprequestCreate() 						\
    vhelprequestCreateOfClass(vhelprequestGetDefaultClass())
#define vhelprequestInit(r)						\
    vhelprequestInitOfClass(r, vhelprequestGetDefaultClass())
#define vhelprequestDestroy(d) 						\
    vinstanceDestroy(vhelprequestGetInstance(d))

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */
#define vhelprequestSetCoordinates(r, x, y)				\
    vclassSend(vhelprequestGetClass(r),					\
	       vhelprequestSET_COORDINATES, (r, x, y))

#define vhelprequestSetName(r, n)					\
    vclassSend(vhelprequestGetClass(r),					\
	       vhelprequestSET_NAME, (r, n))

#define vhelprequestSetObject(r, o)					\
    vclassSend(vhelprequestGetClass(r),					\
	       vhelprequestSET_OBJECT, (r, o))

#define vhelprequestSetHelpData(r, o)					\
    vclassSend(vhelprequestGetClass(r),					\
	       vhelprequestSET_HELP_DATA, (r, o))

#define vhelprequestSetHelpDataOwned(r, o)				\
    vclassSend(vhelprequestGetClass(r),					\
	       vhelprequestSET_HELP_DATA_OWNED, (r, o))

#define vhelprequestSetTriedOnce(r, b)					\
    vclassSend(vhelprequestGetClass(r),					\
	       vhelprequestSET_TRIED_ONCE, (r, b))

#define vhelprequestSetOneTry(r, b)					\
    vclassSend(vhelprequestGetClass(r),					\
	       vhelprequestSET_ONE_TRY, (r, b))

#define vhelprequestGetName(r)		((r)->name)
#define vhelprequestGetObject(r)	((r)->object)
#define vhelprequestGetHelpData(r)	((r)->helpdata)

#define vhelprequestIsTriedOnce(r)					\
    (((r)->flags & _vhelprequestTRIED_ONCE) ? vTRUE : vFALSE)
#define vhelprequestIsOneTry(r)						\
    (((r)->flags & _vhelprequestONE_TRY) ? vTRUE : vFALSE)


vportEND_CPLUSPLUS_EXTERN_C

#endif /* vhelprequestINCLUDED */
