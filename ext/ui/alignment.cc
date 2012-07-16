#include "widget.h"
#include "alignment.h"

static void
dealloc(YAlignment *align)
{
  widget_object_map_remove(align);
}

VALUE
ui_wrap_alignment(YAlignment*align)
{
  return Data_Wrap_Struct(cUIAlignment, ui_widget_mark, dealloc, align);
}

VALUE cUIAlignment;
void init_ui_alignment()
{
  VALUE ui = rb_define_module("UI");

  VALUE klass = rb_define_class_under(ui, "Alignment", cUIWidget);
  cUIAlignment = klass;
}

