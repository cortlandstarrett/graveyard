/*========================================================================
 *
 * File:      $RCSfile: p_symtbl.hh,v $
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
#ifndef P_SYMTBL_HH
#define P_SYMTBL_HH

#include "p_types.hh"
#include "tokens.h"
#include "d_typdef.hh"
#include "vchar.h"

class AST;
class P_error;
class P_check;
class Sym;
class zzs_SymbolTable;

class BPSymbol_Table
{
public:

  //.Member BPSymbol_Table
  BPSymbol_Table( P_error *p_er,
                  P_check *p_pck, 
                  persObjPtr p_self,
                  persObjPtr p_rcvd_evt,
                  persObjPtr p_selected,
                  persObjPtr p_param
                );
  // This is the default constructor for :sym.BPSymbol_Table:Esym..
  // It initializes the symbol table system.

  //.Member BPSymbol_Table
  BPSymbol_Table(BPSymbol_Table *mother);

  //.Member ~BPSymbol_Table
  ~BPSymbol_Table();

  //.Member push
  BPSymbol_Table *push()
  {
    BPSymbol_Table *st = new BPSymbol_Table(this);
    return st;
  }
  // This function creates a new instance of :sym.BPSymbol_Table:esym.
  // and makes it the current context.  All newly-defined symbols will
  // be associated with the :q.current context:eq..
  // A pointer to the new context is returned.

  //.Member pop
  BPSymbol_Table *pop()
  {
    BPSymbol_Table *mother;
    if (st_mother)
      {
        mother = st_mother;
        mother->activate_context();
      }
    else
      mother = this;
    return mother;
  }
  // This member function makes the "mother" of this context the
  // current context.  If there is no higher level context (mother),
  // the context remains the same.
  // A pointer to the new context is returned.

  void stat();

  //-------------------------------------------------------------------
  // Validate this OOA element.
  //-------------------------------------------------------------------

  BPSymbol_Table *get_global_context()
  {
    BPSymbol_Table *new_context;
    for ( new_context=this;
          new_context->st_mother != NULL;
          new_context=new_context->st_mother)
      {}
    return new_context;
  }

  //.Member newadd
  Sym *newadd( AST *ast,
               t_core_data_type datatype,
               persObjPtr objPtr = 0 );

  //.Member newadd
  Sym *newadd( AST *ast,
               t_core_data_type datatype,
               AST *objAST );

  //.Member add
  Sym *add( const char *symbol,
               t_core_data_type datatype,
               persObjPtr objPtr = 0 );

  //.Member setBufferAddr
  void setBufferAddr( const char *p_ascii_buffer,
                      const vchar *p_vchar_buffer )
    {
      ascii_buffer = p_ascii_buffer;
      orig_buffer = p_vchar_buffer;
    }

  //.Member getAsciiBuffer
  const char *getAsciiBuffer()
    {
      return ascii_buffer;
    }

  //.Member getOrigBuffer
  const vchar *getOrigBuffer()
    {
      return orig_buffer;
    }

  //.Member remove
  void remove( Sym *s );

  //.Member can_create_var_type
  bool can_create_var_type( t_core_data_type type )
  {
    UI_printf1("in can_create_var_type(%d)\n", type);
    bool _retv = FALSE;
    switch ( type )
      {
      case INTEGER_DATATYPE:
      case REAL_DATATYPE:
      case STRING_DATATYPE:
      case BOOLEAN_DATATYPE:
      case MAPPING_INST_DATATYPE:
      case MAPPING_INST_REF_DATATYPE:
      case UNIQUE_ID_DATATYPE:
      case EVENT_INST_DATATYPE:
      case OBJECT_INST_REF_DATATYPE:
      case OBJECT_INST_REF_SET_DATATYPE:
        _retv = TRUE;
        break;
      default:
        _retv = FALSE;
      }
    return( _retv );
  }

  //.Member is_var_this_type_defined
  bool is_var_this_type_defined( const vchar *t,
                                 t_core_data_type datatype,
                                 Sym **s );

  //.Member is_var_this_type_defined-2
  bool is_var_this_type_defined( const vchar *t,
                                 t_core_data_type datatype);
 
  //.Member is_var_this_space_defined
  bool is_var_this_space_defined( const vchar *t,
                                  Name_Space_e namespc,
                                  Sym **s );
  
  //.Member is_var_this_space_defined-2
  bool is_var_this_space_defined( const vchar *t,
                                  Name_Space_e namespc );
  
  //.Member is_inst_ref_var
  bool is_inst_ref_var( const vchar *t, Sym **s )
  {
    return (is_var_this_type_defined( t, OBJECT_INST_REF_DATATYPE, s ));
  }
  
  //.Member is_inst_ref_set_var
  bool is_inst_ref_set_var( const vchar *t, Sym **s )
  {
    return (is_var_this_type_defined( t, OBJECT_INST_REF_SET_DATATYPE, s ));
  }

private:

  //.Member init_symbols
  void init_symbols( persObjPtr p_self,
                     persObjPtr p_rcvd_evt,
                     persObjPtr p_selected,
                     persObjPtr p_param );
  // This function sets the initial set of symbols into the symbol table.

  //.Member activate_context  
  void activate_context();
  // This function makes this instance the current context.

  //.Member get_head_context  
  BPSymbol_Table * get_head_context();
  // This function return the instance that is the head of the
  // context instance chain.

  //.Member set_head_context  
  void set_head_context(BPSymbol_Table *new_head);
  // This function makes the instance :sym.new_head:esym. the head
  // of the context instance chain.

  //.Member er
  P_error *er;
  // This is a pointer to the class which surfaces error messages and
  // error counts in the parser.

  //.Member pck
  P_check *pck;
  // This is a pointer to the class that interfaces with the MC_DBMS
  // database.

  //.Member ascii_buffer
  const char *ascii_buffer;
  // This is a pointer to the ASCII input buffer, which is a translated
  // copy of orig_buffer.

  //.Member orig_buffer
  const vchar *orig_buffer;
  // This is a pointer to the original vchar input buffer, prior to
  // translation. 

  //.Member context_level
  int context_level;
  // This data member is used to identify the nesting level of the symbol
  // table.  The outermost level, or global level, is 1.  Each time a control
  // statement is encountered which needs a new nesting level, the number is
  // bumped by one.

  //.Member st_mother
  BPSymbol_Table *st_mother;
  // This data member is used to access the context (and symbol) table
  // which is the mother of this context.

  //.Member sym_table
  Sym *sym_table;
  // This data member is the anchor for the chain of symbol tables entries
  // defined in this context.  A context is defined as an instance of
  // :sym.BPSymbol_Table:esym..

  //.Member next_context
  BPSymbol_Table *next_context;
  // This data member is used to point to the next (less recently created)
  // instance of :sym.BPSymbol_Table:esym. in the list of all of these
  // instances. The global context instance (context_level == 1) points to
  // the most recently created instance.

  //.Member zzs_sym
  zzs_SymbolTable* zzs_sym;
  // This is the hash table used to store the symbols.

};

#endif
