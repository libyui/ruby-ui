#ifndef RUBY_NATIVE_UI_REPLACE_POINT_H
#define RUBY_NATIVE_UI_REPLACE_POINT_H

#include <yui/YReplacePoint.h>
#include "ui.h"

void init_ui_replace_point();

extern VALUE cUIReplacePoint;
VALUE ui_wrap_replace_point(YReplacePoint *pnt);

YReplacePoint * ui_unwrap_replace_point(VALUE point);

#endif