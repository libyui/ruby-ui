#include "widget.h"
#include "exception_guard.h"
#include "radio_button_group.h"
#include "radio_button.h"

static void
dealloc(YRadioButton *btn)
{
  widget_object_map_remove(btn);
}

VALUE
ui_wrap_radio_button(YRadioButton *btn)
{
  return Data_Wrap_Struct(cUIRadioButton, ui_widget_mark, dealloc, btn);
}

YRadioButton *
ui_unwrap_radio_button(VALUE btn)
{
  YRadioButton *ptr = 0L;
  Data_Get_Struct(btn, YRadioButton, ptr);
  return ptr;
}

/**
 * @return [RadioButtonGroup] the radio button group this button belongs to.
 */
VALUE
get_button_group(VALUE self)
{
  YEXCEPTION_TRY
  YRadioButton *ptr = ui_unwrap_radio_button(self);
  YRadioButtonGroup *grp = ptr->buttonGroup();
  return widget_object_map_for(grp);
  YEXCEPTION_CATCH
}

/**
 * @return [Boolean] Current on/off value:
 *   'true' if checked, 'false' if unchecked.
 */
static VALUE
get_value(VALUE self)
{
  YEXCEPTION_TRY
  YRadioButton *ptr = ui_unwrap_radio_button(self);
  return ptr->value() ? Qtrue : Qfalse;
  YEXCEPTION_CATCH
}

/**
 * Set the radio button value (on/off)
 */
static VALUE
set_value(VALUE self, VALUE val)
{
  YEXCEPTION_TRY
  YRadioButton *ptr = ui_unwrap_radio_button(self);
  ptr->setValue(RTEST(val));
  YEXCEPTION_CATCH
}

/**
 * @return [String] the label (the text on the RadioButton)
 */
static VALUE
get_label(VALUE self)
{
  YEXCEPTION_TRY
  YRadioButton *ptr = ui_unwrap_radio_button(self);
  return rb_str_new2(ptr->label().c_str());
  YEXCEPTION_CATCH
}

/**
 * Set the label (the text on the RadioButton).
 */
static VALUE
set_label(VALUE self, VALUE label)
{
  YEXCEPTION_TRY
  YRadioButton *ptr = ui_unwrap_radio_button(self);
  ptr->setLabel(StringValueCStr(label));
  YEXCEPTION_CATCH
}

/**
 * @return [Boolean] true if a bold font should be used
 */
static VALUE
get_use_bold_font(VALUE self)
{
  YEXCEPTION_TRY
  YRadioButton *ptr = ui_unwrap_radio_button(self);
  return ptr->useBoldFont() ? Qtrue : Qfalse;
  YEXCEPTION_CATCH
}

/**
 * Indicate whether or not a bold font should be used.
 */
static VALUE
set_use_bold_font(VALUE self, VALUE use)
{
  YEXCEPTION_TRY
  YRadioButton *ptr = ui_unwrap_radio_button(self);
  ptr->setUseBoldFont(RTEST(use));
  YEXCEPTION_CATCH
}

VALUE cUIRadioButton;
void init_ui_radio_button()
{
  VALUE ui = rb_define_module("UI");

  VALUE klass = rb_define_class_under(ui, "RadioButton", cUIWidget);
  rb_define_method(klass, "button_group", RUBY_METHOD_FUNC(get_button_group), 0);
  rb_define_method(klass, "value", RUBY_METHOD_FUNC(get_value), 0);
  rb_define_method(klass, "value=", RUBY_METHOD_FUNC(set_value), 1);
  rb_define_method(klass, "label", RUBY_METHOD_FUNC(get_label), 0);
  rb_define_method(klass, "label=", RUBY_METHOD_FUNC(set_label), 1);
  rb_define_method(klass, "use_bold_font?", RUBY_METHOD_FUNC(get_use_bold_font), 0);
  rb_define_method(klass, "use_bold_font=", RUBY_METHOD_FUNC(set_use_bold_font), 1);
  cUIRadioButton = klass;

}

