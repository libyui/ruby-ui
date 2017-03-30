$: << File.expand_path(File.join(File.dirname(__FILE__), '../lib'))
require 'ui'
require 'ui/builder/slim'
require 'pp'
#require 'debugger'

include UI::Builder

dialog = main_dialog {
  vbox {
    # row 1
    hbox(:id => :hbox1) {
      frame("PushButton", :Weight => 1) {
        hvcenter {
          vbox {
            push_button "Enabled"
            vspacing
            push_button "Disabled", :Enabled => false
          }
        }
      }
      frame("Label", :Weight => 1) {
        hvcenter {
          vbox {
            label "Headline"
            label "Label"
          }
        }
      }
      frame("CheckBox", :Weight => 1) {
        hvcenter {
          vbox {
            check_box "Check0"
            check_box "Check1"
            check_box "Disabled", :Enabled => false
          }
        }
      }
      frame("RadioButton", :Weight => 1) {
        hvcenter {
          radio_button_group {
            vbox {
              radio_button "Radio0"
              radio_button "Radio1"
              radio_button "Disabled", :Enabled => false
            }
          }
        }
      }
    }
  }
}

count = 0
dialog.wait_for_event do |ev|
  break if ev.cancel? || count > 10
  count += 1
  true
end
