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
          @table ||= {}
          @table[name] ||= 0
          @table[name] += 1
          num = @table[name]
          return "#{name}_#{num}"
        end
      end

      class Compiler < ::Slim::Filter


        set_default_options :dictionary => 'self',
                            :partial => 'partial',
                            :context => nil

        def on_static(content)
          content.to_s
        end

        def on_multi(*exps)
          return compile(exps.first) if exps.size == 1
          exps.map { |exp| compile(exp) }
        end

        def parse_attributes attrs
          attributes = attrs[2..-1].reduce({}) do |acc,el|
            if el[0] == :slim #slim attrs
              acc[el[2].to_sym] = options[:context].instance_eval el[4];
            elsif el[0] == :html #match html attrs with static attr
              acc[el[2].to_sym] = el[3][1];
            else
              raise "Unknown attribute #{el.inspect}"
            end
            acc
          end
        end

        def on_slim_tag(name, attrs, body)
          previous_parent = @current_parent
          name_sym = name.to_sym
          pp attrs
          attributes = parse_attributes attrs
          pp attributes
          if UI::Builder::TOPLEVEL_ELEMENTS.include?(name_sym)
            obj = UI::Builder.send("create_#{name}".to_sym)
          elsif UI::Builder::LEAF_ELEMENTS.include?(name_sym)
            text = compile(body)
            pp text
            attributes[:id] ||= text.gsub(/\s|[-_:.]/,"_")
            obj = UI::Builder.send("create_#{name}".to_sym, @current_parent, text)
          elsif UI::Builder::CONTAINER_ELEMENTS.include?(name_sym)
            obj = UI::Builder.send("create_#{name}".to_sym, @current_parent)
          else
            raise "Unknown element type #{name}"
          end
          attributes[:id] ||= IdGenerator.generate name_sym
          UI.initialize_widget(obj,attributes)
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

      class Evaluator < ::Slim::Filter
        set_default_options :dictionary => 'self',
                            :partial => 'partial',
                            :context => nil
        def on_slim_output (*args)
          ret = options[:context].instance_eval(args[1])
          [:static,ret.to_s]
        end

        def on_multi(*exps)
          #remove all newlines it has no sense for us ( maybe in future for some edit box we place exception here :)
          exps.delete_if { |type,arg| type == :newline }
          result = [:multi]
          text = nil
          exps.each do |exp|
            exp = compile(exp)
            case exp.first
            when :static
              if text
                text << exp.last
              else
                text = exp.last.dup
                result << [:static, text]
              end
            when :multi
              result.concat(exp[1..-1])
              text = nil
            else
              result << exp
              text = nil
            end
          end
          result
        end
      end
      # Filter class that merge statics together, evaluate outputs and clean newlines
      class Cleaner < ::Slim::Filter
        set_default_options :dictionary => 'self',
                            :partial => 'partial',
                            :context => nil

        def on_multi(*exps)
          return compile(exps.first) if exps.size == 1
          result = [:multi]
          text = nil
          exps.each do |exp|
            exp = compile(exp)
            case exp.first
            when :static
              if text
                text << exp.last
              else
                text = exp.last.dup
                result << [:static, text]
              end
            when :multi
              result.concat(exp[1..-1])
              text = nil
            else
              result << exp
              text = nil
            end
          end
          result
        end
      end

      class Engine < Temple::Engine
        set_default_options :context => nil
        use ::Slim::Parser, :file, :tabsize, :encoding, :shortcut, :default_tag
        use ::Slim::Interpolation
        use(:Evaluator) { Evaluator.new options }
        use(:Cleaner) { Cleaner.new options }
        use(:Compiler) { Compiler.new options }
        use Generator
      end

    end
  end
end

module UI
  def self.slim(io,options={})
    UI::Builder::Slim::Engine.new(options).call(io)
  end
end
