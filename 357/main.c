#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define FIRST 3
#define SECOND 5
#define THIRD 7
#define ELEMENTS_IN_MEMORY 10

struct queue {
    unsigned long long number;
    int a,b,c;
    int n;
    struct queue* next;
};


//calculation of a, b, c in number
void calculate_abc(unsigned long long number, int* abc)
{
    for (int i=0;i<3;i++) abc[i] = 0;

    while (number != 1)
    {
        if (number%FIRST == 0)
        {
            abc[0]++;
            number /= FIRST;
        }
        else if (number%SECOND == 0)
        {
            abc[1]++;
            number /= SECOND;
        }
        else if (number%THIRD == 0)
        {
            abc[2]++;
            number /= THIRD;
        }
        else //number is not in sequence
        {
            for (int i=0;i<3;i++) abc[i] = -1;
            return;
        }
    }
}


void get_input(int* n_ptr)
{
    char ch;
    char string[100];
    int i=0;

    while ((ch = getc(stdin)) != '\n')
    {
        string[i++] = ch;
        if (ch == EOF)
        {
            *n_ptr = -1;
            return;
        }
    }
    string[i] = '\0';

    *n_ptr = strtol(string,NULL,10);
}


unsigned long long search_nearest_number(int n, struct queue* node, int* start_n)
{
    int shift = 10000; //разница между n и node->n
    unsigned long long nearest_number;

    if (node -> next == NULL)  //если в очереди один элемент
    {
        if (n-node->n < 0)
            *start_n = -node->n;
        else
            *start_n = node->n;
        return node->number;
    }

    while (node != NULL)
    {
        if (n == node->n)
        {
            printf("%llu\n", node->number);
            return 0;
        }
        else if (abs(n - node->n) <= abs(shift))
        {
            shift = n - node->n;
            nearest_number = node->number;
            *start_n = node->n;
        }
        node = node->next;
    }

    if (shift < 0) //если start_n > 0, то движемся вправо, иначе - влево
    {
        *start_n = -(*start_n);
    }

    return nearest_number;
}

//удаляем первый элемент в линейном списке
struct queue* delete_element(struct queue* start)
{
    struct queue* new_start = start->next;
    free(start);

    return new_start;
}


//вставка нового элемента
void insert(struct queue* node, unsigned long long number_to_insert, int n, int* abc, int* current_elements_number_ptr)
{
    while (node->next != NULL)
    {
        node = node->next;
    }

    node->next = (struct queue*)malloc(sizeof(struct queue));
    node = node->next;
    node->a = abc[0];
    node->b = abc[1];
    node->c = abc[2];
    node->n = n;
    node->number = number_to_insert;
    node->next = NULL;

    *current_elements_number_ptr++;
}

int main(void)
{
    //initialize tree
    struct queue* start = (struct queue*)malloc(sizeof(struct queue));
    start->a = 1;
    start->b = 0;
    start->c = 0;
    start->number = FIRST;
    start->n = 1;
    start->next = NULL;

    int n;
    int current_elements_number = 1; //кол-во элементов в очереди
    unsigned long long next_number;
    int start_n = 0; //номер в последовательности откуда начинаем поиск
    int abc[3] = {-1,-1,-1};
    int overflow = 0;
    while (1) 
    {
        get_input(&n);
        //printf("%d\n", n);
        if (n == -1) return 0;
        if (n == 0 || n<= 0) 
        {
            printf("error\n");
            continue;
        }

        next_number = search_nearest_number(n,start,&start_n);

        if (next_number == 0) continue;

        if (start_n > 0)
        {
            while (start_n != n)
            {
                if (next_number == ULLONG_MAX) //change it
                {
                    overflow = 1;
                    break;
                }
                next_number++;
                calculate_abc(next_number,abc);
                if (abc[0] != -1) start_n++;
            }

            if (overflow == 1)
            {
                printf("overflow\n");
                overflow = 0;
                continue;
            }

            printf("%llu\n", next_number);

            if (current_elements_number >= ELEMENTS_IN_MEMORY)
            {
                start = delete_element(start);
                insert(start,next_number,n,abc,&current_elements_number);
            }
            else
            {
                insert(start,next_number,n,abc,&current_elements_number);
            }
        }
        else //идём влево
        {
            start_n = -start_n;

            while (start_n != n)
            {
                if (next_number == 1)
                {
                    overflow = 1;
                    break;
                }
                next_number--;
                calculate_abc(next_number,abc);
                if (abc[0] != -1) start_n++;
            }

            if (overflow == 1)
            {
                printf("%llu\n", 3);
                overflow = 0;
                continue;
            }

            printf("%llu\n", next_number);

            if (current_elements_number >= ELEMENTS_IN_MEMORY)
            {
                start = delete_element(start);
                insert(start,next_number,n,abc,&current_elements_number);
            }
            else
            {
                insert(start,next_number,n,abc,&current_elements_number);
            }
        }
    }



    return 0;
}