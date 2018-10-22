/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef CMTL_INTERFACE_VIRTUAL_TRANSACTION
#define CMTL_INTERFACE_VIRTUAL_TRANSACTION 1

#include <ostore/portypes.hh>
#include <ostore/cmtl/os_txn_ctx.hh>

class os_global_transaction;

/*
 *********************************
 *                               * 
 *  os_virtual_transaction	 *
 *                               *
 *********************************
 */

/* os_virtual_transaction represents a logical unit of transactional work. */

class _OS_DLLIMPORT(_OS_CMTL) os_virtual_transaction {


public:					/* public static member functions */

  /**
   * Starts a virtual transaction based on information in the transaction
   * context. Upon return from the method, the current thread will be 
   * running in the session in which the transaction will execute.
   */
  static os_virtual_transaction* begin(os_transaction_context & txn_ctx);

  /**
   * Returns the os_virtual_transaction associated with the current thread. If
   * there is more than one, returns the one initiated most recently.  If 
   * there is none, returns null.
   */
  static os_virtual_transaction* get_current();

public:					/* public function members */

  virtual ~os_virtual_transaction() { }

  /**
   * Returns the os_global_transaction enclosing the os_virtual_transaction.
   * All virtual transactions hava a global transaction associated with 
   * them. For independent virtual transactions this is an implicit
   * global transaction created by CMTL.
   */
  virtual os_global_transaction * get_global_transaction() const = 0;

  /**
   * Commit this os_virtual_transaction. This method must be invoked from the
   * thread that initiated the transaction. 
   */
  virtual void commit() = 0;

  /**
   * Abort this os_virtual_transaction. This method must be invoked from the
   * thread that initiated the transaction. 
   */
  virtual void abort() = 0;

  
  /**
   * Returns true if the virtual transaction is an update transaction, false
   * otherwise.
   */
  virtual os_boolean is_update() const = 0;


  /**
   * Returns true if the virtual transaction is a read-only transaction, false
   * otherwise.
   */
  virtual os_boolean is_read_only() const = 0;


  /**
   * Returns the transaction type of this transaction.
   */ 
  virtual os_transaction_context::transaction_type get_transaction_type() const = 0;


  /**
   * Returns the isolation level associated with this transaction.
   */ 
  virtual os_transaction_context::isolation_level get_isolation_level() const = 0;


  /**
   * Returns true if the transaction has been aborted, otherwise false.
   */
  virtual os_boolean is_aborted() const = 0;

  /**
   * Returns true if the transaction has been committed, otherwise false.
   */
  virtual os_boolean is_committed() const = 0;

 
  /**
   * Returns true if the transaction has not been aborted or committed,
   * otherwise false.
   */
  virtual os_boolean is_active() const = 0;

 
  /**
   * Returns the numeric id of the transaction.
   */
  virtual os_int32 get_id() const = 0;

};


/*
 *********************************
 *                               * 
 *  _Stack_virtual_transaction	 *
 *                               *
 *********************************
 */

class _OS_DLLIMPORT(_OS_CMTL) _Stack_virtual_transaction : public basic_undo
{
private:
  os_virtual_transaction *p_vt;
  os_transaction_context &transaction_context;

public:
  _Stack_virtual_transaction(os_transaction_context &txn_ctx);
 ~_Stack_virtual_transaction();
 void begin();
 void commit();
 void abort();
 os_boolean is_active() const;
};


#define OS_BEGIN_VT_WITH_RETRY_LIMIT(unique_tag,txn_context,retry_limit)      \
{                                                                             \
  os_unsigned_int32 _Tx_retry_count = 0;                                      \
  const os_unsigned_int32 _Tx_retry_limit = retry_limit;                      \
  os_boolean _Tx_finished = 0;                                                \
                                                                              \
_ODI_CONCAT(unique_tag,_s):                                                   \
  {									      \
    _Stack_virtual_transaction vt(txn_context);                               \
    TIX_HANDLE(err_objectstore) {					      \
      vt.begin();					                      \
      {		

#define OS_END_VT(unique_tag)                                                 \
      }									      \
      if (vt.is_active())						      \
	vt.commit();							      \
      _Tx_finished = 1;		                                              \
                                                                              \
    } TIX_EXCEPTION {                                                         \
      /* An objectstore exception has occurred.				      \ 
 	 Abort the VT, if still active. 				      \
	 Resignal the exception or retry the VT as appropriate. */	      \
      if (vt.is_active())						      \
	vt.abort();							      \
      tix_exception *excp = tix_handler::get_exception();                     \
      /* if this is not a retry exception, rethrow it. */		      \
      if (!err_restartable.ancestor_of(excp) &&				      \
	excp != &err_no_trans &&					      \
	excp != &err_cmtl_retry && excp != &err_cmtl_abort_and_retry)	      \
        excp->signal(tix_handler::get_report0());                             \
    } TIX_END_HANDLE;                                                         \
  }									      \
                                                                              \
  if (_Tx_finished == 0) {                                                    \
    if (++_Tx_retry_count < _Tx_retry_limit)		                      \
      goto _ODI_CONCAT(unique_tag,_s);                                        \
    err_too_many_retries.signal                                               \
      ("The transaction was retried more than %d times", _Tx_retry_limit);    \
  }                                                                           \
}										  

#define OS_BEGIN_VT(unique_tag,txn_context)			              \
  OS_BEGIN_VT_WITH_RETRY_LIMIT(unique_tag,txn_context,10)

#endif /* CMTL_INTERFACE_VIRTUAL_TRANSACTION */
