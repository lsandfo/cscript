cscript.elf: cscript.c
	gcc -o cscript cscript.c

install: cscript.elf
	cp cscript /usr/sbin/cscript

uninstall: /usr/sbin/cscript
	rm -f /usr/sbin/cscript

clean: cscript
	rm cscript
