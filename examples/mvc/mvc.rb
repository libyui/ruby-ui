$: << File.expand_path(File.join(File.dirname(__FILE__), '../../lib'))
require File.expand_path('../controllers/users_controller',__FILE__)

users = []
UserController.new.index users

