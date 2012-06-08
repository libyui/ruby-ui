#ifndef RUBY_NATIVE_UI_PUSH_BUTTON_H
#define RUBY_NATIVE_UI_PUSH_BUTTON_H

#include <yui/YPushButton.h>
#include "ui.h"

void init_ui_push_button();

extern VALUE cUIPushButton;
VALUE ui_wrap_push_button(YPushButton *btn);

#endif