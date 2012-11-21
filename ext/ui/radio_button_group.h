#ifndef RUBY_NATIVE_UI_RADIO_BUTTON_GROUP_H
#define RUBY_NATIVE_UI_RADIO_BUTTON_GROUP_H

#include <yui/YRadioButtonGroup.h>
#include "ui.h"

void init_ui_radio_button_group();

extern VALUE cUIRadioButtonGroup;
VALUE ui_wrap_radio_button_group(YRadioButtonGroup *grp);

YRadioButtonGroup * ui_unwrap_radio_button_group(VALUE group);

#endif