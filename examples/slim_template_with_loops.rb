$: << File.expand_path(File.join(File.dirname(__FILE__), '../lib'))
require 'ui'

include UI::Template

template =<<EOF
main_dialog
  vbox
    hbox
      input_field Enter your name
    - if false
      label wrong
    - 10.times do |i|
      label test \#{i} abc
    push_button Ok
EOF

dialog = render text: template
dialog.wait_for_event
