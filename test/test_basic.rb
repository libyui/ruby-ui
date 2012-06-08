require File.expand_path(File.join(File.dirname(__FILE__), 'helper'))
require 'ui'

class BasicTest < Test::Unit::TestCase

  def setup
    raise "Hello"
  end

  def test_hello    

    UI.dialog do
      vbox do
        label 'Hello'
        push_button 'OK'
      end
    end

  end


end