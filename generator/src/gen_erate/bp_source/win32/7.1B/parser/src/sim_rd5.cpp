/*========================================================================
 *
 * File:      $RCSfile: sim_rd5.cpp,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:22 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include "SIM_SOR.h"

#include <stdio.h>
#include <fstream.h>

#include <gs_stack.hh>
#include <gs_ui.hh>

#include <i_clock.hh>
#include <i_einst.hh>
#include <i_var.hh>

#include <u_env.hh>
#include <u_cmd.hh>
#include <u_trace.hh>
#include <u_file.hh>

void SIM_SOR::interpret__time__current_date
    (GS_var_si& p_rvalue_var_si)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::interpret__time__current_date ()."));


    I_var* var_ptr
	= I_var::create_in_transient (MAPPING_INST_DATATYPE, DATE_USERDATATYPE);
    if (var_ptr)
    {
	I_date_var* date_var_ptr = var_ptr->get_date_var_ptr ();
	if (date_var_ptr)
	{
	    date_var_ptr->set_to_current_date ();
	    p_rvalue_var_si.replace_var (date_var_ptr);
	}
    }


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End  SIM_SOR::interpret__time__current_date ()."));
}




void SIM_SOR::interpret__time__create_date
  ( int num_params, Description p_param_name[], GS_var_si p_param_value[],    
    GS_var_si& p_rvalue_var_si)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::interpret__time__create_date ()"));

    t_boolean second_specified = FALSE;
    int second = 0;
    t_boolean minute_specified = FALSE;
    int minute = 0;
    t_boolean hour_specified = FALSE;
    int hour = 0;
    t_boolean day_specified = FALSE;
    int day = 0;
    t_boolean month_specified = FALSE;
    int month = 0;
    t_boolean year_specified = FALSE;
    int year = 0;


    int param_num = 0;
    while ( (param_num < num_params) &&
            (!second_specified || !minute_specified || ! hour_specified ||
            !day_specified || !month_specified || !year_specified) )
    {
	if (p_param_value[param_num].get_void_var_ptr ())
	{
		Description err_msg ("Value of '");
		err_msg += p_param_name[param_num];
		err_msg += "' not recoginzed.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #1:  SIM_SOR::interpret__time__create_date ()."));
	    return;
	}


	if (p_param_name[param_num] == "param.year")
	{
	    if (! p_param_value[param_num].get_integer_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'year' expects value of type 'integer'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #2:  SIM_SOR::interpret__time__create_date ()."));
		return;
	    }
	    year_specified = TRUE;
	    year = (int) p_param_value[param_num].get_integer_var_ptr ()->get_value ();
	}
	else if (p_param_name[param_num] == "param.month")
	{
	    if (! p_param_value[param_num].get_integer_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'month' expects value of type 'integer'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #3:  SIM_SOR::interpret__time__create_date ()."));
		return;
	    }
	    month_specified = TRUE;
	    month = (int) p_param_value[param_num].get_integer_var_ptr ()->get_value ();
	}
	else if (p_param_name[param_num] == "param.day")
	{
	    if (! p_param_value[param_num].get_var_ptr ()->get_integer_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'day' expects value of type 'integer'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #4:  SIM_SOR::interpret__time__create_date ()."));
		return;
	    }
	    day_specified = TRUE;
	    day = (int) p_param_value[param_num].get_integer_var_ptr ()->get_value ();
	}
	else if (p_param_name[param_num] == "param.hour")
	{
	    if (! p_param_value[param_num].get_var_ptr ()->get_integer_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'hour' expects value of type 'integer'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #5:  SIM_SOR::interpret__time__create_date ()."));
		return;
	    }
	    hour_specified = TRUE;
	    hour = (int) p_param_value[param_num].get_integer_var_ptr ()->get_value ();
	}
	else if (p_param_name[param_num] == "param.minute")
	{
	    if (! p_param_value[param_num].get_var_ptr ()->get_integer_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'minute' expects value of type 'integer'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #6:  SIM_SOR::interpret__time__create_date ()."));
		return;
	    }
	    minute_specified = TRUE;
	    minute = (int) p_param_value[param_num].get_integer_var_ptr ()->get_value ();
	}
	else if (p_param_name[param_num] == "param.second")
	{
	    if (! p_param_value[param_num].get_var_ptr ()->get_integer_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'second' expects value of type 'integer'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #7:  SIM_SOR::interpret__time__create_date ()."));
		return;
	    }
	    second_specified = TRUE;
	    second = (int) p_param_value[param_num].get_integer_var_ptr ()->get_value ();
	}
	else
	{
		Description err_msg ("Unexpected parameter '");
		err_msg += p_param_name[param_num];
		err_msg += "'.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #8:  SIM_SOR::interpret__time__create_date ()."));
	    return;
	}
        param_num += 1;
    }


    if (! year_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'year'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #9:  SIM_SOR::interpret__time__create_date ()."));
	return;
    }


    if (! month_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'month'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #10:  SIM_SOR::interpret__time__create_date ()."));
	return;
    }


    if (! day_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'day'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #11:  SIM_SOR::interpret__time__create_date ()."));
	return;
    }


    if (! hour_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'hour'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #12:  SIM_SOR::interpret__time__create_date ()."));
	return;
    }


    if (! minute_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'minute'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #13:  SIM_SOR::interpret__time__create_date ()."));
	return;
    }


    if (! second_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'second'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #14:  SIM_SOR::interpret__time__create_date ()."));
	return;
    }


    if ((year < 1) || (year > 3000))
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Parameter 'year' expects value in range 1 to 3000"));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #15:  SIM_SOR::interpret__time__create_date ()."));
	return;
    }


    if ((month < 1) || (month > 12))
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Parameter 'month' expects value in range 1 to 12"));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #16:  SIM_SOR::interpret__time__create_date ()."));
	return;
    }


    if ((day < 1) || (day > 31))
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Parameter 'day' expects value in range 1 to 31"));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #17:  SIM_SOR::interpret__time__create_date ()."));
	return;
    }


    if ((hour < 0) || (hour > 59))
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Parameter 'hour' expects value in range 0 to 23"));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #18:  SIM_SOR::interpret__time__create_date ()."));
	return;
    }


    if ((minute < 0) || (minute > 59))
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Parameter 'minute' expects value in range 0 to 59"));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #19:  SIM_SOR::interpret__time__create_date ()."));
	return;
    }


    if ((second < 0) || (second > 59))
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Parameter 'second' expects value in range 0 to 59"));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #20:  SIM_SOR::interpret__time__create_date ()."));
	return;
    }


    I_var* var_ptr
	= I_var::create_in_transient (MAPPING_INST_DATATYPE, DATE_USERDATATYPE);
    I_date_var* date_var_ptr = var_ptr->get_date_var_ptr ();


    //  Make sure to set year and month before day since range check on day
    //    depends on year and month.
    //
    date_var_ptr->set_year (year);
    date_var_ptr->set_month (month);
    date_var_ptr->set_day (day);
    date_var_ptr->set_hour (hour);
    date_var_ptr->set_minute (minute);
    date_var_ptr->set_second (second);



    if (day != date_var_ptr->get_day ())
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Parameter 'day' expects day of month/year specified"));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #21:  SIM_SOR::interpret__time__create_date ()."));
	return;
    }


    p_rvalue_var_si.replace_var (var_ptr);


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #22:  SIM_SOR::interpret__time__create_date ()."));
}





void SIM_SOR::interpret__time__get_second
  ( int num_params, Description p_param_name[], GS_var_si p_param_value[],    
    GS_var_si& p_rvalue_var_si)
{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::interpret__time__get_second ()" ));


    t_boolean date_specified = FALSE;
    t_int second;

    int param_num = 0;
    while (param_num < num_params && !date_specified)
    {
	if (p_param_value[param_num].get_void_var_ptr ())
	{
		Description err_msg ("Value of '");
		err_msg += p_param_name[param_num];
		err_msg += "' not recoginzed.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #1:  SIM_SOR::interpret__time__get_second ()."));
	    return;
	}


	if (p_param_name[param_num] == "param.date")
	{
	    if (! p_param_value[param_num].get_date_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'date' expects value of type 'date'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #2:  SIM_SOR::interpret__time__get_second ()."));
		return;
	    }
	    if (! p_param_value[param_num].get_date_var_ptr ()->get_var_ptr ()->
		get_is_initialized ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'date' must be initialized"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #3:  SIM_SOR::interpret__time__get_second ()."));
		return;
	    }
	    date_specified = TRUE;
	    second = p_param_value[param_num].get_date_var_ptr ()->get_second ();
	}
	else
	{
		Description err_msg ("Unexpected parameter '");
		err_msg += p_param_name[param_num];
		err_msg += "'.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #4:  SIM_SOR::interpret__time__get_second ()."));
	    return;
	}
        param_num += 1;
    }


    if (! date_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'date'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #5:  SIM_SOR::interpret__time__get_second ()."));
	return;
    }


    p_rvalue_var_si.replace_var (new I_integer_var ((t_long) second));


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #6:  SIM_SOR::interpret__time__get_second ()."));
    return;
}





void SIM_SOR::interpret__time__get_minute
  ( int num_params, Description p_param_name[], GS_var_si p_param_value[],    
    GS_var_si& p_rvalue_var_si)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::interpret__time__get_minute ()." ));

    t_boolean date_specified = FALSE;
    t_int minute;


    int param_num = 0;
    while (param_num < num_params && !date_specified )
    {
	if (p_param_value[param_num].get_void_var_ptr ())
	{
		Description err_msg ("Value of '");
		err_msg += p_param_name[param_num];
		err_msg += "' not recoginzed.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #1:  SIM_SOR::interpret__time__get_minute ()."));
	    return;
	}


	if (p_param_name[param_num] == "param.date")
	{
	    if (! p_param_value[param_num].get_date_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'date' expects value of type 'date'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #2:  SIM_SOR::interpret__time__get_minute ()."));
		return;
	    }
	    if (! p_param_value[param_num].get_date_var_ptr ()->get_var_ptr ()->
		get_is_initialized ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'date' must be initialized"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #3:  SIM_SOR::interpret__time__get_minute ()."));
		return;
	    }
	    date_specified = TRUE;
	    minute = p_param_value[param_num].get_date_var_ptr ()->get_minute ();
	}
	else
	{
		Description err_msg ("Unexpected parameter '");
		err_msg += p_param_name[param_num];
		err_msg += "'.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #4:  SIM_SOR::interpret__time__get_minute ()."));
	    return;
	}
        param_num += 1;
    }


    if (! date_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'date'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #5:  SIM_SOR::interpret__time__get_minute ()."));
	return;
    }


    p_rvalue_var_si.replace_var (new I_integer_var ((t_long) minute));


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #6:  SIM_SOR::interpret__time__get_minute ()."));
    return;
}





void SIM_SOR::interpret__time__get_hour
  ( int num_params, Description p_param_name[], GS_var_si p_param_value[],    
    GS_var_si& p_rvalue_var_si)
{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::interpret__time__get_hour ()" ));


    t_boolean date_specified = FALSE;
    t_int hour;


    int param_num = 0;
    while (param_num < num_params && !date_specified )
    {
	if (p_param_value[param_num].get_void_var_ptr ())
	{
		Description err_msg ("Value of '");
		err_msg += p_param_name[param_num];
		err_msg += "' not recoginzed.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #1:  SIM_SOR::interpret__time__get_hour ()."));
	    return;
	}


	if (p_param_name[param_num] == "param.date")
	{
	    if (! p_param_value[param_num].get_date_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'date' expects value of type 'date'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #2:  SIM_SOR::interpret__time__get_hour ()."));
		return;
	    }
	    if (! p_param_value[param_num].get_date_var_ptr ()->get_var_ptr ()->
		get_is_initialized ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'date' must be initialized"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #3:  SIM_SOR::interpret__time__get_hour ()."));
		return;
	    }
	    date_specified = TRUE;
	    hour = p_param_value[param_num].get_date_var_ptr ()->get_hour ();
	}
	else
	{
		Description err_msg ("Unexpected parameter '");
		err_msg += p_param_name[param_num];
		err_msg += "'.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #4:  SIM_SOR::interpret__time__get_hour ()."));
	    return;
	}
        param_num += 1;
    }


    if (! date_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'date'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #5:  SIM_SOR::interpret__time__get_hour ()."));
	return;
    }


    p_rvalue_var_si.replace_var (new I_integer_var ((t_long) hour));


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #6:  SIM_SOR::interpret__time__get_hour ()."));
    return;
}





void
SIM_SOR::interpret__time__get_day
  ( int num_params, Description p_param_name[], GS_var_si p_param_value[],    
    GS_var_si& p_rvalue_var_si)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::interpret__time__get_day ()" ));


    t_boolean date_specified = FALSE;
    t_int day;


    int param_num = 0;
    while (param_num < num_params && !date_specified )
    {
	if (p_param_value[param_num].get_void_var_ptr ())
	{
		Description err_msg ("Value of '");
		err_msg += p_param_name[param_num];
		err_msg += "' not recoginzed.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #1:  SIM_SOR::interpret__time__get_day ()."));
	    return;
	}


	if (p_param_name[param_num] == "param.date")
	{
	    if (! p_param_value[param_num].get_date_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'date' expects value of type 'date'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #2:  SIM_SOR::interpret__time__get_day ()."));
		return;
	    }
	    if (! p_param_value[param_num].get_date_var_ptr ()->get_var_ptr ()->
		get_is_initialized ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'date' must be initialized"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #3:  SIM_SOR::interpret__time__get_day ()."));
		return;
	    }
	    date_specified = TRUE;
	    day = p_param_value[param_num].get_date_var_ptr ()->get_day ();
	}
	else
	{
		Description err_msg ("Unexpected parameter '");
		err_msg += p_param_name[param_num];
		err_msg += "'.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #4:  SIM_SOR::interpret__time__get_day ()."));
	    return;
	}
        param_num += 1;
    }


    if (! date_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'date'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #5:  SIM_SOR::interpret__time__get_day ()."));
	return;
    }


    p_rvalue_var_si.replace_var (new I_integer_var ((t_long) day));


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #6:  SIM_SOR::interpret__time__get_day ()."));
    return;
}





void SIM_SOR::interpret__time__get_month
  ( int num_params, Description p_param_name[], GS_var_si p_param_value[],    
    GS_var_si& p_rvalue_var_si)


{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::interpret__time__get_month ()" ));


    t_boolean date_specified = FALSE;
    t_int month;


    int param_num = 0;
    while (param_num < num_params && !date_specified )
    {
	if (p_param_value[param_num].get_void_var_ptr ())
	{
		Description err_msg ("Value of '");
		err_msg += p_param_name[param_num];
		err_msg += "' not recoginzed.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #1:  SIM_SOR::interpret__time__get_month ()."));
	    return;
	}


	if (p_param_name[param_num] == "param.date")
	{
	    if (! p_param_value[param_num].get_date_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'date' expects value of type 'date'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #2:  SIM_SOR::interpret__time__get_month ()."));
		return;
	    }
	    if (! p_param_value[param_num].get_date_var_ptr ()->get_var_ptr ()->
		get_is_initialized ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'date' must be initialized"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #3:  SIM_SOR::interpret__time__get_month ()."));
		return;
	    }
	    date_specified = TRUE;
	    month = p_param_value[param_num].get_date_var_ptr ()->get_month ();
	}
	else
	{
		Description err_msg ("Unexpected parameter '");
		err_msg += p_param_name[param_num];
		err_msg += "'.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #4:  SIM_SOR::interpret__time__get_month ()."));
	    return;
	}
        param_num += 1;
    }


    if (! date_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'date'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #5:  SIM_SOR::interpret__time__get_month ()."));
	return;
    }


    p_rvalue_var_si.replace_var (new I_integer_var ((t_long) month));


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #6:  SIM_SOR::interpret__time__get_month ()."));
    return;
}





void SIM_SOR::interpret__time__get_year
  ( int num_params, Description p_param_name[], GS_var_si p_param_value[],    
    GS_var_si& p_rvalue_var_si)


{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::interpret__time__get_year ()" ));


    t_boolean date_specified = FALSE;
    t_int year;


    int param_num = 0;
    while (param_num < num_params && !date_specified )
    {
	if (p_param_value[param_num].get_void_var_ptr ())
	{
		Description err_msg ("Value of '");
		err_msg += p_param_name[param_num];
		err_msg += "' not recoginzed.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #1:  SIM_SOR::interpret__time__get_year ()."));
	    return;
	}


	if (p_param_name[param_num] == "param.date")
	{
	    if (! p_param_value[param_num].get_date_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'date' expects value of type 'date'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #2:  SIM_SOR::interpret__time__get_year ()."));
		return;
	    }
	    if (! p_param_value[param_num].get_date_var_ptr ()->get_var_ptr ()->
		get_is_initialized ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'date' must be initialized"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #3:  SIM_SOR::interpret__time__get_year ()."));
		return;
	    }
	    date_specified = TRUE;
	    year = p_param_value[param_num].get_date_var_ptr ()->get_year ();
	}
	else
	{
		Description err_msg ("Unexpected parameter '");
		err_msg += p_param_name[param_num];
		err_msg += "'.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #4:  SIM_SOR::interpret__time__get_year ()."));
	    return;
	}
        param_num += 1;
    }


    if (! date_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'date'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #5:  SIM_SOR::interpret__time__get_year ()."));
	return;
    }


    p_rvalue_var_si.replace_var (new I_integer_var ((t_long) year));


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #6:  SIM_SOR::interpret__time__get_year ()."));
    return;
}





void SIM_SOR::interpret__time__current_clock
    (GS_var_si& p_rvalue_var_si)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::interpret__time__current_clock ()."));


    p_rvalue_var_si.replace_var
	(new I_timestamp_var (I_Clock::current_time ()));


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End  SIM_SOR::interpret__time__current_clock ()."));
}





void SIM_SOR::interpret__time__timer_start
  ( int num_params, Description p_param_name[], GS_var_si p_param_value[],    
    GS_var_si& p_rvalue_var_si)


{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::interpret__time__timer_start ()" ));


    t_boolean microseconds_specified = FALSE;
    t_long microseconds = 0;
    t_boolean einst_specified = FALSE;
    I_SM_Evt_Inst* einst_ptr = 0;


    int param_num = 0;
    while (param_num < num_params && (!microseconds_specified || !einst_specified) )
    {
	if (p_param_value[param_num].get_void_var_ptr ())
	{
		Description err_msg ("Value of '");
		err_msg += p_param_name[param_num];
		err_msg += "' not recoginzed.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #1:  SIM_SOR::interpret__time__timer_start ()."));
	    return;
	}

	if (p_param_name[param_num] == "param.microseconds")
	{
	    if (! p_param_value[param_num].get_integer_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'microseconds' expects value of type 'integer'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #2:  SIM_SOR::interpret__time__timer_start ()."));
		return;
	    }
	    microseconds_specified = TRUE;
	    microseconds = p_param_value[param_num].get_integer_var_ptr ()->get_value ();
	}
	else if (p_param_name[param_num] == "param.event_inst")
	{
	    if (! p_param_value[param_num].get_event_inst_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'event_inst' expects value of type 'inst<Event>'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #3:  SIM_SOR::interpret__time__timer_start ()."));
		return;
	    }
	    einst_specified = TRUE;
	    einst_ptr
		= p_param_value[param_num].get_event_inst_var_ptr ()->get_einst_ptr ();
	}
	else
	{
		Description err_msg ("Unexpected parameter '");
		err_msg += p_param_name[param_num];
		err_msg += "'.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #4:  SIM_SOR::interpret__time__timer_start ()."));
	    return;
	}
        param_num += 1;
    }


    if (! microseconds_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'microseconds'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #5:  SIM_SOR::interpret__time__timer_start ()."));
	return;
    }


    if (! einst_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'event_inst'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #6:  SIM_SOR::interpret__time__timer_start ()."));
	return;
    }


    if (! einst_ptr)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Parameter 'event_inst' is un-initialized."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #7:  SIM_SOR::interpret__time__timer_start ()."));
	return;
    }


    I_SM_Evt_Inst* new_einst_ptr
	= I_SM_Evt_Inst::copy__I_SM_Evt_Inst (einst_ptr);
    I_timestamp_var new_expiration_time (I_Clock::current_time ());
    new_expiration_time += microseconds;
    new_einst_ptr->set_expiration_time (new_expiration_time);

    I_timer_inst_ref_var* timer_inst_ref_var_ptr
	= new I_timer_inst_ref_var (new_einst_ptr->get_evt_inst_ID ());

    p_rvalue_var_si.replace_var (timer_inst_ref_var_ptr);


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #8:  SIM_SOR::interpret__time__timer_start ()."));
    return;
}




void SIM_SOR::interpret__time__timer_start_recurring
  ( int num_params, Description p_param_name[], GS_var_si p_param_value[],    
    GS_var_si& p_rvalue_var_si)


{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::interpret__time__timer_start_recurring ()" ));


    t_boolean microseconds_specified = FALSE;
    t_long microseconds = 0;
    t_boolean einst_specified = FALSE;
    I_SM_Evt_Inst* einst_ptr = 0;


    int param_num = 0;
    while (param_num < num_params && (!microseconds_specified || !einst_specified) )
    {
	if (p_param_value[param_num].get_void_var_ptr ())
	{
		Description err_msg ("Value of '");
		err_msg += p_param_name[param_num];
		err_msg += "' not recoginzed.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #1:  SIM_SOR::interpret__time__timer_start_recurring ()."));
	    return;
	}

	if (p_param_name[param_num] == "param.microseconds")
	{
	    if (! p_param_value[param_num].get_integer_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'microseconds' expects value of type 'integer'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #2:  SIM_SOR::interpret__time__timer_start_recurring ()."));
		return;
	    }
	    microseconds_specified = TRUE;
	    microseconds = p_param_value[param_num].get_integer_var_ptr ()->get_value ();
	}
	else if (p_param_name[param_num] == "param.event_inst")
	{
	    if (! p_param_value[param_num].get_event_inst_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'event_inst' expects value of type 'inst<Event>'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #3:  SIM_SOR::interpret__time__timer_start_recurring ()."));
		return;
	    }
	    einst_specified = TRUE;
	    einst_ptr
		= p_param_value[param_num].get_event_inst_var_ptr ()->get_einst_ptr ();
	}
	else
	{
		Description err_msg ("Unexpected parameter '");
		err_msg += p_param_name[param_num];
		err_msg += "'.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #4:  SIM_SOR::interpret__time__timer_start_recurring ()."));
	    return;
	}
        param_num += 1;
    }


    if (! microseconds_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'microseconds'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #5:  SIM_SOR::interpret__time__timer_start_recurring ()."));
	return;
    }


    if (! einst_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'event_inst'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #6:  SIM_SOR::interpret__time__timer_start_recurring ()."));
	return;
    }


    if (! einst_ptr)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Parameter 'event_inst' is un-initialized."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #7:  SIM_SOR::interpret__time__timer_start_recurring ()."));
	return;
    }


    I_SM_Evt_Inst* new_einst_ptr
	= I_SM_Evt_Inst::copy__I_SM_Evt_Inst (einst_ptr);
    I_timestamp_var new_expiration_time (I_Clock::current_time ());
    new_expiration_time += microseconds;
    new_einst_ptr->set_expiration_time (new_expiration_time);
    new_einst_ptr->set_recurring_microseconds (microseconds);

    I_timer_inst_ref_var* timer_inst_ref_var_ptr
	= new I_timer_inst_ref_var (new_einst_ptr->get_evt_inst_ID ());

    p_rvalue_var_si.replace_var (timer_inst_ref_var_ptr);


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #8:  SIM_SOR::interpret__time__timer_start_recurring ()."));
    return;
}


void SIM_SOR::interpret__time__timer_remaining_time
  ( int num_params, Description p_param_name[], GS_var_si p_param_value[],    
    GS_var_si& p_rvalue_var_si)


{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::interpret__time__timer_remaining_time ()" ));


    t_boolean timer_inst_ref_specified = FALSE;
    I_timer_inst_ref_var* timer_inst_ref_var_ptr = 0;


    int param_num = 0;
    while (param_num < num_params && !timer_inst_ref_specified )
    {
	if (p_param_value[param_num].get_void_var_ptr ())
	{
		Description err_msg ("Value of '");
		err_msg += p_param_name[param_num];
		err_msg += "' not recoginzed.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #1:  SIM_SOR::interpret__time__timer_remaining_time ()."));
	    return;
	}

	if (p_param_name[param_num] == "param.timer_inst_ref")
	{
	    if (! p_param_value[param_num].get_timer_inst_ref_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'timer_inst_ref' expects value of type 'inst_ref<Timer>'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #2:  SIM_SOR::interpret__time__timer_remaining_time ()."));
		return;
	    }
	    timer_inst_ref_specified = TRUE;
	    timer_inst_ref_var_ptr
		= p_param_value[param_num].get_timer_inst_ref_var_ptr ();
	}
	else
	{
		Description err_msg ("Unexpected parameter '");
		err_msg += p_param_name[param_num];
		err_msg += "'.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #3:  SIM_SOR::interpret__time__timer_remaining_time ()."));
	    return;
	}
        param_num += 1;
    }


    if (! timer_inst_ref_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'timer_inst_ref'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #4:  SIM_SOR::interpret__time__timer_remaining_time ()."));
	return;
    }


    if (! timer_inst_ref_var_ptr)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Internal Error in parameter 'timer_inst_ref'."));
	LOG_ERROR ((L_log_string,
	    "End #5:  SIM_SOR::interpret__time__timer_remaining_time ()."));
	return;
    }


    I_SM_Evt_Inst* einst_ptr = timer_inst_ref_var_ptr->get_einst_ptr ();
    if (! einst_ptr)
    {
	//  The event must have already been processed - send back a 0 value
	//    to indicate such.
	//
	p_rvalue_var_si.replace_var (new I_integer_var ((t_long) 0));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #6:  SIM_SOR::interpret__time__timer_remaining_time ()."));
	return;
    }


    I_timestamp_var current_time (I_Clock::current_time ());
    I_timestamp_var timer_time (einst_ptr->get_expiration_time ());
    if (current_time >= timer_time)
    {
	//  The event has expired - send back a 0 value to indicate such.
	//
	p_rvalue_var_si.replace_var (new I_integer_var ((t_long) 0));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #7:  SIM_SOR::interpret__time__timer_remaining_time ()."));
	return;
    }


    I_timestamp_var remaining_time (timer_time);
    remaining_time -= I_Clock::current_time ();
    t_ulong remaining_us = remaining_time.get_microsecond ();
    remaining_us += (remaining_time.get_second () * 1000000);


    p_rvalue_var_si.replace_var (new I_integer_var ((t_long) remaining_us));


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #8:  SIM_SOR::interpret__time__timer_remaining_time ()."));
    return;
}

void SIM_SOR::interpret__time__timer_reset_time
  ( int num_params, Description p_param_name[], GS_var_si p_param_value[],    
    GS_var_si& p_rvalue_var_si)


{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::interpret__time__timer_reset_time ()" ));


    t_boolean timer_inst_ref_specified = FALSE;
    I_timer_inst_ref_var* timer_inst_ref_var_ptr = 0;
    t_boolean microseconds_specified = TRUE;
    t_long microseconds = 0;


    int param_num = 0;
    while (param_num < num_params && (!timer_inst_ref_specified || microseconds_specified) )
    {
	if (p_param_value[param_num].get_void_var_ptr ())
	{
		Description err_msg ("Value of '");
		err_msg += p_param_name[param_num];
		err_msg += "' not recoginzed.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #1:  SIM_SOR::interpret__time__timer_reset_time ()."));
	    return;
	}

	if (p_param_name[param_num] == "param.timer_inst_ref")
	{
	    if (! p_param_value[param_num].get_timer_inst_ref_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'timer_inst_ref' expects value of type 'inst_ref<Timer>'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #2:  SIM_SOR::interpret__time__timer_reset_time ()."));
		return;
	    }
	    timer_inst_ref_specified = TRUE;
	    timer_inst_ref_var_ptr
		= p_param_value[param_num].get_timer_inst_ref_var_ptr ();
	}
	else if (p_param_name[param_num] == "param.microseconds")
	{
	    if (! p_param_value[param_num].get_integer_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'microseconds' expects value of type 'integer'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #3:  SIM_SOR::interpret__time__timer_reset_time ()."));
		return;
	    }
	    microseconds_specified = TRUE;
	    microseconds = p_param_value[param_num].get_integer_var_ptr ()->get_value ();
	}
	else
	{
		Description err_msg ("Unexpected parameter '");
		err_msg += p_param_name[param_num];
		err_msg += "'.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #3:  SIM_SOR::interpret__time__timer_reset_time ()."));
	    return;
	}
        param_num += 1;
    }


    if (! timer_inst_ref_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'timer_inst_ref'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #5:  SIM_SOR::interpret__time__timer_reset_time ()."));
	return;
    }

    if (! microseconds_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'microseconds'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #6:  SIM_SOR::interpret__time__timer_reset_time ()."));
	return;
    }


    if (! timer_inst_ref_var_ptr)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Internal Error in parameter 'timer_inst_ref'."));
	LOG_ERROR ((L_log_string,
	    "End #5:  SIM_SOR::interpret__time__timer_remaining_time ()."));
	return;
    }


    I_SM_Evt_Inst* einst_ptr = timer_inst_ref_var_ptr->get_einst_ptr ();
    if (! einst_ptr)
    {
	//  The event must have already been processed.
	//
	p_rvalue_var_si.replace_var (new I_boolean_var (FALSE));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #7:  SIM_SOR::interpret__time__timer_reset_time ()."));
	return;
    }


    I_timestamp_var new_expiration_time (I_Clock::current_time ());
    new_expiration_time += microseconds;
    einst_ptr->set_expiration_time (new_expiration_time);


    p_rvalue_var_si.replace_var (new I_boolean_var (TRUE));


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #8:  SIM_SOR::interpret__time__timer_reset_time ()."));
    return;
}




void SIM_SOR::interpret__time__timer_add_time
  ( int num_params, Description p_param_name[], GS_var_si p_param_value[],    
    GS_var_si& p_rvalue_var_si)


{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::interpret__time__timer_add_time ()" ));


    t_boolean timer_inst_ref_specified = FALSE;
    I_timer_inst_ref_var* timer_inst_ref_var_ptr = 0;
    t_boolean microseconds_specified = TRUE;
    t_long microseconds = 0;


    int param_num = 0;
    while (param_num < num_params && (!timer_inst_ref_specified || microseconds_specified) )
    {
	if (p_param_value[param_num].get_void_var_ptr ())
	{
		Description err_msg ("Value of '");
		err_msg += p_param_name[param_num];
		err_msg += "' not recoginzed.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #1:  SIM_SOR::interpret__time__timer_add_time ()."));
	    return;
	}

	if (p_param_name[param_num] == "param.timer_inst_ref")
	{
	    if (! p_param_value[param_num].get_timer_inst_ref_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'timer_inst_ref' expects value of type 'inst_ref<Timer>'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #2:  SIM_SOR::interpret__time__timer_add_time ()."));
		return;
	    }
	    timer_inst_ref_specified = TRUE;
	    timer_inst_ref_var_ptr
		= p_param_value[param_num].get_timer_inst_ref_var_ptr ();
	}
	else if (p_param_name[param_num] == "param.microseconds")
	{
	    if (! p_param_value[param_num].get_integer_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'microseconds' expects value of type 'integer'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #3:  SIM_SOR::interpret__time__timer_add_time ()."));
		return;
	    }
	    microseconds_specified = TRUE;
	    microseconds = p_param_value[param_num].get_integer_var_ptr ()->get_value ();
	}
	else
	{
		Description err_msg ("Unexpected parameter '");
		err_msg += p_param_name[param_num];
		err_msg += "'.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #3:  SIM_SOR::interpret__time__timer_add_time ()."));
	    return;
	}
        param_num += 1;
    }


    if (! timer_inst_ref_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'timer_inst_ref'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #5:  SIM_SOR::interpret__time__timer_add_time ()."));
	return;
    }

    if (! microseconds_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'microseconds'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #6:  SIM_SOR::interpret__time__timer_add_time ()."));
	return;
    }


    if (! timer_inst_ref_var_ptr)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Internal Error in parameter 'timer_inst_ref'."));
	LOG_ERROR ((L_log_string,
	    "End #5:  SIM_SOR::interpret__time__timer_remaining_time ()."));
	return;
    }


    I_SM_Evt_Inst* einst_ptr = timer_inst_ref_var_ptr->get_einst_ptr ();
    if (! einst_ptr)
    {
	//  The event must have already been processed.
	//
	p_rvalue_var_si.replace_var (new I_boolean_var (FALSE));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #7:  SIM_SOR::interpret__time__timer_add_time ()."));
	return;
    }


    I_timestamp_var new_expiration_time (einst_ptr->get_expiration_time ());
    new_expiration_time += microseconds;
    einst_ptr->set_expiration_time (new_expiration_time);


    p_rvalue_var_si.replace_var (new I_boolean_var (TRUE));


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #8:  SIM_SOR::interpret__time__timer_add_time ()."));
    return;
}




void SIM_SOR::interpret__time__timer_cancel
  ( int num_params, Description p_param_name[], GS_var_si p_param_value[],    
    GS_var_si& p_rvalue_var_si)


{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::interpret__time__timer_cancel ()" ));


    t_boolean timer_inst_ref_specified = FALSE;
    I_timer_inst_ref_var* timer_inst_ref_var_ptr = 0;


    int param_num = 0;
    while (param_num < num_params && !timer_inst_ref_specified)
    {
	if (p_param_value[param_num].get_void_var_ptr ())
	{
		Description err_msg ("Value of '");
		err_msg += p_param_name[param_num];
		err_msg += "' not recoginzed.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #1:  SIM_SOR::interpret__time__timer_cancel ()."));
	    return;
	}

	if (p_param_name[param_num] == "param.timer_inst_ref")
	{
	    if (! p_param_value[param_num].get_timer_inst_ref_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'timer_inst_ref' expects value of type 'inst_ref<Timer>'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #2:  SIM_SOR::interpret__time__timer_cancel ()."));
		return;
	    }
	    timer_inst_ref_specified = TRUE;
	    timer_inst_ref_var_ptr
		= p_param_value[param_num].get_timer_inst_ref_var_ptr ();
	}
	else
	{
		Description err_msg ("Unexpected parameter '");
		err_msg += p_param_name[param_num];
		err_msg += "'.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #3:  SIM_SOR::interpret__time__timer_cancel ()."));
	    return;
	}
        param_num += 1;
    }


    if (! timer_inst_ref_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'timer_inst_ref'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #4:  SIM_SOR::interpret__time__timer_cancel ()."));
	return;
    }


    if (! timer_inst_ref_var_ptr)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Internal Error in parameter 'timer_inst_ref'."));
	LOG_ERROR ((L_log_string,
	    "End #5:  SIM_SOR::interpret__time__timer_remaining_time ()."));
	return;
    }


    I_SM_Evt_Inst* einst_ptr = timer_inst_ref_var_ptr->get_einst_ptr ();
    if (! einst_ptr)
    {
	//  The event must have already been processed.
	//
	p_rvalue_var_si.replace_var (new I_boolean_var (FALSE));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #6:  SIM_SOR::interpret__time__timer_cancel ()."));
	return;
    }


    I_SM_Evt_Inst::delete__I_SM_Evt_Inst (einst_ptr);
    timer_inst_ref_var_ptr->set_einst_id (Id::Default);


    p_rvalue_var_si.replace_var (new I_boolean_var (TRUE));


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #7:  SIM_SOR::interpret__time__timer_cancel ()."));
    return;
}




void SIM_SOR::interpret__mc_dbms__get_env_var
  ( int num_params, Description p_param_name[], GS_var_si p_param_value[],    
    GS_var_si& p_rvalue_var_si)


{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::interpret__mc_dbms__get_env_var ()" ));


    t_boolean name_specified = FALSE;
    Description name_str;


    int param_num = 0;
    while (param_num < num_params && !name_specified )
    {
	if (p_param_value[param_num].get_void_var_ptr ())
	{
		Description err_msg ("Value of '");
		err_msg += p_param_name[param_num];
		err_msg += "' not recoginzed.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #1:  SIM_SOR::interpret__mc_dbms__get_env_var ()."));
	    return;
	}


	if (p_param_name[param_num] == "param.name")
	{
	    if (! p_param_value[param_num].get_string_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'name' expects value of type 'string'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #2:  SIM_SOR::interpret__mc_dbms__get_env_var ()."));
		return;
	    }
	    name_specified = TRUE;
	    name_str = p_param_value[param_num].get_string_var_ptr ()->get_value ();
	}
	else
	{
		Description err_msg ("Unexpected parameter '");
		err_msg += p_param_name[param_num];
		err_msg += "'.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #3:  SIM_SOR::interpret__mc_dbms__get_env_var ()."));
	    return;
	}
        param_num += 1;
    }


    if (! name_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'name'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #4:  SIM_SOR::interpret__mc_dbms__get_env_var ()."));
	return;
    }


	char *name_str_ASCII = (char *) vcharExportAlloc( 
		vcharScribeASCIIExport(name_str.char_ptr()));
	Description contents_str = U_env_var::get_value_str (name_str_ASCII);
	vcharExportFree( name_str_ASCII );

    p_rvalue_var_si.replace_var (new I_string_var (contents_str));


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #6:  SIM_SOR::interpret__mc_dbms__get_env_var ()."));
    return;
}




void SIM_SOR::interpret__mc_dbms__put_env_var 
   ( int num_params, Description p_param_name[], GS_var_si p_param_value[])

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::interpret__mc_dbms__put_env_var ()" ));


    t_boolean name_specified = FALSE;
    Description name_str;
    t_boolean value_specified = FALSE;
    Description value_str;


    int param_num = 0;
    while (param_num < num_params && (!name_specified || !value_specified) )
    {
	if (p_param_value[param_num].get_void_var_ptr ())
	{
		Description err_msg ("Value of '");
		err_msg += p_param_name[param_num];
		err_msg += "' not recoginzed.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #1:  SIM_SOR::interpret__mc_dbms__put_env_var ()."));
	    return;
	}


	if (p_param_name[param_num] == "param.name")
	{
	    if (! p_param_value[param_num].get_string_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'name' expects value of type 'string'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #2:  SIM_SOR::interpret__mc_dbms__put_env_var ()."));
		return;
	    }
	    name_specified = TRUE;
	    name_str = p_param_value[param_num].get_string_var_ptr ()->get_value ();
	}
	else if (p_param_name[param_num] == "param.value")
	{
	    if (! p_param_value[param_num].get_string_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'value' expects value of type 'string'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #2:  SIM_SOR::interpret__mc_dbms__put_env_var ()."));
		return;
	    }
	    value_specified = TRUE;
	    value_str = p_param_value[param_num].get_string_var_ptr ()->get_value ();
	}
	else
	{
		Description err_msg ("Unexpected parameter '");
		err_msg += p_param_name[param_num];
		err_msg += "'.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #3:  SIM_SOR::interpret__mc_dbms__put_env_var ()."));
	    return;
	}
        param_num += 1;
    }


    if (! name_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'name'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #4:  SIM_SOR::interpret__mc_dbms__put_env_var ()."));
	return;
    }


    if (! value_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'value'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #4:  SIM_SOR::interpret__mc_dbms__put_env_var ()."));
	return;
    }


	char *name_str_ASCII = (char *) vcharExportAlloc( 
		vcharScribeASCIIExport(name_str.char_ptr()));
	char *value_str_ASCII = (char *) vcharExportAlloc( 
		vcharScribeASCIIExport(value_str.char_ptr()));
	if (U_env_var::put_env_var (name_str_ASCII, value_str_ASCII) )
	{
		LOG_ERROR ((L_log_string, "GS_func_def::exec_predefined(): putenv %s failed.", name_str.char_ptr ()));
	}

	vcharExportFree( name_str_ASCII );
	vcharExportFree( value_str_ASCII );

    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #6:  SIM_SOR::interpret__mc_dbms__put_env_var ()."));
    return;
}




void SIM_SOR::interpret__mc_dbms__shell_command
  ( int num_params, Description p_param_name[], GS_var_si p_param_value[],    
    GS_var_si& p_rvalue_var_si)


{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::interpret__mc_dbms__shell_command ()" ));


    t_boolean command_specified = FALSE;
    Description command_str;


    int param_num = 0;
    while (param_num < num_params && !command_specified )
    {
	if (p_param_value[param_num].get_void_var_ptr ())
	{
		Description err_msg ("Value of '");
		err_msg += p_param_name[param_num];
		err_msg += "' not recoginzed.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #1:  SIM_SOR::interpret__mc_dbms__shell_command ()."));
	    return;
	}


	if (p_param_name[param_num] == "param.command")
	{
	    if (! p_param_value[param_num].get_string_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'command' expects value of type 'string'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #2:  SIM_SOR::interpret__mc_dbms__shell_command ()."));
		return;
	    }
	    command_specified = TRUE;
	    command_str = p_param_value[param_num].get_string_var_ptr ()->get_value ();
	}
	else
	{
		Description err_msg ("Unexpected parameter '");
		err_msg += p_param_name[param_num];
		err_msg += "'.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #3:  SIM_SOR::interpret__mc_dbms__shell_command ()."));
	    return;
	}
        param_num += 1;
    }


    if (! command_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'command'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #4:  SIM_SOR::interpret__mc_dbms__shell_command ()."));
	return;
    }

	char *command_str_ASCII = (char *) vcharExportAlloc( 
		vcharScribeASCIIExport(command_str.char_ptr()));

    int exit_status = U_shell_cmd::exec_shell_cmd (command_str_ASCII);

	vcharExportFree( command_str_ASCII );


    p_rvalue_var_si.replace_var (new I_integer_var (exit_status));


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #6:  SIM_SOR::interpret__mc_dbms__shell_command ()."));
    return;
}




void SIM_SOR::interpret__mc_dbms__file_read
  ( int num_params, Description p_param_name[], GS_var_si p_param_value[],    
    GS_var_si& p_rvalue_var_si)


{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::interpret__mc_dbms__file_read ()" ));


    t_boolean name_specified = FALSE;
    Description name_str;


    int param_num = 0;
    while (param_num < num_params && !name_specified )
    {
	if (p_param_value[param_num].get_void_var_ptr ())
	{
		Description err_msg ("Value of '");
		err_msg += p_param_name[param_num];
		err_msg += "' not recoginzed.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #1:  SIM_SOR::interpret__mc_dbms__file_read ()."));
	    return;
	}


	if (p_param_name[param_num] == "param.name")
	{
	    if (! p_param_value[param_num].get_string_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'name' expects value of type 'string'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #2:  SIM_SOR::interpret__mc_dbms__file_read ()."));
		return;
	    }
	    name_specified = TRUE;
	    name_str = p_param_value[param_num].get_string_var_ptr ()->get_value ();
	}
	else
	{
		Description err_msg ("Unexpected parameter '");
		err_msg += p_param_name[param_num];
		err_msg += "'.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #3:  SIM_SOR::interpret__mc_dbms__file_read ()."));
	    return;
	}
        param_num += 1;
    }


    if (! name_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'name'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #4:  SIM_SOR::interpret__mc_dbms__file_read ()."));
	return;
    }


    Description contents_str;
	char *name_str_ASCII = (char *) vcharExportAlloc( 
		vcharScribeASCIIExport(name_str.char_ptr()));

    RM_file * file_ptr = new RM_file ();
    if (file_ptr->RM_open_media (name_str_ASCII) != RM_render_media::MEDIA_OPENED)
    {
	    Description err_msg ("Unable to open file '");
		err_msg += name_str;
		err_msg += "' for reading.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
    }
    else
    {
	    vchar *line_str;
		while ((line_str = file_ptr->RM_read_vchar ()) != 0)
		{
		    contents_str += line_str;
		    contents_str += "\n";
		}
    }

    delete file_ptr;

    p_rvalue_var_si.replace_var (new I_string_var (contents_str.char_ptr()));

	vcharExportFree( name_str_ASCII );

    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #6:  SIM_SOR::interpret__mc_dbms__file_read ()."));
    return;
}




void SIM_SOR::interpret__mc_dbms__file_write
  ( int num_params, Description p_param_name[], GS_var_si p_param_value[],    
    GS_var_si& p_rvalue_var_si)


{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::interpret__mc_dbms__file_write ()" ));


    t_boolean name_specified = FALSE;
    Description name_str;
    t_boolean contents_specified = FALSE;
    Description contents_str;


    int param_num = 0;
    while (param_num < num_params && (!name_specified || !contents_specified) )
    {
	if (p_param_value[param_num].get_void_var_ptr ())
	{
		Description err_msg ("Value of '");
		err_msg += p_param_name[param_num];
		err_msg += "' not recoginzed.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #1:  SIM_SOR::interpret__mc_dbms__file_write ()."));
	    return;
	}


	if (p_param_name[param_num] == "param.name")
	{
	    if (! p_param_value[param_num].get_string_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'name' expects value of type 'string'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #2:  SIM_SOR::interpret__mc_dbms__file_write ()."));
		return;
	    }
	    name_specified = TRUE;
	    name_str = p_param_value[param_num].get_string_var_ptr ()->get_value ();
	}
	else if (p_param_name[param_num] == "param.contents")
	{
	    if (! p_param_value[param_num].get_string_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'contents' expects value of type 'string'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #2:  SIM_SOR::interpret__mc_dbms__file_write ()."));
		return;
	    }
	    contents_specified = TRUE;
	    contents_str = p_param_value[param_num].get_string_var_ptr ()->get_value ();
	}
	else
	{
		Description err_msg ("Unexpected parameter '");
		err_msg += p_param_name[param_num];
		err_msg += "'.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #3:  SIM_SOR::interpret__mc_dbms__file_write ()."));
	    return;
	}
        param_num += 1;
    }


    if (! name_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'name'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #4:  SIM_SOR::interpret__mc_dbms__file_write ()."));
	return;
    }


    if (! contents_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'contents'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #4:  SIM_SOR::interpret__mc_dbms__file_write ()."));
	return;
    }


    t_boolean success_flag = FALSE;
    ofstream write_file;
	char *name_str_ASCII = (char *) vcharExportAlloc( 
		vcharScribeASCIIExport(name_str.char_ptr()));
    write_file.open (name_str_ASCII, ios::out);
    if (! write_file.good ())
    {
	    Description err_msg ("Unable to open file '");
		err_msg += name_str;
		err_msg += "' for writing.";
		GS_ui::inform (UI_INFORM__ERROR, err_msg);
    }
    else
    {
		char *contents_str_ASCII = (char *) vcharExportAlloc( 
			vcharScribeASCIIExport(contents_str.char_ptr()));
		write_file << contents_str.char_ptr () << endl;
		write_file.close ();
		vcharExportFree( contents_str_ASCII );
		success_flag = TRUE;
    }
    p_rvalue_var_si.replace_var (new I_boolean_var (success_flag));

	vcharExportFree( name_str_ASCII );

    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #6:  SIM_SOR::interpret__mc_dbms__file_write ()."));
    return;
}





void SIM_SOR::interpret__mc_dbms__string_to_integer
  ( int num_params, Description p_param_name[], GS_var_si p_param_value[],    
    GS_var_si& p_rvalue_var_si)


{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::interpret__mc_dbms__string_to_integer ()" ));


    t_boolean string_specified = FALSE;
    Description string_str;


    int param_num = 0;
    while (param_num < num_params && !string_specified )
    {
	if (p_param_value[param_num].get_void_var_ptr ())
	{
		Description err_msg ("Value of '");
		err_msg += p_param_name[param_num];
		err_msg += "' not recoginzed.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #1:  SIM_SOR::interpret__mc_dbms__string_to_integer ()."));
	    return;
	}


	if (p_param_name[param_num] == "param.string")
	{
	    if (! p_param_value[param_num].get_string_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'string' expects value of type 'string'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #2:  SIM_SOR::interpret__mc_dbms__string_to_integer ()."));
		return;
	    }
	    string_specified = TRUE;
	    string_str = p_param_value[param_num].get_string_var_ptr ()->get_value ();
	}
	else
	{
		Description err_msg ("Unexpected parameter '");
		err_msg += p_param_name[param_num];
		err_msg += "'.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #3:  SIM_SOR::interpret__mc_dbms__string_to_integer ()."));
	    return;
	}
        param_num += 1;
    }


    if (! string_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'string'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #4:  SIM_SOR::interpret__mc_dbms__string_to_integer ()."));
	return;
    }


    t_int value_int;
	t_boolean exception_occurred = TRUE;
	vexWITH_HANDLING
	{
		value_int = vnumParseInt(string_str.char_ptr (), 0);
		exception_occurred = FALSE;
	} vexON_EXCEPTION {
			
	} vexEND_HANDLING;
			
	if (exception_occurred)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected integer value in parameter 'string'."));
	LOG_TRACE (L_W_WINDOWS, L_FUNCTION_END, (L_log_string,
	    "End #5:  SIM_SOR::interpret__mc_dbms__string_to_integer ()."));
	return;
    }
    p_rvalue_var_si.replace_var (new I_integer_var (value_int));


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #6:  SIM_SOR::interpret__mc_dbms__string_to_integer ()."));
    return;
}




void SIM_SOR::interpret__mc_dbms__string_to_real
  ( int num_params, Description p_param_name[], GS_var_si p_param_value[],    
    GS_var_si& p_rvalue_var_si)


{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::interpret__mc_dbms__string_to_real ()" ));


    t_boolean string_specified = FALSE;
    Description string_str;


    int param_num = 0;
    while (param_num < num_params && !string_specified )
    {
	if (p_param_value[param_num].get_void_var_ptr ())
	{
		Description err_msg ("Value of '");
		err_msg += p_param_name[param_num];
		err_msg += "' not recoginzed.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #1:  SIM_SOR::interpret__mc_dbms__string_to_real ()."));
	    return;
	}


	if (p_param_name[param_num] == "param.string")
	{
	    if (! p_param_value[param_num].get_string_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'string' expects value of type 'string'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #2:  SIM_SOR::interpret__mc_dbms__string_to_real ()."));
		return;
	    }
	    string_specified = TRUE;
	    string_str = p_param_value[param_num].get_string_var_ptr ()->get_value ();
	}
	else
	{
		Description err_msg ("Unexpected parameter '");
		err_msg += p_param_name[param_num];
		err_msg += "'.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #3:  SIM_SOR::interpret__mc_dbms__string_to_real ()."));
	    return;
	}
        param_num += 1;
    }


    if (! string_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'string'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #4:  SIM_SOR::interpret__mc_dbms__string_to_real ()."));
	return;
    }


    t_double value_real;
	t_boolean exception_occurred = TRUE;
	vexWITH_HANDLING
	{
		value_real = vnumParseFloat(string_str.char_ptr (), 0);
		exception_occurred = FALSE;
	} vexON_EXCEPTION {
			
	} vexEND_HANDLING;
			
	if (exception_occurred)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected real value in parameter 'string'."));
	LOG_TRACE (L_W_WINDOWS, L_FUNCTION_END, (L_log_string,
	    "End #5:  SIM_SOR::interpret__mc_dbms__string_to_real ()."));
	return;
    }
    p_rvalue_var_si.replace_var (new I_real_var (value_real));


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #6:  SIM_SOR::interpret__mc_dbms__string_to_real ()."));
    return;
}


void SIM_SOR::interpret__mc_dbms__integer_to_string
  ( int num_params, Description p_param_name[], GS_var_si p_param_value[],    
    GS_var_si& p_rvalue_var_si)


{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::interpret__mc_dbms__integer_to_string ()" ));


    t_boolean integer_specified = FALSE;
    t_long    integer_val;


    int param_num = 0;
    while (param_num < num_params && !integer_specified )
    {
	if (p_param_value[param_num].get_void_var_ptr ())
	{
		Description err_msg ("Value of '");
		err_msg += p_param_name[param_num];
		err_msg += "' not recoginzed.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #1:  SIM_SOR::interpret__mc_dbms__integer_to_string ()."));
	    return;
	}


	if (p_param_name[param_num] == "param.integer")
	{
	    if (! p_param_value[param_num].get_integer_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'integer' expects value of type 'integer'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #2:  SIM_SOR::interpret__mc_dbms__integer_to_string ()."));
		return;
	    }
	    integer_specified = TRUE;
	    integer_val = p_param_value[param_num].get_integer_var_ptr ()->get_value ();
	}
	else
	{
		Description err_msg ("Unexpected parameter '");
		err_msg += p_param_name[param_num];
		err_msg += "'.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #3:  SIM_SOR::interpret__mc_dbms__integer_to_string ()."));
	    return;
	}
        param_num += 1;
    }


    if (! integer_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'integer'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #4:  SIM_SOR::interpret__mc_dbms__integer_to_string ()."));
	return;
    }


    char int_buf[20];
    sprintf (int_buf, "%ld", integer_val);
    p_rvalue_var_si.replace_var (new I_string_var (int_buf));


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #6:  SIM_SOR::interpret__mc_dbms__integer_to_string ()."));
    return;
}

void SIM_SOR::interpret__mc_dbms__real_to_string
  ( int num_params, Description p_param_name[], GS_var_si p_param_value[],    
    GS_var_si& p_rvalue_var_si)


{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::interpret__mc_dbms__real_to_string ()" ));


    t_boolean real_specified = FALSE;
    t_double  real_val;


    int param_num = 0;
    while (param_num < num_params && !real_specified )
    {
	if (p_param_value[param_num].get_void_var_ptr ())
	{
		Description err_msg ("Value of '");
		err_msg += p_param_name[param_num];
		err_msg += "' not recoginzed.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #1:  SIM_SOR::interpret__mc_dbms__real_to_string ()."));
	    return;
	}


	if (p_param_name[param_num] == "param.real")
	{
	    if (! p_param_value[param_num].get_real_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'real' expects value of type 'real'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #2:  SIM_SOR::interpret__mc_dbms__real_to_string ()."));
		return;
	    }
	    real_specified = TRUE;
	    real_val = p_param_value[param_num].get_real_var_ptr ()->get_value ();
	}
	else
	{
		Description err_msg ("Unexpected parameter '");
		err_msg += p_param_name[param_num];
		err_msg += "'.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #3:  SIM_SOR::interpret__mc_dbms__real_to_string ()."));
	    return;
	}
        param_num += 1;
    }


    if (! real_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'param.real'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #4:  SIM_SOR::interpret__mc_dbms__real_to_string ()."));
	return;
    }


    char real_buf[255];
    // %lf is what's used elsewhere
    sprintf (real_buf, "%lf", real_val);
    p_rvalue_var_si.replace_var (new I_string_var (real_buf));


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #6:  SIM_SOR::interpret__mc_dbms__real_to_string ()."));
    return;
}

void SIM_SOR::interpret__mc_dbms__boolean_to_string
  ( int num_params, Description p_param_name[], GS_var_si p_param_value[],    
    GS_var_si& p_rvalue_var_si)


{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::interpret__mc_dbms__boolean_to_string ()" ));


    t_boolean boolean_specified = FALSE;
    t_boolean boolean_val;


    int param_num = 0;
    while (param_num < num_params && !boolean_specified )
    {
	if (p_param_value[param_num].get_void_var_ptr ())
	{
		Description err_msg ("Value of '");
		err_msg += p_param_name[param_num];
		err_msg += "' not recoginzed.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #1:  SIM_SOR::interpret__mc_dbms__boolean_to_string ()."));
	    return;
	}


	if (p_param_name[param_num] == "param.boolean")
	{
	    if (! p_param_value[param_num].get_boolean_var_ptr ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Parameter 'boolean' expects value of type 'boolean'"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #2:  SIM_SOR::interpret__mc_dbms__boolean_to_string ()."));
		return;
	    }
	    boolean_specified = TRUE;
	    boolean_val = p_param_value[param_num].get_boolean_var_ptr ()->get_value ();
	}
	else
	{
		Description err_msg ("Unexpected parameter '");
		err_msg += p_param_name[param_num];
		err_msg += "'.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #3:  SIM_SOR::interpret__mc_dbms__boolean_to_string ()."));
	    return;
	}
        param_num += 1;
    }


    if (! boolean_specified)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Expected parameter 'boolean'."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #4:  SIM_SOR::interpret__mc_dbms__boolean_to_string ()."));
	return;
    }

    if ( boolean_val )
    {
      p_rvalue_var_si.replace_var (new I_string_var ("TRUE"));
    }
    else
    {
      p_rvalue_var_si.replace_var (new I_string_var ("FALSE"));
    }

    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #6:  SIM_SOR::interpret__mc_dbms__boolean_to_string ()."));
    return;
}

