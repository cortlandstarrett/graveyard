/*========================================================================
 *
 * File:      $RCSfile: p_symtbl.cc,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:22 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <stdio.h>

void tracein(char *r)
{
  // fprintf(stderr, "enter \"%s\"\n", r);
}
void traceout(char *r)
{
  // fprintf(stderr, "exit \"%s\"\n", r);
}

#include "p_symtbl.hh"
#include "p_check.hh"
#include "sym.hh"
#include "myAST.h"
#include "p_msgs.hh"
#include "p_error.hh"
#include "d_typdef.hh"
#include "vstr.h"

BPSymbol_Table::BPSymbol_Table( P_error *p_er,
                                P_check *p_pck, 
                                persObjPtr p_self,
                                persObjPtr p_rcvd_evt,
                                persObjPtr p_selected,
                                persObjPtr p_param
                              ):
  er(p_er),
  pck(p_pck),
  context_level(1),
  st_mother(NULL),
  sym_table(NULL),
  next_context(NULL),
  zzs_sym(NULL)
{
  // This is the global context (the first one for this parse).
  // Put myself at the head of the chain
  next_context = this;
  zzs_sym = zzs_SymbolTable::zzs_init( HashTableSize, StringTableSize );
  activate_context();
  init_symbols(p_self, p_rcvd_evt, p_selected, p_param);
}

BPSymbol_Table::BPSymbol_Table(BPSymbol_Table *mother):
  st_mother(mother),
  sym_table(NULL),
  next_context(NULL)
{
  er = mother->er;
  pck = mother->pck;

  // Initialize before it's used by get_head_context()
  context_level = mother->context_level + 1;

  // Put myself at the head of the chain
  next_context = get_head_context();
  set_head_context(this);

  zzs_sym = mother->zzs_sym;
  activate_context();
}

//.Member ~BPSymbol_Table
BPSymbol_Table::~BPSymbol_Table()
{
  if ( context_level == 1 )
  {
    BPSymbol_Table* head_context = get_head_context();
    while (head_context != this)
    {
      BPSymbol_Table* next_st = head_context->next_context;
      delete head_context;
      head_context = next_st;
    }
    zzs_sym->zzs_super_done();
    delete zzs_sym;
  }
}

//.Member stat
void BPSymbol_Table::stat()
{
  zzs_sym->zzs_stat();
}

//.Member get_head_context
BPSymbol_Table* BPSymbol_Table::get_head_context()
{
  BPSymbol_Table* global_context = this;
  while ( global_context->context_level != 1 )
  {
    global_context = global_context->st_mother; 
  }

  return global_context->next_context;
}

//.Member get_head_context
void BPSymbol_Table::set_head_context(BPSymbol_Table* new_head)
{
  BPSymbol_Table* global_context = this;
  while ( global_context->context_level != 1 )
  {
    global_context = global_context->st_mother; 
  }

  global_context->next_context = new_head;
}


//.Member remove
void
BPSymbol_Table::remove( Sym * s )
{
  zzs_sym->zzs_free(s);
}

//.Member newadd
Sym *
BPSymbol_Table::newadd( AST *ast,
                        t_core_data_type dt_req,
                        AST *objAST )
{
	persObjPtr edt_ptr = pck->get_enum_data_type_ptr(objAST);

	if ( edt_ptr )
		return newadd( ast, dt_req, edt_ptr );
	else
		return newadd( ast, dt_req, objAST->getObjPtr() );
}

//.Member newadd
Sym *
BPSymbol_Table::newadd( AST *ast,
                        t_core_data_type dt_req,
                        persObjPtr op )
{
  Sym *s_ref = NULL;
  if ( !ast )
    return s_ref;
  Name_Space_e namespc;
  bool define_symbol = FALSE;
  bool incompatible_types = FALSE;
  const vchar *v = ast->getVcharText();
  if ( ! is_var_this_type_defined( v, dt_req, &s_ref ) )
    {
      namespc = SYMBOL_ENTRY_NON_INST_REF;
      if ( is_var_this_space_defined( v, namespc, &s_ref ) )
        {
          define_symbol = FALSE;
          incompatible_types = TRUE;
          switch( s_ref->datatype )
            {
            case INTEGER_DATATYPE:
              if ( dt_req == REAL_DATATYPE )
                incompatible_types = FALSE;
              break;
            case REAL_DATATYPE:
              if ( dt_req == INTEGER_DATATYPE )
                incompatible_types = FALSE;
              break;
            case ENUMERATION_DATATYPE:
	          if ( op == s_ref->objPtr)
		        incompatible_types = FALSE;
			  break;
            default:
              break;
            }
        }
      else
        {
          namespc = SYMBOL_ENTRY_INST_REF;
          if ( is_var_this_space_defined( v, namespc, &s_ref ) )
            {
              define_symbol = FALSE;
              incompatible_types = TRUE;
            }
          else
            {
              // symbol not already defined in this namespace
              define_symbol = TRUE;
              incompatible_types = FALSE;
            }
        }
    }
  else // symbol already defined
    {
      switch ( s_ref->datatype )
        {
        case INTEGER_DATATYPE:
        case REAL_DATATYPE:
        case STRING_DATATYPE:
        case BOOLEAN_DATATYPE:
        case MAPPING_INST_DATATYPE:
        case MAPPING_INST_REF_DATATYPE:
        case UNIQUE_ID_DATATYPE:
        case UNKNOWN_DATATYPE:
        case VOID_DATATYPE:
        case QMARK_DATATYPE:
        case FRAGMENT_DATATYPE:
        case SAME_AS_BASE_DATATYPE:
        case CURRENT_STATE_DATATYPE:
        case EVENT_INST_DATATYPE:
		  break;

		case ENUMERATION_DATATYPE:
        case OBJECT_INST_REF_DATATYPE:
        case OBJECT_INST_REF_SET_DATATYPE:
          // objPtr is different means that the object being referred to
          // is different than the defined one.
          if ( op != s_ref->objPtr)
            incompatible_types = TRUE;
        }
    }
  if ( define_symbol )
    {
      switch ( dt_req )
        {
        case INTEGER_DATATYPE:
        case REAL_DATATYPE:
        case STRING_DATATYPE:
        case BOOLEAN_DATATYPE:
        case MAPPING_INST_DATATYPE:
        case MAPPING_INST_REF_DATATYPE:
        case UNIQUE_ID_DATATYPE:
		case ENUMERATION_DATATYPE:
          namespc = SYMBOL_ENTRY_NON_INST_REF;
          UI_printf("  adding entry to symbol table\n");
          s_ref = zzs_sym->zzs_newadd(v);
          s_ref->context = this;
          s_ref->namespc = namespc;
          s_ref->datatype = dt_req;
          s_ref->objPtr = op;
          break;
        case EVENT_INST_DATATYPE:
        case OBJECT_INST_REF_DATATYPE:
        case OBJECT_INST_REF_SET_DATATYPE:
        case BRIDGE_OR_TRANSFORMER_INST_DATATYPE:
          namespc = SYMBOL_ENTRY_INST_REF;
          UI_printf("  adding entry to symbol table\n");
          s_ref = zzs_sym->zzs_newadd(v);
          s_ref->context = this;
          s_ref->namespc = namespc;
          s_ref->datatype = dt_req;
          s_ref->objPtr = op;
          break;
        case UNKNOWN_DATATYPE:
          // Cannot define variable with unknown datatype
          AL_PARSE_ERR1( ast, AL_GETMSG(ERR, 299, 1), v )
          s_ref=NULL;
          break;
        case VOID_DATATYPE:
        case QMARK_DATATYPE:
        case FRAGMENT_DATATYPE:
        case SAME_AS_BASE_DATATYPE:
        case CURRENT_STATE_DATATYPE:
          // Invalid data type for symbol table
          AL_PARSE_ERR1( ast, AL_GETMSG(ERR, 298, 1), v )
          s_ref=NULL;
        }
    }          
  // Don't define the symbol
  if ( incompatible_types )
    {
      switch ( dt_req )
        {
        case EVENT_INST_DATATYPE:
          // Variable/reference must be of type inst<Event>
          AL_PARSE_ERR1( ast, AL_GETMSG(ERR, 283, 1), v )
            break;
        case INTEGER_DATATYPE:
        case REAL_DATATYPE:
        case STRING_DATATYPE:
        case BOOLEAN_DATATYPE:
        case MAPPING_INST_DATATYPE:
        case MAPPING_INST_REF_DATATYPE:
        case UNIQUE_ID_DATATYPE:
        case OBJECT_INST_REF_DATATYPE:
          if ( s_ref->datatype == OBJECT_INST_REF_SET_DATATYPE )
            AL_PARSE_ERR1( ast, AL_GETMSG(ERR, 271, 1), v )
           else
             AL_PARSE_ERR1( ast, AL_GETMSG(ERR, 272, 1), v )
             break;
        case OBJECT_INST_REF_SET_DATATYPE:
          if ( s_ref->datatype == OBJECT_INST_REF_DATATYPE )
            AL_PARSE_ERR1( ast, AL_GETMSG(ERR, 270, 1), v )
          else
            AL_PARSE_ERR1( ast, AL_GETMSG(ERR, 272, 1), v )
            break;
        case UNKNOWN_DATATYPE:
          // Cannot define variable with unknown datatype
          AL_PARSE_ERR1( ast, AL_GETMSG(ERR, 299, 1), v )
          break;                  // no error message
        case VOID_DATATYPE:
        case QMARK_DATATYPE:
        case FRAGMENT_DATATYPE:
        case SAME_AS_BASE_DATATYPE:
        case CURRENT_STATE_DATATYPE:
        case BRIDGE_OR_TRANSFORMER_INST_DATATYPE:
		case ENUMERATION_DATATYPE:
          // Incompatible data types
          AL_PARSE_ERR0( ast, AL_GETMSG(ERR, 274, 0) )
        }
      s_ref = NULL;
    }
  if (s_ref)
    ast->setObjPtr(s_ref->objPtr);
  return s_ref;
}

//.Member add
Sym *
BPSymbol_Table::add( const char *symbol,
                     t_core_data_type dt_req,
                     persObjPtr op )
{
  Sym *s_ref = NULL;
  Name_Space_e namespc;
  vstr *v = vstrCloneScribed( vcharScribeASCII( symbol ) );
  switch ( dt_req )
    {
    case INTEGER_DATATYPE:
    case REAL_DATATYPE:
    case STRING_DATATYPE:
    case BOOLEAN_DATATYPE:
    case MAPPING_INST_DATATYPE:
    case MAPPING_INST_REF_DATATYPE:
    case UNIQUE_ID_DATATYPE:
	case ENUMERATION_DATATYPE:
      namespc = SYMBOL_ENTRY_NON_INST_REF;
      UI_printf("  adding entry to symbol table\n");
      s_ref = zzs_sym->zzs_newadd(v);
      s_ref->context = this;
      s_ref->namespc = namespc;
      s_ref->datatype = dt_req;
      s_ref->objPtr = op;
      break;
    case EVENT_INST_DATATYPE:
    case OBJECT_INST_REF_DATATYPE:
    case OBJECT_INST_REF_SET_DATATYPE:
    case BRIDGE_OR_TRANSFORMER_INST_DATATYPE:
      namespc = SYMBOL_ENTRY_INST_REF;
      UI_printf("  adding entry to symbol table\n");
      s_ref = zzs_sym->zzs_newadd(v);
      s_ref->context = this;
      s_ref->namespc = namespc;
      s_ref->datatype = dt_req;
      s_ref->objPtr = op;
      break;
    case UNKNOWN_DATATYPE:
    case VOID_DATATYPE:
    case QMARK_DATATYPE:
    case FRAGMENT_DATATYPE:
    case SAME_AS_BASE_DATATYPE:
    case CURRENT_STATE_DATATYPE:
      break;
    }
  vstrDestroy(v);
  return s_ref;
}


//.Member init_symbols
void BPSymbol_Table::init_symbols( persObjPtr p_self,
                                   persObjPtr p_rcvd_evt,
                                   persObjPtr p_selected,
                                   persObjPtr p_param )
{
  Sym *s;
  if ( p_self )
    {
      s = add( "self", OBJECT_INST_REF_DATATYPE, p_self );
      s->attrib = SA_READONLY;
      s = add( "Self", OBJECT_INST_REF_DATATYPE, p_self );
      s->attrib = SA_READONLY;
      s = add( "SELF", OBJECT_INST_REF_DATATYPE, p_self );
      s->attrib = SA_READONLY;
    }
  
  if ( p_rcvd_evt )
    {
      s = add( "rcvd_evt", EVENT_INST_DATATYPE, p_rcvd_evt );
      s->attrib = SA_READONLY;
      s = add( "Rcvd_evt", EVENT_INST_DATATYPE, p_rcvd_evt );
      s->attrib = SA_READONLY;
      s = add( "Rcvd_Evt", EVENT_INST_DATATYPE, p_rcvd_evt );
      s->attrib = SA_READONLY;
      s = add( "RCVD_EVT", EVENT_INST_DATATYPE, p_rcvd_evt );
      s->attrib = SA_READONLY;
    }
  
  if ( p_selected )
    {
      s = add( "selected", OBJECT_INST_REF_DATATYPE, p_selected );
      s->attrib = SA_READONLY;
      s = add( "Selected", OBJECT_INST_REF_DATATYPE, p_selected );
      s->attrib = SA_READONLY;
      s = add( "SELECTED", OBJECT_INST_REF_DATATYPE, p_selected );
      s->attrib = SA_READONLY;
    }
  
  if ( p_param )
    {
      s = add( "param", BRIDGE_OR_TRANSFORMER_INST_DATATYPE, p_param );
      s->attrib = SA_READONLY;
      s = add( "Param", BRIDGE_OR_TRANSFORMER_INST_DATATYPE, p_param );
      s->attrib = SA_READONLY;
      s = add( "PARAM", BRIDGE_OR_TRANSFORMER_INST_DATATYPE, p_param );
      s->attrib = SA_READONLY;
    }
}

//.Member is_var_this_type_defined
bool BPSymbol_Table::is_var_this_type_defined( const vchar *t,
                                               t_core_data_type datatype,
                                               Sym **s )
{
  bool _retv = FALSE;
  BPSymbol_Table *context;
  for (context = this; context != NULL; context=context->st_mother)
    {
      *s = zzs_sym->zzs_get(t, context, SYMBOL_ENTRY_INST_REF);
      if ( *s == NULL)
        *s = zzs_sym->zzs_get(t, context, SYMBOL_ENTRY_NON_INST_REF);
      if ( *s )                         // already defined
        {
          if ( (*s)->datatype == datatype )
            _retv = TRUE;
          break;
        }
    }
  return( _retv );
}

//.Member is_var_this_type_defined-2
bool BPSymbol_Table::is_var_this_type_defined( const vchar *t,
                                               t_core_data_type datatype)
{
  Sym *s;
  bool _retv = FALSE;
  BPSymbol_Table *context;
  for (context = this; context != NULL; context=context->st_mother)
    {
      s = zzs_sym->zzs_get(t, context, SYMBOL_ENTRY_INST_REF);
      if ( s == NULL)
        s = zzs_sym->zzs_get(t, context, SYMBOL_ENTRY_NON_INST_REF);
      if ( s )                         // already defined
        {
          if ( s->datatype == datatype )
            _retv = TRUE;
          break;
        }
    }
  return( _retv );
}
  
//.Member is_var_this_space_defined
bool BPSymbol_Table::is_var_this_space_defined( const vchar *t,
                                                Name_Space_e namespc,
                                                Sym **s )
{
  bool _retv = FALSE;
  BPSymbol_Table *context;
  for (context = this; context != NULL; context=context->st_mother)
    {
      *s = zzs_sym->zzs_get(t, context, namespc);
      if ( *s )                         // already defined
        {
          _retv = TRUE;
          break;
        }
    }
  return( _retv );
}
  
//.Member is_var_this_space_defined-2
bool BPSymbol_Table::is_var_this_space_defined( const vchar *t,
                                                Name_Space_e namespc )
{
  bool _retv = FALSE;
  Sym *s;
  BPSymbol_Table *context;
  for (context = this; context != NULL; context=context->st_mother)
    {
      s = zzs_sym->zzs_get(t, context, namespc);
      if ( s )                         // already defined
        {
          _retv = TRUE;
          break;
        }
    }
  return( _retv );
}

//.Member activate_context  
void BPSymbol_Table::activate_context()
{
  zzs_sym->zzs_scope(&sym_table);
}
