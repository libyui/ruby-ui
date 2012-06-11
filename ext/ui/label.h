#ifndef RUBY_NATIVE_UI_LABEL_H
#define RUBY_NATIVE_UI_LABEL_H

#include <yui/YLabel.h>
#include "ui.h"

void init_ui_label();

extern VALUE cUILabel;
VALUE ui_wrap_label(YLabel *btn);

#endif