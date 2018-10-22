/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/* BOOT TYPES USED TO TEST OUT THE CLIENT */
#ifndef __TESTTYPE_HH
#define __TESTTYPE_HH

/* We need virtual functions, but since this is the boot schema, they
   will have to be in the product. So I couldn't drag in the entirety of
   the somewhat weedy test_1 schema */

/* Besides being used for testing, this also serves to get types such
 * as os_virtual_behavior used by libraries such as collections
 * into the boot schema */

#include <ostore/os_types/paddef.hh>

class os_typespec;

class _ODI_test_virtual_behavior
{
public:
  _ODI_test_virtual_behavior () {}
  virtual void dummy_virtual_function() const;
  /* needs to be 8 bytes to potentially allow for 64 bit vtbls */
  os_pad_vftbl_only8

  /* Make sure the class is 8 byte aligned */
  OS_ALIGN_CLASS(8);
};

/* Three peas in a pod */

class _ODI_test_1 : public _ODI_test_virtual_behavior {
public:
  char* string;
  os_pad_ptr8(string)
  os4u id;
  os4u serial;
  _ODI_test_1 () { string = 0; id = 1; serial = 0; }
  virtual os4 v1();
  virtual os4 v2();
  virtual os4 v3();
};

class _ODI_test_2 : public _ODI_test_virtual_behavior {
public:
  char* string;
  os_pad_ptr8(string)
  os4u id;
  os4u serial;
  _ODI_test_2 () { string = 0; id = 2; serial = 0; }
  virtual os4 v1();
  virtual os4 v2();
  virtual os4 v3();
};

class _ODI_test_3 : public _ODI_test_virtual_behavior {
public:
  os4u id;
  os4u serial;
  char* string;
  os_pad_ptr8(string)
  _ODI_test_3 () { string = 0; id = 3; serial = 0; }
  virtual os4 v1();
  virtual os4 v2();
  virtual os4 v3();
};

class _ODI_test_3b : public _ODI_test_virtual_behavior  {
public:
  os4u id;
  os4u serial;
  char* string;
  os_pad_ptr8(string)
  _ODI_test_3b () { string = 0; id = 35; serial = 0; }
};

class _ODI_test_4 : public _ODI_test_3b, public _ODI_test_3 {
public:
  char* string;
  os_pad_ptr8(string)
  os4u id;
  os4u serial;
  _ODI_test_4 () { string = 0; id = 4; serial = 0; }
  virtual os4 v1();
  virtual os4 v2();
  virtual os4 v3();
};

class _ODI_test_5 : public _ODI_test_1,
   	            public _ODI_test_2,
   	            public _ODI_test_3
{
public:
  char* string;
  os_pad_ptr8(string)
  os4u id;
  os4u serial;
  _ODI_test_4 t4;
  _ODI_test_5 () { string = 0; id = 5; serial = 0; }
  virtual os4 v1();
  virtual os4 v2();
  virtual os4 v3();
};

#endif
