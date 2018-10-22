/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _CLIENT_INTERFACE_ALLOC_STRAT_HH_
#define _CLIENT_INTERFACE_ALLOC_STRAT_HH_

/* This type is used in various get_pages_for_allocation calls to
   define what strategy should be used when trying to find space to allocate
   an object in a cluster. Note: in what follows "locked pages" means locked by
   others. "unlocked pages" means not locked by others. Neither imply what lock
   the current client has on the page. Also, the following assumes that pages
   you have write owned (and therefore are not locked by others) have been
   checked for free space first.

   os_allocation_strategy_least_space

	1) look for unlocked pages in the cluster with enough room.  If a suitable
	   contiguous range of pages is found, write lock them and use them.  Done.

	2) Look for locked pages in the cluster with enough room.  If a suitable
	   contiguous range of pages is found, wait for write locks on the page(s).
	   If the page(s) still have enough free space when we get the lock(s), done,
	   else release the lock(s) and go to step 1.
	   If no locked pages with enough space are found, go to step 3.

	3) grow the cluster.

   os_allocation_strategy_least_wait

	1) look for unlocked pages in the cluster with enough room.  If a suitable
	   contiguous range of pages is found, write lock them and use them.  Done.

	2) grow the cluster.
*/

enum os_allocation_strategy {
  os_allocation_strategy_least_space,
  os_allocation_strategy_least_wait,

  os_allocation_strategy_pad = 1<<30
};

#endif /* _CLIENT_INTERFACE_ALLOC_STRAT_HH_ */
