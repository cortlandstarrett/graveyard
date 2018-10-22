/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef REF_HELP_HH
#define REF_HELP_HH

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

/***********************************************************************
  class os_soft_pointer32_initializer
***********************************************************************/
class os_soft_pointer32_initializer : public os_soft_pointer32<void> {
private:

public:	
	void initialize(os_Dumper_reference ref);
};

/***********************************************************************
  class os_soft_pointer64_initializer
***********************************************************************/
class os_soft_pointer64_initializer : public os_soft_pointer64<void> {
private:

public:	
	void initialize(os_Dumper_reference ref);
};

/***********************************************************************
  class os_reference_initializer
***********************************************************************/
class os_reference_initializer : public os_reference {
private:
   os_unsigned_int32 seg_num;
   os_unsigned_int32 clus_num;
   os_unsigned_int32 offset;

public:	
	void initialize(os_Dumper_reference ref);
};


/***********************************************************************
  class os_reference_this_DB_initializer
***********************************************************************/
class os_reference_this_DB_initializer : public os_reference_this_DB {
private:
   os_unsigned_int32 seg_num;
   os_unsigned_int32 clus_num;
   os_unsigned_int32 offset;

public:	
	void initialize(os_Dumper_reference ref);
};

/***********************************************************************
  class os_reference_protected_initializer
***********************************************************************/
class os_reference_protected_initializer : public os_reference_protected {
private:
   os_unsigned_int32 seg_num;
   os_unsigned_int32 clus_num;
   os_unsigned_int32 offset;

public:	
	void initialize(os_Dumper_reference ref);
};

#endif /* REF_HELP_HH */
