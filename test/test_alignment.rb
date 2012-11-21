require File.expand_path(File.join(File.dirname(__FILE__), 'helper'))
require 'ui'

class AlignmentTest < Test::Unit::TestCase

  def test_basics

    dlg = UI.main_dialog {
      vbox {

        frame("Align") {
          vbox {
            top(:id => :top) {
              label "At the top"
            }
            bottom(:id => :bottom) {
              label "At the bottom"
            }
            left(:id => :left) {
              label "At the Left"
            }
            right(:id => :right) {
              label "At the right"
            }
          }
        }

        frame("Center") {
          vbox {
            hcenter(:id => :hcenter) {
              label "H centered"
            }
            vcenter(:id => :vcenter) {
              label "V centered"
            }

            hvcenter(:id => :hvcenter) {
              label "HV centered"
            }
          }
        }

        frame("Margin Box") {
          margin_box(1,2,3,4) {
            label "margin 1 2 3 4"
          }
        }

        frame("Margin Box") {
          margin_box(3,7) {
            label "margin 3,7"
          }
        }
      }
    }

    top = dlg.find(:top)
    bottom = dlg.find(:bottom)

    assert_kind_of UI::Alignment, top
    assert_kind_of UI::Alignment, bottom

    dlg.wait_for_event
  end

end
