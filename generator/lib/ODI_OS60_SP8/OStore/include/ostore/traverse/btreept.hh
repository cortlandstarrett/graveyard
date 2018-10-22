/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef BTREEPT2_HH
#define BTREEPT2_HH

#include <ostore/portypes.hh>
#include <ostore/ostore.hh>

#define OS_BTREE_TEMPLATE				\
template <class Key_t,				\
          class Data_t,				\
          const os_unsigned_int32 Min_per_node,	\
          const os_unsigned_int32 Max_per_node>

#define OS_BTREE_PARS <Key_t, Data_t, Min_per_node, Max_per_node>

#define OS_BTREE_TYPEDEFS				\
typedef _B_tree_pt OS_BTREE_PARS Tree_t;		\
typedef _B_tree_node_pt OS_BTREE_PARS Node_t;	\
typedef _B_tree_entry_pt OS_BTREE_PARS Entry_t

#define OS_NODE_T _B_tree_node_pt OS_BTREE_PARS

OS_BTREE_TEMPLATE class _B_tree_node_pt;


OS_BTREE_TEMPLATE class _B_tree_entry_pt;


OS_BTREE_TEMPLATE class _B_tree_safe_cursor_pt;


OS_BTREE_TEMPLATE class _B_tree_pt 
{
public:
  OS_BTREE_TYPEDEFS;
  friend class _B_tree_node_pt OS_BTREE_PARS;
  friend class _B_tree_safe_cursor_pt OS_BTREE_PARS;
protected:
  Node_t *root;
  os_unsigned_int32 change_tick;
  os_unsigned_int32 cardinality;

  const Node_t *first_leaf() const;

  Node_t *first_leaf()
  { return (Node_t*)(((const Tree_t*)this)->first_leaf()); }

  const Node_t *last_leaf() const;

  Node_t *last_leaf()
  { return (Node_t*)(((const Tree_t*)this)->last_leaf()); }

  const Node_t *find_leaf(Key_t key) const;
    
  Node_t *find_leaf(Key_t key)
  { return (Node_t*)(((const Tree_t*)this)->find_leaf(key)); }

public:
  _B_tree_pt();

  void clear();
    
  ~_B_tree_pt() { clear(); }

  const Data_t *find(Key_t key, os_boolean exact, 
		     Key_t* exact_key = 0) const;

  Data_t *find(Key_t key,
	       os_boolean exact, Key_t* exact_key = 0)
  { return (Data_t*)(((const Tree_t*)this)->find(key, exact, exact_key)); }

  const Data_t *find_first() const;

  Data_t *find_first()
  { return (Data_t*)(((const Tree_t*)this)->find_first()); }

  const Data_t *find_last() const;

  Data_t *find_last()
  { return (Data_t*)(((const Tree_t*)this)->find_last()); }

  void insert(Key_t key,
	      Data_t *data);

  void change_key(Key_t from_key,
		  Key_t to_key);

  os_boolean remove(Key_t key);

  os_unsigned_int32 get_height() const
  { return root == 0 ? 0 : root->get_height(); }

  os_unsigned_int32 get_cardinality() const { return cardinality; }

  os_boolean is_empty() const { return cardinality == 0; }

  void verify() const;

  public: // ObjectStore
    static os_typespec* get_os_typespec ();

};


OS_BTREE_TEMPLATE class _B_tree_entry_pt
{
  // becomes Entry_t
  friend class _B_tree_node_pt OS_BTREE_PARS;
public:
  OS_BTREE_TYPEDEFS;
  typedef Entry_t This_t;

  _B_tree_entry_pt(Key_t key_arg,
		   void *val_arg)
    : key(key_arg)
  { set_value(val_arg); }

  _B_tree_entry_pt() {}

  void set_parent(Node_t *parent) { get_child()->set_parent(parent); }
  
  void set_key(Key_t key_arg) { key = key_arg; }

  Key_t get_key() { return key; }

  const Key_t get_key() const { return key; }

  Data_t *get_data() { return (Data_t*)object; }

  const Data_t *get_data() const { return (const Data_t*)object; }

  void set_data (Data_t* data) { object = data; }

  Node_t *get_child() { return (Node_t*)object; }

  const Node_t *get_child() const { return (const Node_t*)object; }

  void set_child (Node_t* child) { object = child; }

  void* get_value () { return object; }

  const void* get_value () const { return object; }

  void set_value (void* value) { object = value; }

  os_unsigned_int32 verify(const Node_t*,
			   os_unsigned_int32) const { return 1; }

  public: // ObjectStore
    static os_typespec* get_os_typespec ();

private:
  Key_t key;
  // Must get rid of union.
#if 1
    void* object;
#else
  union {
    Data_t *data;
    Node_t *child;
    void *val;
  };
#endif
};


OS_BTREE_TEMPLATE class _B_tree_node_pt 
{
    // becomes Node_t
public:
  OS_BTREE_TYPEDEFS;
  friend class _B_tree_pt OS_BTREE_PARS;
  friend class _B_tree_entry_pt OS_BTREE_PARS;
  friend class _B_tree_safe_cursor_pt OS_BTREE_PARS;

  typedef Node_t This_t;

  _B_tree_node_pt(os_unsigned_int32 height_arg,
		  Node_t *parent_arg,
		  Node_t *left_sibling_arg,
		  Node_t *right_sibling_arg);

  ~_B_tree_node_pt();

  os_unsigned_int32 get_height() const { return height; }

  os_boolean is_empty() const { return count == 0; }

  const Node_t *first_leaf() const;

  Node_t *first_leaf()
  { return (Node_t*)(((const This_t*)this)->first_leaf()); }

  const Node_t *last_leaf() const;

  Node_t *last_leaf()
  { return (Node_t*)(((const This_t*)this)->last_leaf()); }

  const Node_t *find_leaf(Key_t key,
			  os_boolean force) const;

  Node_t *find_leaf(Key_t key,
		    os_boolean force)
  { return (Node_t*)(((const This_t*)this)->find_leaf(key, force)); }

  void insert(Key_t key,
	      Data_t *data,
	      Tree_t *tree);

  const Data_t *find(Key_t key,
		     os_boolean exact, Key_t* exact_key = 0) const;

  Data_t *find(Key_t key,
	       os_boolean exact, Key_t* exact_key = 0)
  { return (Data_t*)(((const This_t*)this)->find(key, exact, exact_key)); }

  void change_key(Key_t from_key,
		  Key_t to_key);

  os_boolean remove(Key_t key,
		    Tree_t *tree);

public:

  void lshift(This_t &src_node,
	      os_unsigned_int32 num);

  void rshift(This_t &src_node,
	      os_unsigned_int32 num);

  void insert_here(Key_t key,
		   void *val,
		   Tree_t *tree);

  void split(Key_t key,
	     void *val,
	     Tree_t *tree);

  os_int32 find_index(Key_t key) const;

  
  Key_t first_key() const { return entries[0].get_key(); }

  Key_t get_key(os_int32 i) const { return entries[i].get_key(); }

  Key_t last_key() const { return entries[count - 1].get_key(); }

  Entry_t &first_entry() { return entries[0]; }

  const Entry_t &first_entry() const { return entries[0]; }

  Entry_t &get_entry(os_int32 i) { return entries[i]; }

  const Entry_t &get_entry(os_int32 i) const { return entries[i]; }

  Entry_t &last_entry() { return entries[count - 1]; }

  const Entry_t &last_entry() const { return entries[count - 1]; }

  os_boolean remove_here(Key_t key,
			 Tree_t *tree);

  void change_key_here(Key_t from_key,
		       Key_t to_key);

  void balance_with_right_sibling(Tree_t *tree);

  void collapse_with_right_sibling(Tree_t *tree);

  void set_parent(Node_t *new_parent) { parent = new_parent; }

  os_unsigned_int32 verify(const Node_t *parent,
			   os_unsigned_int32 index) const;

  public: // ObjectStore
    static os_typespec* get_os_typespec ();

protected:
  Node_t *parent;
  Node_t *left_sibling;
  Node_t *right_sibling;
  os_unsigned_int32 count;
  const os_unsigned_int32 height;
  Entry_t entries[Max_per_node];
};


OS_BTREE_TEMPLATE class _B_tree_safe_cursor_pt 
{
public:
  OS_BTREE_TYPEDEFS;

  _B_tree_safe_cursor_pt(Tree_t *btree);

  _B_tree_safe_cursor_pt() { /* Do not use */ };

  Data_t *first();

  Data_t *last();

  Data_t *next();

  Data_t *previous();

  Data_t *move_to(Key_t key);

  os_boolean at_an_entry();

  Data_t *get_data();

  Key_t get_key();

  void remove_at();

  void change_key_at(Key_t to_key);

  public: // ObjectStore
    static os_typespec* get_os_typespec ();

private:
  Tree_t *tree;
  Node_t *current_leaf_node;
  Key_t current_key;
  os_int32 index;
  os_unsigned_int32 change_tick;
};


OS_BTREE_TEMPLATE
inline _B_tree_safe_cursor_pt OS_BTREE_PARS::_B_tree_safe_cursor_pt(Tree_t *tree_arg)
    : tree(tree_arg),
      current_leaf_node(NULL),
      index(-1)
{}

#endif
