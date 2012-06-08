$: << File.expand_path(File.join(File.dirname(__FILE__), '../lib'))
require 'ui'

UI.popup_dialog {
  vbox {
    hbox {
      push_button "Ok"
      push_button "Cancel"
    }
  }
}.wait_for_event




