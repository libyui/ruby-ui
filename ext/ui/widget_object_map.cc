#include "ui.h"
#include "widget_object_map.h"

// Ruby Hash to keep ptr -> value
static VALUE widgetObjectMap;


static VALUE widget_object_map_ptr_to_ref(void* ptr) {
  unsigned long value = (unsigned long) ptr;
  return LONG2NUM(value);
}

static VALUE widget_object_map_ref_to_object(VALUE reference) {
    unsigned long value = NUM2LONG(reference);
    return (VALUE) value;
}

void widget_object_map_init() {
    yuiDebug() << "object map to be initialized" << std::endl;
    widgetObjectMap = rb_hash_new();
    rb_gc_register_address(&widgetObjectMap);
}


void widget_object_map_add(void* ptr, VALUE object) {
    VALUE key = widget_object_map_ptr_to_ref(ptr);
    //yuiDebug() << "object map add: " << StringValueCStr(key) << " -> " << StringValueCStr(object) << std::endl;
    rb_hash_aset(widgetObjectMap, key, object);
}

VALUE widget_object_map_for(void* ptr) {
    VALUE key = widget_object_map_ptr_to_ref(ptr);
    return rb_hash_aref(widgetObjectMap, key);    
}

void widget_object_map_remove(void* ptr) {    
    VALUE key = widget_object_map_ptr_to_ref(ptr);
    VALUE object = widget_object_map_for(ptr);

    //yuiDebug() << "object map remove: " << StringValueCStr(key) << " -> " << StringValueCStr(object) << std::endl;

    if (object != Qnil) {
        DATA_PTR(object) = 0;
    }
        
    static VALUE delete_function = rb_intern("delete");
    rb_funcall(widgetObjectMap, delete_function, 1, key);
}

