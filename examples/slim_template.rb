$: << File.expand_path(File.join(File.dirname(__FILE__), '../lib'))
require 'ui'
require 'ui/builder/slim'

template =<<EOF
main_dialog
  vbox
    push_button Ok
    hbox
      input_field Enter your name    
EOF

dialog = UI.slim(template)
dialog.wait_for_event
