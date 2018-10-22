/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef FIX_LOAD_HH
#define FIX_LOAD_HH

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

#include <ostore/dumpload/obj_loader.hh>


/***********************************************************************
  class os_Fixup_loader
***********************************************************************/

class os_Fixup_loader : public os_Object_loader {

  public: // Construction
    os_Fixup_loader ();
    ~os_Fixup_loader ();

  public: // Accessors
    virtual Kind get_kind () const;

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
                                           os_Loader_info& info);

  protected: // Accessors
    virtual os_Type_loader* find_type_loader (os_Object_info& info) const;
    virtual os_boolean is_handling_transactions (os_Loader_info* = 0) const;

  protected: // Actions
    virtual os_Loader_action* load (os_Loader_stream& stream,
                                    os_Loader_info& info);
    virtual void create (os_Loader_info& info);

  private: // Friends
    friend class os_Loader;

  };


/***********************************************************************
  class os_Fixup_info
***********************************************************************/

class os_Fixup_info : public os_Object_info {

  public: // Static Construction
    static os_Fixup_info& create_pending_info (const os_Fixup_info&);
    static os_Fixup_info& create_pending_info (const os_Fixup_info&,
                                               void* pending_data);

  public: // Construction
    os_Fixup_info (os_Object_loader&, os_Loader_stream&,
                   os_Loader_info& previous_info);
    os_Fixup_info (const os_Fixup_info&);
    os_Fixup_info (const os_Fixup_info&, void* pending_data);
    ~os_Fixup_info ();

  public: // Accessors
    virtual os_Loader_action::Kind get_kind () const;
    os_boolean has_pending_data () const;
    void* get_pending_data () const;

  public: // Modifiers
    void set_pending_data (void*);

  protected: // Embedded data
    void* pending_data;

  private: // Friends
    friend class os_Fixup_loader;
    friend class os_Type_fixup_loader;

  };


/***********************************************************************
  class os_Type_fixup_loader
***********************************************************************/

class os_Type_fixup_loader : public os_Type_loader {

  public: // Construction
    os_Type_fixup_loader ();
    ~os_Type_fixup_loader ();

  public: // Accessors
    virtual Kind get_kind () const;

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
                                           os_Loader_info& info) = 0;
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
                                           os_Object_info& info,
                                           unsigned number_elements);

  protected: // Actions
    virtual os_Loader_action* load (os_Loader_stream& stream,
                                    os_Type_data& data,
                                    os_boolean is_most_derived_class) = 0;
    virtual void fixup (os_Type_fixup_info& info,
                        os_boolean is_most_derived_class) = 0;

  private: // Actions
    virtual void create (os_Loader_info& info);
    virtual os_Loader_action* load (os_Loader_stream& stream,
                                    os_Loader_info& info,
                                    os_boolean is_most_derived_class);
    virtual void fixup (os_Type_data& data, void* object,
                        os_boolean is_most_derived_class);

  private: // Friends
  //friend void os_Fixup_registration_entry::set_context (os_Loader& loader);

// Shut up Solaris
   virtual os_Loader_action* load (os_Loader_stream& a, os_Loader_info& b)
      {return 0;}
   virtual os_Loader_action* load (os_Loader_stream& a, os_Type_data& b, unsigned c, unsigned d)
      {return os_Type_loader::load(a,b,c,d);}
   virtual void fixup (os_Type_data& a, void* b, unsigned c, unsigned d, unsigned e)
      {os_Type_loader::fixup(a,b,c,d,e);}
  };


/***********************************************************************
  class os_Type_fixup_info
***********************************************************************/

class os_Type_fixup_info : public os_Type_info {

  public: // Construction
    os_Type_fixup_info (os_Type_loader&, os_Loader_stream&, os_Fixup_info&);
    ~os_Type_fixup_info ();

  public: // Accessors
    virtual os_Loader_action::Kind get_kind () const;

  private: // Friends
    friend class os_Type_fixup_loader;

  };


#endif /* FIX_LOAD_HH */
