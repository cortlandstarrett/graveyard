/*----------------------------------------------------------------------------
 * File:  driver.h
 *
 * UML Component (Module) Declaration (Operations and Signals)
 *
 * your copyright statement can go here (from te_copyright.body)
 *--------------------------------------------------------------------------*/

#ifndef DRIVER_H
#define DRIVER_H
#ifdef	__cplusplus
extern	"C"	{
#endif

#include "swap_sys_types.h"
void driver_Port1_init( void );
void driver_Port1_response( const dt_xtUMLReal, const dt_xtUMLInteger, const dt_xtUMLReal );
void driver_Port1_stimulus( const dt_xtUMLReal, const dt_xtUMLInteger, const dt_xtUMLReal );


#ifdef	__cplusplus
}
#endif
#endif  /* DRIVER_H */
