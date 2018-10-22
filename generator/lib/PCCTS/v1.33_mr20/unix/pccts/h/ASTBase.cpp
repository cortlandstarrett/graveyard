/* Abstract syntax tree manipulation functions
 *
 * SOFTWARE RIGHTS
 *
 * We reserve no LEGAL rights to the Purdue Compiler Construction Tool
 * Set (PCCTS) -- PCCTS is in the public domain.  An individual or
 * company may do whatever they wish with source code distributed with
 * PCCTS or the code generated by PCCTS, including the incorporation of
 * PCCTS, or its output, into commerical software.
 *
 * We encourage users to develop software with PCCTS.  However, we do ask
 * that credit is given to us for developing PCCTS.  By "credit",
 * we mean that if you incorporate our source code into one of your
 * programs (commercial product, research project, or otherwise) that you
 * acknowledge this fact somewhere in the documentation, research report,
 * etc...  If you like PCCTS and have developed a nice tool with the
 * output, please mention that you developed it using PCCTS.  In
 * addition, we ask that this header remain intact in our source code.
 * As long as these guidelines are kept, we expect to continue enhancing
 * this system and expect to make other tools available as they are
 * completed.
 *
 * ANTLR 1.33
 * Terence Parr
 * Parr Research Corporation
 * with Purdue University and AHPCRC, University of Minnesota
 * 1989-1998
 */

#include "pcctscfg.h"

#include "pccts_stdio.h"
#include "pccts_stdarg.h"

PCCTS_NAMESPACE_STD

#define ANTLR_SUPPORT_CODE

#include "ASTBase.h"

/* ensure that tree manipulation variables are current after a rule
 * reference
 */
void
ASTBase::link(ASTBase **_root, ASTBase **_sibling, ASTBase **_tail)
{
	if ( *_sibling == NULL ) return;
	if ( *_root == NULL ) *_root = *_sibling;
	else if ( *_root != *_sibling ) (*_root)->_down = *_sibling;
	if ( *_tail==NULL ) *_tail = *_sibling;
	while ( (*_tail)->_right != NULL ) *_tail = (*_tail)->_right;
}

/* add a child node to the current sibling list */
void
ASTBase::subchild(ASTBase **_root, ASTBase **_sibling, ASTBase **_tail)
{
	if ( *_tail != NULL ) (*_tail)->_right = this;
	else {
		*_sibling = this;
		if ( *_root != NULL ) (*_root)->_down = *_sibling;
	}
	*_tail = this;
	if ( *_root == NULL ) *_root = *_sibling;
}

/* make a new AST node.  Make the newly-created
 * node the root for the current sibling list.  If a root node already
 * exists, make the newly-created node the root of the current root.
 */
void
ASTBase::subroot(ASTBase **_root, ASTBase **_sibling, ASTBase **_tail)
{
	if ( *_root != NULL )
		if ( (*_root)->_down == *_sibling ) *_sibling = *_tail = *_root;
	*_root = this;
	(*_root)->_down = *_sibling;
}

/* Apply preorder_action(), etc.. to root then each sibling */
//
//  7-Apr-97 133MR1
//	Fix suggested by Ron House (house@helios.usq.edu.au)
//
void
ASTBase::preorder()
{
	ASTBase *tree = this;

	while ( tree!= NULL )
	{
		if ( tree->_down != NULL ) {
			tree->preorder_before_action(); 		// MR1	
		};
		tree->preorder_action();
		if ( tree->_down!=NULL )
		{
			tree->_down->preorder();
			tree->preorder_after_action();			// MR1
		}
		tree = tree->_right;
	}
}

/* free all AST nodes in tree; apply func to each before freeing */
void
ASTBase::destroy()
{
   ASTBase* tree = this;
   while (tree) {
      if (tree->_down) tree->_down->destroy();

      ASTBase* cur = tree;
      tree = tree->_right;
      delete cur;
   }
}

/* build a tree (root child1 child2 ... NULL)
 * If root is NULL, simply make the children siblings and return ptr
 * to 1st sibling (child1).  If root is not single node, return NULL.
 *
 * Siblings that are actually siblins lists themselves are handled
 * correctly.  For example #( NULL, #( NULL, A, B, C), D) results
 * in the tree ( NULL A B C D ).
 *
 * Requires at least two parameters with the last one being NULL.  If
 * both are NULL, return NULL.
 */
ASTBase *
ASTBase::tmake(ASTBase *root, ...)
{
	va_list ap;
	register ASTBase *child, *sibling=NULL, *tail, *w;

	va_start(ap, root);

	if ( root != NULL )
		if ( root->_down != NULL ) return NULL;
	child = va_arg(ap, ASTBase *);
	while ( child != NULL )
	{
		for (w=child; w->_right!=NULL; w=w->_right) {;} /* find end of child */
		if ( sibling == NULL ) {sibling = child; tail = w;}
		else {tail->_right = child; tail = w;}
		child = va_arg(ap, ASTBase *);
	}
	if ( root==NULL ) root = sibling;
	else root->_down = sibling;
	va_end(ap);
	return root;
}

#ifndef PCCTS_NOT_USING_SOR

/* tree duplicate */
// forgot to check for NULL this (TJP July 23,1995)
ASTBase *
ASTBase::dup()
{
	ASTBase *u, *t=this;
	
	if ( t == NULL ) return NULL;
/*
	u = new ASTBase;
	*u = *t;
*/
	u = (ASTBase *)this->shallowCopy();
	if ( t->_right!=NULL ) u->_right = t->_right->dup();
	else u->_right = NULL;
	if ( t->_down!=NULL ) u->_down = t->_down->dup();
	else u->_down = NULL;
	return u;
}
#endif

//
//  7-Apr-97 133MR1
//  	     Fix suggested by Asgeir Olafsson (olafsson@cstar.ac.com)
//
/* tree duplicate */

#ifndef PCCTS_NOT_USING_SOR

ASTBase *
ASTDoublyLinkedBase::dup()
{
	ASTDoublyLinkedBase *u, *t=this;
	
	if ( t == NULL ) return NULL;
	u = (ASTDoublyLinkedBase *)this->shallowCopy();
	u->_up = NULL;		/* set by calling invocation */
	u->_left = NULL;
	if (t->_right!=NULL) {						// MR1
          u->_right=t->_right->dup();					// MR1
	  ((ASTDoublyLinkedBase *)u->_right)->_left = u;		// MR1
        } else {							// MR1
	  u->_right = NULL;						// MR1
        };								// MR1
	if (t->_down!=NULL) {						// MR1
  	  u->_down = t->_down->dup();					// MR1
          ((ASTDoublyLinkedBase *)u->_down)->_up = u;			// MR1
        } else {							// MR1
	  u->_down = NULL;						// MR1
        };								// MR1
	return u;
}

#endif

/*
 * Set the 'up', and 'left' pointers of all nodes in 't'.
 * Initial call is double_link(your_tree, NULL, NULL).
 */
void
ASTDoublyLinkedBase::double_link(ASTBase *left, ASTBase *up)
{
    ASTDoublyLinkedBase *t = this;

    t->_left = (ASTDoublyLinkedBase *) left;
    t->_up = (ASTDoublyLinkedBase *) up;
    if (t->_down != NULL)
		((ASTDoublyLinkedBase *)t->_down)->double_link(NULL, t);
    if (t->_right != NULL)
		((ASTDoublyLinkedBase *)t->_right)->double_link(t, up);
}

