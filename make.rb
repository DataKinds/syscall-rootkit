define = "#define SYS_CALL_TABLE ((unsigned long**)0x#{`cat /boot/System.map-3.16.0-4-amd64 | grep " sys_call_table" | ruby -ane 'print $_.split(" ")[0]'`})"
File.open("rk.c", "r") do |code|
	firstLine = code.readline
	if firstLine != define
		File.open("rk.c.new", "w") do |newCode|
			newCode.write(define + "\n")
			code.each_line do |oldCodeLine|
				newCode.write oldCodeLine
			end
		end
	end
end
`mv rk.c rk.c.bak`
`mv rk.c.new rk.c`
puts `make`
