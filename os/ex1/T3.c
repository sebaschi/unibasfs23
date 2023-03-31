#include "sort.h"
#include <stdio.h>
int main ()
{
	int size=5;
	int input [] ={5, 9, 1, 2, 3};
	printf("input array:");
	for(int i=0;i<size;i++){
		printf(" %d",input[i]);
	}
	printf("\nafter sort");
	sort(input, size);
	printf("\ninput array after sort:");
        for(int i=0;i<size;i++){
                printf(" %d",input[i]);
        }
	printf("\n");
}
