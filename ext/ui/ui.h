#ifndef RUBY_NATIVE_UI_H
#define RUBY_NATIVE_UI_H

#include "ruby.h"

#define YUILogComponent "ruby-ui"
#include <yui/YUILog.h>

#include "widget_object_map.h"

#ifdef RUBY18_SUPPORT
VALUE rb_funcall_passing_block(VALUE recv, ID mid, int argc, const VALUE *argv);
#endif

extern "C" void __attribute__ ((visibility("default"))) Init_ui();

#endif
