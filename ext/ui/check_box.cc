#include "widget.h"
#include "check_box.h"
#include "exception_guard.h"

static void
dealloc(YCheckBox *box)
{
  widget_object_map_remove(box);
}

VALUE
ui_wrap_check_box(YCheckBox *box)
{
  return Data_Wrap_Struct(cUICheckBox, ui_widget_mark, dealloc, box);
}

static YCheckBox *
ui_unwrap_check_box(VALUE box)
{
  YCheckBox *ptr = 0L;
  Data_Get_Struct(box, YCheckBox, ptr);
  return ptr;
}

/**
 * @return [Boolean] Current on/off value:
 *   +true+ if checked, +false+ if unchecked.
 *   +nil+ if don't care (tri-state)
 */
static VALUE
get_value(VALUE self)
{
  YEXCEPTION_TRY
  YCheckBox *ptr = ui_unwrap_check_box(self);
  switch(ptr->value())
  {
    case YCheckBox_on:
      return Qtrue;
    case  YCheckBox_off:
      return Qfalse;
    default:
      return Qnil;
  }
  YEXCEPTION_CATCH
}

/**
  * Get the current value:
  * @return [Boolean] true if CheckBox is checked
  * @return [Boolean] false if CheckBox is unchecked
  * @return [nil] tri-state: CheckBox is greyed out,
  *  neither checked nor unchecked
  *
  * The user cannot set the 3rd state directly. This status is always
  * only set from the outside, usually because a setting cannot be clearly
  * determined. For example, a checkbox
  *
  *     [ ] Read only
  *
  * would be set to "don't care" (by the application, not directly by the
  * user) when it is to display the read-only state of a group of files
  * where some are read-only and some are writeable.
  *
  */
static VALUE
set_value(VALUE self, VALUE val)
{
  YEXCEPTION_TRY
  YCheckBox *ptr = ui_unwrap_check_box(self);
  if (NIL_P(val)) {
    ptr->setValue(YCheckBox_dont_care);
  }
  else {
    ptr->setValue(RTEST(val) ? YCheckBox_on : YCheckBox_off);
  }
  YEXCEPTION_CATCH
}

/**
 * @return [String] the label (the text on the CheckBox)
 */
static VALUE
get_label(VALUE self)
{
  YEXCEPTION_TRY
  YCheckBox *ptr = ui_unwrap_check_box(self);
  return rb_str_new2(ptr->label().c_str());
  YEXCEPTION_CATCH
}

/**
 * Set the label (the text on the CheckBox).
 */
static VALUE
set_label(VALUE self, VALUE label)
{
  YEXCEPTION_TRY
  YCheckBox *ptr = ui_unwrap_check_box(self);
  ptr->setLabel(StringValueCStr(label));
  YEXCEPTION_CATCH
}

/**
 * @return [Boolean] true if a bold font should be used.
 */
static VALUE
get_use_bold_font(VALUE self)
{
  YEXCEPTION_TRY
  YCheckBox *ptr = ui_unwrap_check_box(self);
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
  YCheckBox *ptr = ui_unwrap_check_box(self);
  ptr->setUseBoldFont(RTEST(use));
  YEXCEPTION_CATCH
}

/**
 * Simplified access to value()
 * @return [Boolean] true if the CheckBox is checked.
 */
static VALUE
get_checked(VALUE self)
{
  YEXCEPTION_TRY
  YCheckBox *ptr = ui_unwrap_check_box(self);
  return ptr->isChecked() ? Qtrue : Qfalse;
  YEXCEPTION_CATCH
}

/**
 * Simplified access to setValue(): Check of uncheck the CheckBox.
 */
static VALUE
set_checked(VALUE self, VALUE checked)
{
  YEXCEPTION_TRY
  YCheckBox *ptr = ui_unwrap_check_box(self);
  ptr->setChecked(RTEST(checked));
  YEXCEPTION_CATCH
}


/**
 * Simplified access to tri-state ("don't care").
 * @return [Boolean] true if the CheckBox is "don't care".
 */
static VALUE
get_dont_care(VALUE self)
{
  YEXCEPTION_TRY
  YCheckBox *ptr = ui_unwrap_check_box(self);
  return ptr->dontCare() ? Qtrue : Qfalse;
  YEXCEPTION_CATCH
}

/**
 * Simplified access to setting tri-state ("don't care").
 */
static VALUE
set_dont_care(VALUE self)
{
  YEXCEPTION_TRY
  YCheckBox *ptr = ui_unwrap_check_box(self);
  ptr->setDontCare();
  YEXCEPTION_CATCH
}

VALUE cUICheckBox;
void init_ui_check_box()
{
  VALUE ui = rb_define_module("UI");

  VALUE klass = rb_define_class_under(ui, "CheckBox", cUIWidget);
  rb_define_method(klass, "value", RUBY_METHOD_FUNC(get_value), 0);
  rb_define_method(klass, "value=", RUBY_METHOD_FUNC(set_value), 1);
  rb_define_method(klass, "label", RUBY_METHOD_FUNC(get_label), 0);
  rb_define_method(klass, "label=", RUBY_METHOD_FUNC(set_label), 1);
  rb_define_method(klass, "use_bold_font?", RUBY_METHOD_FUNC(get_use_bold_font), 0);
  rb_define_method(klass, "use_bold_font=", RUBY_METHOD_FUNC(set_use_bold_font), 1);
  rb_define_method(klass, "checked?", RUBY_METHOD_FUNC(get_checked), 0);
  rb_define_method(klass, "checked=", RUBY_METHOD_FUNC(set_checked), 1);
  rb_define_method(klass, "dont_care?", RUBY_METHOD_FUNC(get_dont_care), 0);
  rb_define_method(klass, "dont_care!", RUBY_METHOD_FUNC(set_dont_care), 0);
  cUICheckBox = klass;

}

