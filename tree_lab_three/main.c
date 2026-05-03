#include <stdio.h>
#include <time.h>
#include <stdlib.h>

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

struct list* insert_sort_list(struct list* list_start, int size)
{
    struct list* last_sorted = list_start;
    struct list* current;
    struct list* temp;
    struct list* prev_temp;
    struct list* swap;
    while (last_sorted->next != NULL)
    {
        current = last_sorted->next;
        if (current->data < list_start->data) //если нужно вставить в начало отсортированной части
        {
            //изменение ссылок
            last_sorted->next = current->next;
            current->next = list_start;
            list_start = current;
        }
        else if (current->data > last_sorted->data) //если нужно вставить в конец отсортированной части
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


int main(void)
{
    int size; //number of elements
    printf("Enter number of elements:");
    if (!scanf("%d", &size)) printf("Input error");

    int* array = malloc(sizeof(int)*size);

    struct list* list_start = malloc(sizeof(struct list));
    
    //filling arr and list with random ints
    srand(time(NULL));
    int x;
    struct list* current = list_start;
    for (int i=0;i<size;i++)
    {
        x = rand();
        array[i] = x;
        current->data = x;
        if (i == size-1)
            current->next = NULL;
        else
        {
            current->next = malloc(sizeof(struct list));
            current = current->next;
        }
    }

    current = list_start;
    for (int i=0;i<size;i++)
    {
        printf("arr: %d  list: %d list_next: %p\n", array[i], current->data, current->next);
        current = current->next;
    }
    insert_sort_arr(array,size);
    list_start = insert_sort_list(list_start,size);
    printf("---------------------------------\n");
    current = list_start;
    for (int i=0;i<size;i++)
    {
        printf("arr: %d  list: %d list_next: %p\n", array[i], current->data, current->next);
        current = current->next;
    }

    return 0;
}