#include "widget.h"
#include "progress_bar.h"
#include "exception_guard.h"

static void
dealloc(YProgressBar *rich)
{
  widget_object_map_remove(rich);
}

VALUE
ui_wrap_progress_bar(YProgressBar *rich)
{
  return Data_Wrap_Struct(cUIProgressBar, ui_widget_mark, dealloc, rich);
}

YProgressBar *
ui_unwrap_progress_bar(VALUE bar)
{
  YProgressBar *ptr = 0L;
  Data_Get_Struct(bar, YProgressBar, ptr);
  return ptr;
}

/*
 * @return [Fixnum] the current progress value
 */
VALUE
value(VALUE self)
{
  YEXCEPTION_TRY
  YProgressBar *ptr = ui_unwrap_progress_bar(self);
  return INT2NUM(ptr->value());
  YEXCEPTION_CATCH
}

/*
 * Set the current progress value
 * @param [Fixnum] val value to set (<= max_value)
 */
VALUE
set_value(VALUE self, VALUE val)
{
  YEXCEPTION_TRY
  YProgressBar *ptr = ui_unwrap_progress_bar(self);
  ptr->setValue(NUM2INT(val));
  YEXCEPTION_CATCH
}

/*
 * @return [Fixnum] The maximum progress value.
 *  @note this value can only be set at creation time
 */
VALUE
max_value(VALUE self)
{
  YEXCEPTION_TRY
  YProgressBar *ptr = ui_unwrap_progress_bar(self);
  return INT2NUM(ptr->maxValue());
  YEXCEPTION_CATCH
}


VALUE cUIProgressBar;
void init_ui_progress_bar()
{
  VALUE ui = rb_define_module("UI");

  VALUE klass = rb_define_class_under(ui, "ProgressBar", cUIWidget);
  cUIProgressBar = klass;

  rb_define_method(klass, "value", RUBY_METHOD_FUNC(value), 0);
  rb_define_method(klass, "value=", RUBY_METHOD_FUNC(set_value), 1);
  rb_define_method(klass, "max_value", RUBY_METHOD_FUNC(max_value), 0);
}

