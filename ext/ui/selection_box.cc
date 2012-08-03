#include "widget.h"
#include "exception_guard.h"
#include "selection_widget.h"
#include "selection_box.h"

static void
dealloc(YSelectionBox *box)
{
  widget_object_map_remove(box);
}

VALUE
ui_wrap_selection_box(YSelectionBox *box)
{
  return Data_Wrap_Struct(cUISelectionBox, ui_selection_widget_mark, dealloc, box);
}

YSelectionBox *
ui_unwrap_selection_box(VALUE box)
{
  YSelectionBox *ptr = 0L;
  Data_Get_Struct(box, YSelectionBox, ptr);
  return ptr;
}

VALUE cUISelectionBox;
void init_ui_selection_box()
{
  VALUE ui = rb_define_module("UI");

  VALUE klass = rb_define_class_under(ui, "SelectionBox", cUISelectionWidget);
  cUISelectionBox = klass;
}

