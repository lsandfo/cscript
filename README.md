# CScript
A tool to run c code like an Interpreter would do.


## Description
This little tool creates a temporary file, open it up in you favorite editor, compile and run it.
The idea about it is to avoid this steps, doing by hand. 
I was annoyed about this, while i start learning C an just want to test an play around with the syntax, so i decided to automate this.


## How it works
It's actually realy simple:
Starting the Script without any arg's for the first time will created a file in '/dev/shm/cscript.c' if not exist, and open it up
with the editor from the EDITOR environment variable. By default a simple main function is present.
After the work is done, the file is saved and the editor is closed, the code will compiled as 'script.elf' and executed.
Running the Script again without arg's, or the '-r' flag, will reopen the file to edit it again, compile and execute it.

Keep in mind that /dev/shm is a tmpfs, which means that the content of it lives inside of you memory.
It will not survive a Reboot.
If you System doesn't support a /dev/shm, the /tmp directory will used.
Alternative you can uncomment and change the 'CUSTOM_PATH' variable, inside of the script, to set a persistence default location.

To clear the previous session and the cache, simply run the script with the '-n' flag to create a new template.

In Case you need to debug something the '-d' flag can be used to start the last executed code inside of a debugger.
The compiler runs with the '-g' flag, to compile the code with debugging informations.
By default the debugger 'gdb' is used, in combination of 'gcc' as compiler.
Both can changed inside of the script, with the 'DEBUGGER' and 'COMPILER' variable.

The '-h' flag prints a help menu.


## Used Flags
Here all current flags:

|Flag | Usage |
|- |- |
| -h | Help Menu |
| -r or none | Reopen the last file or create a new one if not existing |
| -n | Clear the cache and create and open a new template |
| -d | Start last executed one inside of a debugger |


## Some side infos
As said before, i wrote this script while learn C.
There is a good chance that i rewrite this complete thing in C, 
just for fun and learning.

