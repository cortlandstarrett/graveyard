/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef COLL_DL_HH
#define COLL_DL_HH

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

#include <ostore/coll/coll.hh>
/* #include <ostore/coll/tarray.hh> */
#include <dumpload/loader.hh>

//-- forward declarations ---------------------------------------------

class os_Loader_stream; 
class os_Dumper_stream;
class os_Dumper_reference;
class os_Dumper;
class os_coll_rep_list;
class os_coll_index_list;


/***********************************************************************
  Various defines
***********************************************************************/
/* the following fixup names used by both dump and load */
#define OS_COLL_INDEX    "os_coll_index"
#define OS_COLL_CURSOR   "os_coll_cursor"
#define OS_COLL_ELEMENTS "os_coll_elements"
#define OS_COLL_EMBED    "os_coll_embed" 

/* define some collection rep types */
#define OS_DICTIONARY_COLL "os_dictionary"
#define OS_DICTIONARY "os_Dictionary"
#define OS_ARRAY "os_Array"
#define OS_BAG "os_Bag"
#define OS_LIST "os_List"
#define OS_NLIST "os_nList"
#define OS_SET "os_Set"
#define OS_COLLECTION "os_Collection"

/* used for os_dictinary instantiation strings AND
   mark schema strings*/
#define OS_TEMPLATE_NAME "template "
#define OS_DICT_TEMPLATE "os_Dictionary<"
#define OS_DICT_MARK "OS_MARK_DICTIONARY("
#define OS_rDICT_TEMPLATE "os_rDictionary<"
#define OS_rDICT_MARK "OS_MARK_RDICTIONARY("
#define OS_CHAR_ARRAY "os_char_array<"

/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::
  Description: ObjectStore collection dumping API
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

class os_collection_dump {

private:

   os_soft_pointer<void> coll_ref;
   os_cursor * this_cursor;
   os_coll_query * this_query;
   os_int32 dictionary_collection;

public:

   /* constructors and destructors */
   os_collection_dump(os_collection *);
   os_collection_dump(os_cursor *);
   os_collection_dump(os_coll_query*);

   ~os_collection_dump();

   /* dump header information */

   void dump_os_cursor(os_Dumper_stream& stream);
   void dump_coll_header(os_Dumper_stream& stream, os_int32 is_embedded);
   void dump_coll_embed_fixup(os_Dumper_stream& stream);
   void dump_query_header(os_Dumper_stream& stream);
   void dump_cursor_header(os_Dumper & dmp_ref, os_Dumper_stream& stream);
   os_collection * dump_cursor_dummy_header(os_Dumper_stream& stream);

   /* other dump functions */
   os_collection * this_coll()
     { return (os_collection*)(void*)coll_ref; }
 
   void dump_coll_elements(os_Dumper & dmp_ref, char * name, os_Dumper_stream& stream);
   os_int32 dump_coll_indexes(os_Dumper_stream& stream);
      
   /*other odds and ends */
   
   void * get_first_element();
   void * get_outofline();
   os_int32 has_index_rep();
   os_int32 has_content();
   os_int32 has_index();
   os_int32 has_outofline(char * type_name);

private:

   os_int32 get_dict_key_type(const void * p, char * name, char** key_name);
   void dump_key_value(os_int32 key_type, char * key_name, 
                       void* key, void** key_p,
                       os_Dumper & dmp_ref, os_Dumper_stream&);
   void dump_coll_range(os_coll_range * rp, os_Dumper & , os_Dumper_stream&);
   void dump_string(const char * cp, os_Dumper_stream&);
   void set_this_coll(os_collection *);
   
};



/**********************************************************************
  class os_collection_load
***********************************************************************/

class os_collection_load
   {
   friend class os_coll_element_fixup_loader;

 private:

   os_soft_pointer<void> coll_ref;
   os_cursor * this_cursor;
   os_coll_query * this_query;
   os_coll_range * rp;

 public: /* constructors and destructor */

   os_collection_load();
   os_collection_load(os_collection *);
   os_collection_load(os_cursor &);
   os_collection_load(os_coll_query *);
  ~os_collection_load();

 public:   /* operators */
   void operator=(os_collection * coll_ptr);

 public:  /* public create functions */

      os_collection * this_coll()
        { return (os_collection*)(void*)coll_ref; }

      void set_coll(os_collection*);

      os_collection * create_collection(os_segment * seg_ptr,
                                        const os_type & coll_type,
                                        char * type_name,
                                        os_int32 create_new,  
                                        os_unsigned_int32 behavior,
                                        os_unsigned_int32 size,
                                        os_boolean is_dict,
                                        os_Loader* loader);

      os_collection * create_dictionary_collection(os_segment * seg_ptr,
                                                   const os_type * dict_type,
                                                   char * type_name,
                                                   os_unsigned_int32 behavior,
                                                   os_unsigned_int32 size,
                                                   os_Loader* loader);

      void coll_fixup_embedded(os_collection * outofline,
			       os_Dumper_reference& original,
			       os_boolean is_outofline);
 
      os_cursor * create_dummy_cursor(os_segment *);

      os_cursor * create_cursor(os_segment *,
                         os_collection &,
                         char * element, char * path, 
                         os_int32 options);
    
      os_coll_query * create_query(os_segment *, char * element,
                                   char * query, char * file_name,
                                   os_unsigned_int32 line);
 
        
      void create_range(os_int32 qry_type,_OSCOLRNG_Type_Enum key_type,
                        os_int32 low_cond, void * low_value,
                        os_int32 high_cond, void * high_value); 

      os_int32 get_key_value(os_int32 key_type, char * key_name, 
                             void** value, os_Loader_stream& stream,
                             os_Loader* = 0, os_Loader_info* = 0);


      void create_index(os_int32 options, char * element, 
                        char * path, os_segment * seg_ptr);

      void insert_element(void * value);

      void insert_dict_element(void * value, void * key_value, 
                               os_int32 not_ptr_type);
 
   private:

      void clear_all();
      os_index_path * create_path(os_database *, char * element, char * path);
      
  }; 

/**********************************************************************
  class osCollEmbList
***********************************************************************/

class  osCollEmbList {

 public:
     osCollEmbList(os_Dumper_reference e, os_Dumper_reference o)
     {
       outofline_ref = o;
       embedded_ref = e;
     }
     ~osCollEmbList() {}

    os_Dumper_reference get_outofline() { return outofline_ref; }    
    os_Dumper_reference get_embedded() { return outofline_ref; } 

 protected:
    os_Dumper_reference outofline_ref;
    os_Dumper_reference embedded_ref;

public:
    static os_typespec* get_os_typespec();
};
 
/**********************************************************************
  class os_coll_index_list
***********************************************************************/

class os_coll_index_list {

 public:
     os_coll_index_list(char * _element_name, char* _path, 
                        os_int32 _options, os_unsigned_int32 _seg_num);
     ~os_coll_index_list();

    void set_next(os_coll_index_list * _next) { next = _next; }    
    os_coll_index_list * get_next() { return next; }
    os_int32 get_options() { return options; }
    char * get_element_name() { return element_name; }
    char * get_path() { return path; }
    os_unsigned_int32 get_seg_num() { return seg_num; }

 protected:

    os_coll_index_list * next;
    char * element_name; 
    char * path;
    os_int32 options;
    os_unsigned_int32 seg_num;
};

/**********************************************************************
  The following set of lists and classes are used to maintain a list of 
  os_dictionary types.  The types are based on the various flavors of 
  os_dk_wrapper<>.  We borrow the collection   range type enums to 
  specify the dictionary key types.  The default is   always void*.  
  This should probably be in the os_coll library, but placed it here 
  for now so this won't have to be patched in when dumping earlier 
  releases of os.
***********************************************************************/
/**********************************************************************
  class os_coll_dict_key
***********************************************************************/
#define OS_DK_WRAPPER_TYPE "os_dk_wrapper<"

class os_coll_dict_key {

 public:
     os_coll_dict_key(char * _type_name, os_int32 _key_type) 
        : type_name(_type_name), key_type(_key_type) {}
     ~os_coll_dict_key() {}
     
     char * get_type_name() {return type_name;}
     os_int32 get_key_type() {return key_type;} 
     

 private:
     
     char * type_name;
     os_int32 key_type;
};

/**********************************************************************
  class os_coll_dict_key_list
***********************************************************************/

   static os_coll_dict_key key_list[] = {
      os_coll_dict_key("unsigned int",   _OSCOLRNG_UNSIGNED_INT_TAG),
      os_coll_dict_key("int",            _OSCOLRNG_INT_TAG),
      os_coll_dict_key("unsigned short", _OSCOLRNG_UNSIGNED_SHORT_TAG),
      os_coll_dict_key("short",          _OSCOLRNG_SHORT_TAG),
      os_coll_dict_key("unsigned long",  _OSCOLRNG_UNSIGNED_LONG_TAG),
      os_coll_dict_key("long",           _OSCOLRNG_LONG_TAG),
      os_coll_dict_key("float",          _OSCOLRNG_FLOAT_TAG),
      os_coll_dict_key("double",         _OSCOLRNG_DOUBLE_TAG),
      os_coll_dict_key("os_char_star_nocopy", _OSCOLRNG_CHAR_STAR_TAG),
      os_coll_dict_key("os_char_array",  _OSCOLRNG_CHAR_ARR_TAG),
      os_coll_dict_key("char*",          _OSCOLRNG_CHAR_STAR_TAG),
      os_coll_dict_key("const char*",    _OSCOLRNG_CHAR_STAR_TAG),
      os_coll_dict_key("char",           _OSCOLRNG_SIGNED_CHAR_TAG),
      os_coll_dict_key("void*",          _OSCOLRNG_POINTER_TAG),
      os_coll_dict_key("",               _OSCOLRNG_USR_TAG)
   };
  
 
class os_coll_dl_dict_keys {

 
 public:
     // constructors and destructors
     os_coll_dl_dict_keys(os_int32 _key_type) {
	    set_max_dict_keys();
        dict_find_key(_key_type); }

     os_coll_dl_dict_keys(char * _key_char) {
	    set_max_dict_keys();
        dict_find_name(_key_char); }

     ~os_coll_dl_dict_keys() {};
  
     void dict_find_key(os_int32 _key_type) {
        for (i=0; key_list[i].get_key_type() != _key_type && i != max_dict_keys-1; ++i); }  

     void dict_find_name(char * _key_name) {
         for (i=0; (strncmp(key_list[i].get_type_name(), _key_name, 
		                    strlen(key_list[i].get_type_name())) != 0)
		      && i != max_dict_keys-1; ++i); }    
     
     os_int32 get_key_type() {return (key_list[i].get_key_type());}
     char * get_key_name() {return (key_list[i].get_type_name());}  
     
 private:
     void set_max_dict_keys() {
	    max_dict_keys = sizeof(key_list) / sizeof(os_coll_dict_key); }

 private:
     	  
     os_int32 i;
     os_int32 max_dict_keys;
};



#endif /* COLL_DL_HH */
