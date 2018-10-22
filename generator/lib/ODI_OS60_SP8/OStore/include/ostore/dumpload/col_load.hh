/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef COL_LOAD_HH
#define COL_LOAD_HH

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


#include <ostore/dumpload/db_loader.hh>
#include <ostore/dumpload/fixup.hh>
#include <ostore/dumpload/fix_load.hh>

class os_coll_rep_list;
class os_coll_index_list;
class os_collection_load;


/**********************************************************************
  All os_Type_loader and os_Type_fixup_loader classes
***********************************************************************/

class os_coll_loader : public os_Type_loader {

  public:
     os_coll_loader();
    ~os_coll_loader();
  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					os_Loader_info& info);
    
  public: // Actions
    virtual void fixup (os_Type_data& data, void* object,
       os_boolean is_most_derived_class);
    virtual os_Loader_action* load (os_Loader_stream& stream,
		 os_Type_data& data,os_boolean is_most_derived_class);
    virtual void construct (os_Type_data& data, void* object,
                        os_boolean is_most_derived_class);
    virtual void create (os_Loader_info& info);

  public: // Static
     static os_coll_loader& get (); 


};

class os_skip_coll_loader : public os_Type_loader {

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					os_Loader_info& info);
    
  public: // Actions
    virtual void fixup (os_Type_data& data, void* object,
       os_boolean is_most_derived_class);
    virtual os_Loader_action* load (os_Loader_stream& stream,
		 os_Type_data& data,os_boolean is_most_derived_class);
    virtual void construct (os_Type_data& data, void* object,
                        os_boolean is_most_derived_class);
    virtual void create (os_Loader_info& info);

  public: // Static
     static os_skip_coll_loader& get (); 


};

class os_cursor_loader : public os_Type_loader {

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					os_Loader_info& info);
    
  public: // Actions
     virtual void fixup (os_Type_data& data, void* object,
        os_boolean is_most_derived_class);
     virtual os_Loader_action* load (os_Loader_stream& stream,
	     os_Type_data& data,os_boolean is_most_derived_class);
    virtual void construct (os_Type_data& data, void* object,
                        os_boolean is_most_derived_class);
     virtual void create (os_Loader_info& info);

  public: // Static
     static os_cursor_loader& get (); 

};

class os_cursor_fixup_loader : public os_Type_fixup_loader {

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
				                    	os_Loader_info& info);
    
  public: // Actions
    virtual os_Loader_action* load (os_Loader_stream& stream,
              			 os_Type_data& data,os_boolean is_most_derived_class) 
				 {return (os_Loader_action *)0;}
    virtual void fixup (os_Type_fixup_info& info,os_boolean is_most_derived_class);
  private:
//shut up solaris
    virtual os_Loader_action* operator () (os_Loader_stream& a, os_Object_info& b, unsigned c)
       {return os_Type_fixup_loader::operator()(a,b,c);}
    virtual void fixup (os_Type_data& a, void* b, unsigned c, unsigned d, unsigned e)
       {}
    virtual os_Loader_action* load (os_Loader_stream& a, os_Type_data& b, unsigned c, unsigned d)
       {return 0;}
    virtual os_Loader_action* load (os_Loader_stream& a, os_Loader_info& b)
       {return 0;}
    virtual os_Loader_action* load (os_Loader_stream& a, os_Loader_info& b, int c)
       {return 0;}
};

class os_coll_index_fixup_loader : public os_Type_fixup_loader {

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					os_Loader_info& info);
    
	virtual void fixup (os_Type_data& data, void* object) {}
 public: // Actions
    virtual os_Loader_action* load (os_Loader_stream& stream,
                 				 os_Type_data& data,os_boolean is_most_derived_class);
       
    virtual void fixup (os_Type_fixup_info& info,os_boolean is_most_derived_class); 
//shut solaris up
    virtual os_Loader_action* operator () (os_Loader_stream& a, os_Object_info& b, unsigned c)
       {return os_Type_fixup_loader::operator()(a,b,c);}
    virtual void fixup (os_Type_data& a, void* b, unsigned c, unsigned d, unsigned e)
       {}
    virtual os_Loader_action* load (os_Loader_stream& a, os_Type_data& b, unsigned c, unsigned d)
       {return 0;}
    virtual os_Loader_action* load (os_Loader_stream& a, os_Loader_info& b)
       {return 0;}
    virtual os_Loader_action* load (os_Loader_stream& a, os_Loader_info& b, int c)
       {return 0;}
};

class os_coll_query_loader : public os_Type_loader {

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					os_Loader_info& info);
    
    virtual void fixup (os_Type_data& data, void* object,
       os_boolean is_most_derived_class);
  public: // Actions
    virtual os_Loader_action* load (os_Loader_stream& stream,
				 os_Type_data& data,os_boolean is_most_derived_class);
    virtual void create (os_Loader_info& info);
    virtual void construct (os_Type_data& data, void* object,
                        os_boolean is_most_derived_class);
//shut solaris up
    virtual void fixup (os_Type_data& a, void* b, unsigned c, unsigned d, unsigned e)
       {}
    virtual os_Loader_action* load (os_Loader_stream& a, os_Type_data& b, unsigned c, unsigned d)
       {return 0;}
    virtual os_Loader_action* load (os_Loader_stream& a, os_Loader_info& b)
       {return 0;}
    virtual os_Loader_action* load (os_Loader_stream& a, os_Loader_info& b, int c)
       {return 0;}
    virtual os_Loader_action* operator () (os_Loader_stream& a, os_Object_info& b, unsigned c)
       {return os_Type_loader::operator()(a,b,c);}
};

class os_coll_element_fixup_loader : public os_Type_fixup_loader {

  public: // Accessors
    virtual os_boolean is_handling_transactions (os_Loader_info* = 0) const;

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					os_Loader_info& info);

    virtual void fixup (os_Type_data& data, void* object,
       os_boolean is_most_derived_class) {}    

  public: // Actions
    virtual os_Loader_action* load (os_Loader_stream& stream,
				 os_Type_data& data,os_boolean is_most_derived_class);
    virtual void fixup (os_Type_fixup_info& info,os_boolean is_most_derived_class);
  private:
//shut up solaris
    virtual os_Loader_action* operator () (os_Loader_stream& a, os_Object_info& b, unsigned c)
       {return os_Type_fixup_loader::operator()(a,b,c);}
    virtual void fixup (os_Type_data& a, void* b, unsigned c, unsigned d, unsigned e)
       {}
    virtual os_Loader_action* load (os_Loader_stream& a, os_Type_data& b, unsigned c, unsigned d)
       {return 0;}
    virtual os_Loader_action* load (os_Loader_stream& a, os_Loader_info& b)
       {return 0;}
    virtual os_Loader_action* load (os_Loader_stream& a, os_Loader_info& b, int c)
       {return 0;}
};

class os_coll_embed_fixup_loader : public os_Type_fixup_loader {

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					os_Loader_info& info);

    virtual void fixup (os_Type_data& data, void* object,
       os_boolean is_most_derived_class) {}    
  public: // Actions
    virtual os_Loader_action* load (os_Loader_stream& stream,
				 os_Type_data& data,os_boolean is_most_derived_class);
    virtual void fixup (os_Type_fixup_info& info,os_boolean is_most_derived_class);

  private:
//shut solaris up
    virtual os_Loader_action* operator () (os_Loader_stream& a, os_Object_info& b, unsigned c)
       {return os_Type_fixup_loader::operator()(a,b,c);}
    virtual void fixup (os_Type_data& a, void* b, unsigned c, unsigned d, unsigned e)
       {}
    virtual os_Loader_action* load (os_Loader_stream& a, os_Type_data& b, unsigned c, unsigned d)
       {return 0;}
    virtual os_Loader_action* load (os_Loader_stream& a, os_Loader_info& b)
       {return 0;}
    virtual os_Loader_action* load (os_Loader_stream& a, os_Loader_info& b, int c)
       {return 0;}
};


/**********************************************************************
  All os_Type_data and Type_fixup_data classes
***********************************************************************/

class os_coll_data : public os_Type_data {

  public: // Construction
    os_coll_data();
    ~os_coll_data();

    void load(os_Loader_stream&,os_boolean is_most_derived_class);

  protected: // Embedded data
    
    os_int32 is_dictionary;
    os_int32 is_embedded;
    os_unsigned_int32 behavior;
    os_unsigned_int32 rep_enum;
    os_unsigned_int32 size;
    os_Dumper_reference outofline_ref;     
	 
  private: // Friends
    friend class os_coll_loader;
    friend class os_coll_info;
      
};

class os_skip_coll_data : public os_Type_data {

  public: // Construction
    os_skip_coll_data();
    ~os_skip_coll_data();

    void load(os_Loader_stream&,os_boolean is_most_derived_class);

  protected: // Embedded data
    
    os_int32 is_dictionary;
    os_int32 is_embedded;
    os_unsigned_int32 behavior;
    os_unsigned_int32 rep_enum;
    os_unsigned_int32 size;
    os_Dumper_reference outofline_ref;     
	 
  private: // Friends
    friend class os_skip_coll_loader;
    friend class os_skip_coll_info;
      
};

class os_cursor_data : public os_Type_data {

  public: // Construction
    os_cursor_data();   
	~os_cursor_data();   

    void load(os_Loader_stream&,os_boolean is_most_derived_class);
    void load_index (os_Loader_stream& stream); 
    void load_range (os_Loader_stream& stream);
    
  protected: // Embedded data
   os_int32 safe_flag;
   os_int32 use_range;
   os_int32 cursor_dummy;
   os_collection * coll_ptr;
   char * path;
   char * element_name;
   os_int32 query_type;
   os_int32 key_type;
   os_int32 low_cond;
   os_int32 high_cond;
   os_int32 del_low_val;
   os_int32 del_high_val;
   void * low_value;
   void * high_value;
 
  private: // Friends
    friend class os_cursor_loader;
    friend class os_cursor_info;
	friend class os_cursor_fixup_loader;
	friend class os_cursor_fixup_info;
      
}; 

class os_coll_index_fixup_data : public os_Type_data {

  public: // Construction
    os_coll_index_fixup_data();
    ~os_coll_index_fixup_data();   

    void load(os_Loader_stream&,os_boolean is_most_derived_class);
        
  protected: // Embedded data

   os_unsigned_int32 seg_num;  
   os_coll_index_list * index_list;   

  private: // Friends
    friend class os_coll_index_fixup_loader;
    friend class os_coll_index_fixup_info;
      
}; 

class os_coll_query_data : public os_Type_data {

  public: // Construction
    os_coll_query_data();
    ~os_coll_query_data();   

    void load(os_Loader_stream&,os_boolean is_most_derived_class);
        
  protected: // Embedded data
  
   char * element;
   char * query_string;
   char * file_name;
   os_unsigned_int32 line_number;   

  private: // Friends
    friend class os_coll_query_loader;
    friend class os_coll_query_info;
};
 
class os_coll_element_fixup_data : public os_Type_data {

  public: // Construction
    os_coll_element_fixup_data();
    ~os_coll_element_fixup_data();   

    os_Loader_action* load(os_Loader_stream&,os_boolean is_most_derived_class);

    char * get_key_name() 
       { return (char*) (void*) key_name; }

    void * get_key_value() 
       { return key_value; }

    os_collection_load * coll_dp()
       { return (os_collection_load *) (void*) _coll_dp; }

    void set_coll_dp(os_collection_load * coll_ptr)
       { _coll_dp = (void*) coll_ptr; }

    void set_loader(os_Loader* xloader)
       {loader = xloader;}
    os_Loader* get_loader()
       {return loader;}
    void set_info(os_Loader_info* i)
       {info = i;}
    os_Loader_info* get_info()
       {return info;}
        
  protected: // Embedded data
  
   os_Dumper_reference element_ref;
   os_Dumper_reference dictionary_ref;
   os_soft_pointer<void> _coll_dp;
   os_unsigned_int32 element_count;
   os_int32 dict_coll;
   os_int32 del_val;
   os_int32 key_type;
   os_soft_pointer<void> key_name;
   os_soft_pointer<void> key_value;
   os_Loader* loader;
   os_Loader_info* info;

  private: // Friends
    friend class os_coll_element_fixup_loader;
    friend class os_coll_element_fixup_info;
}; 

class os_coll_embed_fixup_data : public os_Type_data {

  public: // Construction
    os_coll_embed_fixup_data();
	~os_coll_embed_fixup_data();   

    void load(os_Loader_stream&,os_boolean is_most_derived_class);
        
  protected: // Embedded data
  
   os_Dumper_reference embedded_ref;
   os_Dumper_reference outofline_ref;
  
  private: // Friends
    friend class os_coll_embed_fixup_loader;
    friend class os_coll_embed_fixup_info;
}; 


/**********************************************************************
  All os_Type_info and os_Type_fixup_info classes
***********************************************************************/

class os_coll_info : public os_Type_info {

  public: // Construction
    os_coll_info (os_Type_loader&, os_Loader_stream&, os_Object_info&,
		       os_coll_data&);
    ~os_coll_info ();

  protected: // Embedded data
    os_coll_data * data;

  private: // Friends
    friend class os_coll_loader;
    friend class os_coll_data;
  
  };

class os_skip_coll_info : public os_Type_info {

  public: // Construction
    os_skip_coll_info (os_Type_loader&, os_Loader_stream&, os_Object_info&,
		       os_skip_coll_data&);
    ~os_skip_coll_info ();

  protected: // Embedded data
    os_skip_coll_data * data;

  private: // Friends
    friend class os_skip_coll_loader;
    friend class os_skip_coll_data;
  
  };

class os_cursor_info : public os_Type_info {

  public: // Construction
    os_cursor_info (os_Type_loader&, os_Loader_stream&, os_Object_info&,
                    os_cursor_data&);
    ~os_cursor_info ();

  protected: // Embedded data
    os_cursor_data * data;

  private: // Friends
    friend class os_cursor_loader;
    friend class os_cursor_data;
  
  };

class os_cursor_fixup_info : public os_Type_fixup_info {

  public: // Construction
    os_cursor_fixup_info (os_Type_loader&, os_Loader_stream&, os_Fixup_info&, os_cursor_data&);
    ~os_cursor_fixup_info ();

  protected: // Embedded data
    os_cursor_data * data;

  private: // Friends
    friend class os_cursor_fixup_loader;
    friend class os_cursor_data;
  
  };

class os_coll_index_fixup_info : public os_Type_fixup_info {

  public: // Construction
    os_coll_index_fixup_info (os_Type_loader&, os_Loader_stream&, os_Fixup_info&,
	                          os_coll_index_fixup_data&);
    ~os_coll_index_fixup_info ();

  protected: // Embedded data
    os_coll_index_fixup_data * data;

  private: // Friends
    friend class os_coll_index_fixup_loader;
    friend class os_coll_index_fixup_data;
  
  };

class os_coll_query_info : public os_Type_info {

  public: // Construction
    os_coll_query_info (os_Type_loader&, os_Loader_stream&, os_Object_info&,
		       os_coll_query_data&);
    ~os_coll_query_info ();

  protected: // Embedded data
    os_coll_query_data * data;
	
  private: // Friends
    friend class os_coll_query_loader;
    friend class os_coll_query_data;
  
  };

class os_coll_element_fixup_info : public os_Type_fixup_info {

  public: // Construction
    os_coll_element_fixup_info (os_Type_loader&, os_Loader_stream&, os_Fixup_info&,
		                        os_coll_element_fixup_data&);
    
    ~os_coll_element_fixup_info ();

  protected: // Embedded data
    os_coll_element_fixup_data * data;

  private: // Friends
    friend class os_coll_element_fixup_loader;
    friend class os_coll_element_fixup_data;
  
  };

class os_coll_embed_fixup_info : public os_Type_fixup_info {

  public: // Construction
    os_coll_embed_fixup_info (os_Type_loader&, os_Loader_stream&, os_Fixup_info&,
		                      os_coll_embed_fixup_data&);
    
    ~os_coll_embed_fixup_info ();

  protected: // Embedded data
    os_coll_embed_fixup_data * data;

  private: // Friends
    friend class os_coll_embed_fixup_loader;
    friend class os_coll_embed_fixup_data;
  
  };



#endif /*COL_LOAD_HH */     

