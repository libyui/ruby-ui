$: << File.expand_path(File.join(File.dirname(__FILE__), '../lib'))
require 'ui'
require 'ui/builder/slim'

template =<<EOF
main_dialog
  vbox
    hbox
      input_field Enter your name    
    push_button Ok
EOF

dialog = UI.slim(template)
dialog.wait_for_event
