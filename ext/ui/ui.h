#ifndef RUBY_NATIVE_UI_H
#define RUBY_NATIVE_UI_H

#include "ruby.h"

typedef VALUE (ruby_method_vararg)(...);

#define C_FUNC(X) ((ruby_method_vararg *) (X))

#endif
