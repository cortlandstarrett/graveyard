/*========================================================================
 *
 * File:      $RCSfile: p_tthred.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:31 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
// This class is used to manage a set of "interesting" AST's
// discovered during the parsing of Action Language statements

#ifndef P_TTHRED_HH
#define P_TTHRED_HH

#include "p_types.hh"
#include "myAST.h"

#define THREAD_ITEM AST 

class P_treeThread
{
public:
  P_treeThread()
  {
    head = NULL;
    tail = NULL;
  }
  ~P_treeThread()
  {}
  void add(THREAD_ITEM *item)
  {
    if ( this && item )
      {
        if ( ! head )
          {
            head = tail = item;
            item->setItemNext( NULL );
          }
        else
          {
            // Chain item
            tail->setItemNext( item );
            tail = item;
          }
      }
  }
  THREAD_ITEM *getItemHead()
  {
    THREAD_ITEM *item = NULL;
    if ( this )
      item = head;
    return item;
  }
private:
  THREAD_ITEM *head;
  THREAD_ITEM *tail;
};

#undef THREAD_ITEM

#endif
