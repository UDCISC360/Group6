#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>


struct timeval timestart;
struct timeval timestop;
struct timeval timediff;

//----------------------------------------------------------

void quickSort( int[], int, int);
int partition( int[], int, int);

void quickSort( int a[], int l, int r)
{
   int j;

   if( l < r ) 
   {
   	// divide and conquer
       j = partition( a, l, r);
       quickSort( a, l, j-1);
       quickSort( a, j+1, r);
   }
	
}


int partition( int a[], int l, int r) {
   int pivot, i, j, t;
   pivot = a[l];
   i = l; j = r+1;
		
   while( 1)
   {
   	do ++i; while( a[i] <= pivot && i <= r );
   	do --j; while( a[j] > pivot );
   	if( i >= j ) break;
   	t = a[i]; a[i] = a[j]; a[j] = t;
   }
   t = a[l]; a[l] = a[j]; a[j] = t;
   return j;
}

//----------------------------------------------------------

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;
 
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
 
        merge(arr, l, m, r);
    }
}

//---------------------------------------------------

struct MaxHeap
{
    int size;
    int* array;
};

// A utility function to swap to integers
void swap(int* a, int* b) { int t = *a; *a = *b;  *b = t; }

// The main function to heapify a Max Heap. The function
// assumes that everything under given root (element at
// index idx) is already heapified
void maxHeapify(struct MaxHeap* maxHeap, int idx)
{
    int largest = idx;  // Initialize largest as root
    int left = (idx << 1) + 1;  // left = 2*idx + 1
    int right = (idx + 1) << 1; // right = 2*idx + 2

    // See if left child of root exists and is greater than
    // root
    if (left < maxHeap->size &&
        maxHeap->array[left] > maxHeap->array[largest])
        largest = left;

    // See if right child of root exists and is greater than
    // the largest so far
    if (right < maxHeap->size &&
        maxHeap->array[right] > maxHeap->array[largest])
        largest = right;

    // Change root, if needed
    if (largest != idx)
    {
        swap(&maxHeap->array[largest], &maxHeap->array[idx]);
        maxHeapify(maxHeap, largest);
    }
}

// A utility function to create a max heap of given capacity
struct MaxHeap* createAndBuildHeap(int *array, int size)
{
    int i;
    struct MaxHeap* maxHeap =
              (struct MaxHeap*) malloc(sizeof(struct MaxHeap));
    maxHeap->size = size;   // initialize size of heap
    maxHeap->array = array; // Assign address of first element of array

    // Start from bottommost and rightmost internal mode and heapify all
    // internal modes in bottom up way
    for (i = (maxHeap->size - 2) / 2; i >= 0; --i)
        maxHeapify(maxHeap, i);
    return maxHeap;
}

// The main function to sort an array of given size
void heapSort(int* array, int size)
{
    // Build a heap from the input data.
    struct MaxHeap* maxHeap = createAndBuildHeap(array, size);

    // Repeat following steps while heap size is greater than 1.
    // The last element in max heap will be the minimum element
    while (maxHeap->size > 1)
    {
        // The largest item in Heap is stored at the root. Replace
        // it with the last item of the heap followed by reducing the
        // size of heap by 1.
        swap(&maxHeap->array[0], &maxHeap->array[maxHeap->size - 1]);
        --maxHeap->size;  // Reduce heap size

        // Finally, heapify the root of tree.
        maxHeapify(maxHeap, 0);
    }
}


int main()

{
	int arrsize;
	srand(0);
	int *a;

   for (int s=0; s<3; s++){
   
      if (s==0)
         printf("\n\n-----QUICK SORT-----\n\n");
      else if (s==1)
         printf("\n\n-----MERGE SORT-----\n\n");
      else
         printf("\n\n-----HEAP SORT-----\n\n");
   
   
      for (arrsize=100; arrsize<=1000000; arrsize=arrsize*10){
         
         printf("\n\nArray Size: %d\n", arrsize);
   	   a = malloc (sizeof(int)*arrsize);
         
	 
         //PRINT UNSORTED ARRAY
         /*
	      printf("\n\nUnsorted array is:\n");
	      for(int i = 0; i < arrsize; i++)
	      	printf(" %d ", a[i]);
         */

         printf("Recorded Times in Seconds:\n");
         for (int trials=8; trials>0; trials--){
            for (int t=0; t<arrsize; t++)
	            a[t] = rand() % arrsize;
            
            if (s==0){	      
               gettimeofday(&timestart, NULL);
               quickSort( a, 0, arrsize-1);
               gettimeofday(&timestop, NULL);
               }
            else if (s==1){
               gettimeofday(&timestart, NULL);
               mergeSort(a, 0, arrsize-1);
               gettimeofday(&timestop, NULL);
               }
            else{
               gettimeofday(&timestart, NULL);
               heapSort(a, arrsize);
               gettimeofday(&timestop, NULL);
            }

            //compute time difference
            timersub(&timestop, &timestart, &timediff);

            /*
            //PRINT SORTED ARRAY
            printf("\n\nSorted array is:\n");
	         for(int i = 0; i < arrsize; ++i)
	         printf(" %d ", a[i]);
            */

	         //printf("\n\nTime start: %ld.%06ld\n", timestart.tv_sec, timestart.tv_usec);
            //printf("Time end: %ld.%06ld\n", timestop.tv_sec, timestop.tv_usec);
            //printf("Times %ld.%06ld\n", timediff.tv_sec, timediff.tv_usec);
            printf("%ld.%06ld\n", timediff.tv_sec, timediff.tv_usec);
         }
      }
    free(a);
    }

    
    return 0;

}






