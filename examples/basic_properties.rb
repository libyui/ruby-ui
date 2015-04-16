$: << File.expand_path(File.join(File.dirname(__FILE__), '../lib'))
require 'ui'

include UI::Builder
main_dialog {
  vbox {
    label "Fill in this please"
    input_field "User Name:", :id=>:name, :Value => "John Doe"
    hbox {
      push_button "Cancel", :id=>:cancel, :HStretch => false
      push_button "Ok", :id=>:ok, :HStretch => false
    }
  }
}.wait_for_event
