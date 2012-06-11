#include "widget.h"
#include "dialog.h"

static void
dealloc(YDialog *dlg)
{
  if (dlg->isValid())
    dlg->destroy();
}

VALUE
ui_wrap_dialog(YDialog *dlg)
{
  return Data_Wrap_Struct(cUIDialog, NULL, dealloc, dlg);
}

static VALUE
destroy(VALUE self)
{
    YDialog *ptr = 0L;
    Data_Get_Struct(self, YDialog, ptr);
    ptr->destroy();
    return Qnil;
}

static VALUE
wait_for_event(VALUE self)
{
    YDialog *ptr = 0L;
    Data_Get_Struct(self, YDialog, ptr);
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

