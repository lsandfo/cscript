#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define MAX_LENGTH 50

// List of functions
void build_frame(FILE *data);
void edit();
void new_edit();
void debug();
void usage(char *argv);


// Configurations
char COMPILER[MAX_LENGTH] = "gcc",
	 DEBUGGER[MAX_LENGTH] = "gdb",
	 *CUSTOM_PATH = NULL,
	 EDITOR[MAX_LENGTH] = "vim";
const bool CREATE_MAIN = true;


// Main
int main(int argc, char *argv[]){
		if (argc == 1){
			return EXIT_FAILURE;
		}
		else if ((strcmp(argv[1], "-h" )) == 0)
				usage(argv[0]);
		else if ((strcmp(argv[1], "-t" )) == 0)
				edit();


		return EXIT_SUCCESS;		
}


// The help message
void usage(char *argv){
		printf("Usage: %s [-rndh]\n"
	"-r: Resume last script\n"
	"-n: Create a new Script and clear cache\n"
	"-d: Run last Script with a debugger\n"
	"-h: Print this help message\n"
	"\n"
	"If a file is given as argument, it's conntent will wrapped inside of a default\n"
	"main function, including stdio.h an stdlib.h, compile it and run it.\n"
	"Else if no argument is given, the last Script is re opend.\n"
	"In case no file exist to resume a new one is created.\n"
	"\n"
	"Please keep in mind that the default location for the written code is\n"
	"in /dev/shm, which means the code exists only temporary inside of you memory.\n"
	"By default, without a custom location, you code WON'T SURVIVE A REBOOT!\n"
	"In case you system got no /dev/shm, the /tmp directory will be used, to store you code.\n", argv);
}

// The function to edit the file
void edit(){
		FILE *tmp_data = fopen("/dev/shm/cscript.c", "a");
		if (tmp_data == NULL){
			perror("Cant open /dev/shm file");
			exit(EXIT_FAILURE);
		}
		fclose(tmp_data);
		system(strcat(EDITOR, " /dev/shm/cscript.c"));
}


