#include <yui/YWidgetID.h>

#include "widget.h"

/**
 * Implement a Widget Id based on ruby objects
 */
class RubyValueWidgetID : public YWidgetID
{
public:
    /**
     * Constructor
     */
    RubyValueWidgetID(VALUE value)
      : _value(value)
    {}

    /**
     * Check if this ID is equal to another.
     *
     * Reimplemented from YWidgetID.
     **/
    virtual bool isEqual( YWidgetID * otherID ) const
    {
        RubyValueWidgetID *that = dynamic_cast<RubyValueWidgetID *>(otherID);
        if (that) {
            return rb_eql(this->rubyValue(), that->rubyValue());
        }
        return false;
    }

    /**
     * Convert the ID value to string.
     * Used for logging and debugging.
     *
     * Reimplemented from YWidgetID.
     **/
    virtual string toString() const
    {
        return StringValueCStr(_value);
    }

    /**
     * Return the ID value.
     **/
    VALUE rubyValue() const
    {
        return _value;
    }

private:
    mutable VALUE _value;
};

static void
dealloc(YWidget *wg)
{

}

VALUE
ui_wrap_widget(YWidget *dlg)
{
  return Data_Wrap_Struct(cUIWidget, NULL, dealloc, dlg);
}

VALUE
id(VALUE self)
{
    YWidget *ptr = 0L;
    Data_Get_Struct(self, YWidget, ptr);
    RubyValueWidgetID *id = dynamic_cast<RubyValueWidgetID *>(ptr->id());
    return id ? id->rubyValue() : Qnil;
}

VALUE
set_id(VALUE self, VALUE id)
{
    YWidget *ptr = 0L;
    Data_Get_Struct(self, YWidget, ptr);
    ptr->setId(new RubyValueWidgetID(id));
    return id;
}

VALUE
has_id(VALUE self)
{
    YWidget *ptr = 0L;
    Data_Get_Struct(self, YWidget, ptr);
    return ptr->hasId() ? Qtrue : Qfalse;
}


VALUE cUIWidget;
void init_ui_widget()
{
  VALUE ui = rb_define_module("UI");

  VALUE klass = rb_define_class_under(ui, "Widget", rb_cObject);
  cUIWidget = klass;

  rb_define_method(klass, "id", C_FUNC(id), 0);
  rb_define_method(klass, "id=", C_FUNC(set_id), 1);
  rb_define_method(klass, "has_id?", C_FUNC(has_id), 0);
}

