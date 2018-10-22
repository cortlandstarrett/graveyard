/*----------------------------------------------------------------------------------------------
* File:  Rte_co_amp.h
*
* VFB generated file
*
* Please Remove this file if you need to make this project portable to VSI project ( with RTE )
*
*-----------------------------------------------------------------------------------------------*/


  
#ifndef RTE_CO_AMP_H
#define RTE_CO_AMP_H

#include "swap_sys_types.h"
#include "Rte_co_driver.h"

extern Std_ReturnType Rte_Write_pt_Port1_stimulus_param( Rte_Instance Rte_self, dt_stimulus_param p_stimulus_param );
extern Std_ReturnType Rte_Read_pt_Port1_stimulus_param( Rte_Instance Rte_self, dt_stimulus_param * p_stimulus_param );
FUNC(void,RTE_APPL_CODE) ib_driver_ru_Port1_stimulus_param( Rte_Instance Rte_self );

#endif 
