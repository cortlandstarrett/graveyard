/*========================================================================
 *
 * File:      $RCSfile: myAST.h,v $
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
#ifndef MYAST_H
#define MYAST_H

#include "p_types.hh"
#include "ASTBase.h"
#include "noleakAST.h"
#include "myToken.h"
#include "ATokPtr.h"
#include "colToken.h"
#include "p_symtbl.hh"
#include "d_typdef.hh"
#include "u_id.hh"
#include "vchar.h"
#include "u_desc.hh"

union Special_Data
{
  t_core_data_type datatype;
};

class AST : public NoLeakAST
{
public:
  AST(ANTLRTokenPtr p, AST *a=0);   // constructor
  AST(ANTLRTokenType t, AST *a=0);  // constructor
  AST(ANTLRTokenPtr p, ANTLRTokenType t); // constructor
  virtual	~AST();              // destructor
  virtual void		dumpNode(const char * s=0, const char *buffer = 0);
  void append(PCCTS_AST *b)            { NoLeakAST::append(b); }
  ANTLRTokenPtr &getTokenPtr()   { return pToken; }
  // Function type() is a virtual function and must be defined
  int type()                     { return getType(); }
  AST *sibling()                 { return (AST *)ASTBase::right(); }
  AST *child()                   { return (AST *)ASTBase::down(); }

  long int getOffset()
    {
      long int retv = 0;
      if ( this )
        {
          ColToken *token = (ColToken *)(getTokenPtr().operator->());
          retv = token->getByteOffset();
        }
      return retv;
    }

  void setOffset(long int p_offset)
    {
      if ( this )
        {
          ColToken *token = (ColToken *)(getTokenPtr().operator->());
          token->setByteOffset(p_offset);
        }
    }

  int getLine()
    {
      int retv = 0;
      if ( this )
        {
          ColToken *token = (ColToken *)(getTokenPtr().operator->());
          retv = token->getLine();
        }
      return retv;
    }

  void setLine(int line)
    {
      if ( this )
        {
          ColToken *token = (ColToken *)(getTokenPtr().operator->());
          token->setLine(line);
        }
    }

  int getColumn()
    {
      int retv = 0;
      if ( this )
        {
          ColToken *token = (ColToken *)(getTokenPtr().operator->());
          retv = token->getColumn();
        }
      return retv;
    }

  void setColumn(int column)
    {
      if ( this )
        {
          ColToken *token = (ColToken *)(getTokenPtr().operator->());
          token->col = column;
        }
    }

  ANTLRTokenType getType()
    {
      ANTLRTokenType retv = (ANTLRTokenType)0;
      if (this)
        retv = pToken->getType();
      return retv;
    }

  void setType(int t)
    {
      if (this)
        pToken->setType((ANTLRTokenType)t);
    }

  ANTLRChar *getAsciiText()
    {
      ANTLRChar *retv = NULL;
      if (this)
        retv = pToken->getText();
      return retv;
    }
  
  const vchar *getVcharText();

  void setAsciiText(ANTLRChar *s)
    {
      if (this)
        {
          pToken->setText(s);
          if (vcharText)
            delete [] vcharText;
          size_t length = strlen(s);
          vcharText = new vchar[length + 1];
          vchar *t = vcharCopyScribedBounded( vcharScribeASCII(s),
                                              vcharText,
                                              length );
          *t = 0;
        }
    }

  void setVcharText(const vchar *s)
    {
      if (this)
        {
          if (vcharText)
            delete [] vcharText;
          size_t length = vcharLength(s);
          vcharText = new vchar[length + 1];
          vchar *t = vcharCopyBounded( s, vcharText, length );
          *t = 0;
          char *sa = Description::createAsciiFromVchar(s);
          pToken->setText(sa);
          Description::freeAsciiFromVchar(sa);
        }
    }

  void setDatatype(t_core_data_type dt)
    {
      if (this)
        datatype = dt;
    }

  t_core_data_type getDatatype()
    {
      t_core_data_type dt = UNKNOWN_DATATYPE;
      if (this)
        dt = datatype;
      return dt;
    }

  void markReloc(Reloc_Type_e rT)
    {
      if (this)
        rType = rT;
    }

  Reloc_Type_e getRelocType()
    {
      Reloc_Type_e lType = UNKNOWN_RELOC_TYPE;
      if (this)
        lType = rType;
      return lType;
    }

  void setItemNext(AST *p_next)
    {
      if ( this )
        itemNext = p_next;
    }

  AST *getItemNext()
    {
      AST *retv = NULL;
      if ( this )
        retv = itemNext;
      return retv;
    }

  persObjPtr getObjPtr()
    {
      persObjPtr lObjPtr = NULL;
      if (this)
        lObjPtr = objPtr;
      return lObjPtr;
    }

  void setObjPtr(persObjPtr lObjPtr)
    {
      if (this)
        objPtr = lObjPtr;
    }

  void set_Id(const Id & p_id)
    {
      if (this)
        object_id = p_id;
    }

  Id get_Id()
    {
      Id id = Id::Default;
      if (this)
        id = object_id;
      return id;
    }

  static void setVcharBuffer(const vchar *p_buf)
    {
      vcharBuffer = p_buf;
    }

  static const vchar* getVcharBuffer()
    {
      return vcharBuffer;
    }

  void panic ( const char *msg )
    { throw msg; }

  char isReadOnly()
    { return p.read_only; }

  void setReadOnly(char p_ro)
    { p.read_only = p_ro; }

  // These functions are used by the verifier back end
  void setSegLength(long int p_len)
    {
      if (this)
        p.segLength = p_len;
    }

  long int getSegLength()
    {
      long int retv = 0;
      if (this)
        {
          if (p.segLength == 0)
            {
              ANTLRChar *s = NULL;
              s = pToken->getText();
              if ( s )
                {
                  p.segLength = strlen( s );
                }
            }
          retv = p.segLength;
        }
      return retv;
    }

  long int getTokenLength()
    {
      long int retv = 0;
      if (this)
        {
          ANTLRChar *s = NULL;
          s = pToken->getText();
          if ( s )
            {
              retv = ::strlen( s );
            }
        }
      return retv;
    }

  // These functions are used by the generator back end
  char *getGenVarName();
  void setGenVarName(char *s);

  
private:
  ANTLRTokenPtr pToken;
  t_core_data_type datatype;
  Reloc_Type_e rType; 
  AST *itemNext;
  persObjPtr objPtr;
  Id object_id;
  vchar *vcharText;
  union
  {
    char genVarName[6];
    struct
    {
      long int segLength;
      char read_only;
    } p;
  };
  static const vchar *vcharBuffer;
};

#endif
