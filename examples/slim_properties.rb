$: << File.expand_path(File.join(File.dirname(__FILE__), '../lib'))
require 'ui'

include UI::Template

template =<<EOF
main_dialog
  vbox
    hbox
      input_field id="input" Value="John Doe" Enter your name
    push_button HStretch=false Ok
EOF

dialog = render text: template
dialog.wait_for_event
