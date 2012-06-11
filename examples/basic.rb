$: << File.expand_path(File.join(File.dirname(__FILE__), '../lib'))
require 'ui'

dialog = UI.main_dialog {
  vbox {
    label "Fill in this please"
    input_field "User Name:"
    hbox {      
      push_button "Ok"
      push_button "Cancel"
    }
  }
}.wait_for_event

STDERR.puts dialog.inspect



