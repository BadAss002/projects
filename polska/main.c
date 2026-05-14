#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define size 82

char operands[] = "abcdefghijklmnopqrstuvwxyz0123456789";
char operators[] = "+-/*";

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
        printf("Stack Overflow\n");
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

int string_check(char * line)
{
    int lcount = 0;
    int rcount = 0;
    int numb_count = 0;
    for (int i=0;i<strlen(line);i++) // проверка количества открывающих и закрывающих скобок
        {
            if (line[i] == '(') lcount++;
            if (line[i] == ')') rcount++;
            if (strchr(operands,line[i])) numb_count++; //если нет чисел и букв
            //if (strchr(operators,line[i]) && strchr(operators,line[i+1]) && i != strlen(line)-1) return -1; // ++ ** +- -- и тд
            if (strchr(operators,line[i])) // ++ ** +- -- +) *) +___+
            {
                int j=i+1;
                while (line[j] != '\0')
                {
                    if (strchr(operators,line[j]) || line[j] == ')') return -1;
                    else if (strchr(operands,line[j]) || line[j] == '(') break;
                    j++;
                }
            }
            //if (strchr(operands,line[i]) && strchr(operands,line[i+1]) && i != strlen(line)-1) return -1;
            if (strchr(operands,line[i])) // 11 aa bb 23 b( 1_____2
            {
                int j=i+1;
                while (line[j] != '\0')
                {
                    if (strchr(operands,line[j]) || line[j] == '(') return -1;
                    else if (strchr(operators,line[j]) || line[j] == ')') break;
                    j++;
                }
            }
            //if (line[i] == '/' && line[i+1] == '0') return -1; //деление на ноль
            if (line[i] == '/') // /0
            {
                int j=i+1;
                while (line[j] != '\0')
                {
                    if (line[j] == '0') return -1;
                    else if (strchr(operands,line[j]) || line[j] == '(') break;
                    j++;
                }
            }
        }
    if (lcount != rcount || numb_count == 0)
    {
        return -1;
    }
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

        if (string_check(line) == -1)
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
            else if (strchr(operators,ch))
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
                    output_str[place] = pop();
                    place++;
                }
                pop();
            }
            // else if (ch != ' ' && strchr(operands,ch) == NULL && strchr(operators,ch) == NULL)
            // {
            //     printf("error\n");
            // }
        }
        output_str[place] = '\0';
        place = 0;
        //printf("%d\n", stack.top);

        //вычисление польской записи
        long long a,b;
        int fl = 1;
        long long big_ch;
        int div_by_zero = 0;

        for (int i=0;i<26;i++) //проверка на наличие латинских букв
        {
            if (strchr(line,operands[i]) != NULL) fl = 0;
        }

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
                    if (b == 0)
                    {
                        printf("error\n");
                        //printf("%s\n", output_str);
                        div_by_zero = 1;
                        break;
                    }
                    push(a/b);
                }
            }
        }

        if (div_by_zero == 0 && fl) //если нет букв и деления на ноль
        {    
            a = pop();
            printf("%s = %lld\n", output_str, a);
        }
        else if (div_by_zero == 0 && !fl) //если есть буквы и нет деления на ноль
            printf("%s\n", output_str);
        else //деление на ноль есть
            continue;

        //clear stack
        while (stack.top != -1) pop();
    }



    return 0;
}