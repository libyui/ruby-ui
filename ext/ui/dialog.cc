#include <list>

#include "widget.h"
#include "dialog.h"
#include "event.h"
#include "callback_filter.h"
#include "exception_guard.h"

using std::list;
using std::find;

/**
 * We have to keep our own duplicated dialog
 * stack as libyui do not provide access to it
 * and we need to delete the dialogs in the
 * right order by implementing the GC
 * mark function.
 */
list<YDialog *> sDialogStack;

/*
 * Document-class: UI::Dialog
 *
 * @see UI
 */

static void
dealloc(YDialog *dlg)
{
  ui_widget_dealloc(dlg);
  // Only delete the dialog if it is the topmost one.
  // Deletion in random order should not happen thanks to
  // sDialogStack and mark(), except at exit.
  //
  // At exit the UI finalizer deletes all dialogs anyway so
  // we don't care.
  if (dlg->isTopmostDialog() && dlg->isValid() && dlg->destroy(false)) {
    yuiDebug() << "destroy ruby object for dialog" << dlg << std::endl;

  //  dlg->deleteTopmostDialog();
    sDialogStack.pop_back();
  }
  else
  {
    yuiDebug() << "Not topmost. Skipping destroy ruby object for dialog" << dlg << std::endl;
  }
}

static void
mark(YDialog *dlg)
{
  yuiDebug() << "mark " << dlg << std::endl;
  // mark all parent dialogs
  list<YDialog *>::reverse_iterator it = find(sDialogStack.rbegin(), sDialogStack.rend(), dlg);
  if (it != sDialogStack.rend()) {
    it++;
    for (; it != sDialogStack.rend(); ++it) {
      VALUE obj = widget_object_map_for(*it);
      if (obj != Qnil) {
        yuiDebug() << "  -> " << *it << std::endl;
        rb_gc_mark(obj);
      }
    }
  }
  ui_widget_mark(dlg);
}

void
ui_dialog_push(YDialog *dlg)
{
  sDialogStack.push_back(dlg);
}

VALUE
ui_wrap_dialog(YDialog *dlg)
{
  return Data_Wrap_Struct(cUIDialog, mark, dealloc, dlg);
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
  YEXCEPTION_TRY
  YDialog *ptr = ui_unwrap_dialog(self);
  ptr->recalcLayout();
  return Qnil;
  YEXCEPTION_CATCH
}

/*
 * Extend wait_for_event with ability to process event in block.
 * @yield [event] pass raised event to block
 * @yield_param [UI::Event] event that occur
 * @yield_return [true,false] response if dialog should continue in waiting
 *   for another event
 *   @example change button label
 *     dialog.wait_for_event do |event|
 *       break unless event.is_a? UI::WidgetEvent
 *       event.widget[:Label] = "Already pressed"
 *       true
 *     end
 */
static VALUE
wait_for_event(VALUE self)
{
  YEXCEPTION_TRY

  YDialog *ptr = ui_unwrap_dialog(self);
  new CallbackFilter(ptr); //see filter documentation
  YEvent *ev = 0L;
  do {
    ev = ptr->waitForEvent();
    if (!rb_block_given_p())
      return convert_event(ev);
  } while (rb_yield(convert_event(ev)) != Qfalse);

  YEXCEPTION_CATCH
}

/*
 * @return [Dialog] current dialog or +nil+ if no dialog open
 */
static VALUE
current_dialog(VALUE self)
{
  YEXCEPTION_TRY
  YDialog *dlg = YDialog::currentDialog(false);
  return widget_object_map_for(dlg);
  YEXCEPTION_CATCH
}

/*
 * how the specified text in a pop-up dialog with a local event loop.
 * This is useful for help texts.
 * 'richText' indicates if YRichText formatting should be applied.
 */
static VALUE
show_text(VALUE klass, VALUE text)
{
  YEXCEPTION_TRY
  YDialog::showText(StringValueCStr(text));
  return Qnil;
  YEXCEPTION_CATCH
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
  rb_define_singleton_method(klass, "show_text", RUBY_METHOD_FUNC(show_text), 1);

}

