#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define MAX_LENGTH 50

// List of functions
void build_frame(char *data);
void edit();
void debug();
void usage(char *argv);
int test_file();
void run_script(char *script);


// Configurations
char COMPILER[MAX_LENGTH] = "gcc",
	 DEBUGGER[MAX_LENGTH] = "gdb",
	 EDITOR[MAX_LENGTH] = "vim",
	 *ENV_EDITOR = NULL;
const bool CREATE_MAIN = true;

// Static Global Variable
char *empty_data = "\n";

// Main
int main(int argc, char *argv[]){
		// Check for environment variable 'EDITOR' and replace it with the Internal, if not empty
		ENV_EDITOR = getenv("EDITOR");
		if (ENV_EDITOR != NULL)
				strcpy(EDITOR, ENV_EDITOR);

	// Check for given arguments or file
		if (argc == 1){
				edit();
				return EXIT_SUCCESS;
		}
		else if ((strcmp(argv[1], "-h" )) == 0)
				usage(argv[0]);
		else if ((strcmp(argv[1], "-r" )) == 0)
				edit();
		else if ((strcmp(argv[1], "-n" )) == 0){
				build_frame(empty_data);
				edit();
		}
		else if ((strcmp(argv[1], "-d" )) == 0)
				debug();
		else
				run_script(argv[1]);


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
		int test = test_file();
		if (test)
				build_frame(empty_data);
		system(strcat(EDITOR, " /dev/shm/cscript.c"));
		system(strcat(COMPILER, " -g -o /dev/shm/cscript.elf /dev/shm/cscript.c"));
		system("/dev/shm/cscript.elf");
}

// Create Main function frame
void build_frame(char *data){
		FILE *frame = fopen("/dev/shm/cscript.c", "w");
		if (frame == NULL){
			perror("Cant build frame");
			exit(EXIT_FAILURE);
		}	
		if (CREATE_MAIN == true){
				fprintf(frame, "#include<stdio.h>\n"
					"#include<stdlib.h>\n"
					"#include<string.h>\n\n\n"
					"int main(void){\n"
					"%s\n"
					"\treturn EXIT_SUCCESS;\n}", data);
		}
		else
				fprintf(frame, "%s", data);
		fclose(frame);
}

// Runs the given script by copy the conntent from the file to a buffer,
// pass it to build_frame(), compile and run it.
void run_script(char *script){
		char *buffer = NULL;
		int position = 0;
		FILE *data = fopen(script, "r");
		if (data == NULL){
			perror("Can't read from given cscript");
			exit(EXIT_FAILURE);
		}
		fseek(data, 0, SEEK_END);
		position = ftell(data);
		buffer = malloc(sizeof(char) * position);
		if (buffer == NULL){
			printf("Cant allocate memory to load the cscript. It is too big for your memory!\n");
			exit(EXIT_FAILURE);
		}
		rewind(data);
		fread(buffer, 1 , position, data);
		build_frame(buffer);
		free(buffer);
		system(strcat(COMPILER, " -g -o /dev/shm/cscript.elf /dev/shm/cscript.c"));
		system("/dev/shm/cscript.elf");	
}

// Test if file exist, if not return 1, else return 0.
int test_file(){
		FILE *file = fopen("/dev/shm/cscript.c", "r");
		if (file == NULL)
				return 1;
		else
				fclose(file);
		return 0;
}
 void debug(){
		int test = test_file();
		if (test){
				printf("There is nothing to debug...\n");
				exit(EXIT_FAILURE);
		}
		else
				system(strcat(DEBUGGER, " /dev/shm/cscript.elf"));
}
