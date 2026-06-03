#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

struct candidates_queue
{
    unsigned long long number;
    struct candidates_queue* next;
};


void candidates_insert(struct candidates_queue* start_node, unsigned long long number_to_insert)
{
    if (start_node->number == 0) //at start of program insert in start_node
    {
        start_node->number = number_to_insert;
        start_node->next = NULL;
        return;
    }

    while(start_node->next != NULL) start_node=start_node->next; //move to end of the queue

    start_node->next = (struct candidates_queue*)malloc(sizeof(struct candidates_queue));
    start_node = start_node->next;
    start_node->number = number_to_insert;
    start_node->next = NULL;
}


//Deletes every ULLONG_MAX node
void candidates_delete(struct candidates_queue** start_ptr)
{
    struct candidates_queue* node = *start_ptr;
    struct candidates_queue* node_to_delete;

    while (node->next != NULL)
    {
        if (node == *start_ptr && node->number == ULLONG_MAX)
        {
            *start_ptr = node->next;
            free(node);
            node = *start_ptr;
            continue;
        }
        else if (node->next->number == ULLONG_MAX)
        {
            node_to_delete = node->next;
            node->next = node->next->next;
            free(node_to_delete);
            continue;   
        }
        node = node->next;
    }
}


//add candidates to queue based only on last number in sequence
void calculate_candidates(unsigned long long sequence_number, struct candidates_queue* candidates_start)
{
    if (ULLONG_MAX/3 < sequence_number) candidates_insert(candidates_start,ULLONG_MAX);
    else candidates_insert(candidates_start,sequence_number*3);

    if (ULLONG_MAX/5 < sequence_number) candidates_insert(candidates_start,ULLONG_MAX);
    else candidates_insert(candidates_start,sequence_number*5);
    
    if (ULLONG_MAX/7 < sequence_number) candidates_insert(candidates_start,ULLONG_MAX);
    else candidates_insert(candidates_start,sequence_number*7);
}   


unsigned long long find_min_in_candidates(struct candidates_queue* start_node)
{
    unsigned long long min = ULLONG_MAX;
    while (start_node != NULL)
    {
        if (start_node->number < min)
        {
            min = start_node->number;
        }
        start_node = start_node->next;
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


void get_input(unsigned long long* n_ptr, int* input_ptr)
{
    //line create
    char line[512];
    char digits[] = "0123456789";
    if (fgets(line,sizeof(line),stdin) == NULL)
    {
        *input_ptr = 0;
        return;
    }
    else 
    {
        *input_ptr = 1;
        line[strcspn(line, "\n")] = '\0';
    }

    //line check
    for (int i=0;line[i];i++)
    {
        if (line[i] == '\0') *input_ptr = -1;
        if (line[i] == '-') *input_ptr = -1; 
        if (strchr(digits,line[i]) == NULL) *input_ptr = -1;
        if (*input_ptr == -1) return;
    }

    if (strlen(line) == 0)
    {
        *input_ptr = -2;
        return;
    }

    //line to ull
    *n_ptr = (unsigned long long)strtoul(line, NULL,10);

    if (*n_ptr <= 0) *input_ptr = -1;

}

void print_list(struct candidates_queue* candidates_start)
{
    while (candidates_start != NULL)
    {
        printf("number: %llu\n", candidates_start->number);
        candidates_start = candidates_start->next;
    }
}

int main(void)
{

    //initialize candidates_queue
    struct candidates_queue* candidates_start = (struct candidates_queue*)calloc(1,sizeof(struct candidates_queue));
    struct candidates_queue* node_to_delete;

    unsigned long long sequence_number = 1;
    int current_n = 1;
    int input;
    unsigned long long n;

    calculate_candidates(sequence_number,candidates_start);

    sequence_number = find_min_in_candidates(candidates_start);

    substitute_selected_candidate(sequence_number,candidates_start);

    candidates_delete(&candidates_start);


    while (1)
    {
        input = 1;
        get_input(&n,&input);

        if (input == -1)
        {
            printf("error\n");
            continue;
        }
        else if (input == -2) //empty line
        {
            continue;
        }
        else if (input == 0)
        {
            return 0;
        }


        if (n < current_n) //reinitialize queue
        {
            current_n = 1;
            while (candidates_start != NULL)
            {
                node_to_delete = candidates_start;
                candidates_start = candidates_start->next;
                free(node_to_delete);
            }
            
            candidates_start = (struct candidates_queue*)calloc(1,sizeof(struct candidates_queue));

            sequence_number = 1;
            current_n = 1;

            calculate_candidates(sequence_number,candidates_start);

            sequence_number = find_min_in_candidates(candidates_start);

            substitute_selected_candidate(sequence_number,candidates_start);

            candidates_delete(&candidates_start);
        }


        while (1)
        {
            if (sequence_number == ULLONG_MAX)
            {
                printf("overflow\n");
                break;
            }
            else if (n == current_n)
            {
                printf("%llu\n", sequence_number);
                break;
            }
            else
            {
                calculate_candidates(sequence_number,candidates_start);
                sequence_number = find_min_in_candidates(candidates_start);
                substitute_selected_candidate(sequence_number,candidates_start);
                candidates_delete(&candidates_start);
                current_n++;
            }

        }
    }


    


    

    return 0;
}