/*========================================================================
 *
 * File:      $RCSfile: sw_com.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:09 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef SW_COM_HH
#define SW_COM_HH


#ifdef OLD_FILE_NAMES
#include <U_typedefs.hh>
#include <D_domain_id.hh>
#include <U_id.hh>
#else
#include <u_typdef.hh>
#include <d_domid.hh>
#include <u_id.hh>
#endif


#include <sg_com.hh>


class Object;
class I_Object_Instance;




//  The following defines pertain to the format of an item which is displayed
//    in the scrolling list - since values can not be separately associated
//    with each item, the item Id is converted to an 8 digit hex string and
//    is stored way out at the end of the item string where the user can not
//    see it.
//
//  NOTE:  The ITEM_STR_FORMAT_STR must be kept the consistent as the
//    ITEM_NAME_STR_SIZE and ITEM_ID_STR_SIZE manually.
//
#define ITEM_NAME_STR_SIZE	300
#define ITEM_ID_STR_SIZE	8
#define ITEM_STR_FORMAT_STR	"%-300.300s%08x"
#define ITEM_STR_SIZE		(ITEM_NAME_STR_SIZE + ITEM_ID_STR_SIZE)
#define ITEM_ID_START		ITEM_NAME_STR_SIZE




class W_window : public W_gui_drivers

{
public:
    Domain*			get_domain_ptr ();
    Object*			get_object_ptr ();
    I_Object_Instance*		get_object_instance_ptr ();


    virtual void		window_update__rerender ();

    virtual void		window_update__version (Id);
    virtual void		window_update__processing_event ();

    Domain_id			get_domain_id ()
				    { return domain_id; }
    Id				get_object_id ()
				    { return object_id; }
    Id				get_object_instance_id ()
				    { return object_inst_id; }



protected:
				W_window ();
				W_window (Domain *);
				W_window (Object *);
				W_window (I_Object_Instance *);
    virtual			~W_window ();


private:

    Domain_id			domain_id;
    Id				im_ocm_oam_id;
    Id				object_id;
    Id				object_inst_id;
};




#endif
