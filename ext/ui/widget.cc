#include <yui/YWidgetID.h>

#include "widget.h"
#include "ruby_value_widget_id.h"

static void
dealloc(YWidget *wg)
{

}

VALUE
ui_wrap_widget(YWidget *dlg)
{
  return Data_Wrap_Struct(cUIWidget, NULL, dealloc, dlg);
}


/** 
 * @return [Object] Widget's id
 */
VALUE
id(VALUE self)
{
    YWidget *ptr = 0L;
    Data_Get_Struct(self, YWidget, ptr);
    RubyValueWidgetID *id = dynamic_cast<RubyValueWidgetID *>(ptr->id());
    return id ? id->rubyValue() : Qnil;
}

VALUE
set_id(VALUE self, VALUE id)
{
    YWidget *ptr = 0L;
    Data_Get_Struct(self, YWidget, ptr);
    ptr->setId(new RubyValueWidgetID(id));
    return id;
}

VALUE
has_id(VALUE self)
{
    YWidget *ptr = 0L;
    Data_Get_Struct(self, YWidget, ptr);
    return ptr->hasId() ? Qtrue : Qfalse;
}


VALUE cUIWidget;
void init_ui_widget()
{
  VALUE ui = rb_define_module("UI");

  VALUE klass = rb_define_class_under(ui, "Widget", rb_cObject);
  cUIWidget = klass;

  // Document-Method: id
  rb_define_method(klass, "id", (ruby_method_vararg *) id, 0);
  rb_define_method(klass, "id=", C_FUNC(set_id), 1);
  rb_define_method(klass, "has_id?", C_FUNC(has_id), 0);
}

