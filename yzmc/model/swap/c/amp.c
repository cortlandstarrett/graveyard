/*----------------------------------------------------------------------------
 * File:  amp.c
 *
 * UML Component Port Messages
 * Component/Module Name:  amp
 *
 * your copyright statement can go here (from te_copyright.body)
 *--------------------------------------------------------------------------*/

#include "swap_sys_types.h"
#include "amp.h"
#include "LOG_bridge.h"
#include "driver.h"
#include "amp_classes.h"

/*
 * Interface:  interconnect
 * Required Port:  Port1
 * From Provider Message:  init
 */
void
amp_Port1_init()
{
  /* SEND Port1::stimulus(power:1.0, size:4, weight:3.1) */
  XTUML_OAL_STMT_TRACE( 1, "SEND Port1::stimulus(power:1.0, size:4, weight:3.1)" );
  amp_Port1_stimulus( 1.0, 4, 3.1 );
}

/*
 * Interface:  interconnect
 * Required Port:  Port1
 * From Provider Message:  response
 */
void
amp_Port1_response( const r_t p_power, const i_t p_size, const r_t p_weight )
{
  /* LOG::LogInfo( message:response received in amp ) */
  XTUML_OAL_STMT_TRACE( 1, "LOG::LogInfo( message:response received in amp )" );
  LOG_LogInfo( "response received in amp" );
}

/*
 * Interface:  interconnect
 * Required Port:  Port1
 * To Provider Message:  stimulus
 */
void
amp_Port1_stimulus( const r_t p_power, const i_t p_size, const r_t p_weight )
{
  driver_Port1_stimulus(  p_power, p_size, p_weight );
}

/*
 * UML Domain Functions (Synchronous Services)
 */

/*
 * Domain Function:  init
 */
void
amp_init()
{
  /* LOG::LogInfo( message:amp sending stimulus ) */
  XTUML_OAL_STMT_TRACE( 1, "LOG::LogInfo( message:amp sending stimulus )" );
  LOG_LogInfo( "amp sending stimulus" );
  /* SEND Port1::stimulus(power:1.0, size:4, weight:3.1) */
  XTUML_OAL_STMT_TRACE( 1, "SEND Port1::stimulus(power:1.0, size:4, weight:3.1)" );
  amp_Port1_stimulus( 1.0, 4, 3.1 );

}

void amp_execute_initialization()
{
  /*
   * Initialization Function:  init
   * Component:  amp
   */
  amp_init();

}
