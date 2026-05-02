#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct list{
    int data;
    struct list* next;
};


int main(void)
{
    int size; //number of elements
    printf("Enter number of elements:");
    if (!scanf("%d", &size)) printf("Input error");

    int* array = malloc(sizeof(int)*size);

    struct list* list = malloc(sizeof(struct list)*size);
    
    srand(time(NULL));
    int x;
    for (int i=0;i<size;i++)
    {
        x = rand();
        array[i] = x;
        list[i].data = x;
        list[i].next = list+i+1;
    }

    return 1;
}