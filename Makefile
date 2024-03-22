cscript.elf: cscript.c
	gcc -o cscript.elf cscript.c

install: cscript.elf
	cp cscript.elf /usr/sbin/cscript

uninstall: /usr/sbin/cscript
	rm -f /usr/sbin/cscript

clean: cscript.elf
	rm cscript.elf
