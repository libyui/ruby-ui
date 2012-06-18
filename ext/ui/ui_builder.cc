#include <stdio.h>

#include <deque>

#include <yui/YUI.h>
#include <yui/YWidgetFactory.h>

#include "widget_object_map.h"

#include "event.h"
#include "exception_guard.h"
#include "ui.h"
#include "widget.h"
#include "dialog.h"
#include "input_field.h"
#include "layout_box.h"
#include "label.h"
#include "push_button.h"
#include "rich_text.h"
#include "replace_point.h"
#include "spacing.h"
#include "squash.h"
#include "replace_point.h"

VALUE mUIBuilder;

/*
 * @visibility private
 */
static VALUE create_main_dialog(VALUE self)
{
  YEXCEPTION_TRY
  YDialog *dlg = YUI::widgetFactory()->createMainDialog();
  return ui_wrap_dialog(dlg);
  YEXCEPTION_CATCH
}

/*
 * @visibility private
 */
static VALUE create_popup_dialog(VALUE self)
{
  YEXCEPTION_TRY
  YDialog *dlg = YUI::widgetFactory()->createPopupDialog();

  VALUE object = ui_wrap_dialog(dlg);
  widget_object_map_add(dlg, object);
  return object;
  YEXCEPTION_CATCH
}

/*
 * @visibility private
 */
static VALUE create_vbox(VALUE self, VALUE parent)
{
  YEXCEPTION_TRY
  YWidget *ptr = ui_unwrap_widget(parent);

  YLayoutBox *box = YUI::widgetFactory()->createVBox(ptr);

  VALUE object = ui_wrap_layout_box(box);
  widget_object_map_add(box, object);
  return object;
  YEXCEPTION_CATCH
}

/*
 * @visibility private
 */
static VALUE create_hbox(VALUE self, VALUE parent)
{
  YEXCEPTION_TRY
  YWidget *ptr = ui_unwrap_widget(parent);

  YLayoutBox *box = YUI::widgetFactory()->createHBox(ptr);

  VALUE object = ui_wrap_layout_box(box);
  widget_object_map_add(box, object);
  return object;
  YEXCEPTION_CATCH
}

/*
 * @visibility private
 */
static VALUE create_push_button(VALUE self, VALUE parent, VALUE text)
{
  YEXCEPTION_TRY
  YWidget *ptr = ui_unwrap_widget(parent);

  YPushButton *btn = YUI::widgetFactory()->createPushButton(ptr, StringValuePtr(text));

  VALUE object = ui_wrap_push_button(btn);
  widget_object_map_add(btn, object);
  return object;
  YEXCEPTION_CATCH
}

/*
 * @visibility private
 */
static VALUE create_label(VALUE self, VALUE parent, VALUE text)
{
  YEXCEPTION_TRY
  YWidget *ptr = ui_unwrap_widget(parent);

  YLabel *lbl = YUI::widgetFactory()->createLabel(ptr, StringValuePtr(text));

  VALUE object = ui_wrap_label(lbl);
  widget_object_map_add(lbl, object);
  return object;
  YEXCEPTION_CATCH
}

/*
 * @visibility private
 */
static VALUE create_input_field(VALUE self, VALUE parent, VALUE text)
{
  YEXCEPTION_TRY
  YWidget *ptr = ui_unwrap_widget(parent);

  YInputField *fld = YUI::widgetFactory()->createInputField(ptr, StringValuePtr(text));

  VALUE object = ui_wrap_input_field(fld);
  widget_object_map_add(fld, object);
  return object;
  YEXCEPTION_CATCH
}

/*
 * @visibility private
 */
static VALUE create_rich_text(VALUE self, VALUE parent, VALUE text)
{
  YEXCEPTION_TRY
  YWidget *ptr = ui_unwrap_widget(parent);

  YRichText *rich = YUI::widgetFactory()->createRichText(ptr, StringValuePtr(text));

  VALUE object = ui_wrap_rich_text(rich);
  widget_object_map_add(rich, object);
  return object;
  YEXCEPTION_CATCH
}

/*
 * @visibility private
 */
static VALUE create_hstretch(VALUE self, VALUE parent)
{
  YEXCEPTION_TRY
  YWidget *ptr = ui_unwrap_widget(parent);

  YSpacing *spc = YUI::widgetFactory()->createHStretch(ptr);

  VALUE object = ui_wrap_spacing(spc);
  widget_object_map_add(spc, object);
  return object;
  YEXCEPTION_CATCH
}

/*
 * @visibility private
 */
static VALUE create_vstretch(VALUE self, VALUE parent)
{
  YEXCEPTION_TRY
  YWidget *ptr = ui_unwrap_widget(parent);

  YSpacing *spc = YUI::widgetFactory()->createVStretch(ptr);

  VALUE object = ui_wrap_spacing(spc);
  widget_object_map_add(spc, object);
  return object;
  YEXCEPTION_CATCH
}

/*
 * @visibility private
 */
static VALUE create_vspacing(VALUE self, VALUE parent)
{
  YEXCEPTION_TRY
  YWidget *ptr = ui_unwrap_widget(parent);

  YSpacing *spc = YUI::widgetFactory()->createVSpacing(ptr);

  VALUE object = ui_wrap_spacing(spc);
  widget_object_map_add(spc, object);
  return object;
  YEXCEPTION_CATCH
}

/*
 * @visibility private
 */
static VALUE create_hspacing(VALUE self, VALUE parent)
{
  YEXCEPTION_TRY
  YWidget *ptr = ui_unwrap_widget(parent);

  YSpacing *spc = YUI::widgetFactory()->createHSpacing(ptr);

  VALUE object = ui_wrap_spacing(spc);
  widget_object_map_add(spc, object);
  return object;
  YEXCEPTION_CATCH
}

/*
 * @visibility private
 */
static VALUE create_hsquash(VALUE self, VALUE parent)
{
  YEXCEPTION_TRY
  YWidget *ptr = ui_unwrap_widget(parent);

  YSquash *spc = YUI::widgetFactory()->createHSquash(ptr);

  VALUE object = ui_wrap_squash(spc);
  widget_object_map_add(spc, object);
  return object;
  YEXCEPTION_CATCH
}

/*
 * @visibility private
 */
static VALUE create_vsquash(VALUE self, VALUE parent)
{
  YEXCEPTION_TRY
  YWidget *ptr = ui_unwrap_widget(parent);

  YSquash *spc = YUI::widgetFactory()->createVSquash(ptr);

  VALUE object = ui_wrap_squash(spc);
  widget_object_map_add(spc, object);
  return object;
  YEXCEPTION_CATCH
}

/*
 * @visibility private
 */
static VALUE create_hvsquash(VALUE self, VALUE parent)
{
  YEXCEPTION_TRY
  YWidget *ptr = ui_unwrap_widget(parent);

  YSquash *spc = YUI::widgetFactory()->createHVSquash(ptr);

  VALUE object = ui_wrap_squash(spc);
  widget_object_map_add(spc, object);
  return object;
  YEXCEPTION_CATCH
}

/*
 * @visibility private
 */
static VALUE create_replace_point(VALUE self, VALUE parent)
{
  YEXCEPTION_TRY
  YWidget *ptr = ui_unwrap_widget(parent);

  YReplacePoint *pnt = YUI::widgetFactory()->createReplacePoint(ptr);

  VALUE object = ui_wrap_replace_point(pnt);
  widget_object_map_add(pnt, object);
  return object;
  YEXCEPTION_CATCH
}

void init_ui_ui_builder() {

  VALUE mUI = rb_define_module("UI");
  mUIBuilder = rb_define_module_under(mUI, "Builder");

  rb_define_singleton_method(mUIBuilder, "create_main_dialog", RUBY_METHOD_FUNC(create_popup_dialog), 0);
  rb_define_singleton_method(mUIBuilder, "create_popup_dialog", RUBY_METHOD_FUNC(create_popup_dialog), 0);

  rb_define_singleton_method(mUIBuilder, "create_hbox", RUBY_METHOD_FUNC(create_hbox), 1);
  rb_define_singleton_method(mUIBuilder, "create_vbox", RUBY_METHOD_FUNC(create_vbox), 1);

  rb_define_singleton_method(mUIBuilder, "create_vstretch", RUBY_METHOD_FUNC(create_vstretch), 1);
  rb_define_singleton_method(mUIBuilder, "create_hstretch", RUBY_METHOD_FUNC(create_hstretch), 1);
  rb_define_singleton_method(mUIBuilder, "create_vspacing", RUBY_METHOD_FUNC(create_vspacing), 1);
  rb_define_singleton_method(mUIBuilder, "create_hspacing", RUBY_METHOD_FUNC(create_hspacing), 1);

  rb_define_singleton_method(mUIBuilder, "create_hsquash", RUBY_METHOD_FUNC(create_hsquash), 1);
  rb_define_singleton_method(mUIBuilder, "create_vsquash", RUBY_METHOD_FUNC(create_vsquash), 1);
  rb_define_singleton_method(mUIBuilder, "create_hvsquash", RUBY_METHOD_FUNC(create_hvsquash), 1);
  rb_define_singleton_method(mUIBuilder, "create_replace_point", RUBY_METHOD_FUNC(create_replace_point), 1);


  rb_define_singleton_method(mUIBuilder, "create_push_button", RUBY_METHOD_FUNC(create_push_button), 2);
  rb_define_singleton_method(mUIBuilder, "create_label", RUBY_METHOD_FUNC(create_label), 2);
  rb_define_singleton_method(mUIBuilder, "create_input_field", RUBY_METHOD_FUNC(create_input_field), 2);
  rb_define_singleton_method(mUIBuilder, "create_rich_text", RUBY_METHOD_FUNC(create_rich_text), 2);

}
