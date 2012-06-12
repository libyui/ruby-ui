#include "ui.h"
#include "widget_object_map.h"

// Ruby Hash to keep ptr -> value
VALUE widgetObjectMap;


static VALUE widget_object_map_ptr_to_ref(const void* ptr) {
  unsigned long value = (const unsigned long) ptr;
  return LONG2NUM(value);
}

static VALUE widget_object_map_object_to_ref(VALUE obj) {
  unsigned long value = (unsigned long) obj;
  return LONG2NUM(value);
}

void widget_object_map_init() {
    yuiDebug() << "object map to be initialized" << std::endl;
    widgetObjectMap = rb_hash_new();
    rb_gc_register_address(&widgetObjectMap);
}


void widget_object_map_add(const void* ptr, VALUE object) {
    VALUE key = widget_object_map_ptr_to_ref(ptr);
    rb_hash_aset(widgetObjectMap, key, object);
}

VALUE widget_object_map_for(const void* ptr) {
    VALUE key = widget_object_map_ptr_to_ref(ptr);
    return rb_hash_aref(widgetObjectMap, key);
}

void widget_object_map_remove(const void* ptr) {    
    VALUE key = widget_object_map_ptr_to_ref(ptr);
    VALUE object = widget_object_map_for(ptr);

    if (object != Qnil) {
        DATA_PTR(object) = 0;
    }
        
    static VALUE delete_function = rb_intern("delete");
    rb_funcall(widgetObjectMap, delete_function, 1, key);
}

