/*========================================================================
 *
 * File:      $RCSfile: p_swhere.cc,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:20 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include "p_swhere.hh"

#include "myToken.h"
#include "myAST.h"
#include "myTokenBuffer.h"
#include "DLGLexer.h"
#include "P.h"
#include "p_ckgendb.hh"

static bool compare_trees ( AST *root, AST *expr );

Special_Where::Special_Where( const vchar *p_obj_kl, 
     const vchar *p_where_spec,
     const vchar *p_key):
  obj_kl(0),
  where_spec(0),
  key(0),
  root(0),
  parsed_where(0),
  next(0),
  ast_list_head(0),
  token_list_head(0)
{
  obj_kl = new vchar [ vcharLength(p_obj_kl)+1];
  vcharCopy ( p_obj_kl, obj_kl );

  where_spec = new vchar [ vcharLength(p_where_spec)+1];
  vcharCopy ( p_where_spec, where_spec );

  key = new vchar [ vcharLength(p_key)+1];
  vcharCopy ( p_key, key );
}

Special_Where::~Special_Where()
{
  delete [] obj_kl;
  delete [] where_spec;
  delete [] key;

  if ( parsed_where ) 
  {
    NoLeakAST* ast_save_head = NoLeakAST::listHead;
    NoLeakToken* token_save_head = NoLeakToken::listHead;
    NoLeakAST::listHead = ast_list_head;
    NoLeakToken::listHead = token_list_head;

    delete parsed_where;

    NoLeakAST::listHead = ast_save_head;
    NoLeakToken::listHead = token_save_head;
  }

}

t_boolean Special_Where::add( Special_Where*& p_table,
     const vchar *p_obj_kl, 
     const vchar *p_where_spec,
     const vchar *p_key,
     unsigned int p_domain_code)
{
  t_boolean ret_val = FALSE;

  if ( !find_by_key (p_table, p_key) &&
       !find_by_kl_ws ( p_table, p_obj_kl, p_where_spec ) )
  {
    Special_Where* new_sw = new Special_Where(p_obj_kl,
       p_where_spec, p_key);

    char *buffer = Description::createAsciiFromVchar(p_where_spec);
    const vchar* saveBuffer = AST::getVcharBuffer();

    try
    {
      // create a parser, and parse the where spec.
      ColToken::accumulated_offset = 0;   // HACK: should be done elsewhere
      DLGStringInput in(buffer); 
      DLGLexer lexer(&in, 2000);
      MyTokenBuffer pipe(&lexer,1);
      ANTLRToken aToken( (ANTLRTokenType)0 );
      lexer.setToken(&aToken);

      new_sw->parsed_where = new P(&pipe);

      P_error er;
      P_checkGenDB ck(&er, FALSE, p_domain_code);

      //-------------------------------------------------------------------
      // Initialize the scanner and parser.
      //-------------------------------------------------------------------
      AST temp_ast(TOK_INST_REF_VAR);
      temp_ast.setVcharText(p_obj_kl);
      temp_ast.setObjPtr(0);
      ck.validate_obj_kl ( &temp_ast );
      if ( temp_ast.getObjPtr() != 0 )
      {  
        new_sw->parsed_where->init(&er, &ck, 0, 0, temp_ast.getObjPtr(), 0 );
        new_sw->parsed_where->initReloc();
        new_sw->parsed_where->setBufferAddr(buffer,
                                            p_where_spec);

        //-------------------------------------------------------------------
        // Fire up the parser by intializing and invoking first rule.
        //-------------------------------------------------------------------
        int parser_rc = 0;
        new_sw->parsed_where->initWSpec(FALSE, FALSE);
        ASTBase* sw_base = 0;
        new_sw->parsed_where->where_spec( &sw_base,
                                          &parser_rc );
        if ( er.error_count() || parser_rc != 0 )
        {
          printf("where_spec parse failed: return code = %d\n", parser_rc);
          vscribe *vs = vcharScribeSystemExport(er.get_error_messages());
          char *s = (char *)vcharExportAlloc(vs);
          printf("%s", s);
          vcharExportFree(s);
          delete new_sw;
        }
        else
        {
          new_sw->root = (AST*)sw_base;
  
          // save off our AST list
          new_sw->ast_list_head = NoLeakAST::listHead;
          NoLeakAST::listHead = 0;

          // save off our token list
          new_sw->token_list_head = NoLeakToken::listHead;
          NoLeakToken::listHead = 0;

          // minimize parser memory usage
          new_sw->add_to_list(p_table);
          ret_val = TRUE;
        }
      }
    }
    catch ( char *msg )
    {
       printf("where_spec parser exception:\n");
       printf("%s\n", msg);
       delete new_sw;
    }

    AST::setVcharBuffer(saveBuffer);
    Description::freeAsciiFromVchar( buffer );
  }

  return ret_val;
}

t_boolean Special_Where::clear( Special_Where*& p_table,
     const vchar *p_obj_kl, 
     const vchar *p_where_spec,
     const vchar *p_key)
{
  t_boolean ret_val = FALSE;

  Special_Where* old_sw = find_by_key (p_table, p_key);
  if ( old_sw )
  {
    old_sw->remove_from_list(p_table);
    delete old_sw;
    ret_val = TRUE;
  }
  else
  {
    old_sw = find_by_kl_ws ( p_table, p_obj_kl, p_where_spec );
    if ( old_sw )
    {
      old_sw->remove_from_list(p_table);
      delete old_sw;
      ret_val = TRUE;
    }
    else    // none found
    {
      ret_val = FALSE;
    }
  }

  return ret_val;
}

t_boolean Special_Where::query(  Special_Where* p_table,
     const vchar *p_obj_kl, 
     const vchar *p_where_spec,
     const vchar *p_key)
{
  t_boolean ret_val = FALSE;

  Special_Where* old_sw = find_by_key (p_table, p_key);
  if ( old_sw )
  {
    ret_val = TRUE;
  }
  else
  {
    old_sw = find_by_kl_ws ( p_table, p_obj_kl, p_where_spec );
    if ( old_sw )
    {
      ret_val = TRUE;
    }
    else    // none found
    {
      ret_val = FALSE;
    }
  }

  return ret_val;
}

t_boolean Special_Where::clear_all( Special_Where*& p_table )
{
  Special_Where* node = p_table;
  while ( node != 0 )
  {
    Special_Where* next_node = node->next;
    delete node;
    node = next_node;
  }

  // set the head pointer back to null, so the next
  // list we build is properly terminated.
  p_table = 0;

  return TRUE;
}

Special_Where* Special_Where::match(  Special_Where* p_table,
     const vchar *p_obj_kl, 
     AST* expr )
{
  Special_Where* node = p_table;
  while ( node != 0 )
  {
    if ( vcharCompare ( node->obj_kl, p_obj_kl ) == 0 )
    {
       if ( compare_trees( node->root, expr ) )
         break;
    }
    node = node->next;
  }

  return node;
}

Special_Where* Special_Where::find_by_key (  Special_Where* p_table,
   const vchar *p_key )
{
  Special_Where* node = p_table;
  while ( node != 0 && vcharCompare ( node->key, p_key ) != 0 )
    node = node->next;

  return node;
}

Special_Where* Special_Where::find_by_kl_ws (  Special_Where* p_table,
     const vchar *p_obj_kl, 
     const vchar *p_where_spec )
{
  Special_Where* node = p_table;
  while ( node != 0 && 
            !(vcharCompare ( node->obj_kl, p_obj_kl ) == 0
                  && vcharCompare ( node->where_spec, p_where_spec ) == 0) )
    node = node->next;

  return node;
}

void Special_Where::add_to_list( Special_Where*& p_table )
{
  this->next = p_table;
  p_table = this;
}

void Special_Where::remove_from_list( Special_Where*& p_table )
{
  // since this is a singly linked list, we
  // have to search for the predecessor 
  // of this node.
  if ( p_table )
  {
    // is this node the head of the list?
    if ( this == p_table )
    {
      p_table = this->next;
    }
    else
    {
      Special_Where* prior = p_table;
      while ( prior != 0 && prior->next != this  )
        prior = prior->next;

      if ( prior != 0 ) // found it in the list
      {
        prior->next = this->next;
        this->next = 0;
      }
    }
  }
}

bool compare_trees ( AST *spec, AST *clause )
{
  bool ret_val = FALSE;

  //  if ( spec )
  //  spec->dumpNode("compare_trees(spec): ");
  //if ( clause )
  //  clause->dumpNode("compare_trees(clause): ");

  if ( spec->getType() == TOK_QMARK )
  {
    // is clause an expression?
    // HACK as long as it's not selected.<>
    //        we'll assume it's ok
    if ( clause->getType() == TOK_INST_REF_VAR )
    {
      if ( strcmp ( clause->getAsciiText(), "selected") != 0 )
      {
        spec->setObjPtr( clause );
        ret_val = TRUE;
      }
    }
    else
    {
      spec->setObjPtr( clause );
      ret_val = TRUE;
    }
  }
  else if ( spec->getType() == clause->getType() )
  {
    switch ( spec->getType() )
    {
      case TOK_EXPRESSION:
      case TOK_PAREN_EXPR:
      // unary operators  (don't allow EMPTY, NOT_EMPTY, CARDINALITY)
      case TOK_NOT:
      case TOK_UNARY_PLUS:
      case TOK_UNARY_MINUS:
        ret_val = compare_trees ( spec->child(), clause->child() );
        break;

      // ordered comparison operators
      case TOK_LESSTHAN:
      case TOK_LE:
      case TOK_GT:
      case TOK_GE:
        ret_val = compare_trees( spec->child(), clause->child() ) &&
                  compare_trees( spec->child()->sibling(), clause->child()->sibling() );
        break;

      // unordered comparison operators
      case TOK_DOUBLEEQUAL: 
      case TOK_NOTEQUAL:

      // boolean conjunction, disjunction
      case TOK_AND:
      case TOK_OR:
        // allow the order to be reversed
        ret_val = ( compare_trees( spec->child(), clause->child() ) &&
                    compare_trees( spec->child()->sibling(), clause->child()->sibling() ) )
             ||   ( compare_trees( spec->child(), clause->child()->sibling() ) &&
                    compare_trees( spec->child()->sibling(), clause->child() ) );
        break;

      case TOK_INST_REF_VAR:
        // verify object name and attribute name are the same
        if ( vcharCompare (spec->getVcharText(), clause->getVcharText()) == 0 &&
             vcharCompare (spec->child()->getVcharText(), clause->child()->getVcharText()) == 0 )
	{
          ret_val = TRUE;
	}
        break;

      case TOK_BRIDGE_EXPR:
        {
          AST *spec_ee_kl = spec->child();
          AST *clause_ee_kl = clause->child();
          if ( vcharCompare ( spec_ee_kl->getVcharText(), clause_ee_kl->getVcharText() ) == 0 )
	  {
            AST *spec_ee_func = spec_ee_kl->sibling();
            AST *clause_ee_func = clause_ee_kl->sibling();
            if ( vcharCompare ( spec_ee_func->getVcharText(), clause_ee_func->getVcharText() ) == 0 )
	    {
              AST *spec_ee_param = spec_ee_kl->sibling();
              bool params_ok = TRUE;
              while ( spec_ee_param && params_ok )
	      {
                // find the corresponding clause parameter
                AST *clause_ee_param = clause_ee_kl->sibling();
                while ( clause_ee_param && 
                        vcharCompare( clause_ee_param->getVcharText(), spec_ee_param->getVcharText() ) != 0 )
	        {
                  clause_ee_param = clause_ee_param->sibling();
                }

                if ( clause_ee_param )
	        {
                  params_ok = params_ok &&
                     compare_trees ( spec_ee_param->child(), clause_ee_param->child() );
	        }
                else
  	        {
                  // couldn't find matching parameter -- something's wrong
                  params_ok = FALSE;
                }
                spec_ee_param = spec_ee_param->sibling();
              }  // while ( spec_ee_param && params_ok )

              ret_val = params_ok;
            }
	  }
        }
        break;

      case TOK_TRANSFORMER_EXPR:
      {
        AST *spec_tr_kl = spec->child();
        AST *clause_tr_kl = clause->child();
        if ( vcharCompare ( spec_tr_kl->getVcharText(), clause_tr_kl->getVcharText() ) == 0 )
	{
          AST *spec_tr_func = spec_tr_kl->sibling();
          AST *clause_tr_func = clause_tr_kl->sibling();
          if ( vcharCompare ( spec_tr_func->getVcharText(), clause_tr_func->getVcharText() ) == 0 )
	  {
            AST *spec_tr_param = spec_tr_kl->sibling();
            bool params_ok = TRUE;
            while ( spec_tr_param && params_ok )
	    {
              // find the corresponding clause parameter
              AST *clause_tr_param = clause_tr_kl->sibling();
              while ( clause_tr_param && 
                      vcharCompare( clause_tr_param->getVcharText(), spec_tr_param->getVcharText() ) != 0 )
	      {
                clause_tr_param = clause_tr_param->sibling();
              }

              if ( clause_tr_param )
	      {
                params_ok = params_ok &&
                   compare_trees ( spec_tr_param->child(), clause_tr_param->child() );
	      }
              else
	      {
                // couldn't find matching parameter -- something's wrong
                params_ok = FALSE;
              }
              spec_tr_param = spec_tr_param->sibling();
	    }  // while ( spec_tr_param && params_ok )

            ret_val = params_ok;
          }
	}
      }
        break;

      default:
        printf ("Internal Error: compare_trees: Unknown token %d\n", spec->getType() );
        break;
    }
  }
  else if ( spec->getType() == TOK_LESSTHAN && clause->getType() == TOK_GE ||
            spec->getType() == TOK_LE && clause->getType() == TOK_GT ||
            spec->getType() == TOK_GT && clause->getType() == TOK_LE ||
            spec->getType() == TOK_GE && clause->getType() == TOK_LESSTHAN )
  {
    // swap order
    ret_val = compare_trees( spec->child(), clause->child()->sibling() ) &&
              compare_trees( spec->child()->sibling(), clause->child() );
  }

  //printf( "compare_trees: ret_val = %d\n", ret_val );
  return ret_val;
}
