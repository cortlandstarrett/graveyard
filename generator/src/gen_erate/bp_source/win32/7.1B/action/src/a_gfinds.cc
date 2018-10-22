/*========================================================================
 *
 * File:      $RCSfile: a_gfinds.cc,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:42:36 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#include <stdlib.h>     // atoi


#include <u_trace.hh>
#include <u_error.hh>

#include "d_domain.hh"
#include "d_subsys.hh"
#include "d_sm_pm.hh"
#include "d_object.hh"
#include "d_rel.hh"
#include "d_smevt.hh"
#include "d_smedi.hh"
#include "d_entity.hh"
#include "d_tfmr.hh"
#include "d_bridge.hh"
#include "d_parm.hh"
#include "d_dattyp.hh"

#include "a_gfinds.hh"

// These enums are also coded in parser/include/p_types.hh:
const int AL_Generic_finds::OBJECT_KEY_LETTERS_FIELD = 1;
const int AL_Generic_finds::RELATIONSHIP_NUMBER_FIELD = 2;
const int AL_Generic_finds::EVENT_LABEL_FIELD = 3;
const int AL_Generic_finds::SM_EVENT_DATA_ITEM_NAME_FIELD = 4;
const int AL_Generic_finds::EE_EVENT_DATA_ITEM_NAME_FIELD = 5;
const int AL_Generic_finds::EXTERNAL_ENTITY_KL_FIELD = 6;
const int AL_Generic_finds::EVENT_MEANING_FIELD = 7;
const int AL_Generic_finds::EVENT_MEANING_TICKED_FIELD = 8;
const int AL_Generic_finds::ATTRIBUTE_FIELD = 9;
const int AL_Generic_finds::RELATIONSHIP_PHRASE_FIELD = 10;
const int AL_Generic_finds::TRANSFORMER_FIELD = 11;
const int AL_Generic_finds::TRANSFORMER_PARM_FIELD = 12;
const int AL_Generic_finds::BRIDGE_FIELD = 13;
const int AL_Generic_finds::BRIDGE_PARM_FIELD = 14;
// Not used: const int AL_Generic_finds::EXTERNAL_ENTITY_NAME_FIELD = 15;
const int AL_Generic_finds::SYNCH_SERVICE_FIELD = 16;
const int AL_Generic_finds::SYNCH_SERVICE_PARM_FIELD = 17;
const int AL_Generic_finds::ENUMERATION_FIELD = 18;
const int AL_Generic_finds::ENUMERATOR_FIELD = 19;


mc_dbms_Bag< Object * > *
AL_Generic_finds::find_object_by_key_letters( Domain * p_domain_ptr,
	const vchar * p_object_key_letters )
{

  LOG_TRACE( L_AL, L_FUNCTION_BEGIN, ( L_log_string,
                                       "Begin AL_Generic_finds::find_object_by_key_letters()...p_object_key_letters = ->%s<-", p_object_key_letters ));
  
  t_boolean found = FALSE;
  D_subsys * ss_ptr = 0;
  Object * object_ptr;
  mc_dbms_Bag< Object * > * object_coll =
    & mc_dbms_Bag<Object *>::create( mc_dbms_database::get_transient_database() );

  FIRST_ELEMENT( ss_ptr,
                 D_subsys,
                 p_domain_ptr->get_current_dd_srm_scm_sam_ptr()->get_dd_subsystem_coll_ptr(),
                 c1 );

  while ( ss_ptr )
    {
      FIRST_ELEMENT( object_ptr,
                     Object,
                     ss_ptr->get_im_ocm_oam_ptr()->get_object_coll_ptr(),
                     c2 );
      
      while ( object_ptr )
	{
          if ( object_ptr->object_key_letters() == p_object_key_letters )
            {
              object_coll->insert( object_ptr );
            }
          NEXT_ELEMENT( object_ptr, c2 );
	}
      
      NEXT_ELEMENT( ss_ptr, c1 );
    }

  LOG_TRACE( L_AL, L_FUNCTION_END, ( L_log_string,
                                     "End AL_Generic_finds::find_object_by_key_letters()...object_coll.card = %d",
                                     object_coll->cardinality() ));

  return( object_coll );

}


mc_dbms_Bag< Relationship * > *
AL_Generic_finds::find_relationship_by_number( Domain * p_domain_ptr,
	const char * p_rel_num )
{

LOG_TRACE( L_AL, L_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Generic_finds::find_relationship_by_number()...p_rel_num = ->%S<-", vcharScribeASCII(p_rel_num) ));

t_uint concerned_rel_num = atoi( p_rel_num );

t_boolean found = FALSE;
D_subsys * ss_ptr = 0;
Relationship * rel_ptr = 0;
mc_dbms_Bag< Relationship * > * rel_coll =
	& mc_dbms_Bag< Relationship * >::create(
	mc_dbms_database::get_transient_database() );

FIRST_ELEMENT( ss_ptr,
			   D_subsys,
			   p_domain_ptr->get_current_dd_srm_scm_sam_ptr()->get_dd_subsystem_coll_ptr(),
			   c1 );

while ( ss_ptr )
{
	FIRST_ELEMENT( rel_ptr,
				   Relationship,
				   ss_ptr->get_im_ocm_oam_ptr()->get_rel_coll_ptr(),
				   c2 );

	while ( rel_ptr )
	{
		LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
			"comparing against relationship number ->%d<-", rel_ptr->get_rel_number() ));

		if ( rel_ptr->get_rel_number() == concerned_rel_num )
		{
			rel_coll->insert( rel_ptr );
		}
		NEXT_ELEMENT( rel_ptr, c2 );
	}

	NEXT_ELEMENT( ss_ptr, c1 );
}

LOG_TRACE( L_AL, L_FUNCTION_END, ( L_log_string,
	"End AL_Generic_finds::find_relationship_by_number()...rel_coll.card = %d",
	rel_coll->cardinality() ));

return( rel_coll );

}


mc_dbms_Bag< D_sm_event * > *
AL_Generic_finds::find_sm_event_by_label( Domain * p_domain_ptr,
	const vchar * p_label )
{

LOG_TRACE( L_AL, L_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Generic_finds::find_sm_event_by_label()...p_label = ->%s<-", p_label ));

D_subsys * ss_ptr = 0;
Object * object_ptr = 0;
D_sm_spt_pm * sm_ptr = 0;
D_sm_event * event_ptr = 0;

mc_dbms_Bag< D_sm_event * > * event_coll =
	& mc_dbms_Bag< D_sm_event * >::create(
	mc_dbms_database::get_transient_database() );

FOR_ALL_ELEMENTS( ss_ptr,
			   D_subsys,
			   p_domain_ptr->get_current_dd_srm_scm_sam_ptr()->get_dd_subsystem_coll_ptr(),
			   c1 )
{
	FOR_ALL_ELEMENTS( object_ptr,
				   Object,
				   ss_ptr->get_im_ocm_oam_ptr()->get_object_coll_ptr(),
				   c2 )
	{
		// Remember we must look in both instance and assigner state
		// models (if they exist).

		sm_ptr = object_ptr->get_instance_sm_spt_pm_ptr();
		if ( sm_ptr )
		{
			FOR_ALL_ELEMENTS( event_ptr,
						   D_sm_event,
						   sm_ptr->get_sm_event_coll_ptr(),
						   c3 )
			{
				LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
					"comparing against event label ->%s<-", event_ptr->get_derived_event_label().char_ptr() ));

				if ( event_ptr->get_derived_event_label() == p_label )
				{
					event_coll->insert( event_ptr );
				}
			}
		}

		sm_ptr = object_ptr->get_assigner_sm_spt_pm_ptr();
		if ( sm_ptr )
		{
			FOR_ALL_ELEMENTS( event_ptr,
						   D_sm_event,
						   sm_ptr->get_sm_event_coll_ptr(),
						   c3 )
			{
				LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
					"comparing against event label ->%s<-", event_ptr->get_derived_event_label().char_ptr() ));

				if ( event_ptr->get_derived_event_label() == p_label )
				{
					event_coll->insert( event_ptr );
				}
			}
		}
	}
}

LOG_TRACE( L_AL, L_FUNCTION_END, ( L_log_string,
	"End AL_Generic_finds::find_sm_event_by_label()...event_coll.card = %d",
	event_coll->cardinality() ));

return( event_coll );

}


mc_dbms_Bag< D_external_entity * > *
AL_Generic_finds::find_external_entity_by_name( Domain * p_domain_ptr,
	const vchar * p_ee )
{

LOG_TRACE( L_AL, L_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Generic_finds::find_external_entity_by_name()...p_ee = ->%s<-",
	p_ee ));

t_boolean found = FALSE;
D_external_entity * ee_ptr = 0;
mc_dbms_Bag< D_external_entity * > * ee_coll =
	& mc_dbms_Bag< D_external_entity * >::create(
	mc_dbms_database::get_transient_database() );

FIRST_ELEMENT( ee_ptr,
			   D_external_entity,
			   p_domain_ptr->get_current_dd_srm_scm_sam_ptr()->
				  get_external_entity_coll_ptr(),
			   c1 );

while ( ee_ptr )
{
	if ( ee_ptr->external_entity_name() == p_ee )
	{
		ee_coll->insert( ee_ptr );
	}

	NEXT_ELEMENT( ee_ptr, c1 );
}

LOG_TRACE( L_AL, L_FUNCTION_END, ( L_log_string,
	"End AL_Generic_finds::find_external_entity_by_name()...ee_coll.card = %d",
	ee_coll->cardinality() ));

return( ee_coll );

}


mc_dbms_Bag< D_external_entity * > *
AL_Generic_finds::find_external_entity_by_key_letters( Domain * p_domain_ptr,
	const vchar * p_ee )
{

LOG_TRACE( L_AL, L_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Generic_finds::find_external_entity_by_key_letters()...p_ee = ->%s<-",
	p_ee ));

D_external_entity * ee_ptr = 0;

mc_dbms_Bag< D_external_entity * > * ee_coll =
	& mc_dbms_Bag< D_external_entity * >::create(
	mc_dbms_database::get_transient_database() );

FIRST_ELEMENT( ee_ptr,
			   D_external_entity,
			   p_domain_ptr->get_current_dd_srm_scm_sam_ptr()->
				  get_external_entity_coll_ptr(),
			   c1 );

while ( ee_ptr )
{
	if ( ee_ptr->external_entity_key_letters() == p_ee )
	{
		ee_coll->insert( ee_ptr );
	}

	NEXT_ELEMENT( ee_ptr, c1 );
}

LOG_TRACE( L_AL, L_FUNCTION_END, ( L_log_string,
	"End AL_Generic_finds::find_external_entity_by_key_letters()...ee_coll.card = %d",
	ee_coll->cardinality() ));

return( ee_coll );

}


mc_dbms_Bag< D_external_entity_event * > *
AL_Generic_finds::find_external_entity_event_by_label( Domain * p_domain_ptr,
	const vchar * p_label )
{

LOG_TRACE( L_AL, L_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Generic_finds::find_external_entity_event_by_label()...p_label = ->%s<-", p_label ));

t_boolean found = FALSE;
D_external_entity * ee_ptr = 0;
D_external_entity_event * event_ptr = 0;
mc_dbms_Bag< D_external_entity_event * > * event_coll =
	& mc_dbms_Bag< D_external_entity_event * >::create(
	mc_dbms_database::get_transient_database() );

FIRST_ELEMENT( ee_ptr,
			   D_external_entity,
			   p_domain_ptr->get_current_dd_srm_scm_sam_ptr()->
				  get_external_entity_coll_ptr(),
			   c1 );

while ( ee_ptr )
{
	FIRST_ELEMENT( event_ptr,
				   D_external_entity_event,
				   ee_ptr->get_external_entity_event_coll_ptr(),
				   c2 );

	while ( event_ptr )
	{
		LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
			"comparing against event label ->%s<-", event_ptr->get_event_label().char_ptr() ));

		if ( event_ptr->get_derived_event_label() == p_label )
		{
			event_coll->insert( event_ptr );
		}
		NEXT_ELEMENT( event_ptr, c2 );
	}

	NEXT_ELEMENT( ee_ptr, c1 );
}

LOG_TRACE( L_AL, L_FUNCTION_END, ( L_log_string,
	"End AL_Generic_finds::find_external_entity_event_by_label()...event_coll.card = %d",
	event_coll->cardinality() ));

return( event_coll );

}


mc_dbms_Bag< D_sm_event_data_item * >
AL_Generic_finds::find_sm_event_data_item_by_name( Domain * p_domain_ptr,
	const vchar * p_event_data_item_name )
{

LOG_TRACE( L_AL, L_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Generic_finds::find_sm_event_data_item_by_name()...p_event_data_item_name = %s", p_event_data_item_name ) );

// This function not yet implemented/needed.

mc_dbms_Bag< D_sm_event_data_item * > event_coll;

return( event_coll );

}


D_external_entity *
AL_Generic_finds::find_external_entity_by_id( const Domain * p_domain_ptr,
	const Id & p_id )
{

LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Generic_finds::find_external_entity_by_id...p_id.class_type = %d, p_id.value = %d", p_id.get_class_type(), p_id.get_entire_value() ) );

D_external_entity * ptr = 0;

if ( p_id.get_class_type() != EXTERNAL_ENTITY_TYPE )
{
	LOG_ERROR( ( L_log_string,
		"AL_Generic_finds::find_external_entity_by_id()...Bad class type! class_type = %d, id = %d", p_id.get_class_type(), p_id.get_entire_value() ) );
}
else
{
	ptr = p_domain_ptr->get_current_dd_srm_scm_sam_ptr()->
		find_external_entity_by_id( p_id );
}

LOG_TRACE( L_AL, L_HI_FUNCTION_END, ( L_log_string,
	"End AL_Generic_finds::find_external_entity_by_id...ptr = 0x%x", ptr ) );

return( ptr );

}


D_external_entity_event *
AL_Generic_finds::find_external_entity_event_by_id( const Domain * p_domain_ptr,
	const Id & p_id )
{

LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Generic_finds::find_external_entity_event_by_id...p_id.class_type = %d, p_id.value = %d", p_id.get_class_type(), p_id.get_entire_value() ) );

D_external_entity_event * ptr = 0;

if ( p_id.get_class_type() != EXT_ENTITY_EVENT_TYPE )
{
	LOG_ERROR( ( L_log_string,
		"AL_Generic_finds::find_external_entity_event_by_id()...Bad class type! class_type = %d, id = %d", p_id.get_class_type(), p_id.get_entire_value() ) );
}
else
{
	t_boolean found = FALSE;
	D_external_entity * ee_ptr;

	FIRST_ELEMENT( ee_ptr,
				   D_external_entity,
				   p_domain_ptr->get_current_dd_srm_scm_sam_ptr()->
					get_external_entity_coll_ptr(),
				   c1 );

	while ( ! found && ee_ptr )
	{
		ptr = ee_ptr->find_external_entity_event( p_id );
		if ( ptr )
		{
			found = TRUE;
		}
		else
		{
			NEXT_ELEMENT( ee_ptr, c1 );
		}
	}
}

LOG_TRACE( L_AL, L_HI_FUNCTION_END, ( L_log_string,
	"End AL_Generic_finds::find_external_entity_event_by_id...ptr = 0x%x", ptr ) );

return( ptr );

}


D_external_entity_event_data_item *
AL_Generic_finds::find_external_entity_event_data_item_by_id(
	const Domain * p_domain_ptr, const Id & p_id )
{

LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Generic_finds::find_external_entity_event_data_item_by_id...p_id.class_type = %d, p_id.value = %d", p_id.get_class_type(), p_id.get_entire_value() ) );

D_external_entity_event_data_item * ptr = 0;

if ( p_id.get_class_type() != EXT_ENTITY_EVENT_DATA_ITEM_TYPE )
{
	LOG_ERROR( ( L_log_string,
		"AL_Generic_finds::find_external_entity_event_data_item_by_id()...Bad class type! class_type = %d, id = %d", p_id.get_class_type(), p_id.get_entire_value() ));
}
else
{
	t_boolean found = FALSE;
	D_external_entity * ee_ptr;

	FIRST_ELEMENT( ee_ptr,
				   D_external_entity,
				   p_domain_ptr->get_current_dd_srm_scm_sam_ptr()->
					get_external_entity_coll_ptr(),
				   c1 );

	while ( ! found && ee_ptr )
	{
		ptr = ee_ptr->find_external_entity_event_data_item( p_id );
		if ( ptr )
		{
			found = TRUE;
		}
		else
		{
			NEXT_ELEMENT( ee_ptr, c1 );
		}
	}
}

LOG_TRACE( L_AL, L_HI_FUNCTION_END, ( L_log_string,
	"End AL_Generic_finds::find_external_entity_event_data_item_by_id...ptr = 0x%x", ptr ) );

return( ptr );

}


Object *
AL_Generic_finds::find_object_by_id( const Domain * p_domain_ptr,
	const Id & p_id )
{

LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Generic_finds::find_object_by_id...p_id.class_type = %d, p_id.value = %d", p_id.get_class_type(), p_id.get_entire_value() ) );

Object * ptr = 0;

if ( p_id.get_class_type() != OBJECT_TYPE )
{
	LOG_ERROR( ( L_log_string,
		"AL_Generic_finds::find_object_by_id()...Bad class type! class_type = %d, id = %d", p_id.get_class_type(), p_id.get_entire_value() ));
}
else
{
	t_boolean found = FALSE;
	D_subsys * ss_ptr;

	FIRST_ELEMENT( ss_ptr,
				   D_subsys,
				   p_domain_ptr->get_current_dd_srm_scm_sam_ptr()->
					get_dd_subsystem_coll_ptr(),
				   c1 );

	while ( ! found && ss_ptr )
	{
		ptr = ss_ptr->get_im_ocm_oam_ptr()->find_object_by_id( p_id );
		if ( ptr )
		{
			found = TRUE;
		}
		else
		{
			NEXT_ELEMENT( ss_ptr, c1 );
		}
	}
}

LOG_TRACE( L_AL, L_HI_FUNCTION_END, ( L_log_string,
	"End AL_Generic_finds::find_object_by_id...ptr = 0x%x", ptr ) );

return( ptr );

}


Attribute *
AL_Generic_finds::find_attribute_by_id( const Domain * p_domain_ptr,
	const Id & p_id )
{

LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Generic_finds::find_attribute_by_id...p_id.class_type = %d, p_id.value = %d", p_id.get_class_type(), p_id.get_entire_value() ) );

Attribute * ptr = 0;

if ( p_id.get_class_type() != ATTRIBUTE_TYPE )
{
	LOG_ERROR( ( L_log_string,
		"AL_Generic_finds::find_attribute_by_id()...Bad class type! class_type = %d, id = %d", p_id.get_class_type(), p_id.get_entire_value() ));
}
else
{
	t_boolean found = FALSE;
	D_subsys * ss_ptr;

	FIRST_ELEMENT( ss_ptr,
				   D_subsys,
				   p_domain_ptr->get_current_dd_srm_scm_sam_ptr()->
					get_dd_subsystem_coll_ptr(),
				   c1 );

	while ( ! found && ss_ptr )
	{
		ptr = ss_ptr->get_im_ocm_oam_ptr()->find_attribute_by_id( p_id );
		if ( ptr )
		{
			found = TRUE;
		}
		else
		{
			NEXT_ELEMENT( ss_ptr, c1 );
		}
	}
}

LOG_TRACE( L_AL, L_HI_FUNCTION_END, ( L_log_string,
	"End AL_Generic_finds::find_attribute_by_id...ptr = 0x%x", ptr ) );

return( ptr );

}


Relationship *
AL_Generic_finds::find_relationship_by_id( const Domain * p_domain_ptr,
	const Id & p_id )
{

LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Generic_finds::find_relationship_by_id...p_id.class_type = %d, p_id.value = %d", p_id.get_class_type(), p_id.get_entire_value() ) );

Relationship * ptr = 0;

if ( p_id.get_class_type() != RELATIONSHIP_TYPE )
{
	LOG_ERROR( ( L_log_string,
		"AL_Generic_finds::find_relationship_by_id()...Bad class type! class_type = %d, id = %d", p_id.get_class_type(), p_id.get_entire_value() ));
}
else
{
	t_boolean found = FALSE;
	D_subsys * ss_ptr;

	FIRST_ELEMENT( ss_ptr,
				   D_subsys,
				   p_domain_ptr->get_current_dd_srm_scm_sam_ptr()->
					get_dd_subsystem_coll_ptr(),
				   c1 );

	while ( ! found && ss_ptr )
	{
		ptr = ss_ptr->get_im_ocm_oam_ptr()->find_relationship_by_id( p_id );
		if ( ptr )
		{
			found = TRUE;
		}
		else
		{
			NEXT_ELEMENT( ss_ptr, c1 );
		}
	}
}

LOG_TRACE( L_AL, L_HI_FUNCTION_END, ( L_log_string,
	"End AL_Generic_finds::find_relationship_by_id...ptr = 0x%x", ptr ) );

return( ptr );

}


D_sm_event *
AL_Generic_finds::find_sm_event_by_id( const Domain * p_domain_ptr,
	const Id & p_id )
{

LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Generic_finds::find_sm_event_by_id...p_id.class_type = %d, p_id.value = %d", p_id.get_class_type(), p_id.get_entire_value() ) );

D_sm_event * sm_event_ptr = 0;

if ( p_id.get_class_type() != EVENT_TYPE )
{
	LOG_ERROR( ( L_log_string,
		"AL_Generic_finds::find_sm_event_by_id()...Bad class type! class_type = %d, id = %d", p_id.get_class_type(), p_id.get_entire_value() ) );
}
else
{
	D_subsys * ss_ptr = 0;
	Object * object_ptr = 0;
	t_boolean sm_found = FALSE;

	FIRST_ELEMENT( ss_ptr,
				   D_subsys,
				   p_domain_ptr->get_current_dd_srm_scm_sam_ptr()->
				   get_dd_subsystem_coll_ptr(),
				   c1 );

	while ( ! sm_found && ss_ptr )
	{
		FIRST_ELEMENT( object_ptr,
					   Object,
					   ss_ptr->get_im_ocm_oam_ptr()->get_object_coll_ptr(),
					   c2 );

		while ( ! sm_found && object_ptr )
		{
			// Remember we must look in both instance and assigner state
			// models (if they exist).

			if (object_ptr->get_instance_sm_spt_pm_id ().get_config_id ()
				== p_id.get_config_id ())
			{
				sm_found = TRUE; 
				D_sm_spt_pm* sm_ptr
					= object_ptr->get_instance_sm_spt_pm_ptr();
				if ( sm_ptr )
				{
					sm_event_ptr = sm_ptr->find_sm_event_by_id( p_id );
				}
			}
			else if (object_ptr->get_assigner_sm_spt_pm_id ().get_config_id ()
				== p_id.get_config_id ())
			{
				sm_found = TRUE; 
				D_sm_spt_pm* sm_ptr
					= object_ptr->get_assigner_sm_spt_pm_ptr();
				if ( sm_ptr )
				{
					sm_event_ptr = sm_ptr->find_sm_event_by_id( p_id );
				}
			}
			else
			{
				NEXT_ELEMENT( object_ptr, c2 );
			}
		}

		NEXT_ELEMENT( ss_ptr, c1 );
	}
}

LOG_TRACE( L_AL, L_HI_FUNCTION_END, ( L_log_string,
	"End AL_Generic_finds::find_sm_event_by_id...sm_event_ptr = 0x%x",
	sm_event_ptr ) );

return( sm_event_ptr );

}


D_sm_event_data_item *
AL_Generic_finds::find_sm_event_data_item_by_id( const Domain * p_domain_ptr,
	const Id & p_id )
{

LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Generic_finds::find_sm_event_data_item_by_id...p_id.class_type = %d, p_id.value = %d", p_id.get_class_type(), p_id.get_entire_value() ) );

D_sm_event_data_item * ptr = 0;

if ( p_id.get_class_type() != EVENT_DATA_ITEM_TYPE )
{
	LOG_ERROR( ( L_log_string,
		"AL_Generic_finds::find_sm_event_data_item_by_id()...Bad class type! class_type = %d, id = %d", p_id.get_class_type(), p_id.get_entire_value() ) );
}
else
{
	D_subsys * ss_ptr = 0;
	Object * object_ptr = 0;
	t_boolean sm_found = FALSE;

	FIRST_ELEMENT( ss_ptr,
				   D_subsys,
				   p_domain_ptr->get_current_dd_srm_scm_sam_ptr()->
				   get_dd_subsystem_coll_ptr(),
				   c1 );

	while ( ! sm_found && ss_ptr )
	{
		FIRST_ELEMENT( object_ptr,
					   Object,
					   ss_ptr->get_im_ocm_oam_ptr()->get_object_coll_ptr(),
					   c2 );

		while ( ! sm_found && object_ptr )
		{
			// Remember we must look in both instance and assigner state
			// models (if they exist).

			if (object_ptr->get_instance_sm_spt_pm_id ().get_config_id ()
				== p_id.get_config_id ())
			{
				sm_found = TRUE; 
				D_sm_spt_pm* sm_ptr
					= object_ptr->get_instance_sm_spt_pm_ptr();
				if ( sm_ptr )
				{
					ptr = sm_ptr->find_sm_event_data_item_by_id( p_id );
				}
			}
			else if (object_ptr->get_assigner_sm_spt_pm_id ().get_config_id ()
				== p_id.get_config_id ())
			{
				sm_found = TRUE; 
				D_sm_spt_pm* sm_ptr
					= object_ptr->get_assigner_sm_spt_pm_ptr();
				if ( sm_ptr )
				{
					ptr = sm_ptr->find_sm_event_data_item_by_id( p_id );
				}
			}
			else
			{
				NEXT_ELEMENT( object_ptr, c2 );
			}
		}

		NEXT_ELEMENT( ss_ptr, c1 );
	}
}

LOG_TRACE( L_AL, L_HI_FUNCTION_END, ( L_log_string,
	"End AL_Generic_finds::find_sm_event_data_item_by_id...ptr = 0x%x", ptr ) );

return( ptr );

}


Object_in_relationship *
AL_Generic_finds::find_object_in_relationship_by_id(
	const Domain * p_domain_ptr, const Id & p_id )
{

LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Generic_finds::find_object_in_relationship_by_id...p_id.class_type = %d, p_id.value = %d", p_id.get_class_type(), p_id.get_entire_value() ) );

if ( p_id.get_class_type() != OBJ_IN_REL_TYPE )
{
	LOG_ERROR( ( L_log_string,
		"AL_Generic_finds::find_object_in_relationship_by_id()...Bad class type! class_type = %d, id = %d", p_id.get_class_type(), p_id.get_entire_value() ) );

	return( 0 );
}

D_subsys * ss_ptr = 0;
Object * object_ptr = 0;
Object_in_relationship * oir_ptr = 0;

FIRST_ELEMENT( ss_ptr,
			   D_subsys,
			   p_domain_ptr->get_current_dd_srm_scm_sam_ptr()->get_dd_subsystem_coll_ptr(),
			   c1 );

while ( ! oir_ptr && ss_ptr )
{
	FIRST_ELEMENT( object_ptr,
				   Object,
				   ss_ptr->get_im_ocm_oam_ptr()->get_object_coll_ptr(),
				   c2 );

	while ( ! oir_ptr && object_ptr )
	{
		oir_ptr = object_ptr->find_object_in_relationship( p_id );
		if ( ! oir_ptr )
		{
			NEXT_ELEMENT( object_ptr, c2 );
		}
	}

	NEXT_ELEMENT( ss_ptr, c1 );
}

LOG_TRACE( L_AL, L_HI_FUNCTION_END, ( L_log_string,
	"End AL_Generic_finds::find_object_in_relationship_by_id()...oir_ptr = 0x%x",
	oir_ptr ) );

return( oir_ptr );

}


D_transformer *
AL_Generic_finds::find_transformer_by_id( const Domain * p_domain_ptr,
	const Id & p_id )
{

LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Generic_finds::find_transformer_by_id...p_id.class_type = %d, p_id.value = %d", p_id.get_class_type(), p_id.get_entire_value() ) );

if ( p_id.get_class_type() != TRANSFORMER_TYPE )
{
	LOG_ERROR( ( L_log_string,
		"AL_Generic_finds::find_transformer_by_id()...Bad class type! class_type = %d, id = %d", p_id.get_class_type(), p_id.get_entire_value() ) );

	return( 0 );
}

D_subsys * ss_ptr = 0;
Object * object_ptr = 0;
D_transformer * trans_ptr = 0;

FIRST_ELEMENT( ss_ptr,
			   D_subsys,
			   p_domain_ptr->get_current_dd_srm_scm_sam_ptr()->get_dd_subsystem_coll_ptr(),
			   c1 );

while ( ! trans_ptr && ss_ptr )
{
	FIRST_ELEMENT( object_ptr,
				   Object,
				   ss_ptr->get_im_ocm_oam_ptr()->get_object_coll_ptr(),
				   c2 );

	while ( ! trans_ptr && object_ptr )
	{
		trans_ptr = object_ptr->find_transformer_by_id( p_id );
		if ( ! trans_ptr )
		{
			NEXT_ELEMENT( object_ptr, c2 );
		}
	}

	NEXT_ELEMENT( ss_ptr, c1 );
}

LOG_TRACE( L_AL, L_HI_FUNCTION_END, ( L_log_string,
	"End AL_Generic_finds::find_transformer_by_id()...trans_ptr = 0x%x",
	trans_ptr ) );

return( trans_ptr );

}


D_transformer *
AL_Generic_finds::find_transformer_by_name( const Domain * p_domain_ptr,
	const vchar * p_name )
{

LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Generic_finds::find_transformer_by_name...p_name = %s",
	p_name ) );

D_subsys * ss_ptr = 0;
Object * object_ptr = 0;
D_transformer * trans_ptr = 0;

FIRST_ELEMENT( ss_ptr,
			   D_subsys,
			   p_domain_ptr->get_current_dd_srm_scm_sam_ptr()->get_dd_subsystem_coll_ptr(),
			   c1 );

while ( ! trans_ptr && ss_ptr )
{
	FIRST_ELEMENT( object_ptr,
				   Object,
				   ss_ptr->get_im_ocm_oam_ptr()->get_object_coll_ptr(),
				   c2 );

	while ( ! trans_ptr && object_ptr )
	{
		trans_ptr = object_ptr->find_transformer_by_name( p_name );
		if ( ! trans_ptr )
		{
			NEXT_ELEMENT( object_ptr, c2 );
		}
	}

	NEXT_ELEMENT( ss_ptr, c1 );
}

LOG_TRACE( L_AL, L_HI_FUNCTION_END, ( L_log_string,
	"End AL_Generic_finds::find_transformer_by_name()...trans_ptr = 0x%x",
	trans_ptr ) );

return( trans_ptr );

}


D_bridge *
AL_Generic_finds::find_bridge_by_id( const Domain * p_domain_ptr,
	const Id & p_id )
{

LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Generic_finds::find_bridge_by_id...p_id.class_type = %d, p_id.value = %d", p_id.get_class_type(), p_id.get_entire_value() ) );

if ( p_id.get_class_type() != BRIDGE_TYPE )
{
	LOG_ERROR( ( L_log_string,
		"AL_Generic_finds::find_bridge_by_id()...Bad class type! class_type = %d, id = %d", p_id.get_class_type(), p_id.get_entire_value() ) );

	return( 0 );
}

D_external_entity * ee_ptr = 0;
D_bridge * bridge_ptr = 0;

FIRST_ELEMENT( ee_ptr,
			   D_external_entity,
			   p_domain_ptr->get_current_dd_srm_scm_sam_ptr()->
				  get_external_entity_coll_ptr(),
			   c1 );

while ( ! bridge_ptr && ee_ptr )
{
	bridge_ptr = ee_ptr->find_bridge_by_id( p_id );
	NEXT_ELEMENT( ee_ptr, c1 );
}

LOG_TRACE( L_AL, L_HI_FUNCTION_END, ( L_log_string,
	"End AL_Generic_finds::find_bridge_by_id()...bridge_ptr = 0x%x",
	bridge_ptr ) );

return( bridge_ptr );

}


D_bridge *
AL_Generic_finds::find_bridge_by_name( const Domain * p_domain_ptr,
	const vchar * p_name )
{

LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Generic_finds::find_bridge_by_name...p_name = %s",
	p_name ));

D_external_entity * ee_ptr = 0;
D_bridge * bridge_ptr = 0;

FIRST_ELEMENT( ee_ptr,
			   D_external_entity,
			   p_domain_ptr->get_current_dd_srm_scm_sam_ptr()->
				  get_external_entity_coll_ptr(),
			   c1 );

while ( ! bridge_ptr && ee_ptr )
{
	bridge_ptr = ee_ptr->find_bridge_by_name( p_name );
	NEXT_ELEMENT( ee_ptr, c1 );
}

LOG_TRACE( L_AL, L_HI_FUNCTION_END, ( L_log_string,
	"End AL_Generic_finds::find_bridge_by_name()...bridge_ptr = 0x%x",
	bridge_ptr ) );

return( bridge_ptr );

}

D_synchronous_service *
AL_Generic_finds::find_synch_service_by_id( const Domain * p_domain_ptr,
	const Id & p_id )
{

LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Generic_finds::find_synchronous_service_by_id...p_id.class_type = %d, p_id.value = %d", p_id.get_class_type(), p_id.get_entire_value() ) );

if ( p_id.get_class_type() != SYNCH_SERVICE_TYPE )
  {
	LOG_ERROR( ( L_log_string,
		"AL_Generic_finds::find_synchronous_service_by_id()...Bad class type! class_type = %d, id = %d", p_id.get_class_type(), p_id.get_entire_value() ) );

	return( 0 );
  }

D_synchronous_service * ss_ptr = p_domain_ptr->
  get_current_dd_srm_scm_sam_ptr()->
  find_synch_service_by_id(p_id);

LOG_TRACE( L_AL, L_HI_FUNCTION_END, ( L_log_string,
	"End AL_Generic_finds::find_synch_service_by_id()...ss_ptr = 0x%x",
	ss_ptr ) );

return( ss_ptr );

}


D_transformer_parm *
AL_Generic_finds::find_transformer_parm_by_id( const Domain * p_domain_ptr,
	const Id & p_id )
{

LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Generic_finds::find_transformer_parm_by_id...p_id.class_type = %d, p_id.value = %d", p_id.get_class_type(), p_id.get_entire_value() ) );

if ( p_id.get_class_type() != TRANSFORMER_PARM_TYPE )
{
	LOG_ERROR( ( L_log_string,
		"AL_Generic_finds::find_transformer_parm_by_id()...Bad class type! class_type = %d, id = %d", p_id.get_class_type(), p_id.get_entire_value() ) );

	return( 0 );
}

D_subsys * ss_ptr = 0;
Object * object_ptr = 0;
D_transformer * trans_ptr = 0;
D_transformer_parm * parm_ptr = 0;

FIRST_ELEMENT( ss_ptr,
			   D_subsys,
			   p_domain_ptr->get_current_dd_srm_scm_sam_ptr()->get_dd_subsystem_coll_ptr(),
			   c1 );

while ( ! parm_ptr && ss_ptr )
{
	FIRST_ELEMENT( object_ptr,
				   Object,
				   ss_ptr->get_im_ocm_oam_ptr()->get_object_coll_ptr(),
				   c2 );

	while ( ! parm_ptr && object_ptr )
	{
		FIRST_ELEMENT( trans_ptr,
					   D_transformer,
					   object_ptr->get_transformer_coll_ptr(),
					   c3 );

		while ( ! parm_ptr && trans_ptr )
		{
			parm_ptr = trans_ptr->find_parameter_by_id( p_id );
			if ( ! parm_ptr )
			{
				NEXT_ELEMENT( trans_ptr, c3 );
			}
		}

		NEXT_ELEMENT( object_ptr, c2 );
	}

	NEXT_ELEMENT( ss_ptr, c1 );
}

LOG_TRACE( L_AL, L_HI_FUNCTION_END, ( L_log_string,
	"End AL_Generic_finds::find_transformer_parm_by_id()...parm_ptr = 0x%x",
	parm_ptr ) );

return( parm_ptr );

}


D_transformer_parm *
AL_Generic_finds::find_transformer_parm_by_name( const Domain * p_domain_ptr,
	const vchar * p_name )
{

LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Generic_finds::find_transformer_parm_by_name...p_name = %s",
	p_name) );

D_subsys * ss_ptr = 0;
Object * object_ptr = 0;
D_transformer * trans_ptr = 0;
D_transformer_parm * parm_ptr = 0;

FIRST_ELEMENT( ss_ptr,
			   D_subsys,
			   p_domain_ptr->get_current_dd_srm_scm_sam_ptr()->get_dd_subsystem_coll_ptr(),
			   c1 );

while ( ! parm_ptr && ss_ptr )
{
	FIRST_ELEMENT( object_ptr,
				   Object,
				   ss_ptr->get_im_ocm_oam_ptr()->get_object_coll_ptr(),
				   c2 );

	while ( ! parm_ptr && object_ptr )
	{
		FIRST_ELEMENT( trans_ptr,
					   D_transformer,
					   object_ptr->get_transformer_coll_ptr(),
					   c3 );

		while ( ! parm_ptr && trans_ptr )
		{
			parm_ptr = trans_ptr->find_parameter_by_name( p_name );
			if ( ! parm_ptr )
			{
				NEXT_ELEMENT( trans_ptr, c3 );
			}
		}

		NEXT_ELEMENT( object_ptr, c2 );
	}

	NEXT_ELEMENT( ss_ptr, c1 );
}

LOG_TRACE( L_AL, L_HI_FUNCTION_END, ( L_log_string,
	"End AL_Generic_finds::find_transformer_parm_by_name()...parm_ptr = 0x%x",
	parm_ptr ) );

return( parm_ptr );

}


D_bridge_parm *
AL_Generic_finds::find_bridge_parm_by_id( const Domain * p_domain_ptr,
	const Id & p_id )
{

LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Generic_finds::find_bridge_parm_by_id...p_id.class_type = %d, p_id.value = %d", p_id.get_class_type(), p_id.get_entire_value() ) );

if ( p_id.get_class_type() != BRIDGE_PARM_TYPE )
{
	LOG_ERROR( ( L_log_string,
		"AL_Generic_finds::find_bridge_parm_by_id()...Bad class type! class_type = %d, id = %d", p_id.get_class_type(), p_id.get_entire_value() ) );

	return( 0 );
}

D_external_entity * ee_ptr = 0;
D_bridge * bridge_ptr = 0;
D_bridge_parm * parm_ptr = 0;

FIRST_ELEMENT( ee_ptr,
			   D_external_entity,
			   p_domain_ptr->get_current_dd_srm_scm_sam_ptr()->
				  get_external_entity_coll_ptr(),
			   c1 );

while ( ! parm_ptr && ee_ptr )
{
	FIRST_ELEMENT( bridge_ptr,
				   D_bridge,
				   ee_ptr->get_bridge_coll_ptr(),
				   c2 );

	while ( ! parm_ptr && bridge_ptr )
	{
		parm_ptr = bridge_ptr->find_parameter_by_id( p_id );
		if ( ! parm_ptr )
		{
			NEXT_ELEMENT( bridge_ptr, c2 );
		}
	}

	NEXT_ELEMENT( ee_ptr, c1 );
}

LOG_TRACE( L_AL, L_HI_FUNCTION_END, ( L_log_string,
	"End AL_Generic_finds::find_bridge_parm_by_id()...parm_ptr = 0x%x",
	parm_ptr ) );

return( parm_ptr );

}


D_synchronous_service_parm *
AL_Generic_finds::find_synch_service_parm_by_id( const Domain * p_domain_ptr,
	const Id & p_id )
{

LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Generic_finds::find_synch_service_parm_by_id...p_id.class_type = %d, p_id.value = %d", p_id.get_class_type(), p_id.get_entire_value() ) );

if ( p_id.get_class_type() != SYNCH_SERVICE_PARM_TYPE )
{
	LOG_ERROR( ( L_log_string,
		"AL_Generic_finds::find_synch_service_parm_by_id()...Bad class type! class_type = %d, id = %d", p_id.get_class_type(), p_id.get_entire_value() ) );

	return( 0 );
}

D_synchronous_service * ss_ptr = 0;
D_synchronous_service_parm * parm_ptr = 0;

FIRST_ELEMENT( ss_ptr,
			   D_synchronous_service,
			   p_domain_ptr->get_current_dd_srm_scm_sam_ptr()->
				  get_synch_service_coll_ptr(),
			   c1 );

while ( ! parm_ptr && ss_ptr )
  {
    parm_ptr = ss_ptr->find_parameter_by_id( p_id );
    if ( ! parm_ptr )
      {
        NEXT_ELEMENT( ss_ptr, c1 );
      }
  }

LOG_TRACE( L_AL, L_HI_FUNCTION_END, ( L_log_string,
	"End AL_Generic_finds::find_synch_service_parm_by_id()...parm_ptr = 0x%x",
	parm_ptr ) );

return( parm_ptr );

}


D_bridge_parm *
AL_Generic_finds::find_bridge_parm_by_name( const Domain * p_domain_ptr,
	const vchar * p_name )
{

LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Generic_finds::find_bridge_parm_by_name...p_name = %s",
	p_name ) );

D_external_entity * ee_ptr = 0;
D_bridge * bridge_ptr = 0;
D_bridge_parm * parm_ptr = 0;

FIRST_ELEMENT( ee_ptr,
			   D_external_entity,
			   p_domain_ptr->get_current_dd_srm_scm_sam_ptr()->
				  get_external_entity_coll_ptr(),
			   c1 );

while ( ! parm_ptr && ee_ptr )
{
	FIRST_ELEMENT( bridge_ptr,
				   D_bridge,
				   ee_ptr->get_bridge_coll_ptr(),
				   c2 );

	while ( ! parm_ptr && bridge_ptr )
	{
		parm_ptr = bridge_ptr->find_parameter_by_name( p_name );
		if ( ! parm_ptr )
		{
			NEXT_ELEMENT( bridge_ptr, c2 );
		}
	}

	NEXT_ELEMENT( ee_ptr, c1 );
}

LOG_TRACE( L_AL, L_HI_FUNCTION_END, ( L_log_string,
	"End AL_Generic_finds::find_bridge_parm_by_name()...parm_ptr = 0x%x",
	parm_ptr ) );

return( parm_ptr );

}


D_data_type *
AL_Generic_finds::find_data_type_by_id( const Domain * p_domain_ptr,
	const Id & p_id )
{

LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Generic_finds::find_data_type_by_id...p_id.class_type = %d, p_id.value = %d", p_id.get_class_type(), p_id.get_entire_value() ) );

D_data_type * data_type_ptr;

if ( p_id.get_class_type() != DATA_TYPE_TYPE )
{
	data_type_ptr = p_domain_ptr->get_current_dd_srm_scm_sam_ptr()->
		find_data_type_by_name( "integer" );
}
else
{
	data_type_ptr = p_domain_ptr->get_current_dd_srm_scm_sam_ptr()->
		find_data_type_by_id( p_id );
	
	if ( data_type_ptr == 0 )
	{
		data_type_ptr = p_domain_ptr->get_current_dd_srm_scm_sam_ptr()->
			find_data_type_by_name( "integer" );
	}
}

LOG_TRACE( L_AL, L_HI_FUNCTION_END, ( L_log_string,
	"End AL_Generic_finds::find_data_type_by_id()...data_type_ptr = 0x%x",
	data_type_ptr ) );

return( data_type_ptr );

}


D_core_data_type *
AL_Generic_finds::find_core_data_type_by_id( const Domain * p_domain_ptr,
	const Id & p_id )
{

LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Generic_finds::find_core_data_type_by_id...p_id.class_type = %d, p_id.value = %d",
	p_id.get_class_type(), p_id.get_entire_value() ) );
	
D_core_data_type * core_data_type_ptr = 0;

D_data_type * data_type_ptr = AL_Generic_finds::find_data_type_by_id(
	p_domain_ptr, p_id );

if ( data_type_ptr )
{
	core_data_type_ptr = data_type_ptr->get_core_data_type_ptr();
}

if ( core_data_type_ptr == 0 )
{
	core_data_type_ptr = p_domain_ptr->get_current_dd_srm_scm_sam_ptr()->
		find_data_type_by_type( INTEGER_DATATYPE );
}

LOG_TRACE( L_AL, L_HI_FUNCTION_END, ( L_log_string,
	"End AL_Generic_finds::find_core_data_type_by_id()...core_data_type_ptr = 0x%x",
	core_data_type_ptr ) );

return( core_data_type_ptr );

}

D_enumerator *
AL_Generic_finds::find_enumerator_by_id( const Domain * p_domain_ptr,
	const Id & p_id )
{

LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Generic_finds::find_enumerator_by_id...p_id.class_type = %d, p_id.value = %d", p_id.get_class_type(), p_id.get_entire_value() ) );

D_enumerator * enum_ptr = 0;

if ( p_id.get_class_type() == ENUMERATOR_TYPE )
{
	enum_ptr = p_domain_ptr->get_current_dd_srm_scm_sam_ptr()->
		find_enumerator_by_id( p_id );
}

LOG_TRACE( L_AL, L_HI_FUNCTION_END, ( L_log_string,
	"End AL_Generic_finds::find_enumerator_by_id()...enum_ptr = 0x%x",
	enum_ptr ) );

return( enum_ptr );

}

