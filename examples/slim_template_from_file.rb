$: << File.expand_path(File.join(File.dirname(__FILE__), '../lib'))
require 'ui'
require 'ui/builder/slim'

TEMPLATE_FILE = File.expand_path("../wizard1.uit",__FILE__)
TEMPLATE_FILE2 = File.expand_path("../wizard2.uit",__FILE__)

dialog = UI.slim(File.read(TEMPLATE_FILE))
dialog.wait_for_event
dialog2 = UI.slim(File.read(TEMPLATE_FILE2))
dialog2.wait_for_event
