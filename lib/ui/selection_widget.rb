
module UI
  class SelectionWidget

    include Enumerable

    alias_method :'<<', :add_item
    alias_method :each, :each_item
    alias_method :items, :to_a

    # Find the (first) item with the specified label or
    # data attribute.
    #
    # @return nil if there is no item with that label or data
    #   attribute
    def find_item(item)
      all = self.items
      return item if item.is_a?(UI::Item) && all.include?(item)

      by_label = all.select do |x|
        x.label == item
      end.first

      by_data = all.select do |x|
        x.data == item
      end.first

      by_label || by_data
    end
    alias_method :find, :find_item

    # @return all selected items.
    def selected_items
      items.select(&:'selected?')
    end

    # @return the (first) selected item or nil if none is selected.
    def selected_item
      selected_items.first
    end

  end
end