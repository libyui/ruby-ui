require 'mkmf'
$CFLAGS = "#{$CFLAGS} -Werror -I/usr/include/YaST2"

unless have_library('yui')
  STDERR.puts "Cannot find libyui"
  STDERR.puts "Is libyui-devel installed ?"
  exit 1
end

find_header 'YUI.h', '/usr/include/YaST2/yui'
create_makefile('ui')