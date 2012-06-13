#ifndef RUBY_NATIVE_CALLBACK_FILTER_H
#define RUBY_NATIVE_CALLBACK_FILTER_H

#include "ui.h"
#include <yui/YEventFilter.h>

class CallbackFilter : public YEventFilter
{
public:
  CallbackFilter(YDialog * dialog) : YEventFilter(dialog) {}
  YEvent * filter (YEvent * event);
};

#endif
