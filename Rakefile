require "rake/testtask"
require "bundler/gem_tasks"
include Rake::DSL

Rake::TestTask.new do |t|
  t.libs << File.expand_path('../test', __FILE__)
  t.libs << File.expand_path('../', __FILE__)
  t.test_files = FileList['test/test*.rb']
  t.verbose = true
end

extra_docs = ['README*']

require 'yard'
YARD::Rake::YardocTask.new(:doc)

task :default => [:compile]
task :recompile => [:clobber,:compile]

gem 'rake-compiler', '>= 0.4.1'
require 'rake/extensiontask'
Rake::ExtensionTask.new('ui') do |ext|
  ext.source_pattern = "*.{c,cc}"
end

