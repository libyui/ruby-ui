require 'temple'
require 'slim/parser'
require 'slim/filter'
require 'slim/interpolation'
require 'ui'
require 'pp'

module UI
  module Builder
    module Slim

      module IdGenerator
        def self.generate(name)
          @@table ||= {}
          @@table[name] ||= 0
          @@table[name] += 1
          num = @@table[name]
          return "#{name}_#{num}"
        end
      end

      class Compiler < Temple::Filter


        set_default_options :dictionary => 'self',
                            :partial => 'partial'

        def on_static(content)
          content.to_s
        end

        def on_multi(*exps)
          #remove all newlines it has no sense for us ( maybe in future for some edit box we place exception here :)
          exps.delete_if { |type,arg| type == :newline }
          return compile(exps.first) if exps.size == 1
          result = [:multi]
          exps.each do |exp|
            exp = compile(exp)
            if exp.is_a?(Array) && exp.first == :multi
              result.concat(exp[1..-1])
            else
              result << exp
            end
          end
        end

        def on_slim_tag(name, attrs, body)
          previous_parent = @current_parent
          name_sym = name.to_sym
          attributes = attrs[2..-1].reduce({}) { |acc,el| acc[el[3]] = el[5]; acc }
          id = attributes["id"]
          if UI::Builder::TOPLEVEL_ELEMENTS.include?(name_sym)
            obj = UI::Builder.send("create_#{name}".to_sym)
          elsif UI::Builder::LEAF_ELEMENTS.include?(name_sym)
            text = compile(body)
            id ||= text.gsub(/\s/,"_")
            obj = UI::Builder.send("create_#{name}".to_sym, @current_parent, text)
          elsif UI::Builder::CONTAINER_ELEMENTS.include?(name_sym)
            obj = UI::Builder.send("create_#{name}".to_sym, @current_parent)
          else
            raise "Unknown element type"
          end
          id ||= IdGenerator.generate name_sym
          obj.id = id.to_sym
          @current_parent = obj
          compile(body)
          @current_parent = previous_parent
          obj
        end
      end

      class Generator < Temple::Generator
        def call(exp)
          exp
        end
      end

      class Engine < Temple::Engine
        use ::Slim::Parser, :file, :tabsize, :encoding, :shortcut, :default_tag
        use ::Slim::Interpolation
        filter :DynamicInliner
        filter :MultiFlattener
        use Compiler
        use(:Generator) { UI::Builder::Slim::Generator.new }
      end

    end
  end
end

module UI
  def self.slim(io)
    UI::Builder::Slim::Engine.new.call(io)
  end
end
