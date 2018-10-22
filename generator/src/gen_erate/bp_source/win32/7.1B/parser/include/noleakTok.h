/*========================================================================
 *
 * File:      $RCSfile: noleakTok.h,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:30 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef NOLEAKTOKEN_H
#define NOLEAKTOKEN_H

/*  This file should be accompanied by DISCLAIMER.TXT stating disclaimers */

#include "tokens.h"
#include "AToken.h"
#include "simpleToken.h"

class NoLeakToken : public SimpleToken {
public:
       /* constructor */		NoLeakToken();
       /* destructor */ virtual	   	~NoLeakToken();
       /* copy constructor */	        NoLeakToken(const NoLeakToken &);
       NoLeakToken &			operator = (const NoLeakToken &);

static void				clearList();
static void				clearCounter();
static void		          	destroyList();
       virtual void	          	dumpNode(const char * s=0);
static void		                dumpList();	// over list
       virtual ANTLRChar *		getText() const =0;
       virtual void			insertNode();	// onto list
       virtual void		      	removeNode();   // from list
       virtual void			setText(const ANTLRChar *)=0;

static int 			   	counter;	// incr on ctor
static NoLeakToken *			listHead;	// all tokens
       NoLeakToken *			next;		// on list
       NoLeakToken *			prev;		// on list
       int				serial;
private:
       void				init();
};

#endif

