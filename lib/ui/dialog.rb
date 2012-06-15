module UI
  class Dialog
    alias_method :wait_for_event_c, :wait_for_event
    class << self
      alias_method :current, :current_dialog
    end
    # extend wait_for_event with ability to process event in block.
    # @yield [event] pass raised event to block
    # @yield_param [UI::Event] event that occur
    # @yield_return [true,false] response if dialog should continue in waiting
    #   for another event
    # @example change button label
    #   dialog.wait_for_event do |event|
    #     break unless event.is_a? UI::WidgetEvent
    #     event.widget[:Label] = "Already pressed"
    #     true
    #   end
    def wait_for_event(options={})
      if block_given?
        while (yield(wait_for_event_c)) do
        end
      else
        return wait_for_event_c
      end
    end
  end
end
