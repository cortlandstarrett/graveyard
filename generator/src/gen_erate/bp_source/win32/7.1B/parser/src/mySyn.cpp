/*========================================================================
 *
 * File:      $RCSfile: mySyn.cpp,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:23 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include "tokens.h"
#include "myToken.h"
#include "P.h"
#include "myAST.h"
#include "p_msgs.hh"

void P::syn(ANTLRAbstractToken *	tok,
            ANTLRChar *			egroup,
            SetWordType *		eset,
            ANTLRTokenType		etok,
            int				k)
{
	int	line;
	int	col;
  ANTLRTokenPtr atok = (ANTLRTokenPtr)LT(1);

  AST astfromtok ( atok );
  AST* p_astfromtok = &astfromtok;

  long int seglen = strlen( atok->getText() );

  p_astfromtok->setSegLength( seglen );
  const vchar *orig_text = p_astfromtok->getVcharText();
  
  AL_PARSE_ERR1( p_astfromtok, AL_GETMSG(ERR,300,1), orig_text )

	if ( !etok && !eset )
    {
      AL_MSG_STR( "\n" );
      return;
    }
	if ( k==1 )
    {
      AL_MSG_STR( "; missing" );
    }
  else
    {
      AL_MSG_STR( "; \"%s\" not",
                    orig_text );
      if ( set_deg(eset)>1 )
        AL_MSG_STR( " in" );
    }
	if ( set_deg(eset)>0 )
    {
      edecode(eset);
    }
  else
    {
      AL_MSG_STR( " %s", vcharScribeASCII(token_tbl[etok]) );
    }
  if ( strlen(egroup) > 0 )
    AL_MSG_STR( " in %s", vcharScribeASCII(egroup) );
	AL_MSG_STR( "\n" );
}

//
// Formatting information for emacs
//
// Local Variables:
// tab-width:2
// End:
//
