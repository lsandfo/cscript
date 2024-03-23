# CScript
A tool to run c code like an Interpreter would do.


## Description
This little tool runs the conntent of a given file inside of a default main function,
including the stdio.h, string.h and stdlib.h, compile it and run it.
If no file is give it creates a temporary file, open it up in you favorite editor (From the EDITOR env var), compile and run it.
The idea about it is to avoid this steps, doing by hand. 
I was annoyed about this, while i start learning C an just want to test an play around with the syntax, so i decided to automate this.

## Examples

As little example a passed file could look like this:
~~~ c
void counter(int i){
		for (i ; i > 0 ; i--)
				printf("%d... ", i);
		printf("\nHappy New Year!\n");
}

int count = 10;

counter(count);

~~~

As you can see no main function is needed or any return value. 

## How it works
It's actually realy simple:
Starting cscript with a file as argument, will read the given conntent, wrap it inside of a default main function in /dev/shm/, compile it and run it.
This should feel like you would run a script in bash or python for example.
Starting the cscript without any arg's for the first time will created a file in '/dev/shm/cscript.c' if not exist, and open it up
with the editor from the EDITOR variable. By default a simple main function is present. If a file was opend previous it will open instead of a new one.
After the work is done, the file is saved and the editor is closed, the code will compiled as 'script.elf' and executed.
Running cscript again without arg's, or the '-r' flag, will reopen the file to edit it again, compile and execute it.

Keep in mind that /dev/shm is a tmpfs, which means that the content of it lives inside of you memory.
It will not survive a Reboot.
To Save a file as binary executable run `cscript -s` to save it in you current directory as `executable_cscript.elf`


To clear the previous session and the cache, simply run the script with the '-n' flag to create a new template.

In Case you need to debug something the '-d' flag can be used to start the last executed code inside of a debugger.
The compiler runs with the '-g' flag, to compile the code with debugging informations.
By default the debugger 'gdb' is used, in combination of 'gcc' as compiler.
Both can changed inside of the source code, with the 'DEBUGGER' and 'COMPILER' variable.

The '-h' flag prints a help menu.


## Used Flags
Here all current flags:

|Flag | Usage |
|- |- |
|file | Run it like a script |
| -h | Help Menu |
| -r or none | Reopen the last file or create a new one if not existing |
| -n | Clear the cache and create and open a new template |
| -d | Start last executed one inside of a debugger |
| -s | Save last executed script as binary in you current location |


## Version's
Firstly i was written this as a POSIX Shell Script, cause i was more expirienced in it.
This Version is no longer under development and no longer part of this Project!
Only the C Version will still developed and updated. 



## Bugs
If you finde some thing, please let me know! 
