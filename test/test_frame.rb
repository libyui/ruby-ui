require File.expand_path(File.join(File.dirname(__FILE__), 'helper'))
require 'ui'

class FrameTest < Test::Unit::TestCase

  def test_basics

    dlg = UI.main_dialog {
      frame('Title', :id => :frame) {
        label "Content text"
      }
    }

    frame = dlg.children.first
    assert_kind_of UI::Frame, frame
    assert_equal "Title", frame.label

    frame.label = "New title"
    assert_equal "New Title", frame.label
  end

end
