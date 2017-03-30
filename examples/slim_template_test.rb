$: << File.expand_path(File.join(File.dirname(__FILE__), '../lib'))
require 'ui'

include UI::Template

template =<<EOF
main_dialog
  vbox
    hbox
      input_field id="test2" Enter your name
      vspacing 0.3
      vspacing 0.3
      hbox
        push_button id=3 Test
      input_field id=15 Enter your name
    / test comment
    push_button id=2 Ok
    push_button id=1 activated=Proc.new{|event,dialog| event.widget[:Label] = event.widget[:Label]+"!";false} Ok
EOF

dialog = render text: template
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
