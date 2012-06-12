#ifndef RUBY_NATIVE_UI_EVENT_H
#define RUBY_NATIVE_UI_EVENT_H

#include <yui/YEvent.h>
#include "ui.h"

VALUE convert_event(const YEvent * event);

#endif
