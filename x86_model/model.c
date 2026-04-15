#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct model{
union t32_eax{
    __uint32_t eax;
    struct u32_16_eax{
        __uint16_t none;   
        union t16_eax{
            __uint16_t ax;
            struct u16_8_eax{
                __uint8_t ah;
                __uint8_t al;
            }u16_8_eax;
        }t16_eax;  
    }u32_16_eax;  
}t32_eax;

union t32_ecx{
    __uint32_t ecx;
    struct u32_16_ecx{
        __uint16_t none;   
        union t16_ecx{
            __uint16_t cx;
            struct u16_8_ecx{
                __uint8_t ch;
                __uint8_t cl;
            }u16_8_ecx;
        }t16_ecx;  
    }u32_16_ecx;  
}t32_ecx;

union t32_edx{
    __uint32_t edx;
    struct u32_16_edx{
        __uint16_t none;   
        union t16_edx{
            __uint16_t dx;
            struct u16_8_edx{
                __uint8_t dh;
                __uint8_t dl;
            }u16_8_edx;
        }t16_edx;  
    }u32_16_edx;  
}t32_edx;

__uint32_t eip;
}model;

void mov(char* regist_ptr, char* arg_ch_ptr)
{
    if (arg_ch_ptr[0] == '0') //если аргумент - число
    {
        int arg = strtol(arg_ch_ptr,NULL,0);
        if (strchr(regist_ptr,'A'))
        {
            if (strchr(regist_ptr, 'E')) //EAX
            {
                model.t32_eax.eax = arg;
            }
            else if (strchr(regist_ptr,'X')) //AX
            {

            }
            else if (strchr(regist_ptr,'H')) //AH
            {

            }
            else //AL
            {

            }
        }
        else if (strchr(regist_ptr,'C'))
        {

        }
        else
        {

        }
    }
    else
    {

    }
}
void shw()
{
    printf("2\n");
}
void add()
{
    printf("3\n");
}
void sub()
{
    printf("4\n");
}

void command_handler(FILE* input_copy)
{
    char line[20];
    char command[4];
    char regist[4];
    char arg_ch[11];
    int arg;
    char state = 0;
    char ch = 0;
    while (fgets(line,20,input_copy))
    {
        //printf("%s\n", line);
        for (int i=0;i<=strlen(line);i++)
        {
            if (line[i] == '\n')
            {
                arg_ch[ch] = '\0';
                ch = 0;
                state = 0;
                break;
            }
            if (line[i] == ' ')
            {
                if (state == 0)
                    command[ch] = '\0';
                else if (state == 1)
                    regist[ch] = '\0';
                state++;
                ch = 0;
            }
            else if (state == 0)
                command[ch++] = line[i];
            else if (state == 1)
                regist[ch++] = line[i];
            else if (state == 2)
                arg_ch[ch++] = line[i];
        }
        if (strcmp(command,"mov") == 0)
        {
            //printf("%s %s %s\n",command, regist, arg_ch);
            mov(regist, arg_ch);
        }
        // else if (strcmp(command,"shw"))
        //     shw();
        // else if (strcmp(command,"add"))
        //     add();
        // else if(strcmp(command,"sub"))
        //     sub();
        
    }
    
}


int main(void)
{
    FILE* input;
    input = fopen("commands.txt","r");
    command_handler(input);

    return 0;
}