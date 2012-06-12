#include "widget.h"
#include "dialog.h"

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

static VALUE
wait_for_event(VALUE self)
{
    YDialog *ptr = ui_unwrap_dialog(self);    
    ptr->waitForEvent();
    return Qnil;
}

VALUE cUIDialog;
void init_ui_dialog()
{
  VALUE ui = rb_define_module("UI");

  VALUE klass = rb_define_class_under(ui, "Dialog", cUIWidget);
  cUIDialog = klass;

  //rb_define_singleton_method(klass, "new", new, 1);  
  rb_define_method(cUIDialog, "wait_for_event", C_FUNC(wait_for_event), 0);
  rb_define_method(cUIDialog, "destroy!", C_FUNC(destroy), 0);

}

