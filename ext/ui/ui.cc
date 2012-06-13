#include <stdio.h>

#include <deque>

#include <yui/YUI.h>
#include <yui/YWidgetFactory.h>
#include <yui/YApplication.h>
#include <yui/YMacro.h>
#include <yui/YMacroRecorder.h>

#include "widget_object_map.h"

#include "event.h"
#include "ui.h"
#include "widget.h"
#include "dialog.h"
#include "input_field.h"
#include "layout_box.h"
#include "label.h"
#include "push_button.h"
#include "rich_text.h"
#include "spacing.h"
#include "squash.h"
#include "ui_builder.h"

VALUE mUI;

/*
 * Document-module UI
 */

/*
 * Open a directory selection box and prompt the user for an existing
 * directory.
 *
 * @param [String] start_dir the initial directory that is displayed.
 * @param [String] headline an explanatory text for the directory selection box.
 *
 * @returns the selected directory name
 *   or an empty string if the user canceled the operation.
 */
static VALUE
ask_for_existing_directory(VALUE self, VALUE start_dir, VALUE headline)
{
  string ret = YUI::app()->askForExistingDirectory(StringValueCStr(start_dir),
                                                   StringValueCStr(headline));
  return rb_str_new2(ret.c_str());
}

/*
 * Open a file selection box and prompt the user for an existing file.
 *
 * @param [String] start_with is the initial directory or file.
 * @param [String] filter one or more blank-separated file patterns, e.g.
 *   "*.png *.jpg"
 * @param [String] headline' an explanatory text for the file selection box.
 *
 * @return [String] the selected file name
 *   or an empty string if the user canceled the operation.
 **/
static VALUE
ask_for_existing_file(VALUE self, VALUE start_with, VALUE filter, VALUE headline)
{
  string ret = YUI::app()->askForExistingFile(StringValueCStr(start_with),
                                              StringValueCStr(filter),
                                              StringValueCStr(headline));
  return rb_str_new2(ret.c_str());
}

/*
 * Open a file selection box and prompt the user for a file to save data
 * to.  Automatically asks for confirmation if the user selects an existing
 * file.
 *
 * @param [String] start_with is the initial directory or file.
 * @param [String] filter one or more blank-separated file patterns, e.g.
 *   "*.png *.jpg"
 * @param [String] headline' an explanatory text for the file selection box.
 *
 * @return [String] the selected file name
 *   or an empty string if the user canceled the operation.
 **/
static VALUE
ask_for_save_file_name(VALUE self, VALUE start_with, VALUE filter, VALUE headline)
{
  string ret = YUI::app()->askForSaveFileName(StringValueCStr(start_with),
                                              StringValueCStr(filter),
                                              StringValueCStr(headline));
  return rb_str_new2(ret.c_str());
}

extern VALUE widgetObjectMap;

/*  
 * @visibility private
 */
static VALUE object_map(VALUE self)
{
  return widgetObjectMap;
}

extern "C" {

void __attribute__ ((visibility("default"))) Init_ui() {

  YUILog::enableDebugLogging();

  /* this tracks C++ objects to ruby objects */
  widget_object_map_init();

  mUI = rb_define_module("UI");

  rb_define_singleton_method(mUI, "object_map", RUBY_METHOD_FUNC(object_map), 0);
  rb_define_singleton_method(mUI, "ask_for_existing_directory", RUBY_METHOD_FUNC(ask_for_existing_directory), 2);
  rb_define_singleton_method(mUI, "ask_for_existing_file", RUBY_METHOD_FUNC(ask_for_existing_file), 3);
  rb_define_singleton_method(mUI, "ask_for_save_file_name", RUBY_METHOD_FUNC(ask_for_save_file_name), 3);

  init_ui_widget();
  init_ui_dialog();
  init_ui_input_field();  
  init_ui_label();
  init_ui_layout_box();
  init_ui_push_button();
  init_ui_spacing();
  init_ui_squash();
  init_ui_rich_text();
  
  init_ui_ui_builder();
}

}