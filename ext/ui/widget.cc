#include <yui/YWidgetID.h>
#include <yui/YProperty.h>

#include "widget.h"
#include "widget_object_map.h"
#include "ruby_value_widget_id.h"

/*
 * Document-class: UI::Widget
 * Base class for all UI widgets
 *
 * You can't create abstract Widget objects
 * @see UI
 */

void
ui_widget_dealloc(YWidget *wg)
{
  // invalidate all children
  for (YWidgetListConstIterator it = wg->childrenBegin();
       it != wg->childrenEnd();
       ++it) {

    YWidget *child = *it;
    if (!child) continue;

    VALUE rb_child = widget_object_map_for(child);
    if (NIL_P(rb_child)) continue;

    // and recursivelly all children
    ui_widget_dealloc(child);

    // Invalidate our own data
    if (!NIL_P(rb_child))
      DATA_PTR(rb_child) = 0;    
  }
  //remove it from the map
  widget_object_map_remove(wg);
}

void
ui_widget_mark(YWidget *wg)
{
  // mark the id
  RubyValueWidgetID *id = dynamic_cast<RubyValueWidgetID *>(wg->id());
  if (id) {
    rb_gc_mark(id->rubyValue());
  }

  // mark our child _ruby_ objects by finding the C
  // ptrs and looking the ruby counterparts in the hash
  for (YWidgetListConstIterator it = wg->childrenBegin();
       it != wg->childrenEnd();
       ++it) {
    YWidget *child = *it;
    VALUE rb_child = widget_object_map_for(child);
    if (rb_child != Qnil)
      rb_gc_mark(rb_child);
  }
}

VALUE
ui_wrap_widget(YWidget *wg)
{
  return Data_Wrap_Struct(cUIWidget, ui_widget_mark, ui_widget_dealloc, wg);
}

YWidget *
ui_unwrap_widget(VALUE wdg)
{
  YWidget *ptr = 0L;
  Data_Get_Struct (wdg, YWidget, ptr);
  if (!ptr) 
    rb_raise(rb_eRuntimeError, "Widget was already destroyed. Probably you destroyed its parent dialog.");
  return ptr;
}

/*
 * For a block {|child| ... } pass every child to the block
 * @yield [child] A child of this widget
 */
VALUE
each_child(VALUE self)
{
    YWidget *ptr = ui_unwrap_widget(self);
    
    for (YWidgetListConstIterator it = ptr->childrenBegin();
         it != ptr->childrenEnd();
         ++it) {
      YWidget *ptr = *it;
      rb_yield(widget_object_map_for(ptr));
    }
    return Qnil;
}

/*
 * @return [Fixnum] Number of children this widget has
 */
VALUE
children_count(VALUE self)
{
    YWidget *ptr = ui_unwrap_widget(self);
    return INT2NUM(ptr->childrenCount());
}

/*
 * @return [Object] Widget's id
 */
VALUE
id(VALUE self)
{
    YWidget *ptr = ui_unwrap_widget(self);
    RubyValueWidgetID *id = dynamic_cast<RubyValueWidgetID *>(ptr->id());
    return id ? id->rubyValue() : Qnil;
}

/*
 * Sets the widget id
 * @param [Object] id Ruby object to be used as an id
 * @see Widget#id
 */
VALUE
set_id(VALUE self, VALUE id)
{
    YWidget *ptr = ui_unwrap_widget(self);
    ptr->setId(new RubyValueWidgetID(id));
    return id;
}

/*
 * @return [Boolean] True if the widget has an assigned id
 */
VALUE
has_id(VALUE self)
{
    YWidget *ptr = ui_unwrap_widget(self);
    return ptr->hasId() ? Qtrue : Qfalse;
}

/*
 * @return [Boolean] True if the widget is valid
 */
VALUE
is_valid(VALUE self)
{
    YWidget *ptr = ui_unwrap_widget(self);
    return ptr->isValid() ? Qtrue : Qfalse;
}

/*
 * @return [Widget] Widget with the requested id or null if not found
 * @param [Object] id id of the widget we are looking for
 * @example
 *   btn = dialog.find_widget(:btn1)
 *   btn.is_a?(UI::Button) => true
 */
VALUE
find_widget(VALUE self, VALUE id)
{
  YWidget *ptr = ui_unwrap_widget(self);
  YWidgetID *idPtr = new RubyValueWidgetID(id);
  YWidget * retPtr = ptr->findWidget(idPtr, false);
  //yuiDebug() << "ptr: " << (unsigned long)  retPtr << std::endl;
  delete idPtr;
  return retPtr ? widget_object_map_for(retPtr) : Qnil;
}

VALUE get_properties(VALUE self)
{
    YWidget *ptr = ui_unwrap_widget(self);
    const YPropertySet & prop_set = ptr->propertySet();
    VALUE result = rb_ary_new2(prop_set.size());
    for (YPropertySet::const_iterator i = prop_set.propertiesBegin();
           i != prop_set.propertiesEnd(); ++i )
    {
      VALUE name = ID2SYM(rb_intern(i->name().c_str()));
      result = rb_ary_push(result,name);
    }
    return result;
}

/*
 * @return [Object] Property named id
 * @param [String] Name of the property.
 *
 * @note You can use a Symbol, it will be internally
 *   converted to a String
 *
 * @example
 *   val = widget[:Label]
 */
VALUE
get_property(VALUE self, VALUE id)
{
    YWidget *ptr = ui_unwrap_widget(self);
    VALUE id_str = rb_funcall(id,rb_intern("to_s"),0);
    const YPropertyValue & property = ptr->getProperty(RSTRING_PTR(id_str));
    VALUE response = Qnil;
    switch (property.type())
    {
    case YStringProperty:
        response = rb_str_new2(property.stringVal().c_str());
        break;
    case YBoolProperty:
        response = property.boolVal() ? Qtrue : Qfalse;
        break;
    case YIntegerProperty:
        //Do not use INT2FIX as YInterger is long long
        response = INT2NUM(property.integerVal());
        break;
    }
    return response;
}

/*
 * Sets a widget property
 * @see Widget#[]
 *
 * @param [String] id id of the property.
 *
 * @note You can use a Symbol, it will be internally
 *   converted to a String
 */
VALUE
set_property(VALUE self, VALUE id, VALUE value)
{
    YWidget *ptr = ui_unwrap_widget(self);
    VALUE id_str = rb_funcall(id,rb_intern("to_s"),0);
    YPropertyValue yui_value;
    switch (TYPE(value))
    {
    case T_STRING:
        yui_value = YPropertyValue(StringValueCStr(value));
        break;
    case T_TRUE:
    case T_FALSE:
        yui_value = YPropertyValue(TYPE(value) == T_TRUE);
        break;
    case T_FIXNUM:
    case T_BIGNUM:
        yui_value = YPropertyValue((YInteger)NUM2INT(value));
        break;
    }
    bool response = ptr->setProperty(StringValueCStr(id_str),yui_value);
    return response;
}

VALUE cUIWidget;
void init_ui_widget()
{
  VALUE ui = rb_define_module("UI");

  VALUE klass = rb_define_class_under(ui, "Widget", rb_cObject);
  cUIWidget = klass;

  rb_define_method(klass, "id", RUBY_METHOD_FUNC(id), 0);
  rb_define_method(klass, "id=", RUBY_METHOD_FUNC(set_id), 1);
  rb_define_method(klass, "has_id?", RUBY_METHOD_FUNC(has_id), 0);
  rb_define_method(klass, "each_child", RUBY_METHOD_FUNC(each_child), 0);
  rb_define_method(klass, "children_count", RUBY_METHOD_FUNC(children_count), 0);
  rb_define_method(klass, "valid?", RUBY_METHOD_FUNC(is_valid), 0);
  rb_define_method(klass, "find_widget", RUBY_METHOD_FUNC(find_widget), 1);
  rb_define_method(klass, "[]", RUBY_METHOD_FUNC(get_property), 1);
  rb_define_method(klass, "[]=", RUBY_METHOD_FUNC(set_property), 2);
  rb_define_method(klass, "properties", RUBY_METHOD_FUNC(get_properties), 0);
}

