$: << File.expand_path(File.join(File.dirname(__FILE__), '../lib'))
require 'ui'
require 'pp'

dialog = UI.main_dialog {
  vbox(:id => :vbox1) {
    label "Press to add", :id => 'lbl1'
    hbox {
      progress_bar "Progress", :id => :bar
      push_button "Increase", :id => :inc_btn
      push_button "Cancel", :id => :cancel
    }
  }
}

dialog.find(:inc_btn).clicked do |ev|
  dialog.find(:bar).value += 10
  next :continue
end

dialog.find(:cancel).clicked do |ev|
  next :cancel
end

dialog.wait_for_event do |ev|
  break if ev.cancel?
  true
end