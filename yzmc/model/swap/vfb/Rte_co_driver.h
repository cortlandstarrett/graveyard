  
/*---------------------------------------------------------------------------------------------- 
* File:  Rte_co_driver.h 
*
* VFB generated file 
*
* Please Remove this file if you need to make this project portable to VSI project ( with RTE ) 
*
*-----------------------------------------------------------------------------------------------*/ 


  
#ifndef RTE_CO_DRIVER_H
#define RTE_CO_DRIVER_H 

#include "swap_sys_types.h" 
#include "Rte_co_amp.h" 

extern Std_ReturnType Rte_Call_pt_Port1_init_op_init( Rte_Instance Rte_self );
FUNC(void,RTE_APPL_CODE) ib_amp_ru_Port1_init( Rte_Instance Rte_self );

extern Std_ReturnType Rte_Write_pt_Port1_response_param( Rte_Instance Rte_self, dt_response_param p_response_param );
extern Std_ReturnType Rte_Read_pt_Port1_response_param( Rte_Instance Rte_self, dt_response_param * response_param );
FUNC(void,RTE_APPL_CODE) ib_amp_ru_Port1_response_param( Rte_Instance Rte_self );


#endif 
