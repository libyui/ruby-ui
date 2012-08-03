#include "widget.h"
#include "exception_guard.h"
#include "item.h"
#include "selection_widget.h"

static void
dealloc(YSelectionWidget *wg)
{
  /*
  // invalidate all children items
  for (YItemConstIterator it = wg->childrenBegin();
       it != wg->childrenEnd();
       ++it) {

    YItem *child = *it;
    if (!child) continue;

    VALUE rb_child = widget_object_map_for(child);
    if (NIL_P(rb_child)) continue;

    // and recursivelly all children
    ui_widget_dealloc(child);

    // Invalidate our own data
    if (!NIL_P(rb_child))
      DATA_PTR(rb_child) 
  */
  widget_object_map_remove(wg);
}

void
ui_selection_widget_mark(YSelectionWidget *wg)
{
  /* mark all children items */
  for (YItemConstIterator it = wg->itemsBegin();
       it != wg->itemsEnd();
       ++it) {

    YItem *child = *it;
    if (!child) continue;

    VALUE rb_child = widget_object_map_for(child);
    if (!NIL_P(rb_child)) rb_gc_mark(rb_child);
  }
  ui_widget_mark(wg);
}

VALUE
ui_wrap_selection_widget(YSelectionWidget *widget)
{
  return Data_Wrap_Struct(cUISelectionWidget, ui_selection_widget_mark, dealloc, widget);
}

YSelectionWidget *
ui_unwrap_selection_widget(VALUE widget)
{
  YSelectionWidget *ptr = 0L;
  Data_Get_Struct(widget, YSelectionWidget, ptr);
  return ptr;
}

/**
 * @return [String] the widget's label (the caption above the item list).
 */
static VALUE
get_label(VALUE self)
{
  YEXCEPTION_TRY
  YSelectionWidget *ptr = ui_unwrap_selection_widget(self);
  return rb_str_new2(ptr->label().c_str());
  YEXCEPTION_CATCH
}

/**
 * Change the widget's label (the caption above the item list).
 */
static VALUE
set_label(VALUE self, VALUE label)
{
  YEXCEPTION_TRY
  YSelectionWidget *ptr = ui_unwrap_selection_widget(self);
  ptr->setLabel(StringValueCStr(label));
  YEXCEPTION_CATCH
}

/**
 * Add one item.
 *
 * @note For tree items, call this only for the toplevel items.
 *   All non-toplevel items are already owned by their respective parent
 *   items. Adding them to the parent widget will clash with this ownership.
 *
 * @param [Item, Object] the item or an object to use to create a new item
 * @return [Item] the item you added, or the new created one if you
 *   added a non +UI::Item+ object. In this case the newly created +UI::Item+
 *   will have the +data+ attribute set to the object.
 */
static VALUE
add_item(VALUE self, VALUE object)
{
  YEXCEPTION_TRY
  YSelectionWidget *ptr = ui_unwrap_selection_widget(self);

  VALUE item = ui_object_to_item(object);
  YItem *item_ptr = ui_unwrap_item(item);
  yuiDebug() << "adding item " << item_ptr << std::endl;
  ptr->addItem(item_ptr);
  ui_item_set_owned(item, true);
  YEXCEPTION_CATCH
}

static VALUE
each_item(VALUE self)
{
  YEXCEPTION_TRY
  YSelectionWidget *ptr = ui_unwrap_selection_widget(self);

  for (YItemConstIterator it = ptr->itemsBegin();
       it != ptr->itemsEnd();
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
 * Select or deselect an item.
 *
 * Notice that this is different from YItem::setSelected() because unlike
 * the latter function, this function informs the parent widget of the
 * selection change.
 *
 * If only one item can be selected at any time (single selection), the
 * derived class will make sure to deselect any previous selection, if
 * applicable.
 */
static VALUE
select_item(int argc, VALUE *argv, VALUE self)
{
  YEXCEPTION_TRY
  YSelectionWidget *ptr = ui_unwrap_selection_widget(self);

  VALUE item;
  VALUE selected;
  rb_scan_args(argc, argv, "11", &item, &selected);

  YItem *item_ptr = ui_unwrap_item(item);
  if (NIL_P(selected))
    ptr->selectItem(item_ptr);
  else
    ptr->selectItem(item_ptr, RTEST(selected));
  return item;
  YEXCEPTION_CATCH
}

static VALUE
deselect_all_items(VALUE self)
{
  YEXCEPTION_TRY
  YSelectionWidget *ptr = ui_unwrap_selection_widget(self);
  ptr->deselectAllItems();
  return self;
  YEXCEPTION_CATCH
}



VALUE cUISelectionWidget;
void init_ui_selection_widget()
{
  VALUE ui = rb_define_module("UI");

  VALUE klass = rb_define_class_under(ui, "SelectionWidget", cUIWidget);
  rb_define_method(klass, "label", RUBY_METHOD_FUNC(get_label), 0);
  rb_define_method(klass, "label=", RUBY_METHOD_FUNC(set_label), 1);
  rb_define_method(klass, "add_item", RUBY_METHOD_FUNC(add_item), 1);
  rb_define_method(klass, "each_item", RUBY_METHOD_FUNC(each_item), 0);
  rb_define_method(klass, "select_item", RUBY_METHOD_FUNC(select_item), -1);
  rb_define_method(klass, "deselect_all_items", RUBY_METHOD_FUNC(deselect_all_items), 0);
  cUISelectionWidget = klass;
}

