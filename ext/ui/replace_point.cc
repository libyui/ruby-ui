#include "widget.h"
#include "replace_point.h"

static void
dealloc(YReplacePoint *wg)
{
  widget_object_map_remove(wg);
}

VALUE
ui_wrap_replace_point(YReplacePoint *dlg)
{
  return Data_Wrap_Struct(cUIReplacePoint, ui_widget_mark, dealloc, dlg);
}

YReplacePoint *
ui_unwrap_replace_point(VALUE point)
{
  YReplacePoint *ptr = 0L;
  Data_Get_Struct(point, YReplacePoint, ptr);
  return ptr;
}

VALUE cUIReplacePoint;
void init_ui_replace_point()
{
  VALUE ui = rb_define_module("UI");

  VALUE klass = rb_define_class_under(ui, "ReplacePoint", cUIWidget);
  cUIReplacePoint = klass;
}