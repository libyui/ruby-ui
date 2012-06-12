# -*- encoding: utf-8 -*-
$:.push File.expand_path("../lib", __FILE__)
require "ui/version"

Gem::Specification.new do |s|
  s.name        = "ui"
  s.version     = UI::VERSION
  s.authors     = ["Duncan Mac-Vicar P.", "Josef Reidinger"]
  s.email       = ["dmacvicar@suse.de", "jreidinger@suse.cz"]
  s.homepage    = ""
  s.summary     = %q{TODO: Write a gem summary}
  s.description = %q{TODO: Write a gem description}

  s.rubyforge_project = "ui"

  s.files         = `git ls-files`.split("\n")
  s.test_files    = `git ls-files -- {test,spec,features}/*`.split("\n")
  s.executables   = `git ls-files -- bin/*`.split("\n").map{ |f| File.basename(f) }
  s.require_paths = ["lib"]

  s.add_runtime_dependency "temple"
  s.add_runtime_dependency "slim"

  s.add_development_dependency("rake-compiler", [">= 0.8"])
  s.add_development_dependency("yard")
  s.extensions  << 'ext/ui/extconf.rb'

end
