/* $Id: iter.c,v 1.3 1996/11/05 20:36:25 lis Exp $ */
/****************************************************************************
 *                (c) Copyright 1991-1994 Visix Software, Inc.              *
 *                           All rights reserved.                           *
 * The following Sample Code is provided for your reference purposes in     *
 * connection with your use of the Galaxy Application Environment (TM)      *
 * software product which you have licensed from Visix Software, Inc.       *
 * ("Visix"). The Sample code is provided to you without any warranty of any*
 * kind and you agree to be responsible for the use and/or incorporation    *
 * of the Sample Code into any software product you develop. You agree to   *
 * fully and completely indemnify and hold Visix harmless from any and all  *
 * loss, claim, liability or damages with respect to your use of the Sample *
 * Code.                                                                    *
 *                                                                          *
 * Subject to the foregoing, you are permitted to copy, modify, and         *
 * distribute the Sample Code for any purpose, and without fee, provided    *
 * that (i) a copyright notice in the in the form of "Copyright 1992 Visix  *
 * Software Inc., 11440 Commerce Park Drive, Reston, VA  22091. All Rights  *
 * Reserved" appears in all copies, (ii) both the copyright notice and this *
 * permission notice appear in all supporting documentation and (iii) you   *
 * are a valid licensee of The Galaxy Application Environment.              *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * Description:                                                             *
 *     This module implements a very simple iterator class. used by isnoop  *
 *     application.                                                         *
 *                                                                          *
 * Modification History:                                                    *
 *     o 12-11-93: created for galaxy 2.0 (ssmc)                            *
 *                                                                          *
 * Special Usage Notes:                                                     *
 *     o                                                                    *
 *                                                                          *
 * Text Editor Formatting:                                                  *
 *     Symantec: Tab(8), Font(Any Fixed Width)                              *
 *     Emacs: see end of file for info                                      *
 *                                                                          *
 ****************************************************************************
 */

#include <vport.h>
#include vstdioHEADER
#include vstdlibHEADER
#include vdebugHEADER
#include vexHEADER
#include vclientHEADER
#include vcharHEADER
#include vstrHEADER
#include vclassHEADER

#include "titer.h"


/* our module's debug tag */

#if (vdebugDEBUG)
static const char *const _iterTag = "titerator";
#define vdebugTAG _iterTag
#endif


/*
 *+------------------------------------------------------------------------+
 * exported exceptions
 *+------------------------------------------------------------------------+
 */
vexClass _titeratorNotAssociatedExceptionClass;
vexClass _titeratorAlreadyAssociatedExceptionClass;

#define titeratorGenerateNotAssociated(MESSAGE)			\
  {vexGenerate(&_titeratorNotAssociatedExceptionClass, 		\
	       vexMESSAGE, MESSAGE, vexERRNO, 0, vexNULL);}
#define titeratorGenerateAlreadyAssociated(MESSAGE)		\
  {vexGenerate(&_titeratorAlreadyAssociatedExceptionClass, 	\
	       vexMESSAGE, MESSAGE, vexERRNO, 0, vexNULL);}


/*
 *+------------------------------------------------------------------------+
 * private types and macros
 *+------------------------------------------------------------------------+
 */

#define AUTOINIT()	\
  {if (!_titeratorMaster || !*_titeratorMaster) startup(); }

/* one per client */
typedef struct _moduleGlobals _moduleGlobals;
struct _moduleGlobals {
  titeratorClass	*defaultClass;
  tseqiteratorClass	*defaultSeqClass;
};

#define globals()			\
  ((_moduleGlobals*)*_titeratorMaster)
#define sendsuper(_m,_a)		\
  vclassSendSuper(globals()->defaultClass, _m, _a)
#define sendsuperSeq(_m,_a)		\
  vclassSendSuper(globals()->defaultSeqClass, _m, _a)


/*
 *+------------------------------------------------------------------------+
 * private variables and routine declarations
 *+------------------------------------------------------------------------+
 */

static void	      **_titeratorMaster = NULL;
static void		startup(void);

static void		init(titerator*);
static void		copyinit(titerator*, titerator*);
static void		copy(titerator*, titerator*);

static void		binder(titerator*, const void*);
static int		more(titerator*);
static void		advance(titerator*);
static void		startover(titerator*);
static const void      *setdata(titerator*, const void*);

static int		seq_at(tseqiterator*);
static int		seq_remaining(tseqiterator*);
static int		seq_more(tseqiterator*);


/*
 *+------------------------------------------------------------------------+
 * pubes
 *+------------------------------------------------------------------------+
 */

titeratorClass*
titeratorGetDefaultClass(void)
{
  AUTOINIT();
  return globals()->defaultClass;
}


tseqiteratorClass*
tseqiteratorGetDefaultClass(void)
{
  AUTOINIT();
  return globals()->defaultSeqClass;
}


/*
 *+------------------------------------------------------------------------+
 * privates
 *+------------------------------------------------------------------------+
 */

static void
startup(void)
{
  if (!_titeratorMaster)
    {
      _titeratorMaster = vclientRegisterModule();

      /* our exception classes */
      vexInitClass(&_titeratorNotAssociatedExceptionClass,
		   vexGetValueNullClass(),
		   "iter Not Associated",
		   sizeof(titeratorNotAssociatedException),
		   (vexDumper)NULL);
      vexInitClass(&_titeratorAlreadyAssociatedExceptionClass,
		   vexGetValueClass(), 
		   "iter Already Associated",
		   sizeof(titeratorAlreadyAssociatedException), 
		   (vexDumper)NULL);
    }

  if (!*_titeratorMaster)
    {
      register titeratorClass    *clas;
      register tseqiteratorClass *seqclas;

      vclientAllocateModule(_titeratorMaster, sizeof(_moduleGlobals));

      clas = vclassSpawn(vobjectGetDefaultClass(), sizeof(titeratorClass));
      vclassSetNameScribed(clas, vcharScribeLiteral("titerator"));
      vclassSetObjectSize(clas, sizeof(titerator));

      /* base (virtual) class */
      vclassSet(clas, vobjectINIT,	    init);
      vclassSet(clas, vobjectCOPY_INIT,	    copyinit);
      vclassSet(clas, vobjectCOPY,	    copy);

      vclassSet(clas, titeratorBIND,        binder);
      vclassSet(clas, titeratorADVANCE,     advance);
      vclassSet(clas, titeratorMORE,        more);
      vclassSet(clas, titeratorSTART_OVER,  startover);
      vclassSet(clas, titeratorSET_DATA,    setdata);

     globals()->defaultClass = clas;


      /* (virtual) sequential iterator */
      seqclas = vclassSpawn(clas, sizeof(tseqiteratorClass));
      vclassSetNameScribed(seqclas, vcharScribeLiteral("tseqiterator"));
      vclassSetObjectSize(seqclas, sizeof(tseqiterator));

      vclassSet(seqclas, titeratorMORE,             seq_more);
      vclassSet(seqclas, tseqiteratorGET_AT,        seq_at);
      vclassSet(seqclas, tseqiteratorGET_REMAINING, seq_remaining);

      globals()->defaultSeqClass = seqclas;
    }

  return;
}




static void
init(register titerator *iter)
{
  sendsuper(vobjectINIT, (iter));

  iter->binding = NULL;
  iter->data    = NULL;

  return;
}




static void
copyinit(register titerator *iter, register titerator *copy)
{
  sendsuper(vobjectCOPY_INIT, (iter, copy));

  copy->binding = NULL;
  copy->data    = iter->data;

  if (iter->binding)
    titeratorAssociate(copy, iter->binding);

  return;
}




static void
copy(register titerator *iter, register titerator *copy)
{
  sendsuper(vobjectCOPY, (iter, copy));

  copy->binding = NULL;
  copy->data    = iter->data;

  if (iter->binding)
    titeratorAssociate(copy, iter->binding);

  return;
}



static void 
binder(register titerator *iter, const void *binding)
{
  vdebugIF(!binding, vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "bind: NULL binding ref!", vexERRNO, 0, vexNULL));

  if (iter->binding && binding)
    titeratorGenerateAlreadyAssociated("binder: cannot alter binding");

  iter->binding = binding;

  return;
}



static void
advance(register titerator *iter)
{
  vdebugWarn("advance: should be overridden\n");
}




static void
startover(register titerator *iter)
{
  vdebugWarn("startover: should be overridden\n");
}




static int
more(register titerator *iter)
{
  vdebugWarn("more: should be overridden!\n");
  return FALSE;
}




static const void *
setdata(register titerator *iter, const void *data)
{
  const void *old;

  old = iter->data;
  iter->data = data;
  return old;
}




static int
seq_at(register tseqiterator *iter)
{
  vdebugWarn("current: should be overidden!\n");
  return -666;
}




static int
seq_remaining(register tseqiterator *iter)
{
  vdebugWarn("remaining: should be overidden!\n");
  return 0;
}



static int
seq_more(register tseqiterator *iter)
{
  return (tseqiteratorGetNumberRemaining(iter)>0);
}




/*
  +-------------------------------------------------------------------------+
   MISC formatting information for emacs in c-mode
  +-------------------------------------------------------------------------+
 */

/*
 * Local Variables:
 * c-indent-level:2
 * c-continued-statement-offset:2
 * c-brace-offset:0
 * c-brace-imaginary-offset:0
 * c-argdecl-indent:5
 * c-label-offset:0
 * c-tab-always-indent:nil
 * End:
 */
