#include<stdio.h>
#include<stdlib.h>
void display(int arr[], int size)
{
	printf("items are:");
	for(int i=0;i<size;i++)
		printf(" %d",arr[i]);
	printf("\n");
}
void count_sort(int  input[], int size)
{
	int max=input[0];
	for(int i=1;i<size;i++)
		if(max<input[i])
			max=input[i];

	int *temp= calloc(max, sizeof(int));
	for(int i=0;i<size;i++)
		temp[input[i]]++;

	int i=0;
	int counter=0;
	while(i<size)
	{
		while(temp[counter]>0)
		{
			input[i]=counter;
			i++;
			temp[counter]--;
		}
		counter++;
	}       
        /* Memory was not freed before, which can cause memory leak */
        free(temp);

}

int main ()
{
	int arr [5]={100, 100,0, 10,12 };
	display(arr,5);
	count_sort(arr,5);
	printf("after sort\n");
	display(arr,5);
}

