$: << File.expand_path(File.join(File.dirname(__FILE__), '../lib'))
require 'ui'
require 'ui/builder/slim'

template =<<EOF
main_dialog
  vbox
    hbox
      input_field Enter your name
    - if false
      label wrong
    - 10.times do |i|
      label test {i}
    push_button Ok
EOF

dialog = UI.slim(template, self)
dialog.wait_for_event
