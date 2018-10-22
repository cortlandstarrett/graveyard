/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef CLUSTER_ACTION_HH
#define CLUSTER_ACTION_HH

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
#include <ostore/traverse/obj_act.hh>



/***********************************************************************
  class os_Cluster_node
***********************************************************************/

class  _OS_DLLIMPORT(_OS_TRAVERSE) os_Cluster_node : public os_Action_node {

  public: // Construction
    os_Cluster_node (os_Cluster_action&, os_cluster&);
    virtual ~os_Cluster_node ();

  public: // Accessors
    virtual os_Action::Action_kind get_kind () const;
    os_Cluster_action& get_cluster_action () const;
    os_cluster& get_cluster () const;

  public: // Visitors
    virtual void be_visited_by(os_Action_node_visitor &visitor) const
      { visitor.visit(*this); }

  public: // Embedded data
    os_cluster* cluster;

  };


/***********************************************************************
  class os_Cluster_action
***********************************************************************/

class  _OS_DLLIMPORT(_OS_TRAVERSE) os_Cluster_action : public os_Action {

  public: // Construction
    os_Cluster_action (os_Object_action* object_action = 0);
    os_Cluster_action (const os_Cluster_action& cluster_action);
    virtual ~os_Cluster_action ();
    virtual os_Action& duplicate (const os_Action*) const;

  public: // static Actions
    static void invoke (os_Cluster_action& cluster_action,
			os_cluster& given_cluster) { 
      
      os_Cluster_node node(cluster_action, given_cluster);
      os_Cluster_action& action = node.setup_action();
      (action)(given_cluster);
    }

  public: // Accessors
    virtual Action_kind get_kind () const;
    virtual int has_state () const;

  public: // Actions
    virtual void operator () (os_cluster& cluster);

  protected: // Embedded data
    os_Object_action* object_action;

  protected: // Accessors
    os_Cluster_node& get_cluster_node () const;

  protected: // Modifiers
    virtual void set_traverser (os_Traverser&);

  protected: // Actions
    os_boolean pre_action (os_cluster& cluster);
    virtual void component_action (os_cluster& cluster);
    void post_action (os_cluster& cluster);

  protected: // Debugging
    virtual void enter (const char* class_name, 
			const char* function_name, os_cluster& cluster);
    virtual void exit (const char* class_name, 
		       const char* function_name, os_cluster& cluster);

  private: // Friends
    friend class os_Segment_action;

  };


#endif /* CLUSTER_ACTION_HH */
