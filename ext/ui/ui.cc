#include <stdio.h>

#include <yui/YUI.h>
#include <yui/YWidgetFactory.h>

#include "ui.h"
#include "widget.h"
#include "dialog.h"
#include "push_button.h"
#include "layout_box.h"

VALUE mUI;
VALUE mUIBuilder;

static VALUE create_popup_dialog(VALUE self)
{
  YDialog *dlg = YUI::widgetFactory()->createPopupDialog();
  return ui_wrap_dialog(dlg);
}

static VALUE create_push_button(VALUE self, VALUE parent, VALUE text)
{
  YWidget *ptr = NULL;
  Data_Get_Struct(parent, YWidget, ptr);

  YPushButton *btn = YUI::widgetFactory()->createPushButton(ptr, StringValuePtr(text));
  return ui_wrap_push_button(btn);
}

static VALUE create_vbox(VALUE self, VALUE parent)
{
  YWidget *ptr = NULL;
  Data_Get_Struct(parent, YWidget, ptr);

  YLayoutBox *box = YUI::widgetFactory()->createVBox(ptr);
  return ui_wrap_layout_box(box);
}

static VALUE create_hbox(VALUE self, VALUE parent)
{
  YWidget *ptr = NULL;
  Data_Get_Struct(parent, YWidget, ptr);

  YLayoutBox *box = YUI::widgetFactory()->createHBox(ptr);
  return ui_wrap_layout_box(box);
}

extern "C" {

void Init_ui() {
  mUI = rb_define_module("UI");
  mUIBuilder = rb_define_module_under(mUI, "Builder");

  init_ui_widget();
  init_ui_layout_box();
  init_ui_dialog();
  init_ui_push_button();

  rb_define_singleton_method(mUIBuilder, "create_popup_dialog", C_FUNC(create_popup_dialog), 0);
  rb_define_singleton_method(mUIBuilder, "create_push_button", C_FUNC(create_push_button), 2);
  rb_define_singleton_method(mUIBuilder, "create_hbox", C_FUNC(create_hbox), 1);
  rb_define_singleton_method(mUIBuilder, "create_vbox", C_FUNC(create_vbox), 1);
}

}