#include <stdio.h>

#include <yui/YUI.h>
#include <yui/YWidgetFactory.h>

#include "widget_object_map.h"

#include "ui.h"
#include "widget.h"
#include "dialog.h"
#include "layout_box.h"
#include "push_button.h"
#include "input_field.h"
#include "label.h"

VALUE mUI;
VALUE mUIBuilder;

static VALUE create_main_dialog(VALUE self)
{
  YDialog *dlg = YUI::widgetFactory()->createMainDialog();
  return ui_wrap_dialog(dlg);
}

static VALUE create_popup_dialog(VALUE self)
{
  YDialog *dlg = YUI::widgetFactory()->createPopupDialog();
  
  VALUE object = ui_wrap_dialog(dlg);
  widget_object_map_add(dlg, object);
  return object;
}

static VALUE create_vbox(VALUE self, VALUE parent)
{
  YWidget *ptr = NULL;
  Data_Get_Struct(parent, YWidget, ptr);

  YLayoutBox *box = YUI::widgetFactory()->createVBox(ptr);

  VALUE object = ui_wrap_layout_box(box);
  widget_object_map_add(box, object);
  return object;
}

static VALUE create_hbox(VALUE self, VALUE parent)
{
  YWidget *ptr = NULL;
  Data_Get_Struct(parent, YWidget, ptr);

  YLayoutBox *box = YUI::widgetFactory()->createHBox(ptr);

  VALUE object = ui_wrap_layout_box(box);
  widget_object_map_add(box, object);
  return object;
}

static VALUE create_push_button(VALUE self, VALUE parent, VALUE text)
{
  YWidget *ptr = NULL;
  Data_Get_Struct(parent, YWidget, ptr);

  YPushButton *btn = YUI::widgetFactory()->createPushButton(ptr, StringValuePtr(text));

  VALUE object = ui_wrap_push_button(btn);
  widget_object_map_add(btn, object);
  return object;
}

static VALUE create_label(VALUE self, VALUE parent, VALUE text)
{
  YWidget *ptr = NULL;
  Data_Get_Struct(parent, YWidget, ptr);

  YLabel *lbl = YUI::widgetFactory()->createLabel(ptr, StringValuePtr(text));
  
  VALUE object = ui_wrap_label(lbl);
  widget_object_map_add(lbl, object);
  return object;
}

static VALUE create_input_field(VALUE self, VALUE parent, VALUE text)
{
  YWidget *ptr = NULL;
  Data_Get_Struct(parent, YWidget, ptr);

  YInputField *fld = YUI::widgetFactory()->createInputField(ptr, StringValuePtr(text));

  VALUE object = ui_wrap_input_field(fld);
  widget_object_map_add(fld, object);
  return object;
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
  init_ui_layout_box();
  
  init_ui_push_button();
  init_ui_label();
  init_ui_input_field();

  rb_define_singleton_method(mUIBuilder, "create_main_dialog", C_FUNC(create_popup_dialog), 0);
  rb_define_singleton_method(mUIBuilder, "create_popup_dialog", C_FUNC(create_popup_dialog), 0);
  
  rb_define_singleton_method(mUIBuilder, "create_hbox", C_FUNC(create_hbox), 1);
  rb_define_singleton_method(mUIBuilder, "create_vbox", C_FUNC(create_vbox), 1);

  rb_define_singleton_method(mUIBuilder, "create_push_button", C_FUNC(create_push_button), 2);
  rb_define_singleton_method(mUIBuilder, "create_label", C_FUNC(create_label), 2);
  rb_define_singleton_method(mUIBuilder, "create_input_field", C_FUNC(create_input_field), 2);
}

}