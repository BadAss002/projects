#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char* p, out[1000];
int flag = 1, ok = 1;
int flag_zero = 0;

int expr(int min_prio) {
    char* start = out + strlen(out);
    int left_is_digit = 1;

    while (*p == ' ') p++;

    if (*p == '(') {
        p++;
        while (*p == ' ') p++;
        if (!expr(0)) return 0;
        while (*p == ' ') p++;
        if (*p != ')') return 0;
        p++;
        left_is_digit = flag;
    }
    else if (isdigit(*p)) {
        left_is_digit = 1;
        sprintf(out + strlen(out), "%c", *p);
        p++;
    }
    else if (islower(*p)) {
        left_is_digit = 0;
        flag = 0;
        sprintf(out + strlen(out), "%c", *p);
        p++;
    }
    else return 0;

    while (1) {
        while (*p == ' ') p++;
        char op = *p;
        int prio = (op == '+' || op == '-') ? 1 : (op == '*' || op == '/') ? 2 : 0;
        if (prio == 0 || prio < min_prio) break;
        p++;
        while (*p == ' ') p++;
        if (*p == '\0') return 0;
        char next_op = *p;
        while (next_op == ' ') next_op = *(++p);
        if (next_op == '+' || next_op == '-' || next_op == '*' || next_op == '/') {
            return 0;
        }

        int right_ok = expr(prio + 1);
        if (!right_ok) return 0;
        sprintf(out + strlen(out), "%c", op);
        if (!left_is_digit || !flag) flag = 0;
    }
    return 1;
}

int zero(char* s) {
    long long stack[256];
    int top = 0;
    int has_variable = 0;

    for (char* c = s; *c; c++) {
        if (islower(*c)) {
            has_variable = 1;
            return 0;  //                    ,                             
        }
        else if (isdigit(*c)) {
            stack[top++] = *c - '0';
        }
        else if (*c == '+') {
            if (top < 2) return 1;
            stack[top - 2] = stack[top - 2] + stack[top - 1];
            top--;
        }
        else if (*c == '-') {
            if (top < 2) return 1;
            stack[top - 2] = stack[top - 2] - stack[top - 1];
            top--;
        }
        else if (*c == '*') {
            if (top < 2) return 1;
            stack[top - 2] = stack[top - 2] * stack[top - 1];
            top--;
        }
        else if (*c == '/') {
            if (top < 2) return 1;
            if (stack[top - 1] == 0) return 1;  //               
            stack[top - 2] = stack[top - 2] / stack[top - 1];
            top--;
        }
    }
    return 0;
}

long long eval(char* s) {
    long long stack[256];
    int top = 0;

    for (char* c = s; *c; c++) {
        if (*c != '+' && *c != '-' && *c != '*' && *c != '/' && !isdigit(*c)) {
            return 0x3F3F3F3F3F3F3F3FLL;
        }

        if (isdigit(*c)) {
            stack[top++] = *c - '0';
        }
        else if (*c == '+') {
            if (top < 2) return 0x3F3F3F3F3F3F3F3FLL;
            stack[top - 2] = stack[top - 2] + stack[top - 1];
            top--;
        }
        else if (*c == '-') {
            if (top < 2) return 0x3F3F3F3F3F3F3F3FLL;
            stack[top - 2] = stack[top - 2] - stack[top - 1];
            top--;
        }
        else if (*c == '*') {
            if (top < 2) return 0x3F3F3F3F3F3F3F3FLL;
            stack[top - 2] = stack[top - 2] * stack[top - 1];
            top--;
        }
        else if (*c == '/') {
            if (top < 2) return 0x3F3F3F3F3F3F3F3FLL;
            if (stack[top - 1] == 0) return 0x3F3F3F3F3F3F3F3FLL;
            stack[top - 2] = stack[top - 2] / stack[top - 1];
            top--;
        }
    }
    return top == 1 ? stack[0] : 0x3F3F3F3F3F3F3F3FLL;
}

int balance_skob(char* s) {
    int balance = 0;
    for (char* c = s; *c; c++) {
        if (*c == '(') balance++;
        else if (*c == ')') {
            balance--;
            if (balance < 0) return 0;
        }
    }
    return balance == 0;
}

int pusto(char* s) {
    for (char* c = s; *c; c++) {
        if (*c == '(') {
            char* next = c + 1;
            while (*next == ' ') next++;
            if (*next == ')') return 1;
        }
    }
    return 0;
}


int main() {
    char line[256];

    while (fgets(line, 256, stdin)) {
        line[strcspn(line, "\n")] = 0;
        int empty = 1;
        for (int i = 0; line[i]; i++) {
            if (line[i] != ' ') {
                empty = 0;
                break;
            }
        }
        if (empty) {
            printf("error\n");
            continue;
        }
        if (pusto(line)) {
            printf("error\n");
            continue;
        }
        if (!balance_skob(line)) {
            printf("error\n");
            continue;
        }
        p = line;
        out[0] = 0;
        flag = 1;
        ok = 1;
        while (*p == ' ') p++;

        if (!expr(0)) {
            ok = 0;
        }
        else {
            while (*p == ' ') p++;
            if (*p != '\0') ok = 0;
        }
        if (!ok) {
            printf("error\n");
            continue;
        }
        if (flag && zero(out)) {
            printf("error\n");
            continue;
        }
        printf("%s", out);
        if (flag) {
            long long val = eval(out);
            if (val == 0x3F3F3F3F3F3F3F3FLL) {
                printf(" = error\n");
            }
            else {
                printf(" = %lld\n", val);
            }
        }
        else {
            printf("\n");
        }
    }
    return 0;
}