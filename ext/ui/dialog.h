#ifndef RUBY_NATIVE_UI_DIALOG_H
#define RUBY_NATIVE_UI_DIALOG_H

#include <yui/YDialog.h>
#include "ui.h"

void init_ui_dialog();

extern VALUE cUIDialog;
VALUE ui_wrap_dialog(YDialog *dlg);

void ui_dialog_push(YDialog *dlg);


#endif