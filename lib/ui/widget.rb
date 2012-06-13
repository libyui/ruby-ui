
module UI
  class Widget

    alias :each :each_child
    alias :find :find_widget

    include Enumerable

    # @return [Array<Widget>] this widget children
    def children
      to_a
    end

  end
end
