/*========================================================================
 *
 * File:      $RCSfile: sym.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:31 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef PSYM_HEADER    /* Allow nesting.   */
#define PSYM_HEADER 1

#include "p_types.hh"
#include "d_typdef.hh"
#include "vchar.h"

/* T e m p l a t e  F o r  S y m b o l  T a b l e  M a n a g e r */

/* define some hash function */
#ifndef HASHVCHAR
#define HASHVCHAR(p_c, hash)                  \
{                                             \
  register const vchar *p_x_x = p_c;          \
  register unsigned int h_x_x = 0;            \
  while ( *p_x_x != '\0' )                    \
    h_x_x = (h_x_x<<1) + *p_x_x++;            \
  hash = h_x_x;                               \
}
#endif

/* minimum symbol table record */
class Sym {
public:
  vchar *symbol;
  Sym *next, *prev, **head, *scope;
  unsigned int hash;
  int namespc;                  /* enumerated value for name space   */
  enum t_core_data_type datatype;   /* data type      */
  enum s_attrib_e attrib;       /* attributes of a symbol            */
  void *context;                /* pointer to the current context    */
  persObjPtr  objPtr;           /* not used                          */
};
typedef Sym *SymPtr;


class zzs_SymbolTable {
public:
  static zzs_SymbolTable* zzs_init(int, int);

  Sym *zzs_newadd(const vchar *);
  //  Sym *zzs_newadd(const char *);

  Sym *zzs_new(register const vchar *);
  //  Sym *zzs_new(register const char *);

  vchar *zzs_strdup(register const vchar *);
  //  vchar *zzs_strdup(register const char *);

  void zzs_add(register Sym *);

  Sym *zzs_get(const vchar *, void *, int);

  void zzs_keydel(const vchar *, void *, int);
  void zzs_del(register Sym *);

  void zzs_done(void);
  void zzs_super_done(void);

  void zzs_free(Sym *);

  Sym **zzs_scope(Sym **);
  Sym *zzs_rmscope(register Sym **);

  void zzs_stat(void);

private:

  zzs_SymbolTable();
 
  Sym **C_curScope;
  Sym **C_table;
  vchar *C_strings;
  vchar *C_strp;
  long int C_size;
  long int C_strsize;

};

#endif





