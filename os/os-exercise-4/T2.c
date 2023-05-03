#include <stdio.h>
#include <stdlib.h>

int readLinesCount(const char * str){
    //TODO implement readlinesCount which returns the total number of lines within the input file
 return 0;
}
void writeLinesCount(const char * str, int count_line){
//TODO implement writeLinesCount which writes a new line in file str has count_line 
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
