require File.expand_path(File.join(File.dirname(__FILE__), 'helper'))
require 'ui'

class CheckBoxTest < Test::Unit::TestCase

  def test_basics

    dialog = UI.main_dialog {
      vbox {
        check_box "Option 1", :id => :opt1
        check_box "Option 2", :id => :opt2
        check_box "Option 3", :id => :opt3
      }
    }

    opt1 = dialog.find(:opt1)
    opt2 = dialog.find(:opt2)
    opt3 = dialog.find(:opt3)

    assert_kind_of UI::CheckBox, opt1

    assert !opt1.value
    assert !opt1.checked?
    assert !opt1.dont_care?

    opt1.checked = true
    assert opt1.checked?
    assert !opt1.dont_care?

    opt1.checked = false
    assert !opt1.checked?
    assert !opt1.dont_care?

    opt1.value = nil
    assert !opt1.checked?
    assert opt1.dont_care?

    opt1.dont_care!
    assert !opt1.checked?
    assert opt1.dont_care?

    assert_equal "Option 1", opt1.label

  end

end