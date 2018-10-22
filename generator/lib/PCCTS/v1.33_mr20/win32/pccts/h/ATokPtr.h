/* ATokPtr.h
 *
 * SOFTWARE RIGHTS
 *
 * We reserve no LEGAL rights to the Purdue Compiler Construction Tool
 * Set (PCCTS) -- PCCTS is in the public domain.  An individual or
 * company may do whatever they wish with source code distributed with
 * PCCTS or the code generated by PCCTS, including the incorporation of
 * PCCTS, or its output, into commerical software.
 *
 * We encourage users to develop software with PCCTS.  However, we do ask
 * that credit is given to us for developing PCCTS.  By "credit",
 * we mean that if you incorporate our source code into one of your
 * programs (commercial product, research project, or otherwise) that you
 * acknowledge this fact somewhere in the documentation, research report,
 * etc...  If you like PCCTS and have developed a nice tool with the
 * output, please mention that you developed it using PCCTS.  In
 * addition, we ask that this header remain intact in our source code.
 * As long as these guidelines are kept, we expect to continue enhancing
 * this system and expect to make other tools available as they are
 * completed.
 *
 * ANTLR 1.33
 * Written by Russell Quong June 30, 1995
 * Adapted by Terence Parr to ANTLR stuff
 * Parr Research Corporation
 * with Purdue University and AHPCRC, University of Minnesota
 * 1989-1998
 */

#ifndef ATokPtr_h
#define ATokPtr_h

#include "pcctscfg.h"

#include "pccts_stdio.h"

PCCTS_NAMESPACE_STD

// pointer to a reference counted object
// robust in that an unused ANTLRTokenPtr can point to NULL.

class ANTLRAbstractToken;

class DllExportPCCTS ANTLRTokenPtr {
public:
    ANTLRTokenPtr(ANTLRAbstractToken *addr=NULL){ptr_ = addr; ref();}
    ANTLRTokenPtr(const ANTLRTokenPtr &lhs)	{ptr_ = lhs.ptr_; lhs.ref();}
    ~ANTLRTokenPtr();

    // use ANTLRTokenPtr as a pointer to ANTLRToken
//
//  8-Apr-97	MR1	Make operator -> a const member function
//			  as well as some other member functions
//
    ANTLRAbstractToken *operator-> () const { return ptr_; }		// MR1
//
//  7-Apr-97 133MR1
//	     Fix suggested by Andreas Magnusson
//			(Andreas.Magnusson@mailbox.swipnet.se)
    void operator = (const ANTLRTokenPtr & lhs);		    	// MR1
    void operator = (ANTLRAbstractToken *addr);
    int operator != (const ANTLRTokenPtr &q) const	    		// MR1 // MR11 unsigned -> int
	{ return this->ptr_ != q.ptr_; }
    int operator == (const ANTLRTokenPtr &q) const  			// MR1 // MR11 unsigned -> int
	{ return this->ptr_ == q.ptr_; }
    int operator == (const ANTLRAbstractToken *addr) const      // MR11
    { return this->ptr_ == addr; }
    int operator != (const ANTLRAbstractToken *addr) const      // MR11
    { return this->ptr_ != addr; }

    void ref() const;
    void deref();

protected:
    ANTLRAbstractToken *ptr_;
};

//typedef ANTLRTokenPtr _ANTLRTokenPtr;

/*
 * Since you cannot redefine operator->() to return one of the user's
 * token object types, we must down cast.  This is a drag.  Here's
 * a macro that helps.  template: "mytoken(a-smart-ptr)->myfield".
 */
#define mytoken(tk) ((ANTLRToken *)(tk.operator->()))

#endif
