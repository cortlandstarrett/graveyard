/*========================================================================
 *
 * File:      $RCSfile: myAST.cpp,v $
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
/*  This file should be accompanied by DISCLAIMER.TXT stating disclaimers */

#include "myAST.h"
#include <string.h>
#include <stdio.h>
#include "P.h"

const vchar *AST::vcharBuffer = 0;

AST::AST(ANTLRTokenPtr tokenNew, AST *other) :
	pToken(tokenNew),
  datatype(UNKNOWN_DATATYPE),
  rType(RELOC_NOT_YET_ADDED),
  itemNext(NULL),
  objPtr(0),
  vcharText(0)
{
  setSegLength(0);
  setReadOnly(1);
  if (other)
    setDatatype(other->getDatatype());
}

AST::AST(ANTLRTokenPtr tokenNew, ANTLRTokenType type) :
	pToken(tokenNew),
  datatype(UNKNOWN_DATATYPE),
  rType(RELOC_NOT_YET_ADDED),
  itemNext(NULL),
  objPtr(0),
  vcharText(0)
{
  setSegLength(0);
  setReadOnly(1);
  setType(type);
}

AST::AST(ANTLRTokenType type, AST *other) :
  pToken(new ANTLRToken(type)),
  datatype(UNKNOWN_DATATYPE),
  rType(RELOC_NOT_YET_ADDED),
  itemNext(NULL),
  objPtr(0),
  vcharText(0)
{
  setSegLength(0);
  setReadOnly(1);
  if (other)
    {
      setColumn(other->getColumn());
      setLine(other->getLine());
      setDatatype(other->getDatatype());
      setOffset( other->getOffset() );
    }
  else
    setOffset( -1 );
}

AST::~AST()
{
   pToken=NULL;
   if (vcharText)
     delete [] vcharText;
};

void AST::dumpNode(const char * s, const char *buffer)
{
  
  ANTLRChar *		q;

  if (! this)
    return;
  if (s != 0)
    {
      printf("%s ",s);
    };
  if (pToken->getType() == Eof)
    {
      printf("TokenType (%s) AST # %d\n",
             P::tokenName(pToken->getType()),
             serial);
    }
  else
    {
    q=mytoken(pToken)->getText();
    if (q == 0)
      {
        q="";
      }
    else if (strcmp(q,"\n") == 0)
      {
        q="NL";
      };
    int next_serial = 0;
    if (itemNext)
      next_serial = itemNext->serial;
    printf("Tt(%s) Tv(%s) #=%d Ln=%d Co=%d So=%d Sl=%d DT=%d rT=%d rN=%d oP=%p Id=%p",
           P::tokenName(pToken->getType()),
           q,
           serial,
           getLine(),
           getColumn(),
           getOffset(),
           getSegLength(),
           datatype,
           rType,
           next_serial,
           objPtr,
           object_id.get_entire_value()
           );
    if ( buffer )
      {
        long int ofs = getOffset();
        long int sg = (size_t)getSegLength();
        if ( ( ofs != -1 ) && ( sg > 0 ) )
          {
            char *ts = new char[sg+1];
            strncpy(ts, buffer+ofs, (size_t)sg);
            ts[sg] = '\0';
            if (sg <20)
              printf(", Ts: %s\n", ts);
            else
              printf(", Ts:\n%s\n", ts);
            delete [] ts;
          }
        else
          printf("\n");
      }
    else
      printf("\n");

  };
}

char *AST::getGenVarName()
{
  char *retv = NULL;
  if (this)
    retv = genVarName;
  return retv;
}

void AST::setGenVarName(char *s)
{
  if (this)
    strcpy ( genVarName, s );
}

const vchar *AST::getVcharText()
{
  vchar *retv = 0;
  if (this)
    {
      if (vcharText)
        retv = vcharText;
      else
        {
          if (vcharBuffer)
            {
              ANTLRChar *string = pToken->getText();
              long int offset = getOffset();        
              const vchar *text = &vcharBuffer[offset];
              size_t length = ::strlen(string);
              vcharText = (vchar *)new vchar[length + 1];
              vchar *endpt = vcharCopyBounded( text, vcharText, length );
              *endpt = 0;
              retv = vcharText;
            }
        }
    }
  return retv;
}



