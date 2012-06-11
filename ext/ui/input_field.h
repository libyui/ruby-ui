#ifndef RUBY_NATIVE_UI_INPUT_FIELD_H
#define RUBY_NATIVE_UI_INPUT_FIELD_H

#include <yui/YInputField.h>
#include "ui.h"

void init_ui_input_field();

extern VALUE cUIInputField;
VALUE ui_wrap_input_field(YInputField *fld);

#endif