$: << File.expand_path(File.join(File.dirname(__FILE__), '../lib'))
require 'ui'
require 'ui/builder/slim'

template =<<EOF
main_dialog
  vbox
    hbox
      input_field id="test2" Enter your name
      input_field id=15 Enter your name
    push_button id=2 Ok
    push_button id=1 activated=Proc.new{|event,dialog| event.widget[:Label] = event.widget[:Label]+"!";false} Ok
EOF

dialog = UI.slim(template, binding)
event = dialog.wait_for_event
puts event.inspect
event.widget[:Label] = "No longer OK"
again = 0
dialog.wait_for_event do |event|
  break unless event.is_a? UI::WidgetEvent
  event.widget[:Label] = "Loop version"
  again += 1
  again < 2
end
