#include "widget.h"
#include "rich_text.h"

static void
dealloc(YRichText *rich)
{
  widget_object_map_remove(rich);
}

VALUE
ui_wrap_rich_text(YRichText *rich)
{
  return Data_Wrap_Struct(cUIRichText, ui_widget_mark, dealloc, rich);
}

VALUE cUIRichText;
void init_ui_rich_text()
{
  VALUE ui = rb_define_module("UI");

  VALUE klass = rb_define_class_under(ui, "RichText", cUIWidget);
  cUIRichText = klass;
}

