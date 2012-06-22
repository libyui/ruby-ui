require 'mkmf'
RbConfig::MAKEFILE_CONFIG['CC'] = ENV['CC'] if ENV['CC']
RbConfig::MAKEFILE_CONFIG['CXX'] = ENV['CXX'] if ENV['CXX']

unless have_library('yui')
  STDERR.puts "Cannot find libyui"
  STDERR.puts "Is libyui-devel installed ?"
  exit 1
end

# only required for old YaST-tied yui
base = case
  when File.exist?('/usr/include/YaST2/yui') then '/usr/include/YaST2'
  else '/usr/include'
end

find_header 'YUI.h', File.join(base, 'yui')

$CFLAGS = "#{$CFLAGS} -g -fvisibility=hidden -I#{base} -I#{File.join(base, 'yui')}"

if RbConfig::CONFIG['ruby_version'] =~ /1\.8/
  $CFLAGS = "#{$CFLAGS} -DRUBY18_SUPPORT"
end

$LIBS << " -lyui"

create_makefile('ui')
