require 'temple'
require 'temple/generators/string_buffer'
require 'slim'
require 'slim/parser'
require 'slim/filter'
require 'slim/embedded'
require 'slim/interpolation'
require 'ui'
require 'pp'

module UI
  module Builder

    # This module allows to build user interfaces
    # using slim templates (http://www.slim-lang.org)
    #
    # @see UI#slim
    module Slim

      # @visibility private
      module IdGenerator
        def self.generate(name)
          @table ||= {}
          @table[name] ||= 0
          @table[name] += 1
          num = @table[name]
          return "#{name}_#{num}"
        end
      end

      # @visibility private
      class Generator < Temple::Generator
        define_options :freeze_static => false

        def call(exp)
          compile(exp)
        end

        def concat(str)
          str
        end

        def on_static(text)
          text
        end

        def on_multi(*exps)
          exps.map{|e| compile(e)}.join(" ")
        end

        def on_code(code)
          code + "\n"
        end
      end

      # @visibility private
      class Evaluator < ::Slim::Filter
        def on_slim_output (*args)
          ret = options[:context].instance_eval(args[1])
          [:static,ret.to_s]
        end

        # @visibility private
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
      # @visibility private
      class Cleaner < ::Slim::Filter

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

      # Convert html tags to dynamic ruby code
      # @visibility private
      class ToRuby < ::Slim::Filter
        def on_static(body)
          [:static, "\""+compile(body)+"\""]
        end

        def on_escape(_flag, body)
          [:multi,
            # enclose it into "" to allow string append
            [:static, "\"\#{"],
            compile(body),
            [:static, "}\""]
          ]
        end

        def parse_attributes attrs
          return {} unless attrs.is_a? Array
          puts attrs.inspect
          attributes = attrs[2..-1].reduce("") do |acc,el|
            acc << ", " unless acc.empty?
            if el[0] == :slim #slim attrs
              acc << ":#{el[2]} => #{el[4]}"
            elsif el[0] == :html #match html attrs with static attr
              el2 = el[3]
              case el2[0]
              when :slim
                acc << ":#{el[2]} => #{el2[3]}"
              when :escape
                acc << ":#{el[2]} => #{el2[2][1]}"
              else
                 raise "unknown attr #{el.inspect}"
              end
            else
              raise "Unknown attribute #{el.inspect}"
            end
            acc
          end
        end

        def on_slim_tag(name, attrs, body)
          attrs_str = parse_attributes attrs
          if LEAF_ELEMENTS.include?(name.to_sym)
            attrs_str.prepend ", " unless attrs_str.empty?
            [:multi, 
              [:static, "#{name} "],
              compile(body),
              [:dynamic, attrs_str + "\n"]
            ]
          else
            attrs_str = "("+attrs_str+")" unless attrs_str.empty?

            [ :multi, 
              [ :dynamic, "#{name}#{ attrs_str } {\n"],
              compile(body),
              [ :static, "}\n" ]
            ]
          end
        end
        alias_method :on_html_tag, :on_slim_tag
      end

      # @visibility private
      class Engine < Temple::Engine
        use ::Slim::Parser
        use ::Slim::Interpolation
        use ::Slim::DoInserter
        use ::Slim::EndInserter
        use ::Slim::Controls
        use Evaluator
        use Cleaner
        use ToRuby
        use Generator
      end

    end
  end
end

module UI

  # Builds a widget/dialog using a slim template
  # 
  # {include:file:examples/slim_template.rb}
  def self.slim(io, context, options={})
    puts "Context: #{context.inspect}"
    code = UI::Builder::Slim::Engine.new(options).call(io)
    puts code
    context.extend UI::Builder
    context.instance_eval code
  end
end
