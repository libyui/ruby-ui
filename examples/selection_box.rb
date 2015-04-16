$: << File.expand_path(File.join(File.dirname(__FILE__), '../lib'))
require 'ui'
require 'ui/builder/slim'
require 'pp'
#require 'debugger'

include UI::Builder
dialog = main_dialog {
  vbox(:id => :vbox1) {
    selection_box "Elements", :id => :box
    right {
      push_button "Close", :id => :cancel
    }
  }
}

class DumbClass
  def to_s
    "LOL!"
  end
end

box = dialog.find(:box)

item = UI::Item.new("Hello")

box << "Bye"
box << item
box << DumbClass.new

box[:Notify] = true
box.selection_changed do |ev|
  UI.debug "changed"
  UI::Dialog.show_text("Selected: #{box.selected_item}")
end

count = 0
dialog.wait_for_event do |ev|
  UI.debug ev.inspect
  #
  break if ev.widget.id == :cancel
  break if ev.cancel? || count > 10
  count += 1
  true
end
