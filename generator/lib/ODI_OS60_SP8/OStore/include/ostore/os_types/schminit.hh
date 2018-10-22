/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _OS_SCHMINIT
#define _OS_SCHMINIT
#include <ostore/hdrstart.hh>

struct os_schema_info;

/* This has to be an aggregate for cfront */
struct _OS_schema_init_info {
#if defined(_OS_MicrosoftCC)
  void fixup_pointers(void **);
#endif
  void register_init_info();
  static _OS_schema_init_info bootstrap_info;
  static os_boolean initialize_app_schema();
  void Initialize();
  os_boolean is_DLL_schema_info() const;
  const char* const* get_DLL_identifiers(os_unsigned_int32& count) const;
  void add_DLL_identifier(const char* id);

  os_boolean link_resolved;   /* really init_info_resolved_xxx bits */
  os_unsigned_int16 format_version;
  os_unsigned_int16 number_of_types;
  os_unsigned_int16 first_rd_number;
  os_unsigned_int16 last_rd_number;
  os_unsigned_int16 first_tag_number;
  os_unsigned_int16 last_tag_number;

  os_unsigned_int16* rep_desc_tags;
  os_unsigned_int8** types;

  os_unsigned_int32* rep_desc_vtbl_entry_offsets;
  const char* const * rep_desc_vtbl_names;
  void** rep_desc_vtbl_addresses;
  os_unsigned_int32*  rep_desc_vtbl_offsets;

  os_unsigned_int32* rep_desc_discriminant_entry_offsets;
  const char*const* rep_desc_discriminant_names;
  void** rep_desc_discriminant_addresses;

  os_unsigned_int32* rep_desc_vbtbl_entry_offsets;
  char** rep_desc_vbtbl_names;
  void** rep_desc_vbtbl_addresses;

  os_unsigned_int32 neutralized_compilers;

  os_schema_info* app_schema_info;

  _OS_schema_init_info* next_init_info;

  os_unsigned_int32 n_vtbl_addresses;
  os_unsigned_int32 n_disc_addresses;
  os_unsigned_int32 n_vbtbl_addresses;

  /* The following slots only exist if 
   * format_version > _Reloc_printer::no_DLL_schema_rep_desc_version
   */
  const char* const* DLL_identifiers;	/* null-terminated array */
};


/* Bits in the link_resolved field, which is declared
 * os_boolean for compatibility with the past but is really an int
 */
enum {
  init_info_resolved_weak_pointers = 1,
  init_info_resolved_fixups = 2
};

/* This version is used when static ctors are supported
 * For Microsoft Visual C++, we do the equivalent
 */
class _OS_dynamic_schema_init_info {
private:
  _OS_schema_init_info& info;
public:
  _OS_dynamic_schema_init_info(_OS_schema_init_info& _info) : info(_info) {
    info.Initialize();
  }
};

/* This group of typedefs, defines, and externs used to be
 * in nreloc/rdff.hh, which is now gone.  They are used in
 * generating the .os_schema.cc file, or equivalent. 
 */

typedef char *_Reloc_vtbl_pointer;
typedef char *_Reloc_discriminant_pointer;
typedef os_int32 (*_Reloc_discriminant_function)(void* this_pointer);

#define OS_RDFF_VTBL_NAMES _Rep_desc_vtbl_names
#define OS_RDFF_DISCRIMINANT_NAMES _Rep_desc_discriminant_names
#define OS_RDFF_VTBL_ADDRESSES _Rep_desc_vtbl_addresses
#define OS_RDFF_VTBL_OFFSETS _Rep_desc_vtbl_offsets
#define OS_RDFF_DISCRIMINANT_ADDRESSES _Rep_desc_discriminant_addresses
#define OS_RDFF_LINK_RESOLVED_MAPS _Rep_desc_link_resolved_maps
extern char *OS_RDFF_VTBL_NAMES[];
extern _Reloc_vtbl_pointer OS_RDFF_VTBL_ADDRESSES[];
extern os_unsigned_int32 OS_RDFF_VTBL_OFFSETS[];
extern char *OS_RDFF_DISCRIMINANT_NAMES[];
extern _Reloc_discriminant_pointer OS_RDFF_DISCRIMINANT_ADDRESSES[];

extern os_boolean OS_RDFF_LINK_RESOLVED_MAPS;

extern _OS_schema_init_info *_Rep_desc_boot_data();

extern _Reloc_vtbl_pointer _Reloc_missing_vtbl;
extern os_int32 _Reloc_missing_virtual_function(void *);

#include <ostore/hdrend.hh>
#endif /* _OS_SCHMINIT */
