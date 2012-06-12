require File.expand_path(File.join(File.dirname(__FILE__), 'helper'))
require 'ui'

class WidgetTest < Test::Unit::TestCase

  def setup
    @dialog = UI::Builder.create_main_dialog
    @vbox = UI::Builder.create_vbox(@dialog)
    @vbox1 = UI::Builder.create_hbox(@vbox)
    @hbox1 = UI::Builder.create_hbox(@vbox)
    @widget = UI::Builder.create_push_button(@vbox1, "Ok")
  end

  def teardown
    @dialog.destroy!
  end

  # Test ruby values as object ids
  def test_id
    
    assert !@widget.has_id?
    assert_equal nil, @widget.id

    @widget.id = :foo

    assert @widget.has_id?
    assert_equal :foo, @widget.id

    obj = Object.new
    @widget.id = obj
    assert_equal obj, @widget.id
    assert_not_equal Object.new, @widget.id
  end

  def test_children
    assert_equal 1, @dialog.children_count
    assert_equal 2, @vbox.children_count
    assert_equal 0, @widget.children_count

    @vbox.each_child do |child|
      puts child.inspect
    end
  end

end