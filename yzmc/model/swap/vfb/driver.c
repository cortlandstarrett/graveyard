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
#ifdef AUTOSAR_ENABLED
#include "Rte_co_driver.h"
#define MC3020_AUTOSAR_RUNNABLE_NUMBER 0
static void* cache_Rte_self;

/*
 * This is the AUTOSAR linkage for the driver component timer.
 */
FUNC(void, RTE_APPL_CODE)
ib_driver_ru_driverTimer( Rte_Instance self )
{
  u1_t t = MC3020_AUTOSAR_RUNNABLE_NUMBER;
  #if ESCHER_SYS_MAX_XTUML_TIMERS > 0
  if ( 0 == MC3020_AUTOSAR_RUNNABLE_NUMBER ) {
    TIM_update();
  }
  #endif
  ooa_loop( &t );
}

FUNC(void, RTE_APPL_CODE)
ib_driver_ru_driver_Initialize( Rte_Instance self )
{
  /* Initialize the system.  */
  cache_Rte_self = (void *) self;
}


#endif

/*
 * Interface:  interconnect
 * Provided Port:  Port1
 * From Provider Message:  init
 */
void
driver_Port1_init()
{
  #ifdef AUTOSAR_ENABLED
  u1_t t = MC3020_AUTOSAR_RUNNABLE_NUMBER;
  Rte_Call_pt_Port1_init_op_init( (Rte_Instance)cache_Rte_self );
  ooa_loop( &t );
  #else
  amp_Port1_init();
  #endif
}

/*
 * Interface:  interconnect
 * Provided Port:  Port1
 * From Provider Message:  response
 */
void
driver_Port1_response( const dt_xtUMLReal p_power, const dt_xtUMLInteger p_size, const dt_xtUMLReal p_weight )
{
  #ifdef AUTOSAR_ENABLED
  //dt_xtUMLSignal dp_signal;
  dt_response_param response_param;
  response_param.p_size=p_size;
  response_param.p_weight=p_weight;
  response_param.p_power=p_power;
  Rte_Write_pt_Port1_response_param( (Rte_Instance) cache_Rte_self, response_param );
  #else
  amp_Port1_response(  p_power, p_size, p_weight );
  #endif
}

/*
 * Interface:  interconnect
 * Provided Port:  Port1
 * To Provider Message:  stimulus
 */
void
driver_Port1_stimulus( const dt_xtUMLReal p_power, const dt_xtUMLInteger p_size, const dt_xtUMLReal p_weight )
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
 * This is the AUTOSAR linkage for the above Port1 port message.
 */
#ifdef AUTOSAR_ENABLED
FUNC(void, RTE_APPL_CODE)
ib_driver_ru_Port1_stimulus_param(Rte_Instance Rte_self)
{
  dt_stimulus_param stimulus_param;
  u1_t t = MC3020_AUTOSAR_RUNNABLE_NUMBER;
  cache_Rte_self = (void*) Rte_self;
  
  /* Receive the data from the RTE.  */
  Rte_Read_pt_Port1_stimulus_param( Rte_self, &stimulus_param );
  
  /* Hand the data into the receiving component port.  */
  driver_Port1_stimulus( stimulus_param.p_power, stimulus_param.p_size, stimulus_param.p_weight);
  
  /* Allow xtUML event queue to dispatch and run to completion.  */
  ooa_loop( &t );
}
#endif

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
