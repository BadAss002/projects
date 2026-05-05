#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <x86intrin.h>

struct list{
    int data;
    struct list* next;
};

void insert_sort_arr(int * A, int size)
{
    for (int i=1;i<size;i++)
    {
        int j=i;
        int x = A[j];
        while (j>0 && x<A[j-1])
        {
            A[j]=A[j-1];
            j--;
        }
        A[j] = x;
    }
}

struct list* insert_sort_list(struct list* list_start)
{
    struct list* last_sorted = list_start;
    struct list* current;
    struct list* temp;
    struct list* prev_temp;
    struct list* swap;
    
    while (last_sorted->next != NULL)
    {
        current = last_sorted->next;
        if (current->data <= list_start->data) //если нужно вставить в начало отсортированной части
        {
            //изменение ссылок
            last_sorted->next = current->next;
            current->next = list_start;
            list_start = current;
        }
        else if (current->data >= last_sorted->data) //если нужно вставить в конец отсортированной части
        {   
            last_sorted = current;
        }
        else
        {
            temp = list_start;
            while (current->data > temp->data)
            {
                prev_temp = temp;
                temp=temp->next;
            }
            //изменение ссылок в списке
            prev_temp->next = current;
            swap = current->next;
            current->next = temp;
            last_sorted->next = swap;
        }
    }

    return list_start;
}

int find_max_arr(int * A, int size)
{
    int x = A[0];
    for (int i=0;i<size-1;i++)
    {
        if (A[i+1] > x) x = A[i+1]; 
    }

    return x;
    // for (int i=0;i<size-1;i++)
    // {
    //     int k=i;
    //     int x=A[i];
    //     for (int j=i+1;j<size-1;j++)
    //     {
    //         if (A[j] > x)
    //         {
    //             k=j;
    //             x=A[k];
    //         }
    //         A[k] = A[i];
    //         A[i] = x;
    //     }
    // }
}

void time_measure(int size, int* array, struct list* list_start)
{
    unsigned long long start;
    unsigned long long end;
    unsigned long long time_arr;
    unsigned long long time_list;
    
    
    
    //output before sorting
    // current = list_start;
    // for (int i=0;i<size;i++)
    // {
    //     printf("arr: %d  list: %d list_next: %p\n", array[i], current->data, current->next);
    //     current = current->next;
    // }

    //measuring execution time
    start = __rdtsc();
    insert_sort_arr(array,size);
    end = __rdtsc();
    time_arr = end - start;
    
    start = __rdtsc();
    list_start = insert_sort_list(list_start); 
    end = __rdtsc();
    time_list = end - start;
    //output after sorting and mesuring execution time
    //printf("---------------------------------\n");
    // current = list_start;
    // for (int i=0;i<size;i++)
    // {
    //     printf("arr: %d  list: %d list_next: %p\n", array[i], current->data, current->next);
    //     current = current->next;
    // }
    if (time_arr > time_list)
        printf("arr: %llu list: %llu, list sort faster by %lf%%\n",time_arr,time_list,((double)time_arr/time_list-1)*100);
    else
        printf("arr: %llu list: %llu, array sort faster by %lf%%\n",time_arr,time_list,((double)time_list/time_arr-1)*100);
}

void fill(int* A, struct list* current, int size)
{
    srand(time(NULL));
    int x;
    for (int i=0;i<size;i++)
    {
        x = rand();
        A[i] = x;
        current->data = x;
        if (i == size-1)
            current->next = NULL;
        else
            current = current->next;
    }
}

int main(void)
{
    int size; //number of elements
    int iterations;
    printf("Enter number of elements:");
    if (!scanf("%d", &size)) printf("Input error");
    printf("Enter number of iterations:");
    if (!scanf("%d", &iterations)) printf("Input error");


    //malloc array
    int* array = malloc(sizeof(int)*size);

    //malloc list
    struct list* list_start = malloc(sizeof(struct list));
    struct list* current = list_start;
    for (int i=0;i<size;i++)
    {
        if (i == size-1)
            current->next = NULL;
        else
        {
            current->next = malloc(sizeof(struct list));
            current = current->next;
        }
    }

    //measuring time
    for (int i=0;i<iterations;i++)
    {
        fill(array,list_start,size);
        time_measure(size,array,list_start); //fix list_start not global
    }


    return 0;
}