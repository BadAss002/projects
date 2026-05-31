#include <stdio.h>
#include <stdlib.h>

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

struct candidates_queue* candidates_delete(struct candidates_queue* start)
{
    struct candidates_queue* new_start = start->next;
    free(start);

    return new_start;
}


//add candidates to queue based only on last sequence_node
void calculate_candidates(struct sequence_queue* sequence_node, struct candidates_queue* candidates_node)
{
    unsigned long long candidate;

    while (sequence_node->next != NULL) sequence_node = sequence_node->next;

    candidate = sequence_node->number;
    candidates_insert(candidates_node,candidate*3); //be aware of candidates_node if not working
    candidates_insert(candidates_node,candidate*5);
    candidates_insert(candidates_node,candidate*7);
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

int main(void)
{
    //initialize sequence_queue
    struct sequence_queue* sequence_start = (struct sequence_queue*)malloc(sizeof(struct sequence_queue));

    //initialize candidates_queue
    struct candidates_queue* candidates_start = (struct candidates_queue*)malloc(sizeof(struct candidates_queue));

    queue_initial_build(sequence_start, candidates_start);

    struct sequence_queue* sequence_node = sequence_start;
    struct candidates_queue* candidates_node = candidates_start;
    while (sequence_node != NULL)
    {
        printf("number: %llu n: %d\n", sequence_node->number, sequence_node->n);
        sequence_node = sequence_node->next;
    }
    while (candidates_node != NULL)
    {
        printf("number: %llu\n", candidates_node->number);
        candidates_node = candidates_node->next;
    }

    return 0;
}