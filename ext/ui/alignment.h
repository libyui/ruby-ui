#ifndef RUBY_NATIVE_UI_ALIGNMENT_H
#define RUBY_NATIVE_UI_ALIGNMENT_H

#include <yui/YAlignment.h>
#include "ui.h"

void init_ui_alignment();

extern VALUE cUIAlignment;
VALUE ui_wrap_alignment(YAlignment *align);

#endif