/*========================================================================
 *
 * File:      $RCSfile: p_swhere.hh,v $
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
#ifndef SWHERE_H
#define SWHERE_H

#include "u_typdef.hh"     // t_boolean
#include "vchar.h"

class ASTBase;
class AST;
class P;
class NoLeakAST;
class NoLeakToken;

class Special_Where
{ 
public:
  static t_boolean add( Special_Where*& p_table, 
     const vchar *obj_kl, 
     const vchar *where_spec,
     const vchar *key,
     unsigned int domain_code);

  static t_boolean clear(  Special_Where*& p_table,
     const vchar *obj_kl, 
     const vchar *where_spec,
     const vchar *key);

  static t_boolean query(  Special_Where* p_table,
     const vchar *obj_kl, 
     const vchar *where_spec,
     const vchar *key);

  static t_boolean clear_all( Special_Where*& p_table ); 

  static Special_Where *match(  Special_Where* p_table,
     const vchar *obj_kl, 
     AST* expr );

  vchar * key;
  vchar * obj_kl;
  vchar * where_spec;
  P* parsed_where;
  AST *root;

  NoLeakAST* ast_list_head;
  NoLeakToken* token_list_head;

private:

  Special_Where(const vchar *obj_kl, 
     const vchar *where_spec,
     const vchar *key);

  ~Special_Where();

  static Special_Where* find_by_key (  Special_Where* p_table, 
     const vchar *key );
  static Special_Where* find_by_kl_ws (  Special_Where* p_table,
     const vchar *obj_kl, 
     const vchar *where_spec );

  void add_to_list( Special_Where*& p_table );
  void remove_from_list( Special_Where*& p_table );

  Special_Where *next;   // keep a list of instances

};

#endif
