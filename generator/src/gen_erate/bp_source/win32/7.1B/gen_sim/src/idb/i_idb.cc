/*========================================================================
 *
 * File:      $RCSfile: i_idb.cc,v $
 * Version:   $Revision: 1.11 $
 * Modified:  $Date: 2013/01/10 23:41:36 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <u_trace.hh>
#include <u_util.hh>
#include <u_tspec.hh>
#include <u_string.hh>
#include <u_typdef.hh>


#include <i_idb.hh>
#include <u_string.hh>
#include <i_c_rop.hh>


static char misc_err_msg [2048];




t_boolean
I_instance_db::domain_code_ok (mc_dbms_database* p_db_ptr, int p_entered_domain_code,
    int &p_chosen_domain_code, String &p_err_msg)
{

t_boolean rc;

char * domain_code_array;

mc_dbms_database_root * root_ptr =
	p_db_ptr->find_root( "domain_codes" );

if ( root_ptr == 0 )
{
	// Go ahead and create domain code array and set them all to
	// DOMAIN_CODE_AVAILABLE.

	domain_code_array = new( p_db_ptr, mc_dbms_typespec::get_char(),
		NUM_DOMAIN_CODES ) char[ NUM_DOMAIN_CODES ];

	for ( int i = 0; i < NUM_DOMAIN_CODES; i++ )
	{
		domain_code_array[ i ] = DOMAIN_CODE_AVAILABLE;
	}

	root_ptr = p_db_ptr->create_root( "domain_codes" );
	root_ptr->set_value( domain_code_array );
}
else
{
	domain_code_array = ( char * ) root_ptr->get_value();
}

if ( p_entered_domain_code == -1 )
{
	// Look for first available slot for a "default" domain code (user did not
	// specify one).

	for ( int i = 0;
		  ( i < NUM_DOMAIN_CODES )
				 &&
		  ( domain_code_array[ i ] != DOMAIN_CODE_AVAILABLE );
		  i++ );

	if ( i >= NUM_DOMAIN_CODES )
	{
		rc = FALSE;
		p_err_msg = "ERROR: All domain codes are already used...please re-import into another generation database or reuse existing domain code if imported data is for that domain";
	}
	else
	{
		// This domain code avaible. Take it! Fill-out error message to report
		// default domain code chosen (not really an error, though).
		domain_code_array[ i ] = DOMAIN_CODE_USED;
        p_chosen_domain_code = i;
		rc = TRUE;
		char buf[ 32 ];
		sprintf( buf, "%d", i );
		p_err_msg = "NOTE: ";
		p_err_msg = p_err_msg + "Domain code " + buf + " allocated for this import.";
	}
}
else
{
	// User entered domain code. Make sure legit and not already being used.

	if ( ( p_entered_domain_code < 0 ) || ( p_entered_domain_code > 15 ) )
	{
		rc = FALSE;
		p_err_msg = "ERROR: Entered domain code is not between 0-15 inclusive.";
		return( rc );
	}

	if (domain_code_array[ p_entered_domain_code ] != DOMAIN_CODE_AVAILABLE)
	{
		domain_code_array[ p_entered_domain_code ] = DOMAIN_CODE_USED;
		rc = TRUE;
		p_err_msg = "NOTE: The domain code you have entered has already been used/allocated, but will allow this import to proceed normally.";
	}
	else
	{
		// This domain code avaible. Take it!
		domain_code_array[ p_entered_domain_code ] = DOMAIN_CODE_USED;
		rc = TRUE;
		char buf[ 32 ];
		sprintf( buf, "%d", p_entered_domain_code );
		p_err_msg = "NOTE: ";
		p_err_msg = p_err_msg + "Domain code " + buf + " allocated for this import.";
	}
}

return( rc );

}





void
I_instance_db::set_sim_domain_code
    (mc_dbms_database* p_db_ptr, t_ulong p_domain_code)

{
    mc_dbms_database_root* root_ptr = p_db_ptr->find_root ("Sim_Domain_Code");

    if (root_ptr)
    {
	int* domain_code_ptr = (int*) root_ptr->get_value ();
	*domain_code_ptr = (int) p_domain_code;
    }
    else
    {
	int* domain_code_ptr
	    = new (p_db_ptr, int_type) int ((int) p_domain_code);
	p_db_ptr->create_root ("Sim_Domain_Code")->set_value (domain_code_ptr);
    }
}





t_ulong
I_instance_db::get_sim_domain_code (mc_dbms_database* p_db_ptr)

{
    mc_dbms_database_root* root_ptr = p_db_ptr->find_root ("Sim_Domain_Code");

    if (root_ptr)
    {
	int* domain_code_ptr = (int*) root_ptr->get_value ();
	return ((t_ulong) *domain_code_ptr);
    }
    else
    {
	return ((t_ulong) 0);
    }
}
