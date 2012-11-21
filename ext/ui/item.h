#ifndef RUBY_NATIVE_UI_ITEM_H
#define RUBY_NATIVE_UI_ITEM_H

#include <yui/YItem.h>
#include "ui.h"

void init_ui_item();

extern VALUE cUIItem;
VALUE ui_wrap_item(YItem *item);
YItem * ui_unwrap_item(VALUE item);

// mark an item as owned/unowned by a SelectionWidget
// so that we know if we need to delete the backing
// pointer later or the SelectionWidget will take care
// of it.
void ui_item_set_owned(VALUE object, bool owned);

// true is this item is owned by a SelectionWidget
bool ui_item_is_owned(VALUE object);

// converts a ruby object to an item
// if the object is an UI::Item already
// the same is returned. Otherwise
// an item with same label as obj.to_s
// is created.
VALUE ui_object_to_item(VALUE object);

#endif