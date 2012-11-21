#ifndef RUBY_NATIVE_UI_FRAME_H
#define RUBY_NATIVE_UI_FRAME_H

#include <yui/YFrame.h>
#include "ui.h"

void init_ui_frame();

extern VALUE cUIFrame;
VALUE ui_wrap_frame(YFrame *frame);

#endif