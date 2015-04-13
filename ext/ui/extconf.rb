require 'mkmf'
RbConfig::MAKEFILE_CONFIG['CC'] = ENV['CC'] if ENV['CC']
RbConfig::MAKEFILE_CONFIG['CXX'] = ENV['CXX'] if ENV['CXX']

unless have_library('yui')
  STDERR.puts "Cannot find libyui"
  STDERR.puts "Is libyui-devel installed ?"
  exit 1
end

# only required for old YaST-tied yui
base = if File.exist?('/usr/include/YaST2/yui')
    '/usr/include/YaST2'
  else
    '/usr/include'
  end

find_header 'YUI.h', File.join(base, 'yui')

$CFLAGS << " -g -fvisibility=hidden -I#{base} -I#{File.join(base, 'yui')}"
$CXXFLAGS << " -g -fvisibility=hidden -I#{base} -I#{File.join(base, 'yui')}"

if RbConfig::CONFIG['ruby_version'] =~ /1\.8/
  $CFLAGS << " -DRUBY18_SUPPORT"
end

$LIBS << " -lyui"

create_header
create_makefile('ui')
