#include "widget.h"
#include "label.h"

static void
dealloc(YLabel *lbl)
{
  widget_object_map_remove(lbl);
}

static void
mark(YLabel *lbl)
{
  ui_widget_mark(lbl);
}

VALUE
ui_wrap_label(YLabel *lbl)
{
  return Data_Wrap_Struct(cUILabel, mark, dealloc, lbl);
}

VALUE cUILabel;
void init_ui_label()
{
  VALUE ui = rb_define_module("UI");

  VALUE klass = rb_define_class_under(ui, "Label", cUIWidget);
  cUILabel = klass;
}

