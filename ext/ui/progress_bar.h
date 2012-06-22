#ifndef RUBY_NATIVE_UI_PROGRESS_BAR_H
#define RUBY_NATIVE_UI_PROGRESS_BAR_H

#include <yui/YProgressBar.h>
#include "ui.h"

void init_ui_progress_bar();

extern VALUE cUIProgressBar;
VALUE ui_wrap_progress_bar(YProgressBar *bar);

#endif