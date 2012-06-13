#include <stdio.h>

#include <deque>

#include <yui/YUI.h>
#include <yui/YWidgetFactory.h>
#include <yui/YMacro.h>
#include <yui/YMacroRecorder.h>

#include "widget_object_map.h"

#include "event.h"
#include "ui.h"
#include "widget.h"
#include "dialog.h"
#include "input_field.h"
#include "layout_box.h"
#include "label.h"
#include "push_button.h"
#include "rich_text.h"
#include "spacing.h"
#include "squash.h"
#include "ui_builder.h"

VALUE mUI;

#if 0
static std::deque<VALUE> _fakeUserInputQueue;

static VALUE
do_user_input(const char *builtin_name,
              long timeout_millisec,
              bool wait)
{
  // Plausibility check for timeout

  if ( timeout_millisec < 0 )
  {
    yuiError() << builtin_name << "(): Invalid value " << timeout_millisec
      << " for timeout - assuming 0"
      << endl;

    timeout_millisec = 0;
  }

  YEvent *  event = 0;
  VALUE input = Qnil;
  
  try {
    YDialog * dialog = YDialog::currentDialog();
    // Check for leftover postponed shortcut check

    if ( dialog->shortcutCheckPostponed() ) {
      yuiError() << "Missing UI::CheckShortcuts() before UI::" << builtin_name
        << "() after UI::PostponeShortcutCheck()!"
        << endl;

      dialog->checkShortcuts( true );
    }

    // Handle events

    if ( fakeUserInputQueue.empty() ) {
      if (wait)
        event = dialog->waitForEvent( timeout_millisec );
      else
        event = dialog->pollEvent();

      if (event) {
        input = convert_event(event);
      }
    }
    else { // _fakeUserInputQueue contains elements -> use the first one
      // Handle macro playing
      input = _fakeUserInputQueue.front();
      yuiDebug() << "Using event from fakeUserInputQueue: "<< input << endl;
      _fakeUserInputQueue.pop_front();
    }

    // Handle macro recording

    if ( YMacro::recording() ) {
      YCPMacroRecorder * macroRecorder = dynamic_cast<YCPMacroRecorder *> ( YMacro::recorder() );

      if ( macroRecorder ) {
        if ( ! input->isVoid() || wait ) { // Don't record empty PollInput() calls
          macroRecorder->beginBlock();
          dialog->saveUserInput( macroRecorder );
          macroRecorder->recordUserInput( input );
          macroRecorder->endBlock();
        }
      }
    }
  }
  catch ( YUIException & exception ) {
    YUI_CAUGHT( exception );
    rb_raise(rb_eRuntimeError, exception.msg().c_str());
  }

  return input;
}
#endif

extern VALUE widgetObjectMap;

/*  
 * @visibility private
 */
static VALUE object_map(VALUE self)
{
  return widgetObjectMap;
}

extern "C" {

void __attribute__ ((visibility("default"))) Init_ui() {

  YUILog::enableDebugLogging();

  /* this tracks C++ objects to ruby objects */
  widget_object_map_init();

  mUI = rb_define_module("UI");
  
  init_ui_widget();
  init_ui_dialog();
  init_ui_input_field();  
  init_ui_label();
  init_ui_layout_box();
  init_ui_push_button();
  init_ui_spacing();
  init_ui_squash();
  init_ui_rich_text();
  
  init_ui_ui_builder();
}

}