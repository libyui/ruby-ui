require "ui/version"
require "ui.so"

module UI
  # Your code goes here...

  # The builder module provides a DSL to
  # build user interfaces using ruby blocks:
  #
  module Builder
    def popup_dialog(&block)
      popup = Builder.create_popup_dialog
      popup.instance_eval(&block)
      popup
    end

    def hbox(&block)
      hbox = Builder.create_hbox(self)
      hbox.instance_eval(&block)
      hbox
    end

    def vbox(&block)
      vbox = Builder.create_vbox(self)
      vbox.instance_eval(&block)
      vbox
    end

    def push_button(text, &block)
      Builder.create_push_button(self, text)
    end

  end

  extend Builder

  class Dialog
    include Builder
  end

  class LayoutBox
    include Builder
  end


end

