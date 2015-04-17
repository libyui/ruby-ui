$: << File.expand_path(File.join(File.dirname(__FILE__), '../lib'))
require 'ui'
require 'ui/template'

include UI::Template
template =<<EOF
main_dialog
  vbox
    hbox
      input_field Enter your name
    push_button Ok
EOF

dialog = render text: template
dialog.wait_for_event
