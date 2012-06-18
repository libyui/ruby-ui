require File.expand_path(File.join(File.dirname(__FILE__), 'helper'))
require 'ui'
require 'ui/builder/slim'

class SlimTest < Test::Unit::TestCase

  def test_build_form

    template =<<EOF
main_dialog
  vbox
    label Database configuration
    input_field Hostname
    input_field Username
    input_field Password
    hbox
      push_button Back
      push_button Next
EOF

    dialog = UI.slim(template)

    dialog.wait_for_event
  end

end