$: << File.expand_path(File.join(File.dirname(__FILE__), '../lib'))
require 'ui'

include UI::Builder
dialog = main_dialog {
  vbox {
    label "Fill in this please"
    input_field "User Name:", :id=>:name
    hbox {
      push_button "Cancel", :id=>:cancel
      push_button "Clear", :id=>:clear
      push_button "Ok", :id=>:ok
    }
  }
}
response = nil
dialog.wait_for_event do |event|
  break if !event.is_a?(UI::WidgetEvent)
  if event.widget.id == :clear
    dialog.find(:name)[:Value] = ""
    next true
  end
  response = event.widget.id
  false
end
puts response.to_s
