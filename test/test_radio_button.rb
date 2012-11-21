require File.expand_path(File.join(File.dirname(__FILE__), 'helper'))
require 'ui'

class RadioButtonTest < Test::Unit::TestCase

  def test_basics

    dialog = UI.main_dialog {
      radio_button_group(:id => :group) {
        vbox {
          radio_button "Option 1", :id => :opt1
          radio_button "Option 2", :id => :opt2
          radio_button "Option 3", :id => :opt3
        }
      }
    }

    group = dialog.find(:group)
    assert_kind_of UI::RadioButtonGroup, group

    opt1 = dialog.find(:opt1)
    opt2 = dialog.find(:opt2)
    opt3 = dialog.find(:opt3)

    assert_kind_of UI::RadioButton, opt1
    assert_equal group, opt1.button_group

    assert !opt1.value
    assert !opt2.value
    assert !opt3.value

    opt1.value = true

    assert opt1.value
    assert !opt2.value
    assert !opt3.value

    # as it is a member of a group, changing
    # the 3rd one should disable the first

    opt3.value = true

    assert !opt1.value
    assert !opt2.value
    assert opt3.value

    # Convertions to Boolean
    opt2.value = String.new
    assert opt2.value
    opt2.value = nil
    assert !opt2.value

    assert_equal "Option 1", opt1.label
    opt1.label = "Changed"
    assert_equal "Changed", opt1.label

    assert !opt1.use_bold_font?
    opt1.use_bold_font = true
    assert opt1.use_bold_font?
  end

end