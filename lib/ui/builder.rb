require "ui/widget"

module UI

  module Builder
    TOPLEVEL_ELEMENTS = [:main_dialog, :popup_dialog]
    CONTAINER_ELEMENTS = [:vbox, :hbox, :hstretch, :vstretch,
                          :hspacing, :vspacing, :hsquash, :vsquash,
                          :hvsquash, :replace_point]
    LEAF_ELEMENTS = [:push_button, :input_field,:label, :rich_text]


    # @visibility private
    def initialize_widget(el, opts)
      el.id = opts[:id] if opts.has_key?(:id)
      properties = el.properties
      opts.each do |k,v|
        el[k] = v if properties.include? k
        if UI::Widget::CALLBACKS.include? k
          el.send(k,&v);
        end
      end
    end

    # @!group Top level elements

    # @!method main_dialog(&block)
    #   @return [Dialog] a main dialog
    #   @example
    #     dlg = UI.main_dialog {
    #       ...
    #     }

    # @!method popup_dialog(&block)
    #   @return [Dialog] a popup dialog
    #   @example
    #     dlg = UI.popup_dialog {
    #       ...
    #     }

    TOPLEVEL_ELEMENTS.each do |element|
      eval <<-EOM #use eval as ruby 1.8 don't have define_method with block
        def #{element}(opts={}, &block)
          el = Builder.create_#{element}
          initialize_widget(el, opts)
          el.instance_eval(&block)
          el
        end
      EOM
    end

    # @!endgroup

    # @!group Container elements

    # @!method vbox(&block)
    #   Creates a vertically alligned container
    #   @return [LayoutBox]
    #   @example
    #     UI.main_dialog {
    #       vbox {
    #         push_button "Ok"
    #       }
    #     }

    # @!method hbox(&block)
    # Horizontally aligned container
    # @see vbox
    # @see LayoutBox

    # @!method hstretch(&block)
    # @!method vstretch(&block)
    # @!method hspacing(&block)
    # @!method vspacing(&block)
    # @!method hsquash(&block)
    # @!method vsquash(&block)
    # @!method hvsquash(&block)

    # @!method replace_point(&block)

    # @!endgroup



    CONTAINER_ELEMENTS.each do |element|
      eval <<-EOM #use eval as ruby 1.8 don't have define_method with block
        def #{element}(opts={}, &block)
          el = Builder.create_#{element}(self)
          initialize_widget(el, opts)
          el.instance_eval(&block)
          el
        end
      EOM
    end

    # @!group Elements

    # @!method push_button(text, &block)
    #   Creates a push button
    #   @return [Button]
    #   @example
    #     UI.main_dialog {
    #       vbox {
    #         push_button "Ok"
    #       }
    #     }

    # @!method input_field(&block)
    # @!method rich_text(&block)
    # @!method label(&block)

    # @!endgroup

    LEAF_ELEMENTS.each do |element|
      eval <<-EOM #use eval as ruby 1.8 don't have define_method with block
        def #{element}(text, opts={}, &block)
          el = Builder.create_#{element}(self.is_a?(UI::Widget) ? self : nil, text)
          initialize_widget(el, opts)
          el
        end
      EOM
    end

  end

  extend Builder

  class Dialog
    include Builder
  end

  class LayoutBox
    include Builder
  end

  class Spacing
    include Builder
  end

  class Squash
    include Builder
  end

  class ReplacePoint
    include Builder
  end

end
