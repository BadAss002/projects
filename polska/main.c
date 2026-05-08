#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define size 82

char operands[] = "abcdefghijklmopqrstuvwxyz0123456789";
char operators[] = "+-/*";
int error = 0;

struct stack{
    long long arr[size];
    char top;
} stack;

char priority(long long a)
{
    if (a == '*' || a == '/')
        return 1;
    else if (a == '+' || a == '-')
        return 0;
    else
        printf("error\n");
}

void push(long long value)
{
    stack.top++;
    stack.arr[stack.top] = value;
}

long long pop()
{
    if (stack.top == -1)
    {
        printf("error\n");
        error = 1;
        return -1;
    }
    long long popped = stack.arr[stack.top];
    stack.top--;
    return popped;
}

long long peek()
{
    return stack.arr[stack.top];
}

int main(void)
{   
    // FILE *input;
    // input = fopen("test.txt","r");
    char line[size];
    char output_str[size];
    char ch;
    char place = 0;
    int temp = 0;
    stack.top = -1;
    stack.arr[0] = -1;

    while (fgets(line,size,stdin))
    {
        int lcount = 0;
        int rcount = 0;
        int numb_count = 0;
        error = 0;
        for (int i=0;i<strlen(line);i++) // проверка количества открывающих и закрывающих скобок
        {
            if (line[i] == '(') lcount++;
            if (line[i] == ')') rcount++;
            if (strchr(operands,line[i])) numb_count++; //если нет чисел
            if (strchr(operators,line[i]) && strchr(operators,line[i+1])) error = 1; // ++ ** +- -- и тд
            if (strchr(operands,line[i]) != NULL && strchr(operands,line[i+1]) != NULL) error = 1; // 11 aa bb 23 и тд
            if (line[i] == '/' && line[i+1] == '0') error = 1;
        }

        if (lcount != rcount || numb_count == 0 || error == 1)
        {
            printf("error\n");
            continue;
        }
        //создание польской записи
        //printf("%d\n", strlen(line));
        for (int i=0;i<=strlen(line);i++)
        {
            ch = line[i];
            if (ch == '\n' || ch == '\0')
            {
                while (stack.top != -1)
                {
                    output_str[place] = pop();
                    place++;
                }
                //break;
            }
            else if (strchr(operands,ch))
            {
                output_str[place] = ch;
                place++;
            }
            else if (ch != ' ' && strchr(operators,ch))
            {
                while (stack.top != -1 && strchr(operators,peek()) && priority(peek()) >= priority(ch))
                {
                    output_str[place] = pop();
                    place++;
                }
                push(ch);
            }
            else if (ch == '(')
            {
                push('(');
            }
            else if (ch == ')')
            {
                while (peek() != '(') 
                {
                    if (stack.top == -1) 
                    {
                        printf("error\n");
                        error = 1;
                    }
                    output_str[place] = pop();
                    place++;
                }
                pop();
            }
            else if (ch != ' ' && strchr(operands,ch) == NULL && strchr(operators,ch) == NULL)
            {
                printf("error\n");
                error = 1;
            }
        }
        output_str[place] = '\0';
        place = 0;
        //printf("%d\n", stack.top);

        //вычисление польской записи
        long long a,b;
        int fl = 1;
        long long big_ch;

        if (error == 1) continue;

        for (int i=0;i<25;i++) //проверка на наличие латинских букв
        {
            if (strchr(line,operands[i]) != NULL) fl = 0;
        }
        if (fl == 1)
        {
            for (int i=0;i<=strlen(output_str);i++)
            {
                big_ch = output_str[i];
                if (big_ch == '\n' || big_ch == '\0')
                {
                    break;
                }
                else if (strchr(operands,big_ch))
                {
                    push(big_ch - '0');
                }
                else if (strchr(operators,big_ch))
                {
                    b = pop();
                    a = pop();
                    if (error == 1) break;
                    //printf("%d %d\n", a,b);
                    if (big_ch == '+')
                    {
                        push(a+b);
                    }
                    else if (big_ch == '-')
                    {
                        push(a-b);
                    }
                    else if (big_ch == '*')
                    {
                        push(a*b);
                    }
                    else if (big_ch == '/')
                    {
                        push(a/b);
                    }
                }
            }
            if (error == 0)
            {
                a = pop();
                printf("%s = %lld\n", output_str, a);
            }
        }   
        else
        {
            printf("%s\n", output_str);
        }
    }



    return 0;
}