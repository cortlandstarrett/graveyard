/*----------------------------------------------------------------------------
 * File:  driver_switch_class.c
 *
 * Class:       switch  (switch)
 * Component:   driver
 *
 * your copyright statement can go here (from te_copyright.body)
 *--------------------------------------------------------------------------*/

#include "swap_sys_types.h"
#include "LOG_bridge.h"
#include "driver_classes.h"


/*
 * Statically allocate space for the instance population for this class.
 * Allocate space for the class instance and its attribute values.
 * Depending upon the collection scheme, allocate containoids (collection
 * nodes) for gathering instances into free and active extents.
 */
static Escher_SetElement_s driver_switch_container[ driver_switch_MAX_EXTENT_SIZE ];
static driver_switch driver_switch_instances[ driver_switch_MAX_EXTENT_SIZE ];
Escher_Extent_t pG_driver_switch_extent = {
  {0}, {0}, &driver_switch_container[ 0 ],
  (Escher_iHandle_t) &driver_switch_instances,
  sizeof( driver_switch ), 0, driver_switch_MAX_EXTENT_SIZE
  };


