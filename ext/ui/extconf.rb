require 'mkmf'
RbConfig::MAKEFILE_CONFIG['CC'] = ENV['CC'] if ENV['CC']
RbConfig::MAKEFILE_CONFIG['CXX'] = ENV['CXX'] if ENV['CXX']

$CFLAGS = "-g -fvisibility=hidden #{$CFLAGS} -I/usr/include/YaST2 -I/usr/include/YaST2/yui"

unless have_library('yui')
  STDERR.puts "Cannot find libyui"
  STDERR.puts "Is libyui-devel installed ?"
  exit 1
end

find_header 'YUI.h', '/usr/include/YaST2/yui'

$LIBS << " -lyui"

create_makefile('ui')
