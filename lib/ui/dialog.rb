module UI
  class Dialog
    alias_method :wait_for_event_c, :wait_for_event
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
