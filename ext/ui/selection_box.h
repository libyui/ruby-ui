#ifndef RUBY_NATIVE_UI_SELECTION_BOX_H
#define RUBY_NATIVE_UI_SELECTION_BOX_H

#include <yui/YSelectionBox.h>
#include "ui.h"

void init_ui_selection_box();

extern VALUE cUISelectionBox;
VALUE ui_wrap_selection_box(YSelectionBox *btn);

#endif