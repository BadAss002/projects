//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node {
    unsigned long long val;
    struct node* next;
} node;

typedef struct {
    node* front;
    node* rear;
} qu;

void push(qu* q, unsigned long long num) {
    node* newnode = (node*)malloc(sizeof(node));
    newnode->val = num;
    newnode->next = NULL;
    if (q->front == NULL) {
        q->front = newnode;
        q->rear = newnode;
    }
    else {
        q->rear->next = newnode;
        q->rear = newnode;
    }
}

void pop(qu* q) {
    if (q->front == NULL)
        return;
    node* tmp = q->front;
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(tmp);
}

void clearqu(qu* q) {
    while (q->front != NULL) {
        pop(q);
    }
}

int main(void) {
    long long k;
    while (scanf("%lld", &k) == 1) {

        if (k <= 0) {
            printf("error\n");
            continue;
        }

        unsigned long long n = k;

        qu q3, q5, q7;

        q3.front = NULL;
        q3.rear = NULL;

        q5.front = NULL;
        q5.rear = NULL;

        q7.front = NULL;
        q7.rear = NULL;

        push(&q3, 3);
        push(&q5, 5);
        push(&q7, 7);

        unsigned long long result = 0;
        int overflow_occurred = 0;

        for (unsigned long long cnt = 0; cnt < n; cnt++) {

            if (q3.front == NULL && q5.front == NULL && q7.front == NULL) {
                overflow_occurred = 1;
                break;
            }

            unsigned long long min_val = ULLONG_MAX;

            if (q3.front != NULL && q3.front->val < min_val) {
                min_val = q3.front->val;
            }
            if (q5.front != NULL && q5.front->val < min_val) {
                min_val = q5.front->val;
            }
            if (q7.front != NULL && q7.front->val < min_val) {
                min_val = q7.front->val;
            }

            result = min_val;

            if (q3.front != NULL && q3.front->val == min_val) {
                pop(&q3);
                if (min_val <= ULLONG_MAX / 3)
                    push(&q3, min_val * 3);
                if (min_val <= ULLONG_MAX / 5)
                    push(&q5, min_val * 5);
                if (min_val <= ULLONG_MAX / 7)
                    push(&q7, min_val * 7);
            }

            if (q5.front != NULL && q5.front->val == min_val) {
                pop(&q5);
                if (min_val <= ULLONG_MAX / 5)
                    push(&q5, min_val * 5);
                if (min_val <= ULLONG_MAX / 7)
                    push(&q7, min_val * 7);
            }

            if (q7.front != NULL && q7.front->val == min_val) {
                pop(&q7);
                if (min_val <= ULLONG_MAX / 7)
                    push(&q7, min_val * 7);
            }
        }

        if (overflow_occurred) {
            printf("overflow\n");
        }
        else {
            printf("%llu\n", result);
        }

        clearqu(&q3);
        clearqu(&q5);
        clearqu(&q7);
    }

    return 0;
}