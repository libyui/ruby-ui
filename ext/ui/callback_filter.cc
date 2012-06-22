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

  VALUE ui = rb_define_module("UI");
  if (rb_class_of(response) == rb_const_get(ui, rb_intern("WidgetEvent"))) {
    // optimize if t is the same event we passed in
    if (response == r_event) {
      return event;
    }
    else {
      // in the future we may allow the users to create their own new events to pass down
      VALUE response_str = rb_any_to_s(response);
      rb_raise(rb_eRuntimeError, "Event was not created by the UI (this is not supported yet): :%s", StringValueCStr(response_str));
    }
  }

  if (TYPE(response) == T_SYMBOL) {
    if (response == ID2SYM(rb_intern("continue"))) {
      return event;
    }
    else if (response == ID2SYM(rb_intern("cancel"))) {
      return new YCancelEvent(); //dialog is responsible to free this value
    }
    else {
      ID got = SYM2ID(response);
      rb_raise(rb_eRuntimeError, "Expected response: :continue or :cancel. Got: :%s", rb_id2name(got));
      return 0;
    }
  }

  // by default we don't pass the event down and assume
  // it was "captured"
  return 0;
}
