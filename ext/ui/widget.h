#ifndef RUBY_NATIVE_UI_WIDGET_H
#define RUBY_NATIVE_UI_WIDGET_H

#include <yui/YWidget.h>
#include "ui.h"

void init_ui_widget();

extern VALUE cUIWidget;
VALUE ui_wrap_widget(YWidget *wg);

#endif