require File.expand_path(File.join(File.dirname(__FILE__), 'helper'))
require 'ui'

class DumbClass
  def to_s
    "LOL"
  end
end

class ItemTest < Test::Unit::TestCase

  def test_basics
    dialog = UI.main_dialog {
      vbox(:id => :vbox1) {
        selection_box "Elements", :id => :box
      }
    }
    box = dialog.find(:box)
    assert_kind_of UI::SelectionBox, box

    # this item is not owned
    item = UI::Item.new('Unowned')

    assert_equal '', item.icon_name
    item.icon_name = 'foo'
    assert_equal 'foo', item.icon_name

    assert_equal 'Unowned', item.label
    item.label = 'foo'
    assert_equal 'foo', item.label

    assert !item.selected?
    item.selected = true
    assert item.selected?
    item.selected = false
    assert !item.selected?
    item.select!
    assert item.selected?

    assert_nil item.parent

    box << UI::Item.new('Hello')
    box << 'Bye'
    obj = DumbClass.new
    box << obj

    assert_kind_of Array, box.items
    assert_equal 3, box.items.size

    box.each_item do |item|
      assert_kind_of UI::Item, item
    end

    items = box.items

    assert_equal items[0], box.find('Hello')
    assert_equal items[2], box.find('LOL')
    assert_equal items[2], box.find(obj)

    assert_equal 'Hello', items[0].label
    assert_equal 'Bye', items[1].label
    assert_equal 'LOL', items[2].label

    assert_equal obj, items[2].data

    #dialog.destroy
    #STDERR.puts "Hello!!!: #{item.instance_variable_get("@_owned")}"
  end

end