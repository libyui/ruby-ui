module UI
  class Widget

    alias_method :each, :each_child
    alias_method :find, :find_widget

    include Enumerable

    # @return [Array<Widget>] this widget children
    def children
      to_a
    end

    CALLBACKS = [:activated, :value_changed, :clicked]
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

    # Fires event handler
    def activated_fire (event, dialog)
      return :continue unless @activated
      @activated.call(event, dialog)
    end

    # Defines callback when value of widget is changed
    # @see #activated
    # @yield [UI::Event] block that gets event when it occur
    # @yieldreturn [nil,Symbol] return value specify what do in event handling
    #     nil represents stopping of event, :cancel generate CancelEvent instead
    #     and :continue pass event further
    def value_change(&block)
      @value_changed = block_given? ? block : nil
    end

    # Fires event handler
    def value_change_fire (event, dialog)
      return :continue unless @value_change
      @value_change.call(event, dialog)
    end

  end
end
