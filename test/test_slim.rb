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

    assert_kind_of UI::Dialog, dialog
    vbox = dialog.children.first
    assert_kind_of UI::LayoutBox, vbox

    widgets = vbox.children
    assert_kind_of UI::Label, widgets[0]
    (1..3).each { |k| assert_kind_of UI::InputField, widgets[k]}
  end

end
