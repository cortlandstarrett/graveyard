  
#ifndef RTE_TYPE_H
#define RTE_TYPE_H 

typedef unsigned char uint8;
typedef int* Rte_Instance; 
typedef unsigned char dt_xtUMLSignal;
typedef uint8 Std_ReturnType; 
typedef int dt_xtUMLInteger; 
typedef double dt_xtUMLReal; 

typedef struct {
  dt_xtUMLReal p_power;
  dt_xtUMLInteger p_size;
  dt_xtUMLReal p_weight;
} dt_response_param;
typedef struct {
  dt_xtUMLReal p_power;
  dt_xtUMLInteger p_size;
  dt_xtUMLReal p_weight;
} dt_stimulus_param;


#define RTE_APPL_CODE  /* Empty */ 

#define FUNC(ReturnType, RTE_CODE)  RTE_CODE ReturnType 


#endif

