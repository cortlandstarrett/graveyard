/*========================================================================
 *
 * File:      $RCSfile: noleakAST.h,v $
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
#ifndef NOLEAKAST_H
#define NOLEAKAST_H

/*  This file should be accompanied by DISCLAIMER.TXT stating disclaimers */

#include "ASTBase.h"

class NoLeakAST : public ASTBase {
public:
       /* constructor */	NoLeakAST();
       /* destructor */ virtual	~NoLeakAST();
       /* copy constructor */	NoLeakAST(const NoLeakAST &);
       NoLeakAST &	        operator = (const NoLeakAST &);
               // save AST list and make a new, empty current list
static void                     init();        
               // clear current list and restore saved list
static void                     cleanup();    
static void			clearList();		   // reset list
static void			clearCounter();
static void			destroyList();		   // over list
       virtual void		dumpNode(const char * s=0, const char * buffer=0);
static void			dumpList();		   // over list
       virtual void		dumpTree(const char * s=0, const char * bufffer=0);
       void			insertNode();		   // to list
       void			removeNode();		   // from list
       void			removeTree();		   // from list

static NoLeakAST *		listHead;		   // all NoLeakASTs

       NoLeakAST *		next;			   // on list
       NoLeakAST *		prev;			   // on list
    
protected:
       virtual void		dumpTree1(int indent, const char * bufffer=0);
       virtual void		dumpTreeIndent(int indent);      

static int			counter;		   // incr by ctor
       int			serial;

private:

// list of all NoLeakASTs listHeads
static NoLeakAST *		listOfListHead;		   

};

#endif
