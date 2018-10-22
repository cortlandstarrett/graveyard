/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef CHAINLST_HH
#define CHAINLST_HH

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

//-- Forward Definitions -----------------------------------------------


template <class Element_type> class os_Chained_list;
template <class Element_type> class os_Chained_list_cursor;


/***********************************************************************
  class os_Chained_list_block
***********************************************************************/

template <class Element_type> class _OS_DLLIMPORT(_OS_TRAVERSE) os_Chained_list_block {

  protected: // Construction
    os_Chained_list_block (os_unsigned_int32 block_size);
    ~os_Chained_list_block ();

  protected: // Modifiers
    Element_type* get_unused_slot (os_unsigned_int32 block_size);
    void empty ();
    void clear (os_unsigned_int32 block_size);

  protected: // ObjectStore
    static os_typespec* get_os_typespec ();

  protected: // Embedded data
    os_Chained_list_block<Element_type>* next;
    os_unsigned_int32 used;
    Element_type* values;

  protected: // ObjectStore
    os_typespec* get_typespec () const;

  private: // Friends
    friend class os_Chained_list<Element_type>;
    friend class os_Chained_list_cursor<Element_type>;

  public: // Instantiation
    static int _instantiate ();

  };


/***********************************************************************
  class os_Chained_list
***********************************************************************/

template <class Element_type> class _OS_DLLIMPORT(_OS_TRAVERSE) os_Chained_list {

  public: // Construction
    os_Chained_list (os_unsigned_int32 block_size = default_block_size);
    ~os_Chained_list ();

  public: // Static accessor
    os_unsigned_int32 get_default_block_size ();

  public: // Static modifier
    void set_default_block_size (os_unsigned_int32 block_size);

  public: // Accessors
    os_boolean is_empty () const;

  public: // Modifiers
    Element_type* get_unused_slot ();
    Element_type& append (const Element_type&);
    void empty ();
    void clear ();

  public: // ObjectStore
    static os_typespec* get_os_typespec ();

  protected: // Embedded data
    os_Chained_list_block<Element_type>* first_block;
    os_Chained_list_block<Element_type>* last_block;
    os_unsigned_int32 block_size;

  protected: // Static data
    static os_unsigned_int32 default_block_size;

  private: // Friends
    friend class os_Chained_list_cursor<Element_type>;

  public: // Instantiation
    static int _instantiate ();

  };


/***********************************************************************
  class os_Chained_list_cursor
***********************************************************************/

template <class Element_type> class _OS_DLLIMPORT(_OS_TRAVERSE) os_Chained_list_cursor {

  public: // Construction
    os_Chained_list_cursor (const os_Chained_list<Element_type>&);
    ~os_Chained_list_cursor ();

  public: // Modifiers
    Element_type* first ();
    Element_type* next ();
    Element_type* current ();

  public: // ObjectStore
    static os_typespec* get_os_typespec ();

  protected: // Embedded data
    os_Chained_list<Element_type>* list;
    os_Chained_list_block<Element_type>* block;
    os_unsigned_int32 block_index;

  public: // Instantiation
    static int _instantiate ();

  };


#endif /* CHAINLST_HH */
