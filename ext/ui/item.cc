#include <yui/YItem.h>
#include "exception_guard.h"
#include "widget.h"
#include "item.h"

typedef struct
{
  YItem *ptr;
  bool owned;
} ItemWrapper;

static void
dealloc(ItemWrapper *wrapper)
{
  YEXCEPTION_TRY
  if (!wrapper->owned) {
    yuiDebug() << "unowned item, destroying...";
    delete wrapper->ptr;
  }
  delete wrapper;
  YEXCEPTION_CATCH
}

static ItemWrapper *
 ui_item_wrapper(VALUE item)
{
  ItemWrapper *wrapper = 0L;

  Data_Get_Struct (item, ItemWrapper, wrapper);
  if (!wrapper)
    rb_raise(rb_eRuntimeError, "Item was already destroyed. Probably you destroyed its owning selection widget.");
  return wrapper;
}

VALUE
ui_wrap_item(YItem *item)
{
  ItemWrapper *wrapper = new ItemWrapper;
  wrapper->ptr = item;
  wrapper->owned = false;
  return Data_Wrap_Struct(cUIItem, 0, dealloc, wrapper);
}

YItem *
ui_unwrap_item(VALUE item)
{
  return ui_item_wrapper(item)->ptr;
}

// fwd decl
static VALUE set_data(VALUE self, VALUE data);

VALUE
ui_object_to_item(VALUE object) {
  VALUE ui = rb_define_module("UI");
  if (rb_class_of(object) == rb_const_get(ui, rb_intern("Item")))
      return object;

  VALUE label = rb_funcall(object, rb_intern("to_s"), 0);
  VALUE item = rb_funcall(cUIItem, rb_intern("new"), 1, label);
  set_data(item, object);
  return item;
}

void
ui_item_set_owned(VALUE object, bool owned)
{
  ui_item_wrapper(object)->owned = owned;
}

bool
ui_item_is_owned(VALUE object)
{
  return ui_item_wrapper(object)->owned;
}

/*
 * @return [String] the item label
 */
static VALUE
get_label(VALUE self)
{
  YEXCEPTION_TRY
  YItem *ptr = ui_unwrap_item(self);
  return rb_str_new2(ptr->label().c_str());
  YEXCEPTION_CATCH
}

/*
 * Set the item label
 */
static VALUE
set_label(VALUE self, VALUE label)
{
  YEXCEPTION_TRY
  YItem *ptr = ui_unwrap_item(self);
  ptr->setLabel(StringValueCStr(label));
  return label;
  YEXCEPTION_CATCH
}

/*
 * @return [String] the item index
 */
static VALUE
get_index(VALUE self)
{
  YEXCEPTION_TRY
  YItem *ptr = ui_unwrap_item(self);
  return INT2NUM(ptr->index());
  YEXCEPTION_CATCH
}

/*
 * Set the item index
 */
static VALUE
set_index(VALUE self, VALUE index)
{
  YEXCEPTION_TRY
  YItem *ptr = ui_unwrap_item(self);
  ptr->setIndex(NUM2INT(index));
  return index;
  YEXCEPTION_CATCH
}

/*
 * @return [String] the 's' icon name
 */
static VALUE
get_icon_name(VALUE self)
{
  YEXCEPTION_TRY
  YItem *ptr = ui_unwrap_item(self);
  return rb_str_new2(ptr->iconName().c_str());
  YEXCEPTION_CATCH
}

/*
 * Set the item's icon name
 */
static VALUE
set_icon_name(VALUE self, VALUE icon)
{
  YEXCEPTION_TRY
  YItem *ptr = ui_unwrap_item(self);
  ptr->setIconName(StringValueCStr(icon));
  return icon;
  YEXCEPTION_CATCH
}

/*
 * @return [Object] the object associated with this item
 */
static VALUE
get_data(VALUE self)
{
  YEXCEPTION_TRY
  YItem *ptr = ui_unwrap_item(self);
  return ptr->data() ? ((VALUE) ptr->data()) : Qnil;
  YEXCEPTION_CATCH
}

/*
 * Set the object associated with this item
 */
static VALUE
set_data(VALUE self, VALUE data)
{
  YEXCEPTION_TRY
  YItem *ptr = ui_unwrap_item(self);
  ptr->setData((void *) data);
  return data;
  YEXCEPTION_CATCH
}

/*
 * @return [Boolean] True if the item is selected
 */
static VALUE
get_selected(VALUE self)
{
  YEXCEPTION_TRY
  YItem *ptr = ui_unwrap_item(self);
  return ptr->selected() ? Qtrue : Qfalse;
  YEXCEPTION_CATCH
}

/*
 * Select or unselect this item. This does not have any effect on any other
 * item; if it is desired that only one item is selected at any time, the
 * caller has to take care of that.
 *
 * @param [Boolean] selected whether the item is selected or not
 */
static VALUE
set_selected(VALUE self, VALUE selected)
{
  YEXCEPTION_TRY
  YItem *ptr = ui_unwrap_item(self);
  ptr->setSelected(RTEST(selected));
  return selected;
  YEXCEPTION_CATCH
}

static VALUE
each_child(VALUE self)
{
  YEXCEPTION_TRY
  YItem *ptr = ui_unwrap_item(self);

  for (YItemConstIterator it = ptr->childrenBegin();
       it != ptr->childrenEnd();
       ++it) {

    YItem *child = *it;
    if (!child)
      continue;

    VALUE rb_child = widget_object_map_for(child);
    if (!NIL_P(rb_child))
      rb_yield(rb_child);
  }
  YEXCEPTION_CATCH
}

/*
 * @return [Item] the item's parent (or nil if the item has no parent)
 */
static VALUE
get_parent(VALUE self)
{
  YEXCEPTION_TRY
  YItem *ptr = ui_unwrap_item(self);
  return widget_object_map_for(ptr->parent());
  YEXCEPTION_CATCH
}

static VALUE
_new(int argc, VALUE *argv, VALUE klass)
{
  YEXCEPTION_TRY

  VALUE label;
  rb_scan_args(argc, argv, "10", &label);

  YItem *item = new YItem(StringValueCStr(label));
  VALUE object = ui_wrap_item(item);

  widget_object_map_add(item, object);
  rb_obj_call_init(object, argc, argv);
  return object;
  YEXCEPTION_CATCH
}

/*
 * Initializes an item with label +label+
 *
 * @param [String] label initial label of the item
 *
 * @example
 *   item = UI::Item.new("Orange")
 */
static VALUE
initialize(int argc, VALUE *argv, VALUE self)
{
  ui_item_set_owned(self, false);
}

VALUE cUIItem;
void init_ui_item()
{
  VALUE ui = rb_define_module("UI");

  VALUE klass = rb_define_class_under(ui, "Item", rb_cObject);
  rb_define_singleton_method(klass, "new", RUBY_METHOD_FUNC(_new), -1);
  rb_define_method(klass, "initialize", RUBY_METHOD_FUNC(initialize), -1);
  rb_define_method(klass, "label", RUBY_METHOD_FUNC(get_label), 0);
  rb_define_method(klass, "label=", RUBY_METHOD_FUNC(set_label), 1);
  rb_define_method(klass, "data", RUBY_METHOD_FUNC(get_data), 0);
  rb_define_method(klass, "data=", RUBY_METHOD_FUNC(set_data), 1);
  rb_define_method(klass, "index", RUBY_METHOD_FUNC(get_index), 0);
  rb_define_method(klass, "index=", RUBY_METHOD_FUNC(set_index), 1);
  rb_define_method(klass, "icon_name", RUBY_METHOD_FUNC(get_icon_name), 0);
  rb_define_method(klass, "icon_name=", RUBY_METHOD_FUNC(set_icon_name), 1);
  rb_define_method(klass, "selected?", RUBY_METHOD_FUNC(get_selected), 0);
  rb_define_method(klass, "selected=", RUBY_METHOD_FUNC(set_selected), 1);
  rb_define_method(klass, "each_child", RUBY_METHOD_FUNC(each_child), 0);
  rb_define_method(klass, "parent", RUBY_METHOD_FUNC(get_parent), 0);
  cUIItem = klass;
}

