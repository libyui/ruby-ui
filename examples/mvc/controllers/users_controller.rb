require 'ui'
require 'ui/builder/slim'
require File.expand_path("../../models/user.rb",__FILE__)
class UserController
  VIEWS_DIR = File.expand_path("../../views/user",__FILE__)
  EDIT_TEMPLATE = File.read(File.join(VIEWS_DIR,"edit.yui"))
  INDEX_TEMPLATE = File.read(File.join(VIEWS_DIR,"index.yui"))
  USER_PARTIAL = File.read(File.join(VIEWS_DIR,"_user_overview.yui"))

  def edit user
    dialog = UI.slim(EDIT_TEMPLATE,:context => user)
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
    GC.start
    response
  end

  def render_user_partial user,parent
    box = UI.slim(USER_PARTIAL,:context => user,:parent => parent)
    button = box.detect {|e| e.is_a? UI::PushButton }
    button.activated do |widget,dialog|
      user = widget.id
      if edit_user user
        label[:Value] = "Surname: "+user.surname
      end
      false
    end
  end

  def index users
    dialog = UI.slim(INDEX_TEMPLATE)
    dialog.find(:save).activated do |event,dialog|
      path = UI.ask_for_existing_file Dir.pwd,"target File"
      puts users.to_json
      false
    end
    dialog.find(:add).activated do |event,dialog|
      user = User.new
      if edit user
        users << user
        render_user_partial user,dialog.find(:users)
        dialog.resize
      end
      false
    end
    users.each { |u| render_user_partial u,dialog.find(:users)}
    dialog.wait_for_event
  end
end
