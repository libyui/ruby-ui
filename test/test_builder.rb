require File.expand_path(File.join(File.dirname(__FILE__), 'helper'))
require 'ui'

class BuilderTest < Test::Unit::TestCase

  def test_build 

    dlg = UI.main_dialog {
      vbox {
        hbox {
          label 'Hello', :id => :lbl1
          push_button 'OK', :Enabled => false
        }
      }
    }

    assert_kind_of UI::Dialog, dlg
    
    vbox = dlg.children.first
    assert_kind_of UI::LayoutBox, vbox
    
    hbox = vbox.children.first
    assert_kind_of UI::LayoutBox, hbox

    lbl = hbox.children[0]
    assert_kind_of UI::Label, lbl
    assert_equal :lbl1, lbl.id

    btn = hbox.children[1]
    assert_kind_of UI::PushButton, btn
    assert !btn[:Enabled]

  end

  def test_exception_handling
    assert_raise(RuntimeError) {
      UI.main_dialog {
        push_button 'OK', :Enabled => false
        push_button 'OK', :Enabled => false
      }
    }
  end

end
