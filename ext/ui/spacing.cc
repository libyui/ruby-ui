#include "widget.h"
#include "spacing.h"

static void
dealloc(YSpacing *btn)
{
  
}

VALUE
ui_wrap_spacing(YSpacing *lbl)
{
  return Data_Wrap_Struct(cUISpacing, NULL, dealloc, lbl);
}

VALUE cUISpacing;
void init_ui_spacing()
{
  VALUE ui = rb_define_module("UI");

  VALUE klass = rb_define_class_under(ui, "Spacing", cUIWidget);
  cUISpacing = klass;
}

