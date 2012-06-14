#include "widget.h"
#include "spacing.h"

static void
dealloc(YSpacing *spc)
{
  widget_object_map_remove(spc);
}

static void
mark(YSpacing *spc)
{
  ui_widget_mark(spc);
}

VALUE
ui_wrap_spacing(YSpacing *spc)
{
  return Data_Wrap_Struct(cUISpacing, mark, dealloc, spc);
}

VALUE cUISpacing;
void init_ui_spacing()
{
  VALUE ui = rb_define_module("UI");

  VALUE klass = rb_define_class_under(ui, "Spacing", cUIWidget);
  cUISpacing = klass;
}

