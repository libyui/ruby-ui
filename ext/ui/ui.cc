#include <stdio.h>

#include <deque>
#include <string>

#include <yui/YUI.h>
#include <yui/YWidgetFactory.h>
#include <yui/YApplication.h>
#include <yui/YMacro.h>
#include <yui/YMacroRecorder.h>

#include "widget_object_map.h"

#include "event.h"
#include "exception_guard.h"
#include "ui.h"
#include "widget.h"
#include "alignment.h"
#include "dialog.h"
#include "frame.h"
#include "check_box.h"
#include "input_field.h"
#include "layout_box.h"
#include "label.h"
#include "progress_bar.h"
#include "push_button.h"
#include "radio_button.h"
#include "radio_button_group.h"
#include "replace_point.h"
#include "rich_text.h"
#include "spacing.h"
#include "squash.h"
#include "ui_builder.h"

using std::string;

static VALUE
ask_for_existing_directory(VALUE self, VALUE start_dir, VALUE headline)
{
  YEXCEPTION_TRY
  string ret = YUI::app()->askForExistingDirectory(StringValueCStr(start_dir),
                                                   StringValueCStr(headline));
  return rb_str_new2(ret.c_str());
  YEXCEPTION_CATCH
}

static VALUE
ask_for_existing_file(VALUE self, VALUE start_with, VALUE filter, VALUE headline)
{
  YEXCEPTION_TRY
  string ret = YUI::app()->askForExistingFile(StringValueCStr(start_with),
                                              StringValueCStr(filter),
                                              StringValueCStr(headline));
  return rb_str_new2(ret.c_str());
  YEXCEPTION_CATCH
}

static VALUE
ask_for_save_file_name(VALUE self, VALUE start_with, VALUE filter, VALUE headline)
{
  YEXCEPTION_TRY
  string ret = YUI::app()->askForSaveFileName(StringValueCStr(start_with),
                                              StringValueCStr(filter),
                                              StringValueCStr(headline));
  return rb_str_new2(ret.c_str());
  YEXCEPTION_CATCH
}

static VALUE
busy_cursor(VALUE self)
{
  YEXCEPTION_TRY
  YUI::app()->busyCursor();
  YEXCEPTION_CATCH
  return Qnil;
}

static VALUE
normal_cursor(VALUE self)
{
  YEXCEPTION_TRY
  YUI::app()->normalCursor();
  YEXCEPTION_CATCH
  return Qnil;
}

static VALUE
beep(VALUE self)
{
  YEXCEPTION_TRY
  YUI::app()->beep();
  YEXCEPTION_CATCH
  return Qnil;
}

extern VALUE widgetObjectMap;

/*
 * @visibility private
 */
static VALUE object_map(VALUE self)
{
  return widgetObjectMap;
}

VALUE mUI;

void Init_ui() {

  mUI = rb_define_module("UI");
  rb_define_singleton_method(mUI, "object_map", RUBY_METHOD_FUNC(object_map), 0);
  rb_define_singleton_method(mUI, "ask_for_existing_directory", RUBY_METHOD_FUNC(ask_for_existing_directory), 2);
  rb_define_singleton_method(mUI, "ask_for_existing_file", RUBY_METHOD_FUNC(ask_for_existing_file), 3);
  rb_define_singleton_method(mUI, "ask_for_save_file_name", RUBY_METHOD_FUNC(ask_for_save_file_name), 3);
  rb_define_singleton_method(mUI, "busy_cursor", RUBY_METHOD_FUNC(busy_cursor), 0);
  rb_define_singleton_method(mUI, "normal_cursor", RUBY_METHOD_FUNC(normal_cursor), 0);
  rb_define_singleton_method(mUI, "beep", RUBY_METHOD_FUNC(beep), 0);

  init_ui_widget();
  init_ui_dialog();
  init_ui_check_box();
  init_ui_input_field();
  init_ui_label();
  init_ui_layout_box();
  init_ui_progress_bar();
  init_ui_push_button();
  init_ui_spacing();
  init_ui_alignment();
  init_ui_squash();
  init_ui_frame();
  init_ui_radio_button();
  init_ui_radio_button_group();
  init_ui_replace_point();
  init_ui_rich_text();

  init_ui_ui_builder();

  YUILog::enableDebugLogging();
  /* this tracks C++ objects to ruby objects */
  widget_object_map_init();
}
