#include <stdio.h>
#include <stdlib.h>
#define SIZE 5
void init(int arr[])
{
	//DONOT change anything in this function
	srand(1000);
	for(int i=0;i<SIZE;i++)
	{
		int random = rand();
		arr[i]=random;
		printf("%d \n", random); 
	}	
}
void update(int arr1[],int arr2[])
{
	//TODO find and fix the issue here
	for(int i=0;i<SIZE;i++)
		arr2[arr1[i]%SIZE]=1; /* arr1 contains arbitrarily large integers. Those cannot be used to index into a fixed size array, so we limit the maximum index to SIZE */
} 
void display(int arr[])
{
	for(int i=0;i<SIZE;i++)
		printf("at inde %d value is %d\n", i, arr[i]);
}
int main()
{
	int arr1 [SIZE];
	int arr2 [SIZE]={-1,-1,-1,-1,-1};
	init(arr1);
	update(arr1,arr2);
	display(arr2);
}


