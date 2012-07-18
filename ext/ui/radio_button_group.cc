#include "widget.h"
#include "radio_button_group.h"

static void
dealloc(YRadioButtonGroup *grp)
{
  widget_object_map_remove(grp);
}

VALUE
ui_wrap_radio_button_group(YRadioButtonGroup *grp)
{
  return Data_Wrap_Struct(cUIRadioButtonGroup, ui_widget_mark, dealloc, grp);
}

YRadioButtonGroup *
ui_unwrap_radio_button_group(VALUE group)
{
  YRadioButtonGroup *ptr = 0L;
  Data_Get_Struct(group, YRadioButtonGroup, ptr);
  return ptr;
}

VALUE cUIRadioButtonGroup;
void init_ui_radio_button_group()
{
  VALUE ui = rb_define_module("UI");

  VALUE klass = rb_define_class_under(ui, "RadioButtonGroup", cUIWidget);
  cUIRadioButtonGroup = klass;
}