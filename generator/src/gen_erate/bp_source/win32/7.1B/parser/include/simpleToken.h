/*========================================================================
 *
 * File:      $RCSfile: simpleToken.h,v $
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
#ifndef SIMPLETOKEN_H
#define SIMPLETOKEN_H

/*  This file should be accompanied by DISCLAIMER.TXT stating disclaimers */

#include "AToken.h"

class SimpleToken : public ANTLRRefCountToken {

protected:
	ANTLRTokenType 		_type;
public:
	int 			_line;
	SimpleToken(ANTLRTokenType t)
		{ setType(t);
		  _line = 0;
		}
	SimpleToken()
		{ setType((ANTLRTokenType)0);
		  _line = 0;
		}
	ANTLRTokenType	getType() const	{ return _type; }
	void setType(ANTLRTokenType t)	{ _type = t; }
	virtual int getLine() const		{ return _line; }
	void setLine(int line)	    	{ _line = line; }
};

#endif
