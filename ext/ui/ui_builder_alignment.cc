#include <stdio.h>

#include <deque>

#include <yui/YUI.h>
#include <yui/YWidgetFactory.h>

#include "widget_object_map.h"

#include "exception_guard.h"
#include "ui.h"
#include "widget.h"
#include "alignment.h"

extern VALUE mUIBuilder;

#define DEFINE_ALIGNMENT(name, factory) \
  static VALUE create_##name(VALUE self, VALUE parent) \
  { \
    YEXCEPTION_TRY \
    YWidget *ptr = ui_unwrap_widget(parent); \
    YAlignment *align = YUI::widgetFactory()->create##factory(ptr); \
    VALUE object = ui_wrap_alignment(align); \
    widget_object_map_add(align, object); \
    return object; \
    YEXCEPTION_CATCH \
 }
DEFINE_ALIGNMENT(left, Left)
DEFINE_ALIGNMENT(right, Right)
DEFINE_ALIGNMENT(top, Top)
DEFINE_ALIGNMENT(bottom, Bottom)
DEFINE_ALIGNMENT(hcenter, HCenter)
DEFINE_ALIGNMENT(vcenter, VCenter)
DEFINE_ALIGNMENT(hvcenter, HVCenter)

/*
 * @visibility private
 */
static VALUE create_margin_box(int argc, VALUE *argv, VALUE self)
{
  YEXCEPTION_TRY

  VALUE parent;
  VALUE p1;
  VALUE p2;
  VALUE p3;
  VALUE p4;

  // if p1 & p2 only: x margin and y margin
  // if p1 & p2 & p3 & p4 : left margin, right margin, top margin,
  //   bottom margin
  rb_scan_args(argc, argv, "32", &parent, &p1, &p2, &p3, &p4);

  YWidget *ptr = ui_unwrap_widget(parent);

  YAlignment *align = 0L;
  if (!NIL_P(p3) && !NIL_P(p4)) {
    align = YUI::widgetFactory()->createMarginBox(ptr, NUM2INT(p1), NUM2INT(p2),
                                                  NUM2INT(p3), NUM2INT(p4));
  }
  else {
    align = YUI::widgetFactory()->createMarginBox(ptr, NUM2INT(p1), NUM2INT(p2));
  }

  VALUE object = ui_wrap_alignment(align);
  widget_object_map_add(align, object);
  return object;
  YEXCEPTION_CATCH
 }


void init_ui_ui_builder_alignment() {

  VALUE mUI = rb_define_module("UI");
  mUIBuilder = rb_define_module_under(mUI, "Builder");

  rb_define_singleton_method(mUIBuilder, "create_left", RUBY_METHOD_FUNC(create_left), 1);
  rb_define_singleton_method(mUIBuilder, "create_right", RUBY_METHOD_FUNC(create_right), 1);
  rb_define_singleton_method(mUIBuilder, "create_top", RUBY_METHOD_FUNC(create_top), 1);
  rb_define_singleton_method(mUIBuilder, "create_bottom", RUBY_METHOD_FUNC(create_bottom), 1);
  rb_define_singleton_method(mUIBuilder, "create_hcenter", RUBY_METHOD_FUNC(create_hcenter), 1);
  rb_define_singleton_method(mUIBuilder, "create_vcenter", RUBY_METHOD_FUNC(create_vcenter), 1);
  rb_define_singleton_method(mUIBuilder, "create_hvcenter", RUBY_METHOD_FUNC(create_hvcenter), 1);

  rb_define_singleton_method(mUIBuilder, "create_margin_box", RUBY_METHOD_FUNC(create_margin_box), -1);
}
