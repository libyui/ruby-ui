$: << File.expand_path(File.join(File.dirname(__FILE__), '../lib'))
require 'ui'
require 'pp'

dialog = UI.main_dialog {
  vbox(:id => :vbox1) {
    label "Fill in this please", :id => 'lbl1'
    input_field "User Name:"
    hbox {      
      push_button "Ok"
      push_button "Cancel"
    }
  }
}
#.wait_for_event

vbox = dialog.find_widget(:vbox1)


dialog.each_child do |child|
  #puts child
end



pp UI.object_map

#STDERR.puts dialog.inspect



