/* C program for Merge Sort */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]


struct struct_list {
int low;
int high;
};

int *arr;
void merge( int l, int m, int r)
{

	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	int L[n1], R[n2];


	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

void* mergeSort(void* arg)
{
    //printf("entred thread\n ");
    struct struct_list *data;
    data = (struct struct_list*) malloc( sizeof(struct struct_list));
    data = (struct struct_list*) arg ;
    //printf("low_arg :: %d\n",data->low);
    //printf("high_arg :: %d\n",data->high);
    int l = data->low;
    int r= data->high;

	if (l < r) {

    int mid = l + (r - l) / 2;

    struct struct_list list_left;
    list_left.low=l;
    list_left.high = mid;
    //printf("low_leftthread :: %d\n",list_left.low);
    //printf("high_leftthread :: %d\n",list_left.high);
    //printf("\n******************\n");

    struct struct_list list_right;
    list_right.low = mid+1;
    list_right.high= r;
    //printf("low_rightthread :: %d\n",list_right.low);
    //printf("high_rightthread :: %d\n",list_right.high);
    //printf("\n******************\n");


    pthread_t thread_left;
    pthread_create(&thread_left , NULL , mergeSort , (void*) &list_left );

    pthread_join(thread_left,NULL);



    pthread_t thread_right ;
    pthread_create(&thread_right ,NULL , mergeSort , (void *) &list_right);

    pthread_join(thread_right,NULL);


    merge(l, mid, r);

	}
}

void printArray(int A[], int size)
{
    FILE * f;
    f = fopen("output_merge.txt","w");
	int i;
	for (i = 0; i < size; i++)
		{
		    printf("%d ", A[i]);
		    fprintf(f,"%d",A[i]);
        }
	printf("\n");
}

int main()
{
    FILE* f ;
    f = fopen("input_merge.txt","r");
    int arr_size,i;
    fscanf(f,"%d",&arr_size);
    arr = (int *)malloc((arr_size)*sizeof(int));


    for(i=0 ;i<arr_size;i++)
        fscanf(f,"%d",&arr[i]);

    printf("THE ARRAY FROM FILE::\n");
    for(i=0 ; i< arr_size ; i++)
        printf("%d ",arr[i]);
    printf("\n**********\n");

	struct struct_list * list;
	list = (struct struct_list*) malloc( sizeof(struct struct_list));
	list->low = 0;
	list->high=arr_size-1;

   // printf("mainArray_low:: %d\n",list->low);
	//printf("mainArray_high :: %d\n",list->high);
   // printf("\n******************\n");

	pthread_t thread;

	pthread_create(&thread , NULL , mergeSort , (void*) list );

	pthread_join(thread,NULL);

	//printf("returned from merge\n");
	fclose(f);

     printf("\n**********\n");
	printf("\nSorted array is \n");
	printArray(arr, arr_size);
	return 0;
}
