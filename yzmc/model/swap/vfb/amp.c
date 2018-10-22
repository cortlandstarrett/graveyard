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
#ifdef AUTOSAR_ENABLED
#include "Rte_co_amp.h"
#define MC3020_AUTOSAR_RUNNABLE_NUMBER 0
static void* cache_Rte_self;

/*
 * This is the AUTOSAR linkage for the amp component timer.
 */
FUNC(void, RTE_APPL_CODE)
ib_amp_ru_ampTimer( Rte_Instance self )
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
ib_amp_ru_amp_Initialize( Rte_Instance self )
{
  /* Initialize the system.  */
  cache_Rte_self = (void *) self;
}


#endif

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
 * This is the AUTOSAR linkage for the above Port1 port operation.
 */
#ifdef AUTOSAR_ENABLED
FUNC(void, RTE_APPL_CODE)
ib_amp_ru_Port1_init( Rte_Instance Rte_self )
{
  u1_t t = MC3020_AUTOSAR_RUNNABLE_NUMBER;
  cache_Rte_self = (void*) Rte_self;
      
  /* Hand the data into the receiving component port.  */
  amp_Port1_init();

  /* Allow xtUML event queue to dispatch and run to completion.  */
  ooa_loop( &t );
}
#endif

/*
 * Interface:  interconnect
 * Required Port:  Port1
 * From Provider Message:  response
 */
void
amp_Port1_response( const dt_xtUMLReal p_power, const dt_xtUMLInteger p_size, const dt_xtUMLReal p_weight )
{
  /* LOG::LogInfo( message:response received in amp ) */
  XTUML_OAL_STMT_TRACE( 1, "LOG::LogInfo( message:response received in amp )" );
  LOG_LogInfo( "response received in amp" );
}

/*
 * This is the AUTOSAR linkage for the above Port1 port message.
 */
#ifdef AUTOSAR_ENABLED
FUNC(void, RTE_APPL_CODE)
ib_amp_ru_Port1_response_param(Rte_Instance Rte_self)
{
  dt_response_param response_param;
  u1_t t = MC3020_AUTOSAR_RUNNABLE_NUMBER;
  cache_Rte_self = (void*) Rte_self;
  
  /* Receive the data from the RTE.  */
  Rte_Read_pt_Port1_response_param( Rte_self, &response_param );
  
  /* Hand the data into the receiving component port.  */
  amp_Port1_response( response_param.p_power, response_param.p_size, response_param.p_weight);
  
  /* Allow xtUML event queue to dispatch and run to completion.  */
  ooa_loop( &t );
}
#endif

/*
 * Interface:  interconnect
 * Required Port:  Port1
 * To Provider Message:  stimulus
 */
void
amp_Port1_stimulus( const dt_xtUMLReal p_power, const dt_xtUMLInteger p_size, const dt_xtUMLReal p_weight )
{
  #ifdef AUTOSAR_ENABLED
  //dt_xtUMLSignal dp_signal;
  dt_stimulus_param stimulus_param;
  stimulus_param.p_size=p_size;
  stimulus_param.p_weight=p_weight;
  stimulus_param.p_power=p_power;
  Rte_Write_pt_Port1_stimulus_param( (Rte_Instance) cache_Rte_self, stimulus_param );
  #else
  driver_Port1_stimulus(  p_power, p_size, p_weight );
  #endif
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
