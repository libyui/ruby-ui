require File.expand_path(File.join(File.dirname(__FILE__), 'helper'))
require 'ui'

class ProgressBarTest < Test::Unit::TestCase

  def test_basics

    dlg = UI.main_dialog {
      progress_bar 'Progress', :id => :bar
    }

    bar = dlg.children.first
    assert_kind_of UI::ProgressBar, bar
    assert_equal 100, bar.max_value
    assert_equal 0, bar.value

    bar.value = 50
    assert_equal 50, bar.value
  end

end
