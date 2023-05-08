#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main ()
{
	int SIZE=100;
	int histogram [10];
	printf("enter numnber: ");
	scanf("%d", &SIZE);
        printf("Before allocating memory, SIZE: %d \n", SIZE);    
	int *generated_numbers = malloc(SIZE*sizeof(int));
        /* Core Dumped allocating memory for 10^7 integers in line above*/
        printf("After allocating memory\n");
        
	for(int i=0;i<10;i++)
	{
		histogram[i]=0;
	}
	srand(1000);
	for(int i=0;i<SIZE;i++)
	{
		generated_numbers[i] = rand()%10;
	}
	for(int i=0;i<SIZE;i++)
	{
		histogram[generated_numbers[i]]++;
	}
	for(int i=0;i<10;i++)
	{
		printf("Value (%d) has been found %d times\n", i, histogram[i]);
	}


}
