#include "event.h"
#include "widget_object_map.h"
#include <string>

VALUE convert_event(const YEvent * event)
{
  const YDialog * dialog = event->dialog();

  VALUE rb_dialog = Qnil;

  if (dialog) {
    rb_dialog = widget_object_map_for(dialog);
  }

    VALUE ui = rb_define_module("UI");
  VALUE result = Qnil;

  switch (event->eventType())
  {
  case YEvent::WidgetEvent:
    const YWidgetEvent* we = static_cast<const YWidgetEvent*>(event);
    VALUE cls = rb_const_get(ui, rb_intern("WidgetEvent"));
    VALUE reason = Qnil;
    switch (we->reason())
    {
    case YEvent::Activated:
      reason = ID2SYM(rb_intern("activated"));
      break;
    case YEvent::SelectionChanged:
      reason = ID2SYM(rb_intern("selection_changed"));
      break;
    case YEvent::ValueChanged:
      reason = ID2SYM(rb_intern("value_changed"));
      break;
    case YEvent::ContextMenuActivated:
      reason = ID2SYM(rb_intern("context_menu_activated"));
      break;
    case YEvent::UnknownReason:
      break; //default nil is fine here
    default:
      rb_raise(rb_eNotImpError, "Unknown reason in event");
    }
    VALUE widget = widget_object_map_for(we->widget());
    result = rb_funcall(cls, rb_intern("new"), 3, widget, reason, rb_dialog);
    break;
  case YEvent::KeyEvent:
    const YKeyEvent* we = static_cast<const YKeyEvent*>(event);
    VALUE cls = rb_const_get(ui, rb_intern("KeyEvent"));
    VALUE widget = widget_object_map_for(we->focusWidget());
    VALUE key = ID2SYM(rb_intern(we->keySymbol().c_str()));
    result = rb_funcall(cls, rb_intern("new"), 3, key, widget, rb_dialog);
    break;
  case YEvent::CancelEvent:
    const YCancelEvent* we = static_cast<const YCancelEvent*>(event);
    VALUE cls = rb_const_get(ui, rb_intern("CancelEvent"));
    result = rb_funcall(cls, rb_intern("new"), 1, rb_dialog);
    break;
  case YEvent::TimeoutEvent:
    const YTimeoutEvent* we = static_cast<const YTimeoutEvent*>(event);
    VALUE cls = rb_const_get(ui,rb_intern("TimeoutEvent"));
    result = rb_funcall(cls, rb_intern("new"), 1, rb_dialog);
    break;
  default: //TODO
      rb_raise(rb_eNotImpError, (std::string("Unknown event type ") + YEvent::toString(event->eventType())).c_str());
  }
  return result;
}
