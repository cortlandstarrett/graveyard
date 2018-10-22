/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef SEG_ACTION_HH
#define SEG_ACTION_HH

/***********************************************************************
*                                                                      *
* Copyright (c) 1997-2000 by eXcelon Corporation. All Rights Reserved.                          *
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

//-- Include files -----------------------------------------------------

#include <ostore/ostore.hh>
#include <ostore/traverse/action.hh>
#include <ostore/traverse/cluster_act.hh>


/***********************************************************************
  class os_Segment_node
***********************************************************************/

class  _OS_DLLIMPORT(_OS_TRAVERSE) os_Segment_node : public os_Action_node {

  public: // Construction
    os_Segment_node (os_Segment_action&, os_segment&);
    virtual ~os_Segment_node ();

  public: // Accessors
    virtual os_Action::Action_kind get_kind () const;
    os_Segment_action& get_segment_action () const;
    os_segment& get_segment () const;

  public: // Visitors
    virtual void be_visited_by(os_Action_node_visitor &visitor) const
      { visitor.visit(*this); }

  public: // Embedded data
    os_segment* segment;
  };


/***********************************************************************
  class os_Segment_action
***********************************************************************/

class  _OS_DLLIMPORT(_OS_TRAVERSE) os_Segment_action : public os_Action {

  public: // Construction
    os_Segment_action (os_Cluster_action* cluster_action);
    os_Segment_action (os_Object_action* object_action = 0);
    os_Segment_action (const os_Segment_action& segment_action);
    virtual ~os_Segment_action ();
    virtual os_Action& duplicate (const os_Action*) const;

  public: // static Actions
    static void invoke (os_Segment_action& segment_action,
			os_segment& given_segment) { 
      os_Segment_node node(segment_action, given_segment);
      os_Segment_action& action = node.setup_action();
      (action)(given_segment);
    }

  public: // Accessors
    virtual Action_kind get_kind () const;
    virtual int has_state () const;

  public: // Actions
    virtual void operator () (os_segment& segment);

  protected: // Embedded data
    os_Cluster_action* cluster_action;
    os_Object_action*  object_action;

  protected: // Accessors
    os_Segment_node& get_segment_node () const;

  protected: // Modifiers
    virtual void set_traverser (os_Traverser&);

  protected: // Actions
    os_boolean pre_action (os_segment& segment);
    virtual void segment_action (os_segment& segment);
    void post_action (os_segment& segment);

  protected: // Debugging
    virtual void enter (const char* class_name, 
			const char* function_name, os_segment& segment);
    virtual void exit (const char* class_name, 
		       const char* function_name, os_segment& segment);

  private: 
    friend class os_Database_action;
    

  };


#endif /* SEG_ACTION_HH */
