$: << File.expand_path(File.join(File.dirname(__FILE__), '../lib'))
require 'ui'

EDIT_DIALOG_TEMPLATE = File.expand_path("../user_edit.yui",__FILE__)
SHOW_DIALOG_TEMPLATE = File.expand_path("../users.yui",__FILE__)

class User
  ATTRS = [ :first_name, :surname, :hair, :skill, :beer ]
  ATTRS.each do |attr|
    attr_accessor attr
  end
  def initialize
    ATTRS.each { |a| send :"#{a}=", "" }
  end
end

include UI::Template

def edit_user user
  dialog = render file: EDIT_DIALOG_TEMPLATE, context: user
  dialog.find(:clear).activated do |event,dialog|
    User::ATTRS.each { |a| dialog.find(a)[:Value] = "" }
    false
  end
  response = false
  dialog.wait_for_event do |event|
    if event.is_a?(UI::CancelEvent)
      break
    elsif event.is_a?(UI::WidgetEvent) && event.widget.id == :ok
      User::ATTRS.each { |a| user.send :"#{a}=",dialog.find(a)[:Value] }
      response = true
      break
    else
      raise "Unknown event #{event.inspect}"
    end
  end
  dialog.destroy!
  response
end

def add_user_to_dialog user,parent
  hbox = UI::Builder.create_hbox(parent)
  label = UI::Builder.create_label(hbox,"Surname: "+user.surname)
  button = UI::Builder.create_push_button(hbox,"Edit")
  button.activated do |widget,dialog|
    if edit_user user
      label[:Value] = "Surname: "+user.surname
    end
    false
  end
end

def show_users users
  @users = users
  dialog = render file: SHOW_DIALOG_TEMPLATE
  dialog.find(:save).activated do |event,dialog|
    path = UI.ask_for_existing_file Dir.pwd,"target File"
    puts users.to_json
    false
  end
  dialog.find(:add).activated do |event,dialog|
    user = User.new
    if edit_user user
      users << user
      add_user_to_dialog user,dialog.find(:users)
      dialog.resize
    end
    false
  end
  dialog.wait_for_event
end

puts ARGV.inspect
users = []
show_users users
