/*----------------------------------------------------------------------------
 * File:  driver_classes.h
 *
 * This file defines the object type identification numbers for all classes
 * in the component:  driver
 *
 * your copyright statement can go here (from te_copyright.body)
 *--------------------------------------------------------------------------*/

#ifndef DRIVER_CLASSES_H
#define DRIVER_CLASSES_H

#ifdef	__cplusplus
extern	"C"	{
#endif

/*
 * Initialization services for component:  driver
 */
extern Escher_Extent_t * const driver_class_info[];
void driver_execute_initialization( void );

#define driver_STATE_MODELS 0
/* Define constants to map to class numbers.  */
#define driver_switch_CLASS_NUMBER 0
#define driver_MAX_CLASS_NUMBERS 1

/* Provide a map of classes to task numbers.  */
#define driver_TASK_NUMBERS 

#define driver_class_dispatchers

/* Provide definitions of the shapes of the class structures.  */

typedef struct driver_switch driver_switch;

/* union of class declarations so we may derive largest class size */
#define driver_CLASS_U \
  char driver_dummy;\


#include "LOG_bridge.h"
#include "driver.h"
#include "driver_switch_class.h"
#ifdef	__cplusplus
}
#endif
#endif  /* DRIVER_CLASSES_H */

