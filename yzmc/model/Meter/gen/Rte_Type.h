  
#ifndef RTE_TYPE_H
#define RTE_TYPE_H 

typedef unsigned char uint8;
typedef int* Rte_Instance; 
typedef unsigned char dt_xtUMLSignal;
typedef uint8 Std_ReturnType; 
typedef int dt_xtUMLInteger; 
typedef bool dt_xtUMLBoolean;
// See note in Meter_sys_types.h about these types:
//   typedef double dt_xtUMLReal;

#define RTE_CODE  /* Empty */
#define RTE_APPL_CODE  /* Empty */ 

#define FUNC(ReturnType, RTE_CODE_DEF)  RTE_CODE_DEF ReturnType


#endif

