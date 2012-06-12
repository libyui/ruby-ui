#include <yui/YWidgetID.h>

#include "widget.h"
#include "widget_object_map.h"
#include "ruby_value_widget_id.h"

static void
dealloc(YWidget *wg)
{
  std::cout << "destroy widget" << std::endl;
}

VALUE
ui_wrap_widget(YWidget *dlg)
{
  return Data_Wrap_Struct(cUIWidget, NULL, dealloc, dlg);
}

static YWidget *
ui_unwrap_widget(VALUE wdg)
{
  YWidget *ptr = 0L;
  Data_Get_Struct (wdg, YWidget, ptr);
  if (!ptr) 
    rb_raise(rb_eRuntimeError, "Widget was already destroyed!");
  return ptr;
}

VALUE
each_child(VALUE self)
{
    YWidget *ptr = ui_unwrap_widget(self);
    
    for (YWidgetListConstIterator it = ptr->childrenBegin();
         it != ptr->childrenEnd();
         ++it) {
      YWidget *ptr = *it;
      rb_yield(widget_object_map_for(ptr));
      //std::cout << *it << std::endl;
    }
    return Qnil;
}

VALUE
children_count(VALUE self)
{
    YWidget *ptr = ui_unwrap_widget(self);
    return INT2NUM(ptr->childrenCount());
}

/** 
 * @return [Object] Widget's id
 */
VALUE
id(VALUE self)
{
    YWidget *ptr = ui_unwrap_widget(self);
    RubyValueWidgetID *id = dynamic_cast<RubyValueWidgetID *>(ptr->id());
    return id ? id->rubyValue() : Qnil;
}

VALUE
set_id(VALUE self, VALUE id)
{
    YWidget *ptr = ui_unwrap_widget(self);
    ptr->setId(new RubyValueWidgetID(id));
    return id;
}

VALUE
has_id(VALUE self)
{
    YWidget *ptr = ui_unwrap_widget(self);
    return ptr->hasId() ? Qtrue : Qfalse;
}

VALUE
is_valid(VALUE self)
{
    YWidget *ptr = ui_unwrap_widget(self);
    return ptr->isValid() ? Qtrue : Qfalse;
}

VALUE
find_widget(VALUE self, VALUE id)
{
  YWidget *ptr = ui_unwrap_widget(self);
  YWidgetID *idPtr = new RubyValueWidgetID(id);
  YWidget * retPtr = ptr->findWidget(idPtr, false);
  //yuiDebug() << "ptr: " << (unsigned long)  retPtr << std::endl;
  delete idPtr;
  return retPtr ? widget_object_map_for(idPtr) : Qnil;
}

VALUE
to_s(VALUE self)
{
    YWidget *ptr = ui_unwrap_widget(self);
    return rb_str_new2(ptr->debugLabel().c_str());
}

VALUE cUIWidget;
void init_ui_widget()
{
  VALUE ui = rb_define_module("UI");

  VALUE klass = rb_define_class_under(ui, "Widget", rb_cObject);
  cUIWidget = klass;

  // Document-Method: id
  //rb_define_method(klass, "to_s", C_FUNC(to_s), 0);
  rb_define_method(klass, "id", C_FUNC(id), 0);
  rb_define_method(klass, "id=", C_FUNC(set_id), 1);
  rb_define_method(klass, "has_id?", C_FUNC(has_id), 0);
  rb_define_method(klass, "each_child", C_FUNC(each_child), 0);
  rb_define_method(klass, "children_count", C_FUNC(children_count), 0);
  rb_define_method(klass, "valid?", C_FUNC(is_valid), 0);
  rb_define_method(klass, "find_widget", C_FUNC(find_widget), 1);
}

