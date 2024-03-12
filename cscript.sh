#!/bin/sh

# Variables, that may change for the best taste. Uncommand a option if
# you don't want to use a system one.
COMPILER="gcc"
DEBUGGER="gdb"
# EDITRO="vim"
# CUSTOM_PATH="/home/lsandfo/tmpfs"

# If no custom path is set /dev/shm is used. If there is
# no /dev/shm present on you system, the /tmp directory is used.
if [ $CUSTOM_PATH ]; then
	temp_path=$CUSTOM_PATH
elif [ -d /dev/shm ] && [ -w /dev/shm ] && [ -x /dev/shm ]; then
	temp_path="/dev/shm"
else
		temp_path="/tmp"
fi

# The help message
usage="Usage: $0 [-rndh]\n
	-r: Resume last script\n
	-n: Create a new Script and clear cache\n
	-d: Run last Script with a debugger\n
	-h: Print this help message\n
	\n
	If no argument is given, the last Script is re opend.\n
	In case no file exist to resume a new one is created.\n
	\n
	Please keep in mind that the default location for the written code is\n
	in /dev/shm, which means the code exists only temporary inside of you memory.\n
	By default, without a custom location, you code WON'T SURVIVE A REBOOT!\n
	In case you system got no /dev/shm, the /tmp directory will be used, to store you code.\n
	"

# Create the "empty" c file. Only add the bare basics, cause typing them
# every time is annoying.
build_frame() {
		echo "#include<stdio.h>
#include<stdlib.h>

int main(void){


		return EXIT_SUCCESS;
}
		" > $temp_path/cscript.c
		}


# The function, where the file will be edit, compiled and executed.
edit(){
		if [ ! -e $temp_path/cscript.c ]; then build_frame; fi
		$EDITOR $temp_path/cscript.c
		$COMPILER -g -o $temp_path/cscript.elf $temp_path/cscript.c
		$temp_path/cscript.elf
}

# If a new file is needed, the old one is simply deleted and a new one
# will created by the edit function
new_edit(){
		rm -f $temp_path/cscript*
		edit
}

# Stop using printf() for Debugging and learn a debugger!
debug(){
		if [ ! -e $temp_path/cscript.c ]; 
		then 
			echo "You first have to create a file with -n"
			exit 1
		fi
		$DEBUGGER $temp_path/cscript.elf
}

# Choosing the arguments, given by commandline. If no args  
# args are given, the a existing one is edit, or a new is created
if [ $# -eq 0 ]
		then
			edit 
			exit 0
fi

while getopts rndh option
		do
				case $option in
				r)	edit;;
				n)	new_edit;;
				d)	debug;;
				h)	echo $usage;; 
				\?)	echo "Wrong argument"; exit 1;;
				esac
done
	
exit
