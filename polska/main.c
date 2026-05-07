#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define size 82

char operands[] = "abcdefghijklmopqrstuvwxyz0123456789";
char operators[] = "+-/*";

struct stack{
    char arr[size];
    char top;
} stack;

char priority(char a)
{
    if (a == '*' || a == '/')
        return 1;
    else if (a == '+' || a == '-')
        return 0;
    else
        printf("wtf?");
}

void push(char value)
{
    stack.top++;
    stack.arr[stack.top] = value;
}

char pop()
{
    char popped = stack.arr[stack.top];
    stack.top--;
    return popped;
}

char peek()
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
        int error = 0;
        for (int i=0;i<strlen(line);i++) // проверка количества открывающих и закрывающих скобок
        {
            if (line[i] == '(') lcount++;
            else if (line[i] == ')') rcount++;
            else if (strchr(operands,line[i])) numb_count++; //если нет чисел
            else if (strchr(operators,line[i]) && strchr(operators,line[i+1])) error = 1; // ++ ** +- -- и тд
            else if (strchr(operands,line[i]) && strchr(operands,line[i+1])) error = 1; // 11 aa bb 23 и тд
        }
        if (lcount != rcount || numb_count == 0 || error == 1)
        {
            printf("error");
            return -1;
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
                        printf("error");
                        return -1;
                    }
                    output_str[place] = pop();
                    place++;
                }
                pop();
            }
            else if (ch != ' ' && strchr(operands,ch) == NULL && strchr(operators,ch) == NULL)
            {
                printf("error");
                return -1;
            }
        }
        output_str[place] = '\0';
        place = 0;
        //printf("%d\n", stack.top);

        //вычисление польской записи
        int a,b;
        int fl = 1;

        for (int i=0;i<25;i++)
        {
            if (strchr(line,operands[i]) != NULL) fl = 0;
        }
        if (fl == 1)
        {
            for (int i=0;i<=strlen(output_str);i++)
            {
                ch = output_str[i];
                if (ch == '\n' || ch == '\0')
                {
                    break;
                }
                else if (strchr(operands,ch))
                {
                    push(ch - '0');
                }
                else if (strchr(operators,ch))
                {
                    b = pop();
                    a = pop();
                    //printf("%d %d\n", a,b);
                    if (ch == '+')
                    {
                        push(a+b);
                    }
                    else if (ch == '-')
                    {
                        push(a-b);
                    }
                    else if (ch == '*')
                    {
                        push(a*b);
                    }
                    else if (ch == '/')
                    {
                        push(a/b);
                    }
                }
            }
            a = pop();
            printf("%s = %d\n", output_str, a);
        }   
        else
        {
            printf("%s\n", output_str);
        }
    }



    return 0;
}