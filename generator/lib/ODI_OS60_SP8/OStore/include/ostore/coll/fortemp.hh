/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _FOREACH_TEMPLATES
#define _FOREACH_TEMPLATES
#ifndef _OS_PSE_COLL
#include <ostore/hdrstart.hh>
#include <ostore/tix.hh>
#else
#include <os_pse/psecoll/hdrstart.hh>
_OS_BEGIN_NAMESPACE(os_pse)
#endif

#ifdef __os_cplusplus
static const char __foreach_template_version[] = "$Revision: 10.8.2.1.2.2.1.1 $";
#endif

/* foreaches need undo's to undo iteration starts. */

class _Foreach_undo : public basic_undo
{
  public:
    os_collection const * it_coll;
    os_cursor _cur;
    _Foreach_undo (const os_collection& coll, os_int32 behavior)
      : _cur(coll, behavior), it_coll(&coll) {}
    _Foreach_undo (const os_collection& coll, const os_index_path& path,
		   os_int32 behavior)
      : _cur(coll, path, behavior), it_coll(&coll) {}
    virtual ~_Foreach_undo ();
    os_cursor& cur() { return _cur; }
};

/*
For an unordered iteration:

         foreach (<init>, <coll>)
             <stmt>
*/

#ifdef __os_cplusplus

template <
  class ELEMENT_TYPE,
  __expression RANGE_VAR,
  __statement STMT,
  __expression BEHAVIOR,
  __expression COLL
> __statement foreach_unordered :
{
  _Foreach_undo _It_frame ($COLL, $BEHAVIOR);
  os_cursor& __p = _It_frame.cur();

  for (void* __e = __p.first(); __p.more(); __e = __p.next())
    {
      $RANGE_VAR = (ELEMENT_TYPE) __e;
      $STMT;
    }
}

template <
  class ELEMENT_TYPE,
  __expression RANGE_VAR,
  __statement STMT,
  __expression BEHAVIOR,
  __expression COLL
> __statement foreach_reverse_unordered :
{
  _Foreach_undo _It_frame ($COLL, $BEHAVIOR);
  os_cursor& __p = _It_frame.cur();

  for (void* __e = __p.last(); __p.more(); __e = __p.previous())
    {
      $RANGE_VAR = (ELEMENT_TYPE) __e;
      $STMT;
    }
}

/*

RANGE_VAR: The variable of INIT.

ELEMENT_TYPE: The type RANGE_VAR.

This template should be instantiated as a single statement, inside {
  ... }, not as a sequence of statements, to limit the scope of the
__c and __p variables.
*/


/*

For an ordered iteration:

As above, except:

- Add a template argument:

        path ORDER

- Add ORDER as an argument to generic_iteration_start.
*/

template <
  class ELEMENT_TYPE,
  __expression RANGE_VAR,
  __statement STMT,
  __expression BEHAVIOR,
  __expression ORDER,
  __expression COLL
> __statement foreach_ordered :
{
  _Foreach_undo _It_frame ($COLL, $ORDER, $BEHAVIOR);
  os_cursor& __p = _It_frame.cur();

  for (void* __e = __p.first(); __p.more(); __e = __p.next())
    {
      $RANGE_VAR = (ELEMENT_TYPE) __e;
      $STMT;
    }
}


template <
  class ELEMENT_TYPE,
  __expression RANGE_VAR,
  __statement STMT,
  __expression BEHAVIOR,
  __expression ORDER,
  __expression COLL
> __statement foreach_reverse_ordered :
{
  _Foreach_undo _It_frame ($COLL, $ORDER, $BEHAVIOR);
  os_cursor& __p = _It_frame.cur();

  for (void* __e = __p.last(); __p.more(); __e = __p.previous())
    {
      $RANGE_VAR = (ELEMENT_TYPE) __e;
      $STMT;
    }
}

#endif

#ifndef _OS_PSE_COLL
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif
#endif
