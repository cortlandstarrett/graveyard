/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#include <assert.h>
#include <ostore/ostore.hh>
#include <ostore/msgsys/msgtrvrs.hh>
#include <ostore/traverse/btreept.hh>


/****************************************************************************/
/* _B_tree_node_pt */
/****************************************************************************/

/* this ctor is for use by the split routine */
OS_BTREE_TEMPLATE
_B_tree_node_pt OS_BTREE_PARS::_B_tree_node_pt(os_unsigned_int32 height_arg,
					       Node_t *parent_arg,
					       This_t *left_sibling_arg,
					       This_t *right_sibling_arg)
  : height(height_arg),
    parent(parent_arg),
    count(0),
    left_sibling(left_sibling_arg),
    right_sibling(right_sibling_arg)
{
  if (right_sibling != NULL)
    right_sibling->left_sibling = this;

  /* link from left sibling to this is set by the caller */
  /* link from parent to this is set by the caller */
}


/* dtor does not unlink node from parent - that is the responsibility of the
   caller */
OS_BTREE_TEMPLATE
_B_tree_node_pt OS_BTREE_PARS::~_B_tree_node_pt()
{
  /* it is illegal to delete a nonleaf node that is occupied */
  if ( ! (height == 0 || count == 0))
    os_Traverser_messages::OS_FATAL(os_Traverser_messages::b_tree_node_pt_delete);

  /* unlink this from left sibling */
  if (left_sibling != NULL)
    left_sibling->right_sibling = right_sibling;

  /* unlink this from right sibling */
  if (right_sibling != NULL)
    right_sibling->left_sibling = left_sibling;
}


/* return the first leaf node in the tree rooted at this node */
OS_BTREE_TEMPLATE const OS_NODE_T *
_B_tree_node_pt OS_BTREE_PARS::first_leaf() const
{
  const Node_t *node = this;
  while (node->height > 0)
    node = node->first_entry().get_child();
  return node;
}


/* return the last leaf node in the tree rooted at this node */
OS_BTREE_TEMPLATE const OS_NODE_T*
_B_tree_node_pt OS_BTREE_PARS::last_leaf() const
{
  const Node_t *node = this;
  while (node->height > 0)
    node = node->last_entry().get_child();
  return node;
}


/* find leaf containing key in tree rooted at this node.  If force is
   true, the leftmost leaf is returned if the key is less than all
   keys in this tree.  If force is false, NULL is returned if the key
   is less than all keys in this tree. */
OS_BTREE_TEMPLATE const OS_NODE_T *
_B_tree_node_pt OS_BTREE_PARS::find_leaf(Key_t key,
					 os_boolean force) const
{
  const Node_t *node = this;
  while (node->height > 0)
  {
    os_int32 i = node->find_index(key);
    if (i < 0)
    {
      if (force)
	i = 0;
      else
	return NULL;
    }
    node = node->get_entry(i).get_child();
  }
  return node;
}


/* do an insert into the tree rooted at this node */
OS_BTREE_TEMPLATE void
_B_tree_node_pt OS_BTREE_PARS::insert(Key_t key,
				      Data_t *data,
				      Tree_t *tree)
{
  Node_t *leaf = find_leaf(key, /*force true*/ 1);
  leaf->insert_here(key, data, tree);
}


/* find an entry covering a key in the tree rooted at this node.
   The given exact_key must be initialized by the caller. */
OS_BTREE_TEMPLATE const Data_t *
_B_tree_node_pt OS_BTREE_PARS::find(Key_t key,
				    os_boolean exact,
				    Key_t* exact_key) const
{
  const Node_t *leaf = find_leaf(key, /*force false*/ 0);
  if (leaf == NULL)
    return NULL;
  os_int32 i = leaf->find_index(key);
  if (i < 0 || (exact && leaf->get_key(i) != key))
    return NULL;
  if (exact_key)
    *exact_key = leaf->get_key(i);
  return leaf->get_entry(i).get_data();
}


/* change a key (must be an exact match) in the tree rooted at this node */
OS_BTREE_TEMPLATE void
_B_tree_node_pt OS_BTREE_PARS::change_key(Key_t from_key,
					  Key_t to_key)
{
  Node_t *leaf = find_leaf(from_key, /*force false*/ 0);
  if (leaf == NULL)
    os_Traverser_messages::OS_FATAL(os_Traverser_messages::b_tree_node_pt_change_key);
  leaf->change_key_here(from_key, to_key);
}


/* remove an entry given a key (that must match exactly) in the tree rooted at
   this node */
OS_BTREE_TEMPLATE os_boolean
_B_tree_node_pt OS_BTREE_PARS::remove(Key_t key,
				      Tree_t *tree)
{
  Node_t *leaf = find_leaf(key, /*force false*/ 0);
  if (leaf == NULL)
    return /*false*/ 0;
  return leaf->remove_here(key, tree);
}


/* verify a single node base, and return the number of data entries in leaves
   at or below this node */
OS_BTREE_TEMPLATE os_unsigned_int32
_B_tree_node_pt OS_BTREE_PARS::verify(const Node_t *parent_arg,
				      os_unsigned_int32 i) const
{
  if (parent != parent_arg)
    os_Traverser_messages::OS_FATAL(os_Traverser_messages::b_tree_node_pt_verify_parent);
  if (count > Max_per_node)
    os_Traverser_messages::OS_FATAL(os_Traverser_messages::b_tree_node_pt_verify_count);

  if (parent == NULL)
  {
    /* if this node is the root, then it cannot have siblings */
    if ( ! (left_sibling == NULL && right_sibling == NULL))
	os_Traverser_messages::
	    OS_FATAL(os_Traverser_messages::b_tree_node_pt_verify_root);
  }
  else
  {
    if (height != parent->get_height() - 1)
	os_Traverser_messages::
	    OS_FATAL(os_Traverser_messages::b_tree_node_pt_verify_height);
    /* this node is not the root */
    /* all nonroot nodes are required to have at least Min_per_node
       entries */
    if (count < Min_per_node)
        os_Traverser_messages::
	    OS_FATAL(os_Traverser_messages::b_tree_node_pt_verify_min);
    /* check that our first key is what our parent thinks it should be */
    if (parent->get_key(i) != first_key())
        os_Traverser_messages::
	    OS_FATAL(os_Traverser_messages::b_tree_node_pt_verify_key);
    /* check that our left sibling is correct according to our parent */
    if (i == 0)
    {
      /* if i == 0, then the parent of our left sibling is the left
	 sibling of our parent */
      if (parent->left_sibling == NULL)
      {
	 /* ... but our parent does not have a left sibling, so we
	   should not have one either */
	 if (left_sibling != NULL)
            os_Traverser_messages::
	        OS_FATAL(os_Traverser_messages::b_tree_node_pt_verify_left_sibling1);
      }
      else
      {
	/* ... and our parent does have a left sibling - so our left
	   sibling should be the last child of the left sibling of the
	   parent */
	const Node_t *left_sib =
	  parent->left_sibling->last_entry().get_child();
	if (left_sib != left_sibling)
            os_Traverser_messages::
	        OS_FATAL(os_Traverser_messages::b_tree_node_pt_verify_left_sibling2);
      }
    }
    else
      /* i > 0, so the parent of our left sibling is our parent */
      if (left_sibling != parent->get_entry(i-1).get_child())
	  os_Traverser_messages::
              OS_FATAL(os_Traverser_messages::b_tree_node_pt_verify_left_sibling3);

    /* check that our right sibling is correct according to our parent */
    if (i == parent->count - 1)
    {
      /* if i == parent->count-1, then the parent of our right sibling
	 is the right sibling of our parent */
      if (parent->right_sibling == NULL)
      {
	 /* ... but our parent does not have a right sibling, so we
	   should not have one either */
	 if (right_sibling != NULL)
	     os_Traverser_messages::
	         OS_FATAL(os_Traverser_messages::b_tree_node_pt_verify_right_sibling1);
      }
      else
      {
	/* ... and our parent does have a right sibling - so our right
	   sibling should be the first child of the right sibling of
	   the parent */
	const Node_t *right_sib =
	  parent->right_sibling->first_entry().get_child();
	if (right_sib != right_sibling)
            os_Traverser_messages::
	        OS_FATAL(os_Traverser_messages::b_tree_node_pt_verify_right_sibling2);
      }
    }
    else
      /* i < parent->count - 1, so the parent of our right sibling is
	 our parent */
      if (right_sibling != parent->get_entry(i+1).get_child())
	  os_Traverser_messages::
              OS_FATAL(os_Traverser_messages::b_tree_node_pt_verify_right_sibling3);
  }

  /* check that the last key in the left sibling is less than our first key
   */ 
  if (left_sibling != NULL)
  {
    if (left_sibling->last_key() >= first_key())
        os_Traverser_messages::
            OS_FATAL(os_Traverser_messages::b_tree_node_pt_verify_left_sibling4);
  }

  /* check that our last key is less than the first key in our right sibling
   */
  if (right_sibling != NULL)
  {
     if (last_key() >= right_sibling->first_key())
         os_Traverser_messages::
             OS_FATAL(os_Traverser_messages::b_tree_node_pt_verify_right_sibling4);
  }

  /* now verify all entries in this node */
  os_unsigned_int32 num = 0;
  for (os_unsigned_int32 j = 0; j < count; j++)
  {
    if (j > 0)
    {
       /* make sure the keys are sorted */
       if (get_key(j-1) >= get_key(j))
           os_Traverser_messages::
	       OS_FATAL(os_Traverser_messages::b_tree_node_pt_verify_right_sibling4);
    }
    if (height > 0)
      /* verify children */
      num += get_entry(j).get_child()->verify(this, j);
    else
      num++;
  }
  return num;
}

/****************************************************************************/
/* _B_tree_node_pt */
/****************************************************************************/


/* shift num entries left from src_node into this node - assumes the shifted
   entries are ordered after all existing entries in this node */
OS_BTREE_TEMPLATE void
_B_tree_node_pt OS_BTREE_PARS::lshift(This_t &src_node,
				      os_unsigned_int32 num)
{
  /* the src_node must have at least num entries */
  if (src_node.count < num)
      os_Traverser_messages::OS_FATAL(os_Traverser_messages::b_tree_node_pt_lshift);
  os_unsigned_int32 i;
  /* move the entries, and set their parent links to point to this node */
  if (height == 0)
  {
    for (i = 0; i < num; i++, count++)
      entries[count] = src_node.entries[i];
  }
  else
  {
    /* same loop as above, only with the addition of the set_parent call */
    for (i = 0; i < num; i++, count++) {
      entries[count] = src_node.entries[i];
      entries[count].get_child()->set_parent(this);
    }
  }
  /* shift the remaining entries in the src_node down to occupy the space
     freed by the entries moved above */
  for (; i < src_node.count; i++)
    src_node.entries[i - num] = src_node.entries[i];

  src_node.count -= num;
}


/* shift num entries right from src_node into this node - assumes the shifted
   entries are ordered before all existing entries in this node */
OS_BTREE_TEMPLATE void
_B_tree_node_pt OS_BTREE_PARS::rshift(This_t &src_node,
				      os_unsigned_int32 num)
{
  /* the src_nod must have at least num entries */
  if (src_node.count < num)
      os_Traverser_messages::OS_FATAL(os_Traverser_messages::b_tree_node_pt_lshift);
  os_int32 i;
  /* make room in this node for the new entries */
  for (i = count - 1; i >= 0; i--)
    entries[i + num] = entries[i];
  /* move the entries, and set their parent links to point to this node */
  if (height == 0)
  {
    for (i = num-1; i >= 0; i--)
      entries[i] = src_node.entries[--src_node.count];
  }
  else
  {
    /* same loop as above, only with the addition of the set_parent call */
    for (i = num-1; i >= 0; i--)
    {
      entries[i] = src_node.entries[--src_node.count];
      entries[i].set_parent(this);
    }
  }
  count += num;
}


/* Insert entry_data into this node, splitting the node if necessary */
OS_BTREE_TEMPLATE void
_B_tree_node_pt OS_BTREE_PARS::insert_here(Key_t key,
					   void *val,
					   Tree_t *tree)
{
  if (count == Max_per_node)
  {
    /* this node is full - so make room */
    if (left_sibling != NULL &&
	left_sibling->count < Max_per_node &&
	(right_sibling == NULL ||
	 right_sibling->count >= left_sibling->count))
    {
      /* move one entry to the left sibling */
      Key_t key0 = first_key();
      if (key < key0) {
	/* just redirect insert to left sibling instead */
	left_sibling->insert_here(key, val, tree);
	return;
      }
      left_sibling->lshift(*this, 1);
      parent->change_key_here(key0, first_key());
    }
    else if (right_sibling != NULL &&
	     right_sibling->count < Max_per_node)
    {
      /* move one entry to the right sibling */
      if (last_key() < key) {
	/* just redirect insert to right sibling instead */
	right_sibling->insert_here(key, val, tree);
	return;
      }
      Key_t key0 = right_sibling->first_key();
      right_sibling->rshift(*this, 1);
      right_sibling->parent->
	change_key_here(key0, right_sibling->first_key());
    }
    else
    {
      /* the siblings are also full, so we have to split this
	 node do the insert - split will do the insert itself,
	 so we can get some tail-recursion */
      split(key, val, tree);
      return;
    }
  }

  os_unsigned_int32 i;
  /* make room for the new entry */
  for (i = count++; i > 0 && key < get_key(i-1); i--)
    entries[i] = entries[i-1];

//  /* make sure the key is not a duplicate */
//  if ( ! (i == 0 || get_key(i-1) < key))
//      os_Traverser_messages::OS_FATAL(os_Traverser_messages::b_tree_node_pt_insert_here);

  /* insert the new entry */
  entries[i].key = key;
  entries[i].set_value(val);
  if (height > 0)
    entries[i].get_child()->set_parent(this);

  /* if we just inserted entry 0, then that constitutes a key change for
     this node - so notify our parent */
  if (i == 0 && parent != NULL)
    parent->change_key_here(get_key(1), key);
}


/* we attempted to insert entry, but there was not enough room - so split was
   called.  Split creates a new right sibling, moves half of the entries from
   this node to the right sibling, and then does the insert.  The insert is
   done within split because split can quickly determine which of the two
   resulting nodes should get the insert, and because it increases the chance
   of tail-recursion optimization */
OS_BTREE_TEMPLATE void
_B_tree_node_pt OS_BTREE_PARS::split(Key_t key,
				     void *val,
				     Tree_t *tree)
{
  if (parent == NULL)
  {
    /* this node is the current root */
    if (tree->root != this)
      os_Traverser_messages::OS_FATAL(os_Traverser_messages::b_tree_node_pt_split);
    /* create a new root */
    parent = new(os_segment::of(this), Node_t::get_os_typespec())
        Node_t(height + 1, NULL, NULL, NULL);
    tree->root = parent;
    /* insert this node in the root */
    parent->insert_here(first_key(), this, tree);
  }
    
  /* create our new right sibling */
  right_sibling = new(os_segment::of(this), This_t::get_os_typespec())
      This_t(height, parent, this, right_sibling);

  /* do not use balance_with_right_sibling because it cannot handle empty
     nodes, and right sibling is currently empty */

  /* determine the pivot index and pivot key - all entries at or above this
     point will be moved to the right sibling, and the rest stay here */
  os_unsigned_int32 pivot_index = count >> 1;
  Key_t pivot_key = entries[pivot_index].get_key();
  os_boolean insert_right = pivot_key < key;
  if (insert_right)
  {
    /* give the right sibling the smaller number of entries */
    pivot_index = (count + 1) >> 1;
    pivot_key = entries[pivot_index].get_key();
  }

  /* now that we know the first key that will be in the right sibling, the
     pivot key, we can insert the right sibling in the parent - this might
     result in a recursive split if the parent is also full */
  parent->insert_here(pivot_key, right_sibling, tree);

  /* move the entries at or above the pivot to the right sibling */
  right_sibling->rshift(*this, count - pivot_index);

  /* now, do the (hopefully tail-recursive) insert */
  if (insert_right)
    right_sibling->insert_here(key, val, tree);
  else
    insert_here(key, val, tree);
}
 

/* Finds the index to the entry in this node that contains key.  If key is
   below the 0th key in this node, the returned index is -1.  If key is at or
   above the last key in this node, the returned index is the last index
   (count - 1), since the last entry includes everything at or above the last
   key.  Otherwise, for some i, key is greater than or equal to the ith key
   and less than the i+1th key, and the returned index is i. */
OS_BTREE_TEMPLATE os_int32
_B_tree_node_pt OS_BTREE_PARS::find_index(Key_t key) const
{
  os_int32 low = 0;
  os_int32 high = count;
  /* use a binary search to find the index between low and high */
  while (high > low)
  {
    os_int32 i = (high + low) >> 1;
    /* low <= i < high at this point */
    if (key < entries[i].get_key())
      /* key is below the ith key */
      high = i;
    else
      /* key is at or above the ith key */
      low = i + 1;
  }

  /* After the above loop, low must equal high.  The only other possibility
     is that high < low, which could only have been caused by the else part
     where low is set to i + 1, if high and i are equal.  However, i and
     high cannot be equal after i is computed, because the left shift
     operation is divide-by-2-and-round-down, and high was greater than low
     when this left shift happened.  So high must be greater than i, which
     means that setting low to i + 1 will not make low greater than high.

     If the last operation before exiting the loop was to set low to i+1,
     then we want to return low - 1 (or high - 1).  If the last operation
     before exiting the loop was to set high to i, then we want to return
     i-1, which is also high - 1. */
  return high - 1;
}


/* Remove an entry from this node - the key of the entry must match the arg
   key exactly.  The entry is not deleted, just removed.  The removal may
   result in rebalancing. */
OS_BTREE_TEMPLATE os_boolean
_B_tree_node_pt OS_BTREE_PARS::remove_here(Key_t key,
					   Tree_t *tree)
{
  /* find the index of the entry to remove */
  os_int32 i = find_index(key);
  if (i < 0)
    /* the key is below the first key on this node, so there is nothing to
       remove */
    return /*false*/ 0;

  if (get_key(i) != key)
    /* key is not an exact match for the ith key */
    return /*false*/ 0;

  /* OK - do the removal */
  count--;
  /* remember the first key for later use... */
  Key_t key0 = first_key();
  os_int32 j;
  /* move the entries above i down one to cover the removal */
  for (j = i; j < (os_int32)count; j++)
    entries[j] = entries[j+1];

  /* if this node is the root, then there is nothing more to do */
  if (parent == NULL)
    return /*true*/ 1;
  /* only the root node could have had a count of 1 prior to the remove */
  if (count <= 0)
      os_Traverser_messages::
          OS_FATAL(os_Traverser_messages::b_tree_node_pt_remove_here1);
  /* if we just changed our first key, notify our parent */
  if (i == 0)
    parent->change_key_here(key0, first_key());

  /* Try balancing things between this node and one of its siblings if there
     are too few entries on this node.  All existing siblings must have
     counts that are >= Min_per_node, else they would have initiated the
     balancing themselves, and nodes that survive a balancing have at least
     Min_per_node entries. If neither sibling exists, then this node must be
     the root - but that case was eliminated above. */
  if (count < Min_per_node)
  {
    /* We will balance this node with its right sibling, unless... */
    This_t *node = this;
    if (right_sibling == NULL ||
	(left_sibling != NULL &&
	 left_sibling->count > right_sibling->count))
      /* ... the left sibling of this node is a better candidate, either
	 because the right_sibling does not exist, or because the left
	 sibling has more entries */
      node = left_sibling;

    if (node == NULL)
        os_Traverser_messages::
            OS_FATAL(os_Traverser_messages::b_tree_node_pt_remove_here2);
    node->balance_with_right_sibling(tree);
  }
  return /*true*/ 1;
}


/* Change a single key in place - either by increasing it or decreasing it
   such that its relative order with the other keys stays the same.  This
   routine runs up the tree from this node when changing the key requires a
   similar change in the parent node (and so on up the tree). */
OS_BTREE_TEMPLATE void
_B_tree_node_pt OS_BTREE_PARS::change_key_here(Key_t from_key,
					       Key_t to_key)
{
  os_int32 i = find_index(from_key);
  /* the from_key must exist on this node at index i */
  if (i < 0)
      os_Traverser_messages::
          OS_FATAL(os_Traverser_messages::b_tree_node_pt_change_key_here1);
  if (get_key(i) != from_key)
      os_Traverser_messages::
          OS_FATAL(os_Traverser_messages::b_tree_node_pt_change_key_here2);
  /* make sure the new key keeps things sorted */
  if (to_key < from_key)
  {
    /* the change decreases the key - so make sure it is not too low by
       comparing it to the previous key */
    if (i > 0)
    {
      if (get_key(i-1) >= to_key)
	  os_Traverser_messages::
	      OS_FATAL(os_Traverser_messages::b_tree_node_pt_change_key_here3);
    }
    else if (left_sibling != NULL)
    {
      if (left_sibling->last_key() >= to_key)
	  os_Traverser_messages::
	      OS_FATAL(os_Traverser_messages::b_tree_node_pt_change_key_here4);
    }
  }
  else
  {
    /* the change increases the key - so make sure it is not too high by
       comparing it to the next key */
    if (i < (os_int32)count - 1)
    {
      if (to_key >= get_key(i+1))
	  os_Traverser_messages::
	      OS_FATAL(os_Traverser_messages::b_tree_node_pt_change_key_here3);
    }
    else if (right_sibling != NULL)
    {
      if (to_key >= right_sibling->first_key())
	  os_Traverser_messages::
	      OS_FATAL(os_Traverser_messages::b_tree_node_pt_change_key_here4);
    }
  }
    
  entries[i].set_key(to_key);
  if (i == 0 && parent != NULL)
    /* tail-recurse from parent on up the tree to the root - only
       have to continue up the tree if the changed key is the
       first key in the node - because only then will our parent
       have the key as well */
    parent->change_key_here(from_key, to_key);
}


/* Attempt to balance the number of entries between this node and its right
   sibling.  If the total number of entries on both nodes is less than
   Max_per_node, then all entries from the right sibling will be moved to
   this node and the right sibling will be removed and deleted - this can
   result in the tree collapsing by one or more levels.  Otherwise, the end
   result is that the number of entrie son this node and on its right sibling
   will both be greater than or equal to Min_per_node, and within 1 of
   each other. */
OS_BTREE_TEMPLATE void
_B_tree_node_pt OS_BTREE_PARS::balance_with_right_sibling(Tree_t *tree)
{
  if (right_sibling == NULL)
      os_Traverser_messages::
          OS_FATAL(os_Traverser_messages::b_tree_node_pt_balance_with_right_sibling);
  os_unsigned_int32 total_count = count + right_sibling->count;
  if (total_count <= Max_per_node) {
    /* collapse the right sibling into this node, and remove it */
    collapse_with_right_sibling(tree);
    return;
  }

  os_int32 avg = total_count >> 1;
  /* remember the first key in the right sibling for later use...*/
  Key_t key0 = right_sibling->first_key();
  if ((os_int32)count < avg)
    /* left shift avg-count entries from  right sibling to this node */
    lshift(*right_sibling, avg - count);
  else if ((os_int32)right_sibling->count < avg)
    /* right shift avg_count entries from this node to right sibling */
    right_sibling->rshift(*this, avg - right_sibling->count);
  else
    /* both nodes have the same number of entries - so there is
       nothing to do */
    return;
  /* After shifting, the first key of the right sibling has changed - so
     tell its parent (which is not necessarily our parent) */
  right_sibling->parent->change_key_here(key0, right_sibling->first_key());
}


/* Collapse the right sibling of this node into this node in the case where
   the total number of entries on both nodes is less than Min_per_node.
   This will always result in the right sibling being removed and deleted, but
   it can also result in a collapse into the root node, in which case this
   node will also be removed and deleted, and the height of the root will
   decrease by one. */
OS_BTREE_TEMPLATE void
_B_tree_node_pt OS_BTREE_PARS::collapse_with_right_sibling(Tree_t *tree)
{
  if (right_sibling == NULL)
      os_Traverser_messages::
          OS_FATAL(os_Traverser_messages::b_tree_node_pt_collapse_with_right_sibling1);
  os_unsigned_int32 total_count = count + right_sibling->count;
  if (total_count > Max_per_node)
      os_Traverser_messages::
          OS_FATAL(os_Traverser_messages::b_tree_node_pt_collapse_with_right_sibling2);
  if (parent == NULL)
      os_Traverser_messages::
          OS_FATAL(os_Traverser_messages::b_tree_node_pt_collapse_with_right_sibling3);
  /* Move all entries from the right sibling to this node */
  lshift(*right_sibling, right_sibling->count);
  /* check for the case when the parent is the root, and this node and its
     right sibling are the only two children - this is the case where the
     height of the root will decrease */
  if (parent->parent == NULL && parent->count == 2)
  {
    /* parent is the root, so it must be the parent of the right sibling
       as well */
    if (right_sibling->parent != parent)
        os_Traverser_messages::
            OS_FATAL(os_Traverser_messages::b_tree_node_pt_collapse_with_right_sibling4);
    /* remove the parent and right_sibling, and become the root */
    parent->count = 0;
    delete parent;
    parent = NULL;
    delete right_sibling;
    right_sibling = NULL;
    tree->root = this;
  }
  else
  {
    /* delete and remove the right sibling - do the delete before the
       remove so that the remove can be tail-recursive */
    Key_t rsibkey0 = right_sibling->first_key();
    Node_t *rsibpar = right_sibling->parent;
    delete right_sibling;
    /* this remove might cause recursive rebalancing and collapsing */
    rsibpar->remove_here(rsibkey0, tree);
  }
}


/****************************************************************************/
/* _B_tree_pt */
/****************************************************************************/

/* user-visible ctor */
OS_BTREE_TEMPLATE
_B_tree_pt OS_BTREE_PARS::_B_tree_pt()
    : root(NULL),
      change_tick(0),
      cardinality(0)
{
  /* check that the mins and maxes all make sense */
  if (Min_per_node < 2)
      os_Traverser_messages::OS_FATAL(os_Traverser_messages::b_tree_pt_b_tree_pt1);
  if (Min_per_node > (Max_per_node + 1) >> 1)
      os_Traverser_messages::OS_FATAL(os_Traverser_messages::b_tree_pt_b_tree_pt2);
}


OS_BTREE_TEMPLATE void
_B_tree_pt OS_BTREE_PARS::clear()
{
  /* delete the tree from the leaves up */
  Node_t *node, *parent;
  for (node = first_leaf(); node != NULL; node = parent)
  {
    parent = node->parent;
    do
    {
      Node_t *tmp_node = node;
      node = node->right_sibling;
      tmp_node->count = 0;
      delete tmp_node;
    } while (node != NULL);
  }

  cardinality = 0;
  root = NULL;
  change_tick++;
}


/* return the first leaf in the tree, or NULL if there is none */
OS_BTREE_TEMPLATE const OS_NODE_T *
_B_tree_pt OS_BTREE_PARS::first_leaf() const
{
  if (root == NULL)
    return NULL;

  return root->first_leaf();
}


/* return the last leaf in the tree, or NULL if there is none */
OS_BTREE_TEMPLATE const OS_NODE_T *
_B_tree_pt OS_BTREE_PARS::last_leaf() const
{
  if (root == NULL)
    return NULL;

  return root->last_leaf();
}


/* return the leaf containing the given key (or at least covering the range of
   keys that includes the give key) */
OS_BTREE_TEMPLATE const OS_NODE_T *
_B_tree_pt OS_BTREE_PARS::find_leaf(Key_t key) const
{
  if (root == NULL)
    return NULL;

  return root->find_leaf(key, /*force false*/ 0);
}


/* return a pointer to the data corresponding to the given key, or NULL if
   there is no such key in the tree. The given exact_key must be 
   initialized by the caller. */
OS_BTREE_TEMPLATE const Data_t *
_B_tree_pt OS_BTREE_PARS::find(Key_t key,
			       os_boolean exact,
			       Key_t* exact_key) const
{
  if (cardinality == 0)
    return NULL;

  return root->find(key, exact, exact_key);
}


/* return a pointer to the first data, or NULL if the tree is empty */
OS_BTREE_TEMPLATE const Data_t *
_B_tree_pt OS_BTREE_PARS::find_first() const
{
  if (cardinality == 0)
    return NULL;

  const Node_t *leaf = root->first_leaf();

  return leaf->first_entry().get_data();
}


/* return a pointer to the last data, or NULL if the tree is empty */
OS_BTREE_TEMPLATE const Data_t *
_B_tree_pt OS_BTREE_PARS::find_last() const
{
  if (cardinality == 0)
    return NULL;

  const Node_t *leaf = root->last_leaf();

  return leaf->last_entry().get_data();
}


/* insert data into the tree - duplicate keys are replaced */
OS_BTREE_TEMPLATE void
_B_tree_pt OS_BTREE_PARS::insert(Key_t key,
				 Data_t *data)
{
  cardinality++;
  change_tick++;
  if (root == NULL)
    root = new(os_segment::of(this), Node_t::get_os_typespec())
        Node_t(0, NULL, NULL, NULL);

  root->insert(key, data, this);
}


/* change a key in the tree - the from_key must exist in the tree, and the
   change must keep the key sorted with respect to neighboring keys */
OS_BTREE_TEMPLATE void
_B_tree_pt OS_BTREE_PARS::change_key(Key_t from_key,
				     Key_t to_key)
{
  if (root == NULL)
      os_Traverser_messages::OS_FATAL(os_Traverser_messages::b_tree_pt_change_key);
  root->change_key(from_key, to_key);
}


/* remove the data in the tree corresponding to the given key.  If the key is
   not found, then nothing is removed, and false is returned.  Otherwise,
   remove returns true */
OS_BTREE_TEMPLATE os_boolean
_B_tree_pt OS_BTREE_PARS::remove(Key_t key)
{
  if (cardinality == 0)
    return /*false*/ 0;
  if (root->remove(key, this))
  {
    cardinality--;
    change_tick++;
    return /*true*/ 1;
  }
  return /*false*/ 0;
}


/* verify an entire btree - makes sure all links are correct, all keys are
   sorted, and that the cardinality matches the actual number of data entries
   */
OS_BTREE_TEMPLATE void
_B_tree_pt OS_BTREE_PARS::verify() const
{
  if (root == NULL)
  {
    if (cardinality)
        os_Traverser_messages::OS_FATAL(os_Traverser_messages::b_tree_pt_verify1);
    return;
  }

  os_unsigned_int32 num =
    root->verify(/*parent*/NULL, /*index*/0);
  if (cardinality != num)
      os_Traverser_messages::OS_FATAL(os_Traverser_messages::b_tree_pt_verify2);
}

    
/****************************************************************************/
/* _B_tree_safe_cursor_pt */
/****************************************************************************/


OS_BTREE_TEMPLATE Data_t *
_B_tree_safe_cursor_pt OS_BTREE_PARS::first()
{
  if (tree->is_empty()) {
    index = -1;
    current_leaf_node = NULL;
    return NULL;
  }
  
  index = 0;
  change_tick = tree->change_tick;
  current_leaf_node = tree->first_leaf();
  if (current_leaf_node != NULL)
  {
    current_key = current_leaf_node->first_key();
    return current_leaf_node->first_entry().get_data();
  }
  else
    return NULL;
}


OS_BTREE_TEMPLATE Data_t *
_B_tree_safe_cursor_pt OS_BTREE_PARS::last()
{
  if (tree->is_empty()) {
    index = 0;
    current_leaf_node = NULL;
    return NULL;
  }

  change_tick = tree->change_tick;
  current_leaf_node = tree->last_leaf();
  if (current_leaf_node != NULL)
  {
    current_key = current_leaf_node->last_key();
    index = current_leaf_node->count - 1;
    return current_leaf_node->last_entry().get_data();
  }
  else
    return NULL;
}


OS_BTREE_TEMPLATE Data_t *
_B_tree_safe_cursor_pt OS_BTREE_PARS::next()
{
  if (!at_an_entry())
  {
    if (index < 0)
      /* before first - next is first */
      return first();
    
    if (current_leaf_node == NULL)
      /* after last - no next */
      return NULL;
  }

  if (++index >= (os_int32)current_leaf_node->count)
  {
    /* go to right sibling */
    current_leaf_node = current_leaf_node->right_sibling;
    index = 0;
    if (current_leaf_node != NULL)
      current_key = current_leaf_node->first_key();
    else
      return NULL;
  }
  else
    /* normal intranode case */
    current_key = current_leaf_node->get_key(index);
    
  return current_leaf_node->get_entry(index).get_data();
}


OS_BTREE_TEMPLATE Data_t *
_B_tree_safe_cursor_pt OS_BTREE_PARS::previous()
{
  if (!at_an_entry())
  {
    if (index < 0)
      /* before first - no previous */
      return NULL;

    if (current_leaf_node == NULL)
      /* after last - previous is last */
      return last();
  }

  if (index == 0)
  {
    /* go to left sibling */
    current_leaf_node = current_leaf_node->left_sibling;
    if (current_leaf_node != NULL)
    {
      /* there is a left sibling */
      index = current_leaf_node->count - 1;
      current_key = current_leaf_node->get_key(index);
    }
    else
    {
      /* no left sibling */
      index = -1;
      return NULL;
    }
  }
  else
    /* normal intranode case */
    current_key = current_leaf_node->get_key(--index);

  return current_leaf_node->get_entry(index).get_data();
}


OS_BTREE_TEMPLATE Data_t *
_B_tree_safe_cursor_pt OS_BTREE_PARS::move_to(Key_t key)
{
  change_tick = tree->change_tick;
  current_leaf_node = tree->find_leaf(key);
  if (current_leaf_node == NULL ||
      (index = current_leaf_node->find_index(key)) < 0)
  {
    /* before the first entry */
    index = -1;
    current_leaf_node = NULL;
    current_key = key;
    return NULL;
  }
  current_key = current_leaf_node->get_key(index);
  return current_leaf_node->get_entry(index).get_data();
}


OS_BTREE_TEMPLATE os_boolean
_B_tree_safe_cursor_pt OS_BTREE_PARS::at_an_entry()
{
  while (/*true*/ 1)
  {
    if (tree->is_empty() || current_leaf_node == NULL)
      return /*false*/ 0;

    if (change_tick != tree->change_tick)
      move_to(current_key);
    else
    {
      if (index < 0)
          os_Traverser_messages::
	      OS_FATAL(os_Traverser_messages::b_tree_safe_cursor_pt_at_an_entry1);
      if (index >= (os_int32)current_leaf_node->count)
	  os_Traverser_messages::
	      OS_FATAL(os_Traverser_messages::b_tree_safe_cursor_pt_at_an_entry2);
      current_key = current_leaf_node->get_key(index);
      return /*true*/ 1;
    }
  }
  /* Compiler workaround--Should never be reached. */
  return /*false*/ 0;
}


OS_BTREE_TEMPLATE Data_t *
_B_tree_safe_cursor_pt OS_BTREE_PARS::get_data()
{
  if (!at_an_entry())
    return NULL;

  return current_leaf_node->get_entry(index).get_data();
}


OS_BTREE_TEMPLATE Key_t
_B_tree_safe_cursor_pt OS_BTREE_PARS::get_key()
{
  at_an_entry();
  return current_key;
}


OS_BTREE_TEMPLATE void
_B_tree_safe_cursor_pt OS_BTREE_PARS::remove_at()
{
  if (!at_an_entry())
    return;

  os_boolean removed = current_leaf_node->remove_here(current_key, tree);
  if ( ! removed)
      os_Traverser_messages::
          OS_FATAL(os_Traverser_messages::b_tree_safe_cursor_pt_remove_at);
  tree->cardinality--;
  tree->change_tick++;
  /* let the next op do the resync */
}


OS_BTREE_TEMPLATE void
_B_tree_safe_cursor_pt OS_BTREE_PARS::change_key_at(Key_t to_key)
{
  if (!at_an_entry())
    return;

  current_leaf_node->change_key_here(current_key, to_key);
  current_key = to_key;
}


