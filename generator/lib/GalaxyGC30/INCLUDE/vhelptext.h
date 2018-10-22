/* $Id: vhelptext.h,v 1.6 1997/09/11 23:13:33 robert Exp $ */

/* -----------------------------------------------------------------------
 *
 *  vhelptext.h
 *
 *  Programming interface to the vhelptext
 *
 *  (c) Copyright Visix Software
 *  All rights reserved
 *
 * -----------------------------------------------------------------------
 */

#ifndef vhelptextINCLUDED
#define vhelptextINCLUDED	1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vinstanceINCLUDED
#include vinstanceHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vscribeINCLUDED
#include vscribeHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct	vhelptext			vhelptext;
typedef struct	vhelptextClass			vhelptextClass;       
typedef struct	vhelptextTemplate		vhelptextTemplate;       

struct vhelptextTemplate {
  const char	*name;
  const char	*text;			 
};


/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * Creation/Destruction/Class Management
 */
vhelptextClass *vhelptextGetDefaultClass(void);

vhelptextClass *vhelptextGetClass(
    vhelptext		*helptext
    );

vhelptext *vhelptextCreateOfClass(
    vhelptextClass	*helptextClass
    );

vhelptext *vhelptextCreate(
   void
   );

vhelptext *vhelptextInit(
   vhelptext		*helptext
   );

vhelptext *vhelptextInitOfClass(
   vhelptext		*helptext,
   vhelptextClass	*clas
   );

vhelptext *vhelptextDestroy(
    vhelptext		*helptext
    );			

vinstance *vhelptextGetInstance(
    vhelptext	*helptext
    );

/*
 * Class specific API.
 */

void vhelptextSetString(
    vhelptext 		*helptext,			     
    const vchar		*string
    );

void vhelptextSetStringScribed(
    vhelptext 		*helptext,			     
    vscribe		*scribe
    );

const vchar *vhelptextGetString(
    vhelptext 		*helptext
    );

/*
 * Global convenience functions.
 */

vdict *vhelptextCreateDictFromTemplates(const vhelptextTemplate *templates,
					size_t count);

void vhelptextClearDict(vdict *dict);

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vhelptext {
    vinstance		  instance;
    unsigned short        flags;
    const vchar		 *string;
};

#define vhelptextCLASS(SUPER, HELPTEXT)			        	\
    vinstanceCLASS(SUPER, HELPTEXT);				        \
    vclassMETHOD(vhelptextSET_STRING_SCRIBED,			        \
		 (HELPTEXT *helptext, vscribe *scribe))	       

struct vhelptextClass {
    vhelptextCLASS(vhelptextClass, vhelptext);
};

/*
 * Flag values.
 */
enum 
{
    _vhelptextSTRING_OWNED = 0x0001
};

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */
#define vhelptextGetInstance(t)     vportBASE_OBJECT((t), instance)
#define vhelptextGetClass(t)						\
    ((vhelptextClass*)vinstanceGetClass(vhelptextGetInstance(t)))
#define vhelptextCreateOfClass(c) 					\
    ((vhelptext *)vinstanceCreateOfClass((vinstanceClass*)(c)))
#define vhelptextInitOfClass(t, c) 					\
    vinstanceInitOfClass(vhelptextGetInstance(t), (vinstanceClass*)(c))
#define vhelptextCreate() 						\
    vhelptextCreateOfClass(vhelptextGetDefaultClass())
#define vhelptextInit(t)						\
    vhelptextInitOfClass((t), vhelptextGetDefaultClass())
#define vhelptextDestroy(t) 						\
    vinstanceDestroy(vhelptextGetInstance(t))

#define vhelptextGetString(t)	 ((t)->string)
#define vhelptextSetString(t, s) vhelptextSetStringScribed((t), vcharScribe(s))

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vhelptextSetStringScribed(r, s)					\
    vclassSend(vhelptextGetClass(r), vhelptextSET_STRING_SCRIBED, (r, s))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vhelptextINCLUDED */
