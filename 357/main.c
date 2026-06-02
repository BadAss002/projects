#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
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

unsigned long long pow_ull(unsigned long long x, unsigned long long y)
{
    unsigned long long result = 1;
    for (int i=0;i<y;i++)
    {
        if (ULLONG_MAX/x < result) return 0; //overflow
        result *= x;
    }

    return result;
}


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
    char numbers[] = "0123456789";
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

    for (int i=0;string[i] != '\0';i++)
    {
        if (strchr(numbers,string[i]) == NULL) *n_ptr = 0;
    }
}


unsigned long long search_nearest_number(int n, struct queue* node, int* start_n, int* abc)
{
    int shift = 10000; //разница между n и node->n
    unsigned long long nearest_number;

    while (node != NULL)
    {
        if (n == node->n)
        {
            printf("%llu\n", node->number);
            return 0;
        }
        else if (n - node->n <= shift && n-node->n > 0)
        {
            shift = n - node->n;
            nearest_number = node->number;
            *start_n = node->n;
            abc[0] = node->a;
            abc[1] = node->b;
            abc[2] = node->c;
        }
        node = node->next;
    }

    if (shift == 10000) //искомый номер элемента в последовательности меньше меньшего в очереди
    {
        *start_n = 1;
        nearest_number = 3;
        abc[0] = 1;
        abc[1] = 0;
        abc[2] = 0;
    }

    return nearest_number;
}


//ОСВОБОЖДЕНИЕ ПАМЯТИ
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

    (*current_elements_number_ptr)++;
}


unsigned long long calculate_next_number(unsigned long long start_number, int* start_n, int* abc)
{
    int abc_sum = 0;
    unsigned long long candidate;
    unsigned long long next_number = ULLONG_MAX;
    unsigned long long diff;
    unsigned long long threes,fives,sevens;
    int start_abc[3] = {abc[0],abc[1],abc[2]};
    for (int i=0;i<3;i++) abc_sum+=abc[i];

    int fl=1;

    for (int i=0;i<=100;i++)
    {
        threes = pow_ull(FIRST,i);
        if (threes == 0) break;
        for (int j=0;j<=100;j++)
        {
            fives = pow_ull(SECOND,j);
            if (fives == 0) break;
            for (int k=0;k<=100;k++)
            {
                sevens = pow_ull(THIRD,k);
                if (sevens == 0) break;

                if (i+j+k == 0 || (i<start_abc[0] && j<start_abc[1] && k<start_abc[2])) continue;

                candidate = threes*fives*sevens;

                if ((ULLONG_MAX/threes)/fives < sevens) continue; //skip overflow

                if (candidate < next_number && candidate > start_number) 
                {
                    next_number = candidate;
                    abc[0] = i;
                    abc[1] = j;
                    abc[2] = k;
                }

                if (next_number != ULLONG_MAX && i>start_abc[0] && j> start_abc[1] && k > start_abc[2]) break;

                //printf("%d %d %d %llu\n", i,j,k, start_number);
            }
        }
    }

    (*start_n)++;

    if (next_number != ULLONG_MAX) return next_number;
    else return 0;
}


int main(void)
{


    //initialize tree
    struct queue* list_start = (struct queue*)malloc(sizeof(struct queue));
    list_start->a = 1;
    list_start->b = 0;
    list_start->c = 0;
    list_start->number = FIRST;
    list_start->n = 1;
    list_start->next = NULL;

    int n;
    int current_elements_number = 1; //кол-во элементов в очереди
    unsigned long long start_number;
    unsigned long long next_number;
    int start_n;
    int abc[3] = {-1,-1,-1};


    while (1) 
    {
        get_input(&n);
        //printf("%d\n", n);
        if (n == -1) return 0;
        if (n == 0 || n<= 0) 
        {
            printf("error: %d\n",n);
            continue;
        }

        start_number = search_nearest_number(n,list_start,&start_n, abc);
        
        if (start_number == 0) continue; //если в очереди уже есть искомый элемент последовательности

        if (n == 1) 
        {
            printf("%llu\n", (unsigned long long)3);
            continue;
        }

        while (n != start_n)
        {
            next_number = calculate_next_number(start_number, &start_n, abc);
            start_number = next_number;

            if (next_number == 0)
            {
                printf("overflow\n");
                break;
            }

            if (n == start_n) printf("%llu\n", next_number);

            if (current_elements_number >= ELEMENTS_IN_MEMORY)
            {
                list_start = delete_element(list_start);
                current_elements_number--;
                insert(list_start,next_number,start_n,abc,&current_elements_number);
            }
            else
            {
                insert(list_start,next_number,start_n,abc,&current_elements_number);
            }
        }
        
    }


    return 0;
}