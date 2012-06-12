require File.expand_path(File.join(File.dirname(__FILE__), 'helper'))
require 'ui'

class WidgetTest < Test::Unit::TestCase

  def setup
    @dialog = UI::Builder.create_main_dialog
    @vbox = UI::Builder.create_vbox(@dialog)
    @vbox1 = UI::Builder.create_hbox(@vbox)
    @hbox1 = UI::Builder.create_hbox(@vbox)
    @btn = UI::Builder.create_push_button(@vbox1, "Ok")
    @btn.id = :btn1
  end

  def teardown
    @dialog.destroy!
  end

  # Test ruby values as object ids
  def test_id

    assert @btn.has_id?
    assert_equal :btn1, @btn.id

    @btn.id = :foo

    assert @btn.has_id?
    assert_equal :foo, @btn.id

    obj = Object.new
    @btn.id = obj
    assert_equal obj, @btn.id
    assert_not_equal Object.new, @btn.id
  end

  def test_children
    assert_equal 1, @dialog.children_count
    assert_equal 2, @vbox.children_count
    assert_equal 0, @btn.children_count

    @vbox.each_child do |child|
      assert child.is_a?(UI::LayoutBox)
    end

    btn = @dialog.find_widget(:btn1)
    assert_nil btn


  end

  def test_properties
    assert @dialog.properties.include? :HWeight
    assert @dialog.properties.include? :Enabled
    assert @dialog[:Enabled]
    @dialog[:Enabled] = false
    assert !@dialog[:Enabled]
    assert @btn.properties.include? :Label
    assert_equal "Ok", @btn[:Label]
    @btn[:Label] = "Fail"
    assert "Fail", @btn[:Label]
  end

  def test_builder_properties_passing
    @dialog = UI.main_dialog(:id => "Test", :Enabled => false) {}
    assert !@dialog[:Enabled]
  end
end
