
module UI

  # Items are used in +SelectionWidget+ widgets
  #
  # @example
  #   selection_box << UI::Item.new("orange")
  #
  # +SelectionWidget+ will automatically convert other
  # objects to an item.
  #
  # @example
  #   selection_box << Person.new("John")
  #
  #   selection_box.items.first => #<UI::Item:0x0000000245abd0>
  #   selection_box.items.first.data => #<Person:0x0000000245abd0>
  #
  # The label of the item will also be automatically set to the
  # string representation of the object.
  #
  class Item

    include Enumerable

    alias_method :each, :each_child

    # @return [Array] all children
    alias_method :children, :to_a

    # Select this item
    #
    # @see select=
    def select!
      self.selected = true
    end

    # @return [String] string representation of the item
    #   If there is an object associated (data attribute)
    #   its string representation will be used. Otherwise
    #   the item's label.
    def to_s
      (data.to_s if data) || label
    end

  end

end