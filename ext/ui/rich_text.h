#ifndef RUBY_NATIVE_UI_RICH_TEXT_H
#define RUBY_NATIVE_UI_RICH_TEXT_H

#include <yui/YRichText.h>
#include "ui.h"

void init_ui_rich_text();

extern VALUE cUIRichText;
VALUE ui_wrap_rich_text(YRichText *rich);

#endif