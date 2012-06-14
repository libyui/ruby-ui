#include "widget.h"
#include "input_field.h"

static void
dealloc(YInputField *fld)
{
  widget_object_map_remove(fld);
}

static void
mark(YInputField *fld)
{
  ui_widget_mark(fld);
}

VALUE
ui_wrap_input_field(YInputField *fld)
{
  return Data_Wrap_Struct(cUIInputField, mark, dealloc, fld);
}

VALUE cUIInputField;
void init_ui_input_field()
{
  VALUE ui = rb_define_module("UI");

  VALUE klass = rb_define_class_under(ui, "InputField", cUIWidget);
  cUIInputField = klass;
}

