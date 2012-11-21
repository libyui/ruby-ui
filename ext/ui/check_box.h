#ifndef RUBY_NATIVE_UI_CHECK_BOX_H
#define RUBY_NATIVE_UI_CHECK_BOX_H

#include <yui/YCheckBox.h>
#include "ui.h"

void init_ui_check_box();

extern VALUE cUICheckBox;
VALUE ui_wrap_check_box(YCheckBox *box);

#endif