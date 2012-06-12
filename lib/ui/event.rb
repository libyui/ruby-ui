module UI
  class Event
    attr_reader :dialog

    def initialize(dialog)
      @dialog = dialog
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
