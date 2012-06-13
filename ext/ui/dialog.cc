#include "widget.h"
#include "dialog.h"
#include "event.h"
#include "callback_filter.h"
#include "exception_guard.h"

/*
 * Document-class: UI::Dialog
 *
 * @see UI
 */

static void
dealloc(YDialog *dlg)
{
  yuiDebug() << "destroy ruby object for dialog" << dlg << std::endl;

  ui_widget_dealloc(dlg);

  if (dlg->isValid())
    dlg->destroy();
  
}

VALUE
ui_wrap_dialog(YDialog *dlg)
{
  return Data_Wrap_Struct(cUIDialog, ui_widget_mark, dealloc, dlg);
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
  YEXCEPTION_TRY
  YDialog *ptr = ui_unwrap_dialog(self);
  dealloc(ptr);

  // Now the underlaying object is deleted (ptr) but
  // the ruby object still exists, make it invalid
  DATA_PTR(self) = 0;
  YEXCEPTION_CATCH

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
_open(VALUE self)
{
  YEXCEPTION_TRY
  YDialog *ptr = ui_unwrap_dialog(self);
  ptr->open();
  return self;
  YEXCEPTION_CATCH
}

/*
 * @return [Boolean] true if Dialog#open was already called
 */
static VALUE
is_open(VALUE self)
{
  YEXCEPTION_TRY
  YDialog *ptr = ui_unwrap_dialog(self);
  return ptr->isOpen() ? Qtrue : Qfalse;
  YEXCEPTION_CATCH
}

/*
 * Recalculate size of dialog. Useful after modification of childer.
 */
static VALUE
resize(VALUE self)
{
  YDialog *ptr = ui_unwrap_dialog(self);
  ptr->recalcLayout();
  return Qnil;
}

/*
 * Recalculate size of dialog. Useful after modification of childer.
 */
static VALUE
resize(VALUE self)
{    
    YDialog *ptr = ui_unwrap_dialog(self);
    ptr->recalcLayout();
    return Qnil;
}

static VALUE
wait_for_event(VALUE self)
{
  YEXCEPTION_TRY
  YDialog *ptr = ui_unwrap_dialog(self);
  new CallbackFilter(ptr); //see filter documentation
  YEvent * ev = ptr->waitForEvent();
  return convert_event(ev);
  YEXCEPTION_CATCH
}

/*
 * @return [Dialog] current dialog or +nil+ if no dialog open
 */
static VALUE
current_dialog(VALUE self)
{
  YDialog *dlg = YDialog::currentDialog(false);

  return widget_object_map_for(dlg);

}

VALUE cUIDialog;
void init_ui_dialog()
{
  VALUE ui = rb_define_module("UI");

  VALUE klass = rb_define_class_under(ui, "Dialog", cUIWidget);
  cUIDialog = klass;

  rb_define_method(klass, "wait_for_event", RUBY_METHOD_FUNC(wait_for_event), 0);
  rb_define_method(klass, "destroy!", RUBY_METHOD_FUNC(destroy), 0);
  rb_define_method(klass, "open", RUBY_METHOD_FUNC(_open), 0);
  rb_define_method(klass, "open?", RUBY_METHOD_FUNC(is_open), 0);
  rb_define_method(klass, "resize", RUBY_METHOD_FUNC(resize), 0);
  rb_define_singleton_method(klass, "current_dialog", RUBY_METHOD_FUNC(current_dialog), 0);

}

