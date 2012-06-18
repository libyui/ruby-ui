#include "callback_filter.h"
#include "event.h"
#include "widget_object_map.h"

using std::string;

YEvent * CallbackFilter::filter (YEvent * event)
{
  if (event->eventType() != YEvent::WidgetEvent) //we handle only widget events now
    return event;
  YWidgetEvent * wevent = static_cast<YWidgetEvent*>(event);
  YWidget * widget = wevent->widget();
  if (!widget)
    return event;

  VALUE r_widget = widget_object_map_for(widget);
  VALUE method = Qnil;
  switch (wevent->reason())
  {
    case YEvent::Activated:
    {
      method = rb_intern("activated_fire");
      break;
    }
    case YEvent::ValueChanged:
    {
      method = rb_intern("value_change_fire");
      break;
    }
  }
  if (NIL_P(method))
    return event;

  YDialog * ydialog = dialog();
  VALUE r_dialog = widget_object_map_for(ydialog);
  VALUE r_event = convert_event(event);
  VALUE response = rb_funcall(r_widget, method, 2, r_event, r_dialog);

  if (TYPE(response) == T_SYMBOL) {
    if (response == ID2SYM(rb_intern("continue"))) {
      return event;
    }
    else if (response == ID2SYM(rb_intern("cancel"))) {
      return new YCancelEvent(); //dialog is responsible to free this value
    }
    else {
      rb_raise(rb_eRuntimeError, (string("Expected response: :continue or :cancel. Got: ") + StringValuePtr(response)).c_str());
      return 0;
    }
  }

  return (RTEST(response) ? event : 0);
}
