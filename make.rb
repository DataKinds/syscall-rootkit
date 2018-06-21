#!/usr/bin/env ruby
require "erb"

linuxVersion = `uname -r`.chomp
puts "uname -r = #{linuxVersion}"
puts "using /boot/System.map-#{linuxVersion}"
syscallOffset = `sudo cat /boot/System.map-#{linuxVersion} | grep ' sys_call_table' | ruby -ane 'print $_.split(" ")[0]'`
define = "#define SYS_CALL_TABLE ((unsigned long**)0x#{syscallOffset})"
puts "sys_call_table definition:\n    #{define}"
puts "creating rk.c from rk.c.erb"
rkTemplate = ERB.new(File.read "rk.c.erb")
File.write "rk.c", rkTemplate.result_with_hash({define: define})
puts "done"
puts "to finish the building process, please run `make`. if this message occurs during the `make` process, please ignore it."
