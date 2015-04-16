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
#include "selection_box.h"
#include "spacing.h"
#include "squash.h"
#include "replace_point.h"

#include "ui_builder_alignment.h"

VALUE mUIBuilder;

/*
 * @visibility private
 */
static VALUE create_main_dialog(VALUE self)
{
  YEXCEPTION_TRY
  YDialog *dlg = YUI::widgetFactory()->createMainDialog();
  ui_dialog_push(dlg);
  yuiDebug() << "new " << dlg << std::endl;

  VALUE object = ui_wrap_dialog(dlg);
  widget_object_map_add(dlg, object);
  return object;
  YEXCEPTION_CATCH
}

/*
 * @visibility private
 */
static VALUE create_popup_dialog(VALUE self)
{
  YEXCEPTION_TRY
  YDialog *dlg = YUI::widgetFactory()->createPopupDialog();
  ui_dialog_push(dlg);
  yuiDebug() << "new " << dlg << std::endl;

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
static VALUE create_progress_bar(int argc, VALUE *argv, VALUE self)
{
  YEXCEPTION_TRY

  VALUE parent;
  VALUE text;
  VALUE maxProgress;
  VALUE currProgress;

  rb_scan_args(argc, argv, "22", &parent, &text, &maxProgress, &currProgress);

  YWidget *ptr = ui_unwrap_widget(parent);

  YProgressBar *bar;
  if (!NIL_P(maxProgress))
    bar = YUI::widgetFactory()->createProgressBar(ptr, StringValuePtr(text),
                                                  NUM2INT(maxProgress));
  else
    bar = YUI::widgetFactory()->createProgressBar(ptr, StringValuePtr(text));

  if (!NIL_P(currProgress))
    bar->setValue(NUM2INT(currProgress));

  VALUE object = ui_wrap_progress_bar(bar);
  widget_object_map_add(bar, object);
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
static VALUE create_check_box(VALUE self, VALUE parent, VALUE text)
{
  YEXCEPTION_TRY
  YWidget *ptr = ui_unwrap_widget(parent);

  YCheckBox *box = YUI::widgetFactory()->createCheckBox(ptr, StringValuePtr(text));

  VALUE object = ui_wrap_check_box(box);
  widget_object_map_add(box, object);
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
static VALUE create_radio_button(VALUE self, VALUE parent, VALUE text)
{
  YEXCEPTION_TRY
  YWidget *ptr = ui_unwrap_widget(parent);

  YRadioButton *btn = YUI::widgetFactory()->createRadioButton(ptr, StringValuePtr(text));

  VALUE object = ui_wrap_radio_button(btn);
  widget_object_map_add(btn, object);
  return object;
  YEXCEPTION_CATCH
}

/*
 * @visibility private
 */
static VALUE create_radio_button_group(VALUE self, VALUE parent)
{
  YEXCEPTION_TRY
  YWidget *ptr = ui_unwrap_widget(parent);

  YRadioButtonGroup *grp = YUI::widgetFactory()->createRadioButtonGroup(ptr);

  VALUE object = ui_wrap_radio_button_group(grp);
  widget_object_map_add(grp, object);
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
static VALUE create_selection_box(VALUE self, VALUE parent, VALUE label)
{
  YEXCEPTION_TRY
  YWidget *ptr = ui_unwrap_widget(parent);

  YSelectionBox *box = YUI::widgetFactory()->createSelectionBox(ptr, StringValuePtr(label));

  VALUE object = ui_wrap_selection_box(box);
  widget_object_map_add(box, object);
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

static VALUE create_vspacing(int argc, VALUE *argv, VALUE self)
{
  YEXCEPTION_TRY

  VALUE parent;
  VALUE size;

  rb_scan_args(argc, argv, "11", &parent, &size);

  YWidget *ptr = ui_unwrap_widget(parent);

  YSpacing *spc = YUI::widgetFactory()->createVSpacing(ptr, size == Qnil ? 1.0 : NUM2DBL(size));

  VALUE object = ui_wrap_spacing(spc);
  widget_object_map_add(spc, object);
  return object;
  YEXCEPTION_CATCH
}

/*
 * @visibility private
 */
static VALUE create_hspacing(int argc, VALUE *argv, VALUE self)
{
  YEXCEPTION_TRY

  VALUE parent;
  VALUE size;

  rb_scan_args(argc, argv, "11", &parent, &size);

  YWidget *ptr = ui_unwrap_widget(parent);

  YSpacing *spc = YUI::widgetFactory()->createHSpacing(ptr, size == Qnil ? 1.0 : NUM2DBL(size));

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
static VALUE create_frame(VALUE self, VALUE parent, VALUE label)
{
  YEXCEPTION_TRY
  YWidget *ptr = ui_unwrap_widget(parent);

  YFrame *frame = YUI::widgetFactory()->createFrame(ptr, StringValueCStr(label));

  VALUE object = ui_wrap_frame(frame);
  widget_object_map_add(frame, object);
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

  rb_define_singleton_method(mUIBuilder, "create_main_dialog", RUBY_METHOD_FUNC(create_main_dialog), 0);
  rb_define_singleton_method(mUIBuilder, "create_popup_dialog", RUBY_METHOD_FUNC(create_popup_dialog), 0);

  rb_define_singleton_method(mUIBuilder, "create_hbox", RUBY_METHOD_FUNC(create_hbox), 1);
  rb_define_singleton_method(mUIBuilder, "create_vbox", RUBY_METHOD_FUNC(create_vbox), 1);

  rb_define_singleton_method(mUIBuilder, "create_vstretch", RUBY_METHOD_FUNC(create_vstretch), 1);
  rb_define_singleton_method(mUIBuilder, "create_hstretch", RUBY_METHOD_FUNC(create_hstretch), 1);
  rb_define_singleton_method(mUIBuilder, "create_vspacing", RUBY_METHOD_FUNC(create_vspacing), -1);
  rb_define_singleton_method(mUIBuilder, "create_hspacing", RUBY_METHOD_FUNC(create_hspacing), -1);

  init_ui_ui_builder_alignment();

  rb_define_singleton_method(mUIBuilder, "create_hsquash", RUBY_METHOD_FUNC(create_hsquash), 1);
  rb_define_singleton_method(mUIBuilder, "create_vsquash", RUBY_METHOD_FUNC(create_vsquash), 1);
  rb_define_singleton_method(mUIBuilder, "create_hvsquash", RUBY_METHOD_FUNC(create_hvsquash), 1);

  rb_define_singleton_method(mUIBuilder, "create_frame", RUBY_METHOD_FUNC(create_frame), 2);
  rb_define_singleton_method(mUIBuilder, "create_progress_bar", RUBY_METHOD_FUNC(create_progress_bar), -1);
  rb_define_singleton_method(mUIBuilder, "create_push_button", RUBY_METHOD_FUNC(create_push_button), 2);
  rb_define_singleton_method(mUIBuilder, "create_label", RUBY_METHOD_FUNC(create_label), 2);
  rb_define_singleton_method(mUIBuilder, "create_check_box", RUBY_METHOD_FUNC(create_check_box), 2);
  rb_define_singleton_method(mUIBuilder, "create_input_field", RUBY_METHOD_FUNC(create_input_field), 2);
  rb_define_singleton_method(mUIBuilder, "create_radio_button", RUBY_METHOD_FUNC(create_radio_button), 2);
  rb_define_singleton_method(mUIBuilder, "create_rich_text", RUBY_METHOD_FUNC(create_rich_text), 2);
  rb_define_singleton_method(mUIBuilder, "create_selection_box", RUBY_METHOD_FUNC(create_selection_box), 2);

  rb_define_singleton_method(mUIBuilder, "create_radio_button_group", RUBY_METHOD_FUNC(create_radio_button_group), 1);
  rb_define_singleton_method(mUIBuilder, "create_replace_point", RUBY_METHOD_FUNC(create_replace_point), 1);

}
