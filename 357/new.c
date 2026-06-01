#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

struct sequence_queue
{
    unsigned long long number;
    int n;
    struct sequence_queue* next;
};

struct candidates_queue
{
    unsigned long long number;
    struct candidates_queue* next;
};


//funcs for queues
void sequence_insert(struct sequence_queue* node, unsigned long long number_to_insert, int n_to_insert)
{
    while(node->next != NULL) node=node->next; //move to end of the queue

    node->next = (struct sequence_queue*)malloc(sizeof(struct sequence_queue));
    node = node->next;
    node->number = number_to_insert;
    node->n = n_to_insert;
    node->next = NULL;
}

struct sequence_queue* sequence_delete(struct sequence_queue* start)
{
    struct sequence_queue* new_start = start->next;
    free(start);

    return new_start;
}

void candidates_insert(struct candidates_queue* node, unsigned long long number_to_insert)
{
    while(node->next != NULL) node=node->next; //move to end of the queue

    node->next = (struct candidates_queue*)malloc(sizeof(struct candidates_queue));
    node = node->next;
    node->number = number_to_insert;
    node->next = NULL;
}


//Deletes every ULLONG_MAX node
struct candidates_queue* candidates_delete(struct candidates_queue* start)
{
    struct candidates_queue* node = start;
    struct candidates_queue* new_start = start;
    struct candidates_queue* prev;
    struct candidates_queue* current;

    while (node->next != NULL)
    {
        if ((node == start || node == new_start) && node->number == ULLONG_MAX)
        {
            new_start = node->next;
            free(node);
            node = new_start;
            continue;
        }
        else if (node->next->number == ULLONG_MAX)
        {
            prev = node;
            current = node->next;
            prev->next = current->next;
            free(current);
            continue;   
        }
        node = node->next;
    }


    return new_start;
}


//add candidates to queue based only on last sequence_node
void calculate_candidates(struct sequence_queue* sequence_node, struct candidates_queue* candidates_node)
{
    unsigned long long candidate;

    while (sequence_node->next != NULL) sequence_node = sequence_node->next;

    candidate = sequence_node->number;

    if (ULLONG_MAX/3 < candidate) candidates_insert(candidates_node,ULLONG_MAX);
    else candidates_insert(candidates_node,candidate*3);

    if (ULLONG_MAX/5 < candidate) candidates_insert(candidates_node,ULLONG_MAX);
    else candidates_insert(candidates_node,candidate*5);
    
    if (ULLONG_MAX/7 < candidate) candidates_insert(candidates_node,ULLONG_MAX);
    else candidates_insert(candidates_node,candidate*7);
}   


//3 5 7
//9 15 21 15 25 35 21 35 49
void queue_initial_build(struct sequence_queue* sequence_node, struct candidates_queue* candidates_node)
{
    //first_sequence_node
    sequence_node->number = (unsigned long long)3;
    sequence_node->n = (int)1;
    sequence_node->next = NULL;

    //1-3 candidate_nodes
    candidates_node->number = (unsigned long long)9;
    candidates_node->next = (struct candidates_queue*)malloc(sizeof(struct candidates_queue));
    candidates_node = candidates_node->next;
    candidates_node->number = (unsigned long long)15;
    candidates_node->next = (struct candidates_queue*)malloc(sizeof(struct candidates_queue));
    candidates_node = candidates_node->next;
    candidates_node->number = (unsigned long long)21;
    candidates_node->next = NULL;

    //5
    //15 25 35
    sequence_insert(sequence_node,(unsigned long long)5,(int)2);
    calculate_candidates(sequence_node,candidates_node);

    //7
    //21 35 49
    sequence_insert(sequence_node,(unsigned long long)7,(int)3);
    calculate_candidates(sequence_node,candidates_node);
}


unsigned long long find_min_in_candidates(struct candidates_queue* node)
{
    unsigned long long min = ULLONG_MAX;
    while (node != NULL)
    {
        if (node->number < min)
        {
            min = node->number;
        }
        node = node->next;
    }

    return min;
}

void substitute_selected_candidate(unsigned long long number_to_substitute, struct candidates_queue* candidates_start)
{
    while (candidates_start != NULL)
    {
        if (candidates_start->number == number_to_substitute)
        {
            candidates_start->number = ULLONG_MAX;
        }
        candidates_start = candidates_start->next;
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

    if (strlen(string) == 0) *n_ptr = -2;
}

void print_lists(struct sequence_queue* sequence_start, struct candidates_queue* candidates_start)
{
    while (sequence_start != NULL)
    {
        printf("number: %llu n: %d\n", sequence_start->number, sequence_start->n);
        sequence_start = sequence_start->next;
    }
    while (candidates_start != NULL)
    {
        printf("number: %llu\n", candidates_start->number);
        candidates_start = candidates_start->next;
    }
}

int main(void)
{
    //initialize sequence_queue
    struct sequence_queue* sequence_start = (struct sequence_queue*)malloc(sizeof(struct sequence_queue));

    //initialize candidates_queue
    struct candidates_queue* candidates_start = (struct candidates_queue*)malloc(sizeof(struct candidates_queue));

    queue_initial_build(sequence_start, candidates_start);

    int n;
    char state = 0;
    char overflow = 0;
    unsigned long long min;
    struct sequence_queue* sequence_node = sequence_start;
    struct candidates_queue* candidates_node = candidates_start;
    
    while (1)
    {
        if (state != 2) get_input(&n);
        if (n==-2) continue;
        if (n==-1) 
        {
            return 0;
        }
        else if (n == 0 || n<= 0) 
        {
            printf("error\n");
            continue;
        }

        //checking where is n regarding sequence_queue
        //state = 0 (in queue), state = 1 (more than last element of queue), state = 2 (less than first element in queue)
        sequence_node = sequence_start;
        while (sequence_node != NULL)
        {
            if (n == sequence_node->n)
            {
                printf("%llu\n", sequence_node->number);
                state = 0;
                sequence_node = sequence_start; //remember this just in case
                break;
            }
            else if (n > sequence_node->n && sequence_node->next == NULL)
            {
                state = 1;
                break;
            }
            else if (n < sequence_node->n && sequence_node == sequence_start)
            {
                state = 2;
                break;
            }
            sequence_node = sequence_node->next;
        }


        if (state == 0)
        {
            continue;
        }
        else if (state == 1)
        {
            //do nothing   
        }
        else if (state == 2)
        {
            sequence_node = sequence_start->next;
            candidates_node = candidates_start->next;
            struct sequence_queue* node_to_delete_seq;
            struct candidates_queue* node_to_delete_cand;
            while (sequence_node != NULL)
            {
                node_to_delete_seq = sequence_node;
                sequence_node=sequence_node->next;
                free(node_to_delete_seq);
            }
            while (candidates_node != NULL)
            {
                node_to_delete_cand = candidates_node;
                candidates_node=candidates_node->next;
                free(node_to_delete_cand);
            }

            queue_initial_build(sequence_start, candidates_start);
            sequence_node = sequence_start;
            while (sequence_node->next != NULL) sequence_node = sequence_node->next;
            candidates_node = candidates_start;
            continue;
        }

        //search of next element while n != sequence->n
        while (1)
        {

            min = find_min_in_candidates(candidates_start);

            if (min == ULLONG_MAX)
            {
                overflow = 1;
                break;
            }

            sequence_insert(sequence_start,min,sequence_node->n+1);                
            sequence_node = sequence_node->next;

            substitute_selected_candidate(min, candidates_start);

            calculate_candidates(sequence_node,candidates_start);
            //print_lists(sequence_start,candidates_start);

            //DELETION
            sequence_start = sequence_delete(sequence_start);
            candidates_start = candidates_delete(candidates_start);
            //print_lists(sequence_start,candidates_start);


            if (n == sequence_node->n)
            {
                printf("%llu\n", sequence_node->number);
                break;
            }
        }
        // print_lists(sequence_start,candidates_start);
        // return 0;



        if (overflow == 1)
        {
            printf("overflow\n");
            overflow = 0;
            continue;
        }

    }


    

    return 0;
}