require 'yaml'
require 'ui'
require 'ui/builder/slim'
require File.expand_path("../../models/user.rb",__FILE__)
class UserController
  VIEWS_DIR = File.expand_path("../../views/user",__FILE__)
  EDIT_TEMPLATE = File.read(File.join(VIEWS_DIR,"edit.yui"))
  INDEX_TEMPLATE = File.read(File.join(VIEWS_DIR,"index.yui"))
  USER_PARTIAL = File.read(File.join(VIEWS_DIR,"_user_overview.yui"))

  def clear event,dialog
    User::ATTRS.each { |a| dialog.find(a)[:Value] = "" }
    false
  end

  def edit user
    dialog = UI.slim(EDIT_TEMPLATE,:context => user)
    dialog.find(:clear).activated &method(:clear)
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

  def render_user_partial user,parent
    box = UI.slim(USER_PARTIAL,:context => user,:parent => parent)
    button = box.detect {|e| e.is_a? UI::PushButton }
    label = box.detect {|e| e.is_a? UI::Label }
    button.activated do |event,dialog|
      user = event.widget.id
      if edit user
        label[:Value] = "Surname: "+user.surname
      end
      false
    end
  end

  def saveload event,dialog
    if @users.empty? #loading
      path = UI.ask_for_existing_file Dir.pwd,"*.yaml *","Target file to load users"
      return if path.empty?
      @users = YAML.load File.read path
      @users.each { |u| render_user_partial u,dialog.find(:users)}
      event.widget[:Label] = "Save"
      dialog.resize
    else
      path = UI.ask_for_save_file_name Dir.pwd,"*.yaml *","File to store users list"
      return if path.empty?
      File.open(path,"w") { |f| f.write @users.to_yaml }
    end
    false
  end

  def add_user event, dialog
    user = User.new
    if edit user
      @users << user
      render_user_partial user,dialog.find(:users)
      dialog.find(:saveload)[:Label] = "Save"
      dialog.resize
    end
    false
  end

  def index users
    @users = users
    dialog = UI.slim(INDEX_TEMPLATE)
    dialog.find(:saveload).activated &method(:saveload)
    dialog.find(:add).activated &method(:add_user)
    dialog.wait_for_event
  end
end
