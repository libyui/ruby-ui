module UI

  module Builder
    TOPLEVEL_ELEMENTS = [:main_dialog, :popup_dialog]
    CONTAINER_ELEMENTS = [:vbox, :hbox, :hstretch, :vstretch,
                          :hspacing, :vspacing, :hsquash, :vsquash, :hvsquash]
    LEAF_ELEMENTS = [:push_button, :input_field,:label, :rich_text]

    ELEMENT_CALLBACKS = [:activated, :value_changed]
    # @visibility private
    def initialize_widget(el, opts)
      el.id = opts[:id] if opts[:id]
      properties = el.properties
      opts.each do |k,v|
        el[k] = v if properties.include? k
        if ELEMENT_CALLBACKS.include? k
          el.send(k,&v);
        end
      end
    end

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

    LEAF_ELEMENTS.each do |element|
      eval <<-EOM #use eval as ruby 1.8 don't have define_method with block
        def #{element}(text, opts={}, &block)
          el = Builder.create_#{element}(self,text)
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

end
