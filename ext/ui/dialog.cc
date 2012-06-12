#include "widget.h"
#include "dialog.h"
#include "event.h"

/*
 * Document-class: UI::Dialog
 *
 * @see UI
 */

static void
dealloc(YDialog *dlg)
{
  yuiDebug() << "destroy ruby object for dialog" << dlg << std::endl;
  if (dlg->isValid())
    dlg->destroy();
}

VALUE
ui_wrap_dialog(YDialog *dlg)
{
  return Data_Wrap_Struct(cUIDialog, NULL, dealloc, dlg);
}

YDialog *
ui_unwrap_dialog(VALUE dlg)
{
  YDialog *ptr = 0L;
  Data_Get_Struct(dlg, YDialog, ptr);
  if (!ptr) 
    rb_raise(rb_eRuntimeError, "Dialog was already destroyed!");
  return ptr;
}

static VALUE
destroy(VALUE self)
{    
    YDialog *ptr = ui_unwrap_dialog(self);
    ptr->destroy();

    // Now the underlaying object is deleted (ptr) but
    // the ruby object still exists, make it invalid
    DATA_PTR(self) = 0;

    return Qnil;
}

/*
 * Open a newsly created dialog: Finalize it and make it visible on the
 * screen.
 *
 * Applications should call this once after all children are created.
 * If the application does not do this, it will be done automatically upon the
 * next call to Dialog#wait_for_event (or related).
 *
 */
static VALUE
open(VALUE self)
{    
    YDialog *ptr = ui_unwrap_dialog(self);
    ptr->open();
    return self;
}

/*
 * @return [Boolean] true if Dialog#open was already called
 */
static VALUE
is_open(VALUE self)
{    
    YDialog *ptr = ui_unwrap_dialog(self);
    return ptr->isOpen() ? Qtrue : Qfalse;
}

static VALUE
wait_for_event(VALUE self)
{
    YDialog *ptr = ui_unwrap_dialog(self);    
    YEvent * ev = ptr->waitForEvent();
    return convert_event(ev);
}

VALUE cUIDialog;
void init_ui_dialog()
{
  VALUE ui = rb_define_module("UI");

  VALUE klass = rb_define_class_under(ui, "Dialog", cUIWidget);
  cUIDialog = klass;

  rb_define_method(klass, "wait_for_event", RUBY_METHOD_FUNC(wait_for_event), 0);
  rb_define_method(klass, "destroy!", RUBY_METHOD_FUNC(destroy), 0);
  rb_define_method(klass, "open", RUBY_METHOD_FUNC(open), 0);
  rb_define_method(klass, "open?", RUBY_METHOD_FUNC(is_open), 0);

}

