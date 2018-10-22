/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/*
 *  Parameterized Reference Classes
 *  This file contains a template for all "thin layer" reference classes.
 *  The input cpp variables are:
 *	REF_TEMPLATE_DECL		Template declaration
 *	REF_IS_LOCAL			1 = local reference, 0 = nonlocal reference
 *	REF_TYPE			Type of the reference
 *	REF_BASE_TYPE			Type of the nonparameterized base class
 *	REF_TO_TYPE			Type of the class being referenced
 *      IS_OS_OLD_REF                   1 = os_old_reference, 0 = current os_reference
 *	REF_CAST			Nonparameterized type to provide cast to
 */

#ifdef OBJECTSTORE_REF_COMPILE_ENV

#ifdef __TEMPLATES__
#define REF_TYPE_TMPL REF_TYPE<REF_TO_TYPE>
#else
#define REF_TYPE_TMPL REF_TYPE
#endif

#ifndef __NOTEMPLATES__

REF_TEMPLATE_DECL
class _OS_DLLIMPORT(_OS_CLIENT) REF_TYPE : public REF_BASE_TYPE {
public:
  REF_TYPE(REF_TO_TYPE * p) : REF_BASE_TYPE((void *)p) {};
  REF_TYPE(const REF_TYPE_TMPL& ref) : REF_BASE_TYPE(ref) {};
  REF_TYPE() : REF_BASE_TYPE () {};
  static os_typespec * get_os_typespec();

  REF_TYPE_TMPL & operator=(const REF_TO_TYPE *p) {
      REF_BASE_TYPE::operator=(p);
      return *this;
  }
  REF_TYPE_TMPL & operator=(const REF_TYPE_TMPL & r) {
    REF_BASE_TYPE::operator=(*((const REF_BASE_TYPE *)&r));
    return *this;
  }

#ifdef REF_CAST
#if !defined(_OS_cfrontC) && !defined(__os_cafe)
  operator const REF_CAST & () const { return *((const REF_CAST *)this); }
  operator REF_CAST & () { return *((REF_CAST *)this); }
#endif
#endif

#if REF_IS_LOCAL == 1
  REF_TO_TYPE * resolve (os_database * db) const {
      return (REF_TO_TYPE *) REF_BASE_TYPE::resolve(db);
  };

#else 
  REF_TO_TYPE * resolve () const {
      return (REF_TO_TYPE *) REF_BASE_TYPE::resolve();
  };
  operator REF_TO_TYPE * () const {
      return (REF_TO_TYPE *) REF_BASE_TYPE::resolve();
  };
  REF_TO_TYPE * operator->() const {
      return (REF_TO_TYPE *) REF_BASE_TYPE::resolve();
  };
#endif
};

#endif  /* ndef __NOTEMPLATES__ */

#endif	/* def OBJECTSTORE_REF_COMPILE_ENV */
