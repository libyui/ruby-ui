#ifndef RUBY_NATIVE_UI_SQUASH_H
#define RUBY_NATIVE_UI_SQUASH_H

#include <yui/YSquash.h>
#include "ui.h"

void init_ui_squash();

extern VALUE cUISquash;
VALUE ui_wrap_squash(YSquash *sq);

#endif