require File.expand_path(File.join(File.dirname(__FILE__), 'helper'))
require 'ui'

class WidgetTest < Test::Unit::TestCase

  def setup    
  end

  # Test ruby values as object ids
  def test_id
    dialog = UI::Builder.create_main_dialog
    widget = UI::Builder.create_push_button(dialog, "Ok")

    assert !widget.has_id?

    assert_equal nil, widget.id

    widget.id = :foo

    assert widget.has_id?

    assert_equal :foo, widget.id

    obj = Object.new
    widget.id = obj
    assert_equal obj, widget.id
    assert_not_equal Object.new, widget.id
  end


end