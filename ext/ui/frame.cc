#include "widget.h"
#include "frame.h"

static void
dealloc(YFrame *frame)
{
  widget_object_map_remove(frame);
}

VALUE
ui_wrap_frame(YFrame *frame)
{
  return Data_Wrap_Struct(cUIFrame, ui_widget_mark, dealloc, frame);
}

VALUE cUIFrame;
void init_ui_frame()
{
  VALUE ui = rb_define_module("UI");

  VALUE klass = rb_define_class_under(ui, "Frame", cUIWidget);
  cUIFrame = klass;
}

