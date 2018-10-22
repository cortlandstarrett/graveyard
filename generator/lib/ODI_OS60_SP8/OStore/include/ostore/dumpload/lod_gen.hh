/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef LOD_GEN_HH
#define LOD_GEN_HH

/***********************************************************************
*                                                                      *
* Copyright (c) 1998-2000 by eXcelon Corporation. All Rights Reserved.                          *
*                                                                      *
* eXcelon Corporation Confidential Restricted material.  This work     *
* contains confidential trade secrets of eXcelon Corp..  Use,          *
* examination, copying, transfer and/or disclosure to others are       *
* prohibited, except with the express written agreement of eXcelon     *
* Corp.                                                                *
*                                                                      *
* THIS WORK IS PROVIDED AS IS, WHERE IS, WITH ABSOLUTELY NO WARRANTIES *
* WHATSOEVER, WHETHER EXPRESS OR IMPLIED.                              *
*                                                                      *
***********************************************************************/
/***********************************************************************
* Author:  Rick Tompkins                                               *
* Version: 0.0                                                         *
***********************************************************************/


//-- Include files -----------------------------------------------------

#include <ostore/ostore.hh>
#include <ostore/coll.hh>

#include <ostore/dumpload/intrpgen.hh>
#include <ostore/dumpload/intrplod.hh>


/***********************************************************************
  class os_Embedded_loader_generator
***********************************************************************/

class os_Embedded_loader_generator : public os_Interpretive_loader_generator
{

  public: // Construction
    os_Embedded_loader_generator (os_Interpretive_loader&, os_Traverser&);
    ~os_Embedded_loader_generator ();

  public: // Accessors

  public: // Modifiers

  public: // Base Actions
    // Pre-actions
    virtual os_boolean pre_action (const os_base_class& base_class);

  public: // Member Variable Actions
    // Pre-actions
    virtual os_boolean pre_action (const os_member_variable& member_variable);

  protected: // Embedded data

  };


#endif /* LOD_GEN_HH */
