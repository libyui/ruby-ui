require File.expand_path(File.join(File.dirname(__FILE__), 'helper'))
require 'ui'

class ReplacePointTest < Test::Unit::TestCase

  def test_replace

    dialog = UI.main_dialog {
      vbox {
        label "This is fixed", :id => :lbl1
        replace_point(:id => :point) {
          label "Original content", :id => :lbl2
        }
      }
    }

    assert_raise(RuntimeError, "Only works with replace points") do
      dialog.replace(:lbl1) do
        label "New content"
      end
    end

    assert_equal("Original content", dialog.find(:lbl2)[:Value])

    dialog.replace(:point) do
      label "New content", :id => :lbl2
    end

    assert_equal("New content", dialog.find(:lbl2)[:Value])


  end

end