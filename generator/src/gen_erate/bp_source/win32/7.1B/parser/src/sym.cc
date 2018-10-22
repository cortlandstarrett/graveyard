/*========================================================================
 *
 * File:      $RCSfile: sym.cc,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:22 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
/*
 * Simple symbol table manager using coalesced chaining to resolve collisions
 *
 * Doubly-linked lists are used for fast removal of entries.
 *
 * 'sym.h' must have a definition for typedef "Sym".  Sym must include at
 * minimum the following fields:
 *
 *		...
 *		char *symbol;
 *		struct ... *next, *prev, **head, *scope;
 *		unsigned int hash;
 *		...
 *
 * 'template.h' can be used as a template to create a 'sym.h'.
 *
 * 'head' is &(table[hash(itself)]).
 * The hash table is not resizable at run-time.
 * The scope field is used to link all symbols of a current scope together.
 * Scope() sets the current scope (linked list) to add symbols to.
 * Any number of scopes can be handled.  The user passes the address of
 * a pointer to a symbol table
 * entry (INITIALIZED TO NULL first time).
 *
 * Available Functions:
 *
 *	zzs_init(s1,s2)	--	Create hash table with size s1, string table size s2.
 *	zzs_done()	--	Free hash and string table created with zzs_init().
 *	zzs_super_done()--	Free all symbol table entries and then free 
 *            hash and string table created with zzs_init().
 *	zzs_add(key,rec)--	Add 'rec' with key 'key' to the symbol table.
 *	zzs_newadd(key)	--	create entry; add using 'key' to
 *            the symbol table.
 *	zzs_get(key,context, ns)	--	Return pointer to last record entered
 *       under 'key'
 *						Else return NULL
 *	zzs_del(p)		--	Unlink the entry associated with p.  This does
 *						NOT free 'p' and DOES NOT remove it from a scope
 *						list.  If it was a part of your intermediate code
 *						tree or another structure.  It will still be there.
 *			  			It is only removed from further consideration
 *						by the symbol table.
 *      zzs_free(key,context, ns)  -- Unlink the entry associated with key, 
 *            and free the memory of the symbol table entry
 *	zzs_keydel(s)	--	Unlink the entry associated with key s.
 *						Calls zzs_del(p) to unlink.
 *	zzs_scope(sc)	--	Specifies that everything added to the symbol
 *			   			table with zzs_add() is added to the list (scope)
 *						'sc'.  'sc' is of 'Sym **sc' type and must be
 *						initialized to NULL before trying to add anything
 *						to it (passing it to zzs_scope()).  Scopes can be
 *					    switched at any time and merely links a set of
 *						symbol table entries.  If a NULL pointer is
 *						passed, the current scope is returned.
 *	zzs_rmscope(sc)	--	Remove (zzs_del()) all elements of scope 'sc'
 *						from the symbol table.  The entries are NOT
 *						free()'d.  A pointer to the first
 *			   			element in the "scope" is returned.  The user
 *			   			can then manipulate the list as he/she chooses
 *			   			(such as freeing them all). NOTE that this
 *			   			function sets your scope pointer to NULL,
 *			   			but returns a pointer to the list for you to use.
 *	zzs_stat()		--	Print out the symbol table and some relevant stats.
 *	zzs_new(key)	--	Create a new record with calloc() of type Sym.
 *			   			Add 'key' to the string table and make the new
 *			   			records 'symbol' pointer point to it.
 *	zzs_strdup(s)	--	Add s to the string table and return a pointer
 *			   			to it.  Very fast allocation routine
 *						and does not require strlen() nor calloc().
 *
 * Example:
 *
 *	#include <stdio.h>
 *	#include "sym.h"
 *
 *	main()
 *	{
 *	    Sym *scope1=NULL, *scope2=NULL, *a, *p;
 *	
 *	    zzs_init(101, 100);
 *	
 *	    a = zzs_new("Apple");	zzs_add(a->symbol, a);	-- No scope
 *	    zzs_scope( &scope1 );	-- enter scope 1
 *	    a = zzs_new("Plum");	zzs_add(a->symbol, a);
 *	    zzs_scope( &scope2 );	-- enter scope 2
 *	    a = zzs_new("Truck");	zzs_add(a->symbol, a);
 *	
 *    	p = zzs_get("Plum",NULL, ns);
 *    	if ( p == NULL ) fprintf(stderr, "Hmmm...Can't find 'Plum'\n");
 *	
 *    	p = zzs_rmscope(&scope1)
 *    	for (; p!=NULL; p=p->scope) {printf("Scope1:  %s\n", p->symbol);}
 *    	p = zzs_rmscope(&scope2)
 *    	for (; p!=NULL; p=p->scope) {printf("Scope2:  %s\n", p->symbol);}
 * }
 *
 * Terence Parr
 * Purdue University
 * February 1990
 *
 * CHANGES
 *
 *	Terence Parr
 *	May 1991
 *		Renamed functions to be consistent with ANTLR
 *		Made HASH macro
 *		Added zzs_keydel()
 *		Added zzs_newadd()
 *		Fixed up zzs_stat()
 *
 *	July 1991
 *		Made symbol table entry save its hash code for fast comparison
 *			during searching etc...
 */

#include <stdio.h>
#if __STDC__ == 1
#include <string.h>
#include <stdlib.h>
#else
#include "malloc.h"
#endif
#ifdef MEMCHK
#include "trax.h"
#endif
#include "sym.hh"

#include "tokens.h"
#include "P.h"

#define StrSame		0

zzs_SymbolTable::zzs_SymbolTable():
  C_curScope(0),
  C_size(0),
  C_table(0),
  C_strings(0),
  C_strp(0),
  C_strsize(0)
{}

zzs_SymbolTable*
zzs_SymbolTable::zzs_init(
  int sz,
  int strs
)
{
	if ( sz <= 0 || strs <= 0 ) return 0;

        zzs_SymbolTable* new_table = new zzs_SymbolTable();
	new_table->C_table = (Sym **) calloc(sz, sizeof(Sym *));
	if ( new_table->C_table == NULL )
	{
		fprintf(stderr, "Cannot allocate table of size %d\n", sz);
		exit(1);
	}
	new_table->C_strings = (vchar *) calloc(strs, sizeof(vchar));
	if ( new_table->C_strings == NULL )
	{
		fprintf(stderr, "Cannot allocate string table of size %d\n", strs);
		exit(1);
	}
	new_table->C_size = sz;
	new_table->C_strsize = strs;
	new_table->C_strp = new_table->C_strings;

        return new_table;
}

/* create a new symbol table entry and add it to the symbol table */
Sym *
zzs_SymbolTable::zzs_newadd(
  const vchar *s
)
{
  Sym *p = zzs_new(s);
  if ( p != NULL )
    zzs_add(p);
  return p;
}

/*
 * Given a key, this function allocates and returns a pointer to a
 * symbol table record whose "symbol" pointer is reset to a position
 * in the string table.
 */
Sym *
zzs_SymbolTable::zzs_new(
  const vchar *s
)
{
  register Sym *rec;
  if ( (rec = (Sym *) calloc(1,sizeof(Sym))) == 0 )
    {
      fprintf(stderr,"Out of memory\n");
      exit(1);
    }
  rec->symbol = zzs_strdup(s);
  HASHVCHAR(rec->symbol, rec->hash);
  // next, prev, head
  rec->namespc = -1;	
  rec->datatype = UNKNOWN_DATATYPE;
  rec->attrib = SA_READWRITE;
  rec->context = 0;
  rec->objPtr = 0;
  return rec;
}


/* Add a key to the string table and return a pointer to it.
 * Bump the pointer into the string table to next avail position.
 */
vchar *
zzs_SymbolTable::zzs_strdup(
  register const vchar *src
)
{
  vchar *start=C_strp;
  register const vchar *stop = &(C_strings[C_strsize-2]);
  while ( *src != '\0' )
    {
      if ( C_strp < stop )
        *C_strp++ = *src++;
      else
        {
          fprintf(stderr,
                  "sym: string table overflow (%d chars)\n", C_strsize);
          exit(-1);
        }
    }
  *C_strp++ = '\0';

  return( start );
}

void
zzs_SymbolTable::zzs_add(
  register Sym *rec
)
{
  register unsigned int h = rec->hash % C_size;
  rec->next = C_table[h];	/* Add to doubly-linked list */
  rec->prev = NULL;
  if ( rec->next != NULL )
    (rec->next)->prev = rec;
  C_table[h] = rec;
  rec->head = &(C_table[h]);
  if ( C_curScope != NULL )
    {
      rec->scope = *C_curScope;
      *C_curScope = rec;
    }
}

Sym *
zzs_SymbolTable::zzs_get(
  const vchar *s,
  void * context,
  int namespc
)
{
  register Sym *q;
  register Sym *r = NULL;
  register int ns = namespc;
  register unsigned int h=0;
	
  HASHVCHAR(s, h);
	
  for (q = C_table[h%C_size]; q != NULL; q = q->next)
    {
      if ( q->hash == h )  /* do we even have a chance of matching? */
        {
          if ( ( q->context == context ) && ( q->namespc == ns ) )
            {
              if ( vcharCompare(q->symbol, s) == StrSame )
                {
                  r = q;
                  break;
                }
            }
        }
    }
  return( r );
}

void
zzs_SymbolTable::zzs_done()
{
	if ( C_table != NULL ) free( C_table );
	if ( C_strings != NULL ) free( C_strings );
}

void zzs_SymbolTable::zzs_super_done()
{
  int i;
  
  if ( C_table != NULL )
    for ( i = 0; i < C_size; ++i )
    {
      while (C_table[i])
      { 
        zzs_free(C_table[i]);
      }
    }

  zzs_done();
}

/*
 * Unlink p from the symbol table.  Hopefully, it's actually in the
 * symbol table.
 *
 * If p is not part of a bucket chain of the symbol table, bad things
 * will happen.
 *
 * Will do nothing if all list pointers are NULL
 */
void
zzs_SymbolTable::zzs_del(
  register Sym *p
)
{
  if ( p == NULL )
    {fprintf(stderr, "zzs_del(NULL)\n"); exit(1);}
  if ( p->prev == NULL )	/* Head of list */
    {
      register Sym **t = p->head;
		
      if ( t == NULL )
        return;	/* not part of symbol table */
      (*t) = p->next;
      if ( (*t) != NULL ) (*t)->prev = NULL;
    }
  else
    {
      (p->prev)->next = p->next;
      if ( p->next != NULL )
        (p->next)->prev = p->prev;
    }
  p->next = p->prev = NULL;	/* not part of symbol table anymore */
  p->head = NULL;
}

void
zzs_SymbolTable::zzs_keydel(
  const vchar *v,
  void * context,
  int namespc
)
{
  Sym *p = zzs_get(v, context, namespc);

  if ( p != NULL )
    zzs_del( p );
}

/* S c o p e  S t u f f */

/* Set current scope to 'scope'; return current scope if 'scope' == NULL */
Sym **
zzs_SymbolTable::zzs_scope(
  Sym **scope
)
{
  if ( scope == NULL )
    return( C_curScope );
  C_curScope = scope;
  return( scope );
}

/* Remove a scope described by 'scope'.  Return pointer to 1st element in scope */
Sym *
zzs_SymbolTable::zzs_rmscope(
  register Sym **scope
)
{
  register Sym *p;
  Sym *start;

  if ( scope == NULL )
    return(NULL);
  start = p = *scope;
  for (; p != NULL; p=p->scope)
    { zzs_del( p ); }
  *scope = NULL;
  return( start );
}

void
zzs_SymbolTable::zzs_stat()
{
  static unsigned short count[20];
  unsigned int i,n=0,low=0, hi=0;
  register Sym **p;
  float avg=0.0;
	
  for (i=0; i<20; i++) count[i] = 0;
  for (p=C_table; p<&(C_table[C_size]); p++)
    {
      register Sym *q = *p;
      unsigned int len;
		
      if ( q != NULL && low==0 )
        low = p-C_table;
      len = 0;
      if ( q != NULL )
        printf("[%d]", p-C_table);
      while ( q != NULL )
        {
          len++;
          n++;
          char *s = (char *)vcharExportAlloc(vcharScribeSystem(q->symbol));
          printf( " %s\t\t%d\t%d\n",
                  s,
                  q->namespc,
                  q->datatype );
          vcharExportFree(s);
          q = q->next;
          /* if ( q == NULL ) printf("\n"); */
        }
      if ( len>=20 ) printf("zzs_stat: count table too small\n");
      else count[len]++;
      if ( *p != NULL ) hi = p-C_table;
    }

  printf("Storing %d recs used %d hash positions out of %d\n",
         n, C_size-count[0], C_size);
  printf("%f %% utilization\n",
         ((float)(C_size-count[0]))/((float)C_size));
  for (i=0; i<20; i++)
    {
      if ( count[i] != 0 )
        {
          avg += (((float)(i*count[i]))/((float)n)) * i;
          printf("Buckets of len %d == %d (%f %% of recs)\n",
                 i, count[i], 100.0*((float)(i*count[i]))/((float)n));
        }
    }
  printf("Avg bucket length %f\n", avg);
  printf("Range of hash function: %d..%d\n", low, hi);
}

/*
 * Given a string, this function locates the corresponding symbol table
 * record in current scope, removes the entry from the symbol table,
 * and frees the memory allocated to the entry.
 */

void
zzs_SymbolTable::zzs_free(
  Sym *p
)
{
  if ( p != NULL )
    {
      zzs_del( p );
      free( p );
    }
}
