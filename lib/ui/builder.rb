require "ui/widget"

module UI

  module Builder
    TOPLEVEL_ELEMENTS = [:main_dialog, :popup_dialog]
    CONTAINER_ELEMENTS = [:vbox, :hbox, :hstretch, :vstretch,
                          :hspacing, :vspacing, :hsquash, :vsquash,
                          :hvsquash, :replace_point]
    LEAF_ELEMENTS = [:push_button, :input_field, :label, :progress_bar, :rich_text]


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

    [TOPLEVEL_ELEMENTS, CONTAINER_ELEMENTS,
      LEAF_ELEMENTS].flatten.each do |element|
      eval <<-EOM #use eval as ruby 1.8 don't have define_method with block
        def #{element}(*args, &block)
          opts = {}
          # If last element is a Hash
          # we assume they are options
          if args.last.is_a?(Hash)
            opts = args.pop
          end
          # add parent if needed
          unless TOPLEVEL_ELEMENTS.include?(:#{element})
            args.unshift(self)
          end
          el = Builder.create_#{element}(*args)
          initialize_widget(el, opts)
          unless LEAF_ELEMENTS.include?(:#{element})
            el.instance_eval(&block)
          end
          el
        end
      EOM
    end

    # @!group Top level elements

    # @!method main_dialog(&block)
    #   @return [Dialog] a main dialog
    #   @example
    #     dlg = UI.main_dialog {
    #       ...
    #     }
    #def main_dialog(opts={}, &block)
    #  el = Builder.create_main_dialog
    #
    #end
    # @!method popup_dialog(&block)
    #   @return [Dialog] a popup dialog
    #   @example
    #     dlg = UI.popup_dialog {
    #       ...
    #     }

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

    # @!method progress_bar(label, max_value = 100)
    #   Creates a progress bar
    #   @param [String] label The caption above the progress bar
    #   @param [Fixnum] max_value Maximum progress value
    #   @return [ProgressBar]
    #   @example
    #     UI.main_dialog {
    #       vbox {
    #         progress_bar "Current progress"
    #       }
    #     }

    # @!method input_field(&block)
    # @!method rich_text(&block)
    # @!method label(&block)

    # @!endgroup

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
