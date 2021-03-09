#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include <time.h>
#define MAX 10

FILE *f;
void *mult(void* arg)
{
    int *data = (int *)arg;
    int k = 0, i = 0;

    int columnsA = data[0];
    for (i = 1; i <= columnsA; i++)
        k += data[i]*data[i+columnsA];

    int *p = (int*)malloc(sizeof(int));
    *p = k;
    pthread_exit(p);

}
int main_elment_by_element ()
{
    int rowsA,columnsA,rowsB,columnsB ;

    int i,j,k;
    f = fopen("matrix_input.txt","r");
    printf("ELEMENT BY ELEMENT METHOD\n");
    printf("reading file ......\n");
    fscanf(f,"%d %d", &rowsA,&columnsA);
    int matA[rowsA][columnsA];


    for (i = 0; i < rowsA; i++)
    {
        for (j = 0; j < columnsA; j++)
        {
            fscanf(f,"%d", &matA[i][j]);
        }
    }


    fscanf(f,"%d %d", &rowsB,&columnsB);
    int matB[rowsB][columnsB];
    for (i = 0; i < rowsB; i++)
    {
        for (j = 0; j < columnsB; j++)
        {
            fscanf(f,"%d", &matB[i][j]);
        }
    }
    printf("\n*****************\n");

    printf("Matrix A\n");
    // Displaying matA
    for (i = 0; i < rowsA; i++)
    {
        for(j = 0; j < columnsA; j++)
            printf("%d ",matA[i][j]);
        printf("\n");
    }
    printf("Matrix B\n");
    // Displaying matB
    for (i = 0; i < rowsB; i++)
    {
        for(j = 0; j < columnsB; j++)
            printf("%d ",matB[i][j]);
        printf("\n");
    }

    printf("\n*****************\n");

    fclose(f);
    int max = rowsA*columnsB;

    clock_t start, end;
    double cpu_time_used;

    start = clock();

    pthread_t *threads;
    threads = (pthread_t*)malloc(max*sizeof(pthread_t));

    int count = 0;
    int* data = NULL;
    for (i = 0; i < rowsA; i++)
        for (j = 0; j < columnsB; j++)
        {

            //storing row and column elements in data
            data = (int *)malloc((20)*sizeof(int));
            data[0] = columnsA;

            for (k = 0; k < columnsA; k++)
                data[k+1] = matA[i][k];

            for (k = 0; k < rowsB; k++)
                data[k+columnsA+1] = matB[k][j];

            //creating threads
            pthread_create(&threads[count++], NULL, mult, (void*)(data));

        }


    f = fopen("matrix_output.txt","w");
    printf("RESULTANT MATRIX IS :- \n");
    for (i = 0; i < max; i++)
    {
        void *k;

        //Joining all threads and collecting return value
        pthread_join(threads[i], &k);


        int *p = (int *)k;
        printf("%d ",*p);
        fprintf(f,"%d ",*p);
        if ((i + 1) % columnsB == 0)
            {
                printf("\n");
                fprintf(f,"\n");
            }
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Program took %f seconds to execute \n", cpu_time_used);
    fprintf(f,"END1 %f\n",cpu_time_used);

    return cpu_time_used;

}

/* *******************************************************************************/

void * mult_join_row (void* arg_2)
{
    int *data_2 = (int *)arg_2;
    int k = 0, i = 0;
    int shifter;

    int rowsB = data_2[0];
    int columnsB = data_2[1];
    int resulted_array[columnsB];

    int  * p_2 = (int)malloc(rowsB*sizeof(int));
    int *l = p_2;


    for(shifter=1 ; shifter <= columnsB ; shifter++ )
    {
        for (i = 2 ; i <= rowsB+1 ; i++)
        {
            k += data_2[i]*data_2[i+rowsB*shifter];
        }
        //resulted_array[shifter]=k;
        //k=0;
        *p_2 ++ = k;
        k=0;
    }

    pthread_exit(l);

}


int main_row()
{



    int rowsA,columnsA,rowsB,columnsB ;


    // int r1=MAX,c1=MAX,r2=MAX,c2=MAX;
    int i,j,k;



    FILE *f_2 = fopen("matrix_input.txt","r");
    printf("\n********************\n");
     printf("\n********************\n");
     printf("\n");
    printf("ROW BY ROW METHOD\n");
    printf("reading file ......\n");
   // printf("Enter no. of rows & columns for Matrix A ::");
    fscanf(f_2,"%d %d", &rowsA,&columnsA);
    int matA[rowsA][columnsA];
    //printf("\nEnter values to the matrix :: \n");
    for (i = 0; i < rowsA; i++)
    {
        for (j = 0; j < columnsA; j++)
        {
            fscanf(f_2,"%d", &matA[i][j]);
        }
    }
    //printf("Enter no. of rows  for Matrix B ::");
    fscanf(f_2,"%d %d", &rowsB,&columnsB);
    int matB[rowsB][columnsB];
    //printf("\nEnter values to the matrix :: \n");
    for (i = 0; i < rowsB; i++)
    {
        for (j = 0; j < columnsB; j++)
        {
            //printf("\nEnter B[%d][%d] value :: ",i,j);
            fscanf(f_2,"%d", &matB[i][j]);
        }
    }
    printf("\n*****************\n");

    printf("Matrix A\n");
    // Displaying matA
    for (i = 0; i < rowsA; i++)
    {
        for(j = 0; j < columnsA; j++)
            printf("%d ",matA[i][j]);
        printf("\n");
    }
    printf("Matrix B\n");
    // Displaying matB
    for (i = 0; i < rowsB; i++)
    {
        for(j = 0; j < columnsB; j++)
            printf("%d ",matB[i][j]);
        printf("\n");
    }

    printf("\n*****************\n");


    int max = rowsA+(rowsB*columnsB);

     clock_t start, end;
    double cpu_time_used;

    start = clock();


    //declaring array of threads of size r1*c2
    pthread_t *threads_2;
    threads_2 = (pthread_t*)malloc(rowsA*sizeof(pthread_t));
    int count = 0;
    int* data_2 = NULL;
    for (i = 0; i < rowsA; i++)
    {

        //storing row and column elements in data
        data_2 = (int *)malloc((max+2)*sizeof(int));
        data_2[0] = rowsB;
        data_2[1] = columnsB ;

        for (k = 0; k < columnsA; k++)
            data_2[k+2] = matA[i][k];

        int counter = 0 ;
        for(j =1 ; j <= columnsB ; j ++)
        {
            for (k = 0; k < (rowsB) ; k++)
            {
                data_2[k+columnsA*j+2] = matB[k][j-1];
                //data1[k+c1*j+2] = matB[k][j-1];
                //data[counter+columnsA+2] = matB[k][j];
                //counter++;
            }
        }
        //creating threads
        pthread_create(&threads_2[count++], NULL, mult_join_row, (void*)(data_2));

    }
    fclose(f_2);

    //f_2=fopen("matrix_output.txt","a");

    printf("RESULTANT MATRIX IS :- \n");
    for (i = 0; i < rowsA ; i++)
    {
        void *k_2;

        //Joining all threads and collecting return value
        pthread_join(threads_2[i], &k_2);


        int *p_2 = (int *)k_2;
        for(j=0 ; j< columnsB ; j++)
           {
               fprintf(f,"%d ",*p_2);
               printf("%d ",*p_2);
               *p_2++;
           }


        printf("\n");
        fprintf(f,"\n");
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Program took %f seconds to execute \n", cpu_time_used);
    fprintf(f,"END2 %f",cpu_time_used);
    fclose(f_2);
    fclose(f);
    return cpu_time_used;


}
int main()
{
    int first_time_elapsed = main_elment_by_element() ;
    int secind_time_elapsed = main_row();

}

