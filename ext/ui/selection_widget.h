#ifndef RUBY_NATIVE_UI_SELECTION_WIDGET_H
#define RUBY_NATIVE_UI_SELECTION_WIDGET_H

#include <yui/YSelectionWidget.h>
#include "ui.h"

void init_ui_selection_widget();

extern VALUE cUISelectionWidget;
VALUE ui_wrap_selection_widget(YSelectionWidget *widget);
void ui_selection_widget_mark(YSelectionWidget *wg);

#endif