#include <stdio.h>
#include <stdlib.h>

int readLinesCount(const char * str){
    //TODO implement readlinesCount which returns the total number of lines within the input file
    char current;
    FILE* file = fopen(str, "r"); /* Open file in read-only mode */
    if (file == NULL) {
        printf("Could not open file %s", str);
        exit(1);
    }
    int count = 0;
    current = fgetc(file);
    while (current != EOF) {
        if (current == '\n') {
            count++;
        }
        current =  fgetc(file);
    }
    fclose(file);
    return count;
}
void writeLinesCount(const char * str, int count_line){

    FILE * file = fopen(str, "a+");
    char* in;

    if (file == NULL) {
        printf("Could not open file %s.\n", str);
    } else {
        fprintf(file, "%d\n", count_line);
    }
    fclose(file);


}
int main(int argc, char * argv[])
{
	
	int files_count=atoi(argv[1]);
	int i=0;
	while(i<files_count){
		int num_lines=readLinesCount(argv[2+i]);
		writeLinesCount("output.txt", num_lines);
		i++;
	}

}
