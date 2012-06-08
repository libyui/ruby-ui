#ifndef RUBY_NATIVE_UI_LAYOUTBOX_H
#define RUBY_NATIVE_UI_LAYOUTBOX_H

#include <yui/YLayoutBox.h>
#include "ui.h"

void init_ui_layout_box();

extern VALUE cUILayoutBox;
VALUE ui_wrap_layout_box(YLayoutBox *wg);

#endif