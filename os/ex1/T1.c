
#include<stdlib.h>
#include<stdio.h>

int get_frequency(int *, int, int);
void display_results(int param1);

int main(int argc, char *argv[]){
	int total_size=1000;
	int search_size=1000;
	int target=5;
	// allocation
	int * input_data = (int *) malloc(total_size * sizeof(int));

	// initialization
	for(int i=0;i<total_size;i++)
		input_data[i]=1;

	// usage 1
	printf("Search for target %d\n",5);
	int res=get_frequency(input_data, 5, 10);
	display_results(res); // could not find target

	// usage 2
	printf("Search for target %d\n",1);
	res=get_frequency(input_data, 1000, 1);
	display_results(res); // target has been found 1000
	free(input_data); 

	return 0;
}

int get_frequency(const int * input, int length, int target){
	int i;
	int counter = 0;
	//Loop over input and count occurences of target
	for(i = 0; i < size; i++){
		//Increase count if current input == target
		if(*in == target){
			counter++;
		}
		//Increase pointer location by 1 to get next element
		in++;
	}
	//return -1 if no target found, else return frequencey of target
	return counter == 0 ? -1 : counter;
}
void display_results(int param1){
	switch(param1){
		case -1:
			printf("could not find target\n");
			break;
		default:
			printf("target has been found %d\n", param1);
	}
}
