module UI
  class Dialog

    class << self
      alias_method :current, :current_dialog
    end

  end
end
