/*----------------------------------------------------------------------------
 * File:  driver.c
 *
 * UML Component Port Messages
 * Component/Module Name:  driver
 *
 * your copyright statement can go here (from te_copyright.body)
 *--------------------------------------------------------------------------*/

#include "swap_sys_types.h"
#include "driver.h"
#include "LOG_bridge.h"
#include "amp.h"
#include "driver_classes.h"

/*
 * Interface:  interconnect
 * Provided Port:  Port1
 * From Provider Message:  init
 */
void
driver_Port1_init()
{
  amp_Port1_init();
}

/*
 * Interface:  interconnect
 * Provided Port:  Port1
 * From Provider Message:  response
 */
void
driver_Port1_response( const r_t p_power, const i_t p_size, const r_t p_weight )
{
  amp_Port1_response(  p_power, p_size, p_weight );
}

/*
 * Interface:  interconnect
 * Provided Port:  Port1
 * To Provider Message:  stimulus
 */
void
driver_Port1_stimulus( const r_t p_power, const i_t p_size, const r_t p_weight )
{
  /* LOG::LogInfo( message:stimulus received in driver ) */
  XTUML_OAL_STMT_TRACE( 1, "LOG::LogInfo( message:stimulus received in driver )" );
  LOG_LogInfo( "stimulus received in driver" );
  /* LOG::LogInfo( message:sending response from driver ) */
  XTUML_OAL_STMT_TRACE( 1, "LOG::LogInfo( message:sending response from driver )" );
  LOG_LogInfo( "sending response from driver" );
  /* SEND Port1::response(power:( PARAM.power * 0.84 ), size:( PARAM.size + 5 ), weight:( PARAM.weight + 3.7 )) */
  XTUML_OAL_STMT_TRACE( 1, "SEND Port1::response(power:( PARAM.power * 0.84 ), size:( PARAM.size + 5 ), weight:( PARAM.weight + 3.7 ))" );
  driver_Port1_response( ( p_power * 0.84 ), ( p_size + 5 ), ( p_weight + 3.7 ) );
}

/*
 * UML Domain Functions (Synchronous Services)
 */

/* xtUML class info (collections, sizes, etc.) */
Escher_Extent_t * const driver_class_info[ driver_MAX_CLASS_NUMBERS ] = {
  &pG_driver_switch_extent
};


void driver_execute_initialization()
{
}
