#include <stdio.h>

#include <yui/YUI.h>
#include <yui/YWidgetFactory.h>

#include "widget_object_map.h"

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

VALUE mUI;
VALUE mUIBuilder;

/*
 * @visibility private
 */
static VALUE create_main_dialog(VALUE self)
{
  YDialog *dlg = YUI::widgetFactory()->createMainDialog();
  return ui_wrap_dialog(dlg);
}

/*
 * @visibility private
 */
static VALUE create_popup_dialog(VALUE self)
{
  YDialog *dlg = YUI::widgetFactory()->createPopupDialog();
  
  VALUE object = ui_wrap_dialog(dlg);
  widget_object_map_add(dlg, object);
  return object;
}

/*
 * @visibility private
 */
static VALUE create_vbox(VALUE self, VALUE parent)
{
  YWidget *ptr = NULL;
  Data_Get_Struct(parent, YWidget, ptr);

  YLayoutBox *box = YUI::widgetFactory()->createVBox(ptr);

  VALUE object = ui_wrap_layout_box(box);
  widget_object_map_add(box, object);
  return object;
}

/*
 * @visibility private
 */
static VALUE create_hbox(VALUE self, VALUE parent)
{
  YWidget *ptr = NULL;
  Data_Get_Struct(parent, YWidget, ptr);

  YLayoutBox *box = YUI::widgetFactory()->createHBox(ptr);

  VALUE object = ui_wrap_layout_box(box);
  widget_object_map_add(box, object);
  return object;
}

/*
 * @visibility private
 */
static VALUE create_push_button(VALUE self, VALUE parent, VALUE text)
{
  YWidget *ptr = NULL;
  Data_Get_Struct(parent, YWidget, ptr);

  YPushButton *btn = YUI::widgetFactory()->createPushButton(ptr, StringValuePtr(text));

  VALUE object = ui_wrap_push_button(btn);
  widget_object_map_add(btn, object);
  return object;
}

/*
 * @visibility private
 */
static VALUE create_label(VALUE self, VALUE parent, VALUE text)
{
  YWidget *ptr = NULL;
  Data_Get_Struct(parent, YWidget, ptr);

  YLabel *lbl = YUI::widgetFactory()->createLabel(ptr, StringValuePtr(text));
  
  VALUE object = ui_wrap_label(lbl);
  widget_object_map_add(lbl, object);
  return object;
}

/*
 * @visibility private
 */
static VALUE create_input_field(VALUE self, VALUE parent, VALUE text)
{
  YWidget *ptr = NULL;
  Data_Get_Struct(parent, YWidget, ptr);

  YInputField *fld = YUI::widgetFactory()->createInputField(ptr, StringValuePtr(text));

  VALUE object = ui_wrap_input_field(fld);
  widget_object_map_add(fld, object);
  return object;
}

/*
 * @visibility private
 */
static VALUE create_rich_text(VALUE self, VALUE parent, VALUE text)
{
  YWidget *ptr = NULL;
  Data_Get_Struct(parent, YWidget, ptr);

  YRichText *rich = YUI::widgetFactory()->createRichText(ptr, StringValuePtr(text));

  VALUE object = ui_wrap_rich_text(rich);
  widget_object_map_add(rich, object);
  return object;
}

/*
 * @visibility private
 */
static VALUE create_hstretch(VALUE self, VALUE parent)
{
  YWidget *ptr = NULL;
  Data_Get_Struct(parent, YWidget, ptr);

  YSpacing *spc = YUI::widgetFactory()->createHStretch(ptr);

  VALUE object = ui_wrap_spacing(spc);
  widget_object_map_add(spc, object);
  return object;
}

/*
 * @visibility private
 */
static VALUE create_vstretch(VALUE self, VALUE parent)
{
  YWidget *ptr = NULL;
  Data_Get_Struct(parent, YWidget, ptr);

  YSpacing *spc = YUI::widgetFactory()->createVStretch(ptr);

  VALUE object = ui_wrap_spacing(spc);
  widget_object_map_add(spc, object);
  return object;
}

/*
 * @visibility private
 */
static VALUE create_vspacing(VALUE self, VALUE parent)
{
  YWidget *ptr = NULL;
  Data_Get_Struct(parent, YWidget, ptr);

  YSpacing *spc = YUI::widgetFactory()->createVSpacing(ptr);

  VALUE object = ui_wrap_spacing(spc);
  widget_object_map_add(spc, object);
  return object;
}

/*
 * @visibility private
 */
static VALUE create_hspacing(VALUE self, VALUE parent)
{
  YWidget *ptr = NULL;
  Data_Get_Struct(parent, YWidget, ptr);

  YSpacing *spc = YUI::widgetFactory()->createHSpacing(ptr);

  VALUE object = ui_wrap_spacing(spc);
  widget_object_map_add(spc, object);
  return object;
}

/*
 * @visibility private
 */
static VALUE create_hsquash(VALUE self, VALUE parent)
{
  YWidget *ptr = NULL;
  Data_Get_Struct(parent, YWidget, ptr);

  YSquash *spc = YUI::widgetFactory()->createHSquash(ptr);

  VALUE object = ui_wrap_squash(spc);
  widget_object_map_add(spc, object);
  return object;
}

/*
 * @visibility private
 */
static VALUE create_vsquash(VALUE self, VALUE parent)
{
  YWidget *ptr = NULL;
  Data_Get_Struct(parent, YWidget, ptr);

  YSquash *spc = YUI::widgetFactory()->createVSquash(ptr);

  VALUE object = ui_wrap_squash(spc);
  widget_object_map_add(spc, object);
  return object;
}

/*
 * @visibility private
 */
static VALUE create_hvsquash(VALUE self, VALUE parent)
{
  YWidget *ptr = NULL;
  Data_Get_Struct(parent, YWidget, ptr);

  YSquash *spc = YUI::widgetFactory()->createHVSquash(ptr);

  VALUE object = ui_wrap_squash(spc);
  widget_object_map_add(spc, object);
  return object;
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

void Init_ui() {

  YUILog::enableDebugLogging();

  /* this tracks C++ objects to ruby objects */
  widget_object_map_init();

  mUI = rb_define_module("UI");
  mUIBuilder = rb_define_module_under(mUI, "Builder");

  init_ui_widget();
  init_ui_dialog();
  init_ui_input_field();  
  init_ui_label();
  init_ui_layout_box();
  init_ui_push_button();
  init_ui_spacing();
  init_ui_squash();
  init_ui_rich_text();
  

  rb_define_singleton_method(mUI, "object_map", RUBY_METHOD_FUNC(object_map), 0);

  rb_define_singleton_method(mUIBuilder, "create_main_dialog", RUBY_METHOD_FUNC(create_popup_dialog), 0);
  rb_define_singleton_method(mUIBuilder, "create_popup_dialog", RUBY_METHOD_FUNC(create_popup_dialog), 0);
  
  rb_define_singleton_method(mUIBuilder, "create_hbox", RUBY_METHOD_FUNC(create_hbox), 1);
  rb_define_singleton_method(mUIBuilder, "create_vbox", RUBY_METHOD_FUNC(create_vbox), 1);

  rb_define_singleton_method(mUIBuilder, "create_vstretch", RUBY_METHOD_FUNC(create_vstretch), 1);
  rb_define_singleton_method(mUIBuilder, "create_hstretch", RUBY_METHOD_FUNC(create_hstretch), 1);
  rb_define_singleton_method(mUIBuilder, "create_vspacingf", RUBY_METHOD_FUNC(create_vspacing), 1);
  rb_define_singleton_method(mUIBuilder, "create_hspacing", RUBY_METHOD_FUNC(create_hspacing), 1);

  rb_define_singleton_method(mUIBuilder, "create_hsquash", RUBY_METHOD_FUNC(create_hsquash), 1);
  rb_define_singleton_method(mUIBuilder, "create_vsquash", RUBY_METHOD_FUNC(create_vsquash), 1);
  rb_define_singleton_method(mUIBuilder, "create_hvsquash", RUBY_METHOD_FUNC(create_hvsquash), 1);
  

  rb_define_singleton_method(mUIBuilder, "create_push_button", RUBY_METHOD_FUNC(create_push_button), 2);
  rb_define_singleton_method(mUIBuilder, "create_label", RUBY_METHOD_FUNC(create_label), 2);
  rb_define_singleton_method(mUIBuilder, "create_input_field", RUBY_METHOD_FUNC(create_input_field), 2);
  rb_define_singleton_method(mUIBuilder, "create_rich_text", RUBY_METHOD_FUNC(create_rich_text), 2);
}

}