require "bundler/gem_tasks"
include Rake::DSL

task :default => [:compile, :test]
gem 'rake-compiler', '>= 0.4.1'
require 'rake/extensiontask'
Rake::ExtensionTask.new('ui')

