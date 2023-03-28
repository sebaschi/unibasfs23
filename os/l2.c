void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort(int arr[], int size)
{
   int i, j;
   for (i = 0; i < size-1; i++)    
  
       // Last i elements are already in place   
       for (j = 0; j < size-i-1; j++) 
           if (arr[j] < arr[j+1])
              swap(&arr[j], &arr[j+1]);
}
