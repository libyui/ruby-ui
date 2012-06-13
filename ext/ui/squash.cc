#include "widget.h"
#include "squash.h"

static void
dealloc(YSquash *sq)
{
  widget_object_map_remove(sq);
}

VALUE
ui_wrap_squash(YSquash *sq)
{
  return Data_Wrap_Struct(cUISquash, NULL, dealloc, sq);
}

VALUE cUISquash;
void init_ui_squash()
{
  VALUE ui = rb_define_module("UI");

  VALUE klass = rb_define_class_under(ui, "Squash", cUIWidget);
  cUISquash = klass;
}

