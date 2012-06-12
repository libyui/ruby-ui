#ifndef UI_WIDGET_OBJECT_MAP_H
#define UI_WIDGET_OBJECT_MAP_H

#include "ruby.h"

/**
 * initializes the object map
 */
void widget_object_map_init();

void widget_object_map_add(const void* ptr, VALUE object);

VALUE widget_object_map_for(const void* ptr);

void widget_object_map_remove(const void* ptr);

#endif
