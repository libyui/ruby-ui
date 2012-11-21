#ifndef RUBY_NATIVE_UI_RADIO_BUTTON_H
#define RUBY_NATIVE_UI_RADIO_BUTTON_H

#include <yui/YRadioButton.h>
#include "ui.h"

void init_ui_radio_button();

extern VALUE cUIRadioButton;
VALUE ui_wrap_radio_button(YRadioButton *btn);

#endif