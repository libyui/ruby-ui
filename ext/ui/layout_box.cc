#include "widget.h"
#include "layout_box.h"

static void
dealloc(YLayoutBox *wg)
{
  widget_object_map_remove(wg);
}

VALUE
ui_wrap_layout_box(YLayoutBox *dlg)
{
  return Data_Wrap_Struct(cUILayoutBox, ui_widget_mark, dealloc, dlg);
}

VALUE cUILayoutBox;
void init_ui_layout_box()
{
  VALUE ui = rb_define_module("UI");

  VALUE klass = rb_define_class_under(ui, "LayoutBox", cUIWidget);
  cUILayoutBox = klass;  
}