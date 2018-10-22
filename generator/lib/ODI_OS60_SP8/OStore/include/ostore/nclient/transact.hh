/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef CLIENT_INTERFACE_TRANSACT
#define CLIENT_INTERFACE_TRANSACT 1

#include <ostore/hdrstart.hh>
#include <ostore/facade.hh>
#include <ostore/tix.hh>

#if defined(__STDC__) 
#ifndef _OS_ANSI_TOKENS
#define _OS_ANSI_TOKENS
#endif
#endif

/* This gets exported as os_transaction::maximum_name_length in cs_expd.cc */
#define OS_MAX_TXN_NAME_LENGTH 48

class _Stack_transaction;
class tix_exception;
class os_session;

class _OS_DLLIMPORT(_OS_CLIENT) os_transaction : public os_facade {
public:
  enum transaction_type_enum {none, update, read_only, xa,
			      transaction_type_enum_pad = 1<<30};
  enum transaction_scope_enum { local = 1, global,
				transaction_scope_enum_pad = 1<<30};

public:					/* PUBLIC FUNCTION MEMBERS */
  ~os_transaction() {};
  void operator delete(void *ptr);

  os_boolean top_level() const;
  os_transaction *get_parent() const;
  transaction_type_enum get_type() const;
  transaction_scope_enum get_scope() const;
  os_boolean is_aborted() const;
  os_boolean is_committed() const;
  os_boolean is_prepared() const;
  char* get_name() const;
  void  set_name(const char* new_name);

private:
  /* special methods for use only by _Stack_transaction. */
  friend class _Stack_transaction;
  void set_delayed_abort(os_boolean);
  void mark_for_abort();
  os_boolean is_marked_for_abort() const;
  static void call_before_retry_hook(os_unsigned_int32 n_retries);
  
public:					/* PUBLIC STATIC FUNCTION MEMBERS */
  static os_transaction *get_current();
  static os_transaction *begin(transaction_type_enum t_type = update,
			       transaction_scope_enum t_scope = local);
  static os_transaction *begin(const char* name, 
			       transaction_type_enum t_type = update,
			       transaction_scope_enum t_scope = local);
  static void checkpoint(os_transaction * = 0);
  static void commit(os_transaction * = 0);
  static void prepare_to_commit(os_transaction * = 0);
  static void abort(os_transaction * = 0);
  static void abort_top_level();/* Abort the top level (outermost) transaction. */
  static void set_max_retries(os_unsigned_int32);
  static os_unsigned_int32 get_max_retries();
  static os_boolean is_lock_contention();

  os_session *session_of();
};

typedef os_transaction::transaction_type_enum os_transaction_type;
typedef os_transaction::transaction_scope_enum os_transaction_scope;

/* Class _Stack_transaction, along with the macros OS_BEGIN_TXN and
   OS_END_TXN, implement lexical scope transactions.

   The two macros bracket a program block.  When this block is
   entered, a transaction begins; when the block is exited, the
   transaction ends.  If the transaction aborts due to deadlock, it is
   restarted a limited number of times.  If the transaction is
   explicitly aborted by a call to os_transaction::abort, an exception
   (err_explicit_abort) is raised to bring control back to the
   transaction's scope, which is then exited.

   If the block is exited normally, i.e. by executing past the end of
   the program block, the transaction is automatically committed.  If
   the block is exited in any other way, the transaction is aborted.

   When the transaction's scope is exited for any reason, if the
   abort_reason_ptr argument to OS_BEGIN_TXN is non-null, the
   tix_exception* it refers to will be set to indicate the success or
   failure of the transaction.  If *abort_reason_ptr is set to null,
   the transaction committed.  Otherwise, *abort_reason_ptr points to
   the exception that caused the transaction to abort.  If the abort
   was invoked explicitly by user's program code, *abort_reason_ptr
   will point to err_explicit_abort.
   
   The _Stack_transaction object is allocated on the stack, and
   contains a pointer to a regular os_transaction facade object.  The
   os_transaction class has a minimum of special methods only for use
   by _Stack_transaction, to support the different behavior of
   os_transaction::abort.  _Stack_transaction's destructor is
   responsible for aborting the transaction when the scope is exited,
   and for setting *abort_reason_ptr.

   The charter of the two macros is to set up handlers for both
   err_restartable and err_explicit_abort.  They also wrap the whole
   transaction block in a "goto" loop and maintain a counter to
   implement automatic restart when there is an abort due to deadlock.
   A "goto" loop is used in lieu of "while" or "for" to avoid setting
   up an invisible block that would change the meaning of "break" and
   "continue" within the scope of the transaction.

   The err_restartable handler always re-throws the exception that it
   caught, unless the current transaction is the top-level
   transaction.  This means that a deadlock always aborts and restarts
   the outermost transaction.

   The err_explicit_abort handler re-throws the exception that it
   caught unless the current transaction is the one that was marked
   for abort by os_transaction::abort.  Thus all nested transactions 
   are aborted before the scope of the targeted transaction is reached.
*/

class _OS_DLLIMPORT(_OS_CLIENT) _Stack_transaction : public basic_undo {
private:
  os_transaction *p_os_transaction;
  tix_exception_p p_abort_reason;
  tix_exception_p *pp_abort_reason_report_location;

public:
  _Stack_transaction( tix_exception_p * abort_reason_report_location);

 ~_Stack_transaction();

 void begin_transaction(char const *name,
			os_transaction_type t_type);

 void begin_transaction(os_unsigned_int32 line_number,
			char const *file_name,
			char const *tag,
			os_transaction_type t_type);

 void commit();
 void set_abort_reason(tix_exception *abort_reason);
 os_boolean is_committed() const;
 os_boolean is_aborted() const;
 os_boolean is_top_level() const;
 os_boolean is_marked_for_abort() const;

 static os_boolean check_retries(os_unsigned_int32 n_retries);
};
 
#define OS_BEGIN_TXN(unique_tag,abort_reason_ptr,txn_type)                    \
{                                                                             \
  os_unsigned_int32 _Tx_retry_count = 0;                                      \
  os_boolean _Tx_finished = 0;                                                \
  tix_exception_p *_Tx_abort_reason_ptr = abort_reason_ptr;                   \
                                                                              \
_ODI_CONCAT(unique_tag,_s):                                                   \
  {                                                                           \
    _Stack_transaction _Tx_local(_Tx_abort_reason_ptr);                       \
    TIX_HANDLE(err_restartable) {                                             \
      TIX_HANDLE(err_explicit_abort) {                                        \
        _Tx_local.begin_transaction(__LINE__, __FILE__,                       \
				     "unique_tag", txn_type);                 \
        {                                   

#define OS_BEGIN_TXN_NAMED(unique_tag,abort_reason_ptr,txn_type,txn_name)     \
{                                                                             \
  os_unsigned_int32 _Tx_retry_count = 0;                                      \
  os_boolean _Tx_finished = 0;                                                \
  tix_exception_p *_Tx_abort_reason_ptr = abort_reason_ptr;                   \
                                                                              \
_ODI_CONCAT(unique_tag,_s):                                                   \
  {                                                                           \
    _Stack_transaction _Tx_local(_Tx_abort_reason_ptr);                       \
                                                                              \
    TIX_HANDLE(err_restartable) {                                             \
      TIX_HANDLE(err_explicit_abort) {                                        \
        _Tx_local.begin_transaction(txn_name, txn_type);                      \
        {                                   

#define OS_END_TXN(unique_tag)                                                \
        }                                                                     \
        if (!_Tx_local.is_committed() && !_Tx_local.is_aborted())             \
          _Tx_local.commit();                                                 \
        _Tx_finished = 1;                                                     \
      } TIX_EXCEPTION {                                                       \
        /* If this is not the target of the abort, re-throw the exception.    \
           _Tx_local's destructor will abort */                               \
        if (!_Tx_local.is_marked_for_abort())                                 \
          err_explicit_abort.signal("");                                      \
        _Tx_local.set_abort_reason(&err_explicit_abort);                      \
        _Tx_finished = 1;                                                     \
      } TIX_END_HANDLE;                                                       \
                                                                              \
    } TIX_EXCEPTION {                                                         \
      tix_exception *excp = tix_handler::get_exception();                     \
      /* if this is not the top level transaction, rethrow the exception.     \
         _Tx_local's destructor will abort. */                                \
      if (!_Tx_local.is_top_level())                                          \
        excp->signal(tix_handler::get_report0());                             \
      else								      \
	excp->release_pointer();					      \
    } TIX_END_HANDLE;                                                         \
  }  /* exit scope of _Tx_local */                                            \
                                                                              \
  if (_Tx_finished == 0) {                                                    \
    if (_Stack_transaction::check_retries(++_Tx_retry_count))                 \
      goto _ODI_CONCAT(unique_tag,_s);                                        \
    if (_Tx_abort_reason_ptr)                                                 \
      *_Tx_abort_reason_ptr = &err_too_many_retries;                          \
    err_too_many_retries.signal                                               \
      ("The transaction was retried more than %d times",                      \
       os_transaction::get_max_retries());                                    \
  }                                                                           \
}
  
#include <ostore/hdrend.hh>

#endif /* CLIENT_INTERFACE_TRANSACT */
