/*========================================================================
 *
 * File:      $RCSfile: colToken.h,v $
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
#ifndef COLTOKEN_H
#define COLTOKEN_H

/*  This file should be accompanied by DISCLAIMER.TXT stating disclaimers */

#include "tokens.h"
#include "noleakTok.h"
#include "AToken.h"

struct ColToken : public NoLeakToken {

       /* constructor */		ColToken();
       /* destructor */ virtual	   	~ColToken();
       /* constructor */		ColToken(ANTLRTokenType t);
       /* constructor */		ColToken(ANTLRTokenType t,
    					           ANTLRChar *	text,
					           int		line);
       /* copy constructor */	        ColToken(const ColToken &);

       static long int accumulated_offset;
       ColToken &			operator = (const ColToken &);
       virtual void	          	dumpNode(const char * s=0);
       virtual ANTLRChar * 		getText() const {return pText;};
       virtual ANTLRAbstractToken *	makeToken(
						ANTLRTokenType	ANTLRTokenType,
					        ANTLRChar	*text,
					        int		line);
       virtual void 			setText(const ANTLRChar *s);

       int				col;		// column
       int getColumn() { return col; }
       long int byte_offset;
       long int getByteOffset() const { return byte_offset; }
       void setByteOffset() { byte_offset = accumulated_offset + col - 1; }
       void setByteOffset(long int p_offset) { byte_offset = p_offset; }
       static void update_offset( int colval ) {
         accumulated_offset += colval;
       }
       ANTLRChar *			pText;

       void panic ( const char *msg )
         { throw msg; }

private:
       void				init();
};

#endif



