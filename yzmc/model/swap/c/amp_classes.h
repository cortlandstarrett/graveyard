/*----------------------------------------------------------------------------
 * File:  amp_classes.h
 *
 * This file defines the object type identification numbers for all classes
 * in the component:  amp
 *
 * your copyright statement can go here (from te_copyright.body)
 *--------------------------------------------------------------------------*/

#ifndef AMP_CLASSES_H
#define AMP_CLASSES_H

#ifdef	__cplusplus
extern	"C"	{
#endif

/*
 * Initialization services for component:  amp
 */
void amp_execute_initialization( void );

/*
 * UML Domain Functions (Synchronous Services)
 */
void amp_init( void );


#include "LOG_bridge.h"
#include "amp.h"
#ifdef	__cplusplus
}
#endif
#endif  /* AMP_CLASSES_H */

