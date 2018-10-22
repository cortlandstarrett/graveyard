  
/*---------------------------------------------------------------------------------------------- 
* File:  amp_vfb.c 
*
* VFB generated file 
*
* Please Remove this file if you need to make this project portable to VSI project ( with RTE ) 
*
*-----------------------------------------------------------------------------------------------*/ 


#include "Rte_co_amp.h"  

#ifdef AUTOSAR_ENABLED

static dt_stimulus_param amp_stimulus_param;
  
Std_ReturnType Rte_Write_pt_Port1_stimulus_param( Rte_Instance Rte_self, dt_stimulus_param p_stimulus_param )
{
  amp_stimulus_param.p_size = p_stimulus_param.p_size;
  amp_stimulus_param.p_weight = p_stimulus_param.p_weight;
  amp_stimulus_param.p_power = p_stimulus_param.p_power;
  ib_driver_ru_Port1_stimulus_param( Rte_self );
  return 0;
}

Std_ReturnType Rte_Read_pt_Port1_stimulus_param( Rte_Instance Rte_self, dt_stimulus_param * p_stimulus_param )
{
  *p_stimulus_param = amp_stimulus_param;
  return 0;
}
extern void Escher_xtUMLmain( void );
int main( int argc, char ** argv )
{
  Escher_xtUMLmain();
  return 0;
}

#endif
