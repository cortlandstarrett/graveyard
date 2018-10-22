/* $Id: vdomitem.h,v 1.14 1996/06/10 22:12:47 gregt Exp $ */

/************************************************************

    vdomainitem.h
    C Interface to domain items

    Copyright Visix Software  1991
    All rights reserved

************************************************************/

#ifndef vdomainitemINCLUDED
#define vdomainitemINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vdomainviewINCLUDED
#include vdomainviewHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vdomainitem		vdomainitem;
typedef struct vdomainitemClass		vdomainitemClass;

typedef vdomain				vdomainitemDomain;

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vdomainitemStartup(void);


/* Domain Item Class Functions */

vdomainitemClass *vdomainitemGetDefaultClass(void);

vdomainClass *vdomainitemGetDefaultDomainClass(void);

/* Initialization and allocation */

vdomainitem *vdomainitemCreate(void);

vdomainitem *vdomainitemCreateOfClass(
    vdomainitemClass	*clas
    );
    
vdomainitem *vdomainitemClone(
    vdomainitem	    	*domainitem
    );

void vdomainitemCopy(
    vdomainitem    	*domainitem,
    vdomainitem	    	*targetItem
    );

void vdomainitemCopyInit(
    vdomainitem    	*domainitem,
    vdomainitem	    	*targetItem
    );

void vdomainitemInit(
    vdomainitem	    	*domainitem
    );

void vdomainitemInitOfClass(
    vdomainitem		*domainitem,
    vdomainitemClass	*clas
    );

void vdomainitemDestroy(
    vdomainitem	    	*domainitem
    );

vdomainitem *vdomainitemLoad(
    vresource		resource
    );

void vdomainitemLoadInit(
    vdomainitem		*domainitem,
    vresource		resource
    );

void vdomainitemStore(
    vdomainitem		*domainitem,
    vresource		resource
    );

/* Domain Item attribute modification */

void vdomainitemSetData(
    vdomainitem		*domainitem,
    void		*data
    );

/* Domain Item attribute access */

vdomainitemClass *vdomainitemGetClass(
    vdomainitem		*domainitem
    );

void *vdomainitemGetData(
    vdomainitem		*domainitem
    );

/* Other Routines */

vdomainview *vdomainitemGetView(
    vdomainitem		*domainitem
    );

vdomain *vdomainitemGetDomain(
    vdomainitem		*domainitem
    );


/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vdomainitem {
    vdomainview	item;
    /*   future expansion */
};

/*
 * Domain Item Class Definition
 */

#define vdomainitemCLASS(SUPER, ITEM, NOTIFY, DOMAIN)		    	      \
    vdomainviewCLASS(SUPER, ITEM, NOTIFY, DOMAIN);		   	      \
    vclassMETHOD_RET(vdomainitemCREATE_DOMAIN, vdomain *, (ITEM *domainItem))

struct vdomainitemClass {
    vdomainitemCLASS(vdomainitemClass, vdomainitem, vdialogItemNoteProc,
		     vdomain);
};


vportALIAS(vdomainitemDomain, vdomain)

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vdomainitemGetView(i)       (vportBASE_OBJECT(i, item))
#define vdomainitemGetItem(i)	    (vdomainviewGetItem(vdomainitemGetView(i)))
#define vdomainitemGetLoadable(i)	\
	(vdomainviewGetLoadable(vdomainitemGetView(i)))

#define vdomainitemCreateOfClass(c)	\
	((vdomainitem *) vdomainviewCreateOfClass((vdomainviewClass *) (c)))
#define vdomainitemInitOfClass(i,c)	\
	vdomainviewInitOfClass(vdomainitemGetView(i), (vdomainviewClass *) (c))
#define vdomainitemInit(i)	  vdomainitemInitOfClass((i), \
				       vdomainitemGetDefaultClass());
#define vdomainitemDestroy(i)	   vdomainviewDestroy(vdomainitemGetView(i))
#define vdomainitemClone(i)		\
	((vdomainitem *) vloadableCloneOfSubclass(vdomainitemGetLoadable(i),  \
			      (vloadableClass *) vdomainitemGetDefaultClass()))
#define vdomainitemCopyInit(c,t)	\
	vloadableCopyInitOfSubclass(vdomainitemGetLoadable(c),		      \
				    vdomainitemGetLoadable(t),		      \
			       (vloadableClass *) vdomainitemGetDefaultClass())
#define vdomainitemCopy(c, t)		\
	vdomainviewCopy(vdomainitemGetView(c), vdomainitemGetView(t))
#define vdomainitemLoad(r)		\
	((vdomainitem *) vloadableLoadOfSubclass(r,			      \
			      (vloadableClass *) vdomainitemGetDefaultClass()))
#define vdomainitemLoadInit(c,r)	\
	vloadableLoadInitOfSubclass(vdomainitemGetLoadable(c), r	      \
			       (vloadableClass *) vdomainitemGetDefaultClass())
#define vdomainitemStore(c, r)		\
	vdomainviewStore(vdomainitemGetView(c), r)
#define vdomainitemSetData(c, d)	\
	vdomainviewSetData(vdomainitemGetView(c), d)

#define vdomainitemGetClass(i)		\
	((vdomainitemClass *) vdomainviewGetClass(vdomainitemGetView(i)))

#define vdomainitemGetDomain(i)     vdomainviewGetDomain(vdomainitemGetView(i))

#define vdomainitemGetData(i)       vdomainviewGetData(vdomainitemGetView(i))

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

/*
 * * * * * * * * * DOMAIN ITEM GLOBAL VARIABLES * * * * * * * * * *
 */


vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vdomainitemINCLUDED */

