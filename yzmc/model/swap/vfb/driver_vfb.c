  
/*---------------------------------------------------------------------------------------------- 
* File:  driver_vfb.c 
*
* VFB generated file 
*
* Please Remove this file if you need to make this project portable to VSI project ( with RTE ) 
*
*-----------------------------------------------------------------------------------------------*/ 



#include "Rte_co_driver.h"  

#ifdef AUTOSAR_ENABLED

static dt_response_param driver_response_param;
  
Std_ReturnType Rte_Call_pt_Port1_init_op_init( Rte_Instance Rte_self )
{
  ib_amp_ru_Port1_init( Rte_self );
  return 0;
}

Std_ReturnType Rte_Write_pt_Port1_response_param( Rte_Instance Rte_self, dt_response_param p_response_param )
{
  driver_response_param.p_size = p_response_param.p_size;
  driver_response_param.p_weight = p_response_param.p_weight;
  driver_response_param.p_power = p_response_param.p_power;
  ib_amp_ru_Port1_response_param( Rte_self );
  return 0;
}

Std_ReturnType Rte_Read_pt_Port1_response_param( Rte_Instance Rte_self, dt_response_param * p_response_param )
{
  *p_response_param = driver_response_param;
  return 0;
}

#endif
