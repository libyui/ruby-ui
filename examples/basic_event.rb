$: << File.expand_path(File.join(File.dirname(__FILE__), '../lib'))
require 'ui'

dialog = UI.main_dialog {
  vbox {
    label "Fill in this please"
    input_field "User Name:"
    hbox {
      push_button "Ok", :id=>:ok
      push_button "Cancel", :id=>cancel
    }
  }
}
event = dialog.wait_for_event
if event.is_a?(UI::WidgetEvent) && event.widget.id == :ok
  return true
else
  return false
end

