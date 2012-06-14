module UI
  class Event
    attr_reader :dialog

    def initialize(dialog)
      @dialog = dialog
    end

    def widget?
      self.is_a? WidgetEvent
    end

    def key?
      self.is_a? KeyEvent
    end

    def cancel?
      self.is_a? CancelEvent
    end

    def timeout?
      self.is_a? TimeoutEvent
    end
  end

  class WidgetEvent < Event
    attr_reader :widget,:reason

    def initialize widget,reason,dialog
      super dialog
      @widget = widget
      @reason = reason
    end
  end

  class KeyEvent < Event
    attr_reader :focused_widget,:key

    def initialize key,focused_widget,dialog
      super dialog
      @focused_widget = widget
      @key = key
    end
  end

  class CancelEvent < Event
    def initialize(dialog)
      super dialog
    end
  end

  class TimeoutEvent < Event
    def initialize(dialog)
      super dialog
    end
  end

  #TODO DebugEvent, MenuEvent
end
