#ifndef RUBY_NATIVE_UI_SPACING_H
#define RUBY_NATIVE_UI_SPACING_H

#include <yui/YSpacing.h>
#include "ui.h"

void init_ui_spacing();

extern VALUE cUISpacing;
VALUE ui_wrap_spacing(YSpacing *btn);

#endif