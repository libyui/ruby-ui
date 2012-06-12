require File.expand_path(File.join(File.dirname(__FILE__), 'helper'))
require 'ui'

class DialogTest < Test::Unit::TestCase

  def test_destroy_invalid
    
    dialog = UI::Builder.create_main_dialog

    assert !dialog.open?
    dialog.open
    assert dialog.open?

    dialog.destroy!

    assert_raises RuntimeError do
      dialog.children_count
    end

  end

end