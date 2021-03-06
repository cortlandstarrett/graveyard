/******************************************************************************
*               (c) Copyright 1991,92,93 Visix Software, Inc.              
*                           All rights reserved.                           
* The following Sample Code is provided for your reference purposes in     
* connection with your use of the Galaxy Application Environment (TM)      
* software product which you have licensed from Visix Software, Inc.       
* ("Visix"). The Sample code is provided to you without any warranty of any
* kind and you agree to be responsible for the use and/or incorporation    
* of the Sample Code into any software product you develop. You agree to   
* fully and completely indemnify and hold Visix harmless from any and all  
* loss, claim, liability or damages with respect to your use of the Sample 
* Code.                                                                    
*                                                                          
* Subject to the foregoing, you are permitted to copy, modify, and         
* distribute the Sample Code for any purpose, and without fee, provided    
* that (i) a copyright notice in the in the form of "Copyright 1992 Visix  
* Software Inc., 11440 Commerce Park Drive, Reston, VA  22091. All Rights  
* Reserved" appears in all copies, (ii) both the copyright notice and this 
* permission notice appear in all supporting documentation and (iii) you   
* are a valid licensee of The Galaxy Application Environment.              
*                                                                          
******************************************************************************/

#ifndef domainINCLUDED
#define domainINCLUDED TRUE

#ifndef vportINCLUDED
#include <vport.h> /* for v*HEADER */
#endif

#ifndef vdomainviewINCLUDED
#include vdomainviewHEADER
#endif

enum {
  myDomainObjectLINE,
  myDomainObjectPOINT
};

struct _myDomainObject {
  int                     objectType;
  vdomainObject          *domainObject;
  struct _myDomainObject *connection1;
  struct _myDomainObject *connection2;
  vpoint                  point1;
  vpoint                  point2;
  vbool                   amMoving;
};

typedef struct _myDomainObject myDomainObject;

void domainSetupView (vdomainview *view);
void domainCleanupView (vdomainview *view);

myDomainObject *domainCreateMyObject ();
myDomainObject *domainAddPoint (vdomain *domain, int x1, int y1);
myDomainObject *domainAddLine (vdomain *domain, int x1, int y1, int x2, int y2);
myDomainObject *domainConnectLine (vdomain *domain, myDomainObject *myObject, int x2, int y2);
myDomainObject *domainConnectPoint (vdomain *domain, myDomainObject *myObject);

#endif
