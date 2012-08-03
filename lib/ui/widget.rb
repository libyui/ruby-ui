module UI
  class Widget

    alias_method :each, :each_child
    alias_method :find, :find_widget

    include Enumerable

    # @return [Array<Widget>] this widget children
    def children
      to_a
    end

    CALLBACKS = [:activated, :value_changed, :clicked, :selection_changed]
    # Defines callback when widget is activated ( e.g. clicked on button )
    # @yield [UI::Event,UI::Dialog] block that gets event when it occur and
    #     dialog where it happen
    # @yieldreturn [nil,Symbol] return value specify what do in event handling
    #     nil represents stopping of event, :cancel generate CancelEvent instead
    #     and :continue pass event further
    def activated(&block)
      @activated = block_given? ? block : nil
    end
    alias_method :clicked, :activated

    # Defines callback when value of widget is changed
    # @see #activated
    # @yield [UI::Event] block that gets event when it occur
    # @yieldreturn [nil,Symbol] return value specify what do in event handling
    #     nil represents stopping of event, :cancel generate CancelEvent instead
    #     and :continue pass event further
    def value_changed(&block)
      @value_changed = block_given? ? block : nil
    end

    # Defines callback when selected item changes
    # @see #activated
    # @see #value_changed
    # @yield [UI::Event] block that gets event when it occurs
    # @yieldreturn [nil,Symbol] return value specify what do in event handling
    #     nil represents stopping of event, :cancel generates CancelEvent instead
    #     and :continue pass event further
    def selection_changed(&block)
      @selection_changed = block_given? ? block : nil
    end

    # Fires event handler
    # @visibility private
    def value_changed_fire (event, dialog)
      return :continue unless @value_changed
      @value_changed.call(event, dialog)
    end

    # Fires event handler
    # @visibility private
    def activated_fire (event, dialog)
      return :continue unless @activated
      @activated.call(event, dialog)
    end

    def selection_changed_fire(event, dialog)
      return :continue unless @selection_changed
      @selection_changed.call(event, dialog)
    end

  end
end
