#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
extern int errno;
int main(int argc, char * argv[]){

	if(argc<3){
		printf("Usage ./T2.o folder_path link_name\n");
	}

	char *folder_path = argv[1];
	char *file = argv[2];
	//Create directory based on user input with permissions bits set to 0700
	int succ = mkdir(folder_path,0700);
	//If mkdir() returns -1, it failed to create the directory for some reason. 
	if(succ == -1){
		// Check if error is due to access control, if so inform user.
		if (errno == EACCES){
			printf("cannot create directory %s: Permission denied.\n", folder_path);
			// return -1 to indicate failure
			return -1;
		}
	}
	succ = symlink(folder_path, file);
	//check if creating symlink results in an error.
	if(succ == -1){
		//Check if error is due to file already existing, if so, inform user.
		if(errno == EEXIST){
			printf("cannot create directory %s: File exists.\n", folder_path);
			// return -1 to indicate failure
			return -1;
		}
	}
	return 0;
}
