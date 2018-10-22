/*----------------------------------------------------------------------------
 * File:  amp.h
 *
 * UML Component (Module) Declaration (Operations and Signals)
 *
 * your copyright statement can go here (from te_copyright.body)
 *--------------------------------------------------------------------------*/

#ifndef AMP_H
#define AMP_H
#ifdef	__cplusplus
extern	"C"	{
#endif

#include "swap_sys_types.h"
void amp_Port1_init( void );
void amp_Port1_response( const dt_xtUMLReal, const dt_xtUMLInteger, const dt_xtUMLReal );
void amp_Port1_stimulus( const dt_xtUMLReal, const dt_xtUMLInteger, const dt_xtUMLReal );


#ifdef	__cplusplus
}
#endif
#endif  /* AMP_H */
