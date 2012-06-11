#ifndef RUBY_VALUE_WIDGET_ID
#define RUBY_VALUE_WIDGET_ID

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


#endif
