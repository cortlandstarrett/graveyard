.invoke base_arch_prefix = get_base_arch_prefix_name()
/*
 * Statically allocate space for the instance population for this class.
 * Allocate space for the class instance and its attribute values.
 * Depending upon the collection scheme, allocate containoids (collection
 * nodes) for gathering instances into free and active extents.
 */
.invoke objExtent = fx_get_object_extent_size(te_class)
.if (objExtent.result == true)
    .assign max_size_value = objExtent.max_size_value
    .if ( "$r{objExtent.include_file}" != "")
#include "${objExtent.include_file}"	/* ${max_size_value} is defined in this file */
    .end if
#define ${te_class.GeneratedName}_MAX_EXTENT_SIZE ${max_size_value}
.else
#define ${te_class.GeneratedName}_MAX_EXTENT_SIZE ${te_class.MaxExtentSize}
.end if

static ${te_set.scope}${te_extent.type} ${te_class.GeneratedName}_class_info;

static ${te_set.scope}${te_set.element_type} * ${te_class.GeneratedName}_container;
static ${te_class.GeneratedName} * ${te_class.GeneratedName}_instance;

/******************************************************************************
 * Initialize object factory services.
 *****************************************************************************/
#include "sys_mechs.h"
void ${te_class.GeneratedName}_FactoryInit()
{
    ${te_class.GeneratedName}_container = (${te_set.scope}${te_set.element_type} *)malloc(sizeof(${te_set.scope}${te_set.element_type}*${te_class.GeneratedName}_MAX_EXTENT_SIZE);
    ${te_class.GeneratedName}_instance = (${te_class.GeneratedName} *)malloc(sizeof(${te_class.GeneratedName}*${te_class.GeneratedName}_MAX_EXTENT_SIZE);

    ${te_class.GeneratedName}_class_info.active.head = NULL;
    ${te_class.GeneratedName}_class_info.inactive.head = NULL;
    ${te_class.GeneratedName}_class_info.container = ${te_class.GeneratedName}_container;
    ${te_class.GeneratedName}_class_info.pool = (${te_instance.handle})${te_class.GeneratedName}_instance;
    ${te_class.GeneratedName}_class_info.size = sizeof(${te_class.GeneratedName});
    ${te_class.GeneratedName}_class_info.initial_state = 1;
    ${te_class.GeneratedName}_class_info.population = ${te_class.GeneratedName}_MAX_EXTENT_SIZE;

    ${base_arch_prefix.result}_ClassFactoryInit(&${te_class.GeneratedName}_class_info);

}
.//
