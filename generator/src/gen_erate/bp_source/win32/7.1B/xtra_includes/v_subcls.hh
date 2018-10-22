/*========================================================================
 *
 * File:      $RCSfile: v_subcls.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:11 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef		V_SUB_CLASS_HH
#define		V_SUB_CLASS_HH

#include <vdialog.h>
#include <vcontain.h>
#include <vtextitem.h>
#include <vdomview.h>

#include <u_id.hh>

typedef struct ostextview   ostextview;
typedef struct ostextviewClass ostextviewClass;

typedef ostextview * (*ostextviewCreate) ( void );

typedef int (*ostextviewNoteProc) (
        ostextview  *dialog,
        vevent     *event,
		int		message
        );

ostextviewClass * ostextviewGetDefaultClass(void);

struct ostextview
{
   vtextview    name;
};

#define ostextviewCLASS(SUPER, ITEM, NOTIFY)   \
    vtextviewCLASS(SUPER, ITEM, NOTIFY)

struct ostextviewClass {
    ostextviewCLASS(ostextviewClass, ostextview, ostextviewNoteProc);
 };

// Action specific functions
#define ostextviewCreatOfClass(c)        \
    ((ostextview *) vtextviewCreateOfClass((vdialog *) (c)))
#define ostextviewCreate()   \
    ostextviewCreateOfClass(ostextviewGetDefaultClass())


typedef struct ptdraw   ptdraw;
typedef struct ptdrawClass ptdrawClass;

class CE_text;
class Graphical_Element;


class ptdrawObjectData {
public:
  ptdrawObjectData(Graphical_Element* p_ge):
     m_ge(p_ge)
	 {}
  ~ptdrawObjectData()
	 { m_ge = 0; }
  Graphical_Element* m_ge;
};

typedef ptdraw * (*ptdrawCreate) ( void );

typedef int (*ptdrawNoteProc) (
        ptdraw  *contain,
        vevent     *event
        ) ;

vdomainClass * ptdrawGetDefaultDomainClass(void);
vdomainviewClass * ptdrawGetDefaultClass(void);
vdomainviewEventClass * ptdrawGetDefaultEventClass(void);

#endif

