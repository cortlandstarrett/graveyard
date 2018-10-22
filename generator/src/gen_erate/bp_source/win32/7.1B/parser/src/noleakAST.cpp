/*========================================================================
 *
 * File:      $RCSfile: noleakAST.cpp,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:21 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 *  28-May-97	clearList does removeNode on all elements of list 
 */
/*  This file should be accompanied by DISCLAIMER.TXT stating disclaimers */

#include "noleakAST.h"
#include <stdio.h>

NoLeakAST::NoLeakAST() : 
	next(0),
	prev(0),
        serial(++counter) {
   insertNode();
}

NoLeakAST::~NoLeakAST() {
   removeNode();
};

NoLeakAST::NoLeakAST(const NoLeakAST & from) :
	ASTBase(from),
	next(0),
	prev(0),
	serial(++counter) {
   insertNode();
}

// no need to copy information since both nodes already on list

NoLeakAST & NoLeakAST::operator = (const NoLeakAST & from) {
   return *this;
}

void NoLeakAST::init() {
    NoLeakAST* newHead = new NoLeakAST();

    // the c'tor automatically puts the node on the list
    newHead->removeNode();

    // only use the next pointer for chaining
    // use the prev pointer to store the old listHead

    newHead->next = listOfListHead;
    newHead->prev = listHead;
    listHead = 0;
    listOfListHead = newHead;
}

void NoLeakAST::cleanup() {

    NoLeakAST* newListOfHead = listOfListHead->next;
    NoLeakAST* newListHead = listOfListHead->prev;
    
    // add listOfListHead node to list so it will be 
    // deleted by destroyList()
    listOfListHead->insertNode();

    // first clean out all entries on the current list
    destroyList();

    // and set listHead back to previous value
    listHead = newListHead;
    listOfListHead = newListOfHead;

}

void NoLeakAST::insertNode() {
   if (listHead == 0) {
      listHead=this;
      prev=this;
      next=this;
   } else {
      next=listHead;
      prev=listHead->prev;
      next->prev=this;
      prev->next=this;      
      listHead=this;
   };
}

void NoLeakAST::removeNode() {
   next->prev=prev;
   prev->next=next;
   if (listHead == this) {
     listHead=next;
     if (listHead == this) {
	listHead=0;
     };
   };
   prev=0;
   next=0;     
}

void NoLeakAST::destroyList() {

   while (listHead != 0) {
     delete listHead;		// uses side-effect of destructor
   };
}

void NoLeakAST::dumpNode(const char * s, const char * buffer) {

   if (s != 0) {printf("%s ",s);};
   printf("AST # %d\n",serial);
}

void NoLeakAST::dumpList() {
    
   NoLeakAST *	element;

   if (listHead == 0) {
      printf("\n*** AST list is empty ***\n");
   } else {
      printf("\n*** Dump of ASTs on list ***\n\n");
      element=listHead;
      do {
        element->dumpNode("DumpList");
        element=element->next;
      } while (element != listHead);
      printf("\n*** End of Dump ***\n\n");
   };
}

void NoLeakAST::dumpTree1(int indent, const char * buffer) {

   NoLeakAST *	tree=this;

//------------------------------------------------
// NOTE: The following AL statement breaks this:
//        bridge AA::foo(a:1, b:3*4);
//------------------------------------------------

   dumpTreeIndent(indent);
   dumpNode(0, buffer);
   if (tree->down() != 0)
     ( (NoLeakAST *)tree->down() )->dumpTree1(indent+1, buffer);
   if (tree->right() != 0)
     ( (NoLeakAST *)tree->right() )->dumpTree1(indent, buffer);
}

void NoLeakAST::removeTree() {

   NoLeakAST *	subTree;

   if (down() != 0) {
      for (subTree=(NoLeakAST *)down();
	   subTree != 0;
	   subTree=(NoLeakAST *)subTree->right()) {
         subTree->removeTree();
      };
   };
   removeNode();
}

void NoLeakAST::dumpTree(const char * s, const char * buffer) {

   if (s != 0) {printf("\n%s:\n",s);}
   else {printf("\n");}
   dumpTree1(0, buffer);
}

void NoLeakAST::dumpTreeIndent(int indent) {

   int		i;

   for (i=0;i<indent;i++) {
     printf("  ");
   };
}

void NoLeakAST::clearList() {

   while (listHead != 0) {	// uses side-effect of removeNode
     listHead->removeNode();
   };
}

void NoLeakAST::clearCounter() {
   counter=0;
}

NoLeakAST * NoLeakAST::listHead=0;
NoLeakAST * NoLeakAST::listOfListHead=0;
int NoLeakAST::counter=0;

