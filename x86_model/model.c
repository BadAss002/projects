#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct model{
union t32_eax{
    __uint32_t eax;
    struct u32_16_eax{   
        union t16_eax{
            __uint16_t ax;
            struct u16_8_eax{
                __uint8_t al;
                __uint8_t ah;
            }u16_8_eax;
        }t16_eax;  
        __uint16_t none;
    }u32_16_eax;
}t32_eax;

union t32_ecx{
    __uint32_t ecx;
    struct u32_16_ecx{   
        union t16_ecx{
            __uint16_t cx;
            struct u16_8_ecx{
                __uint8_t cl;
                __uint8_t ch;
            }u16_8_ecx;
        __uint16_t none;
        }t16_ecx;  
    }u32_16_ecx;  
}t32_ecx;

union t32_edx{
    __uint32_t edx;
    struct u32_16_edx{   
        union t16_edx{
            __uint16_t dx;
            struct u16_8_edx{
                __uint8_t dl;
                __uint8_t dh;
            }u16_8_edx;
        __uint16_t none;
        }t16_edx;  
    }u32_16_edx;  
}t32_edx;

__uint32_t eip;
}model;

int regtoi(char * regist_ptr) //converts string registr to int
{
    int number;
    if (strchr(regist_ptr,'A'))
        {
            if (strchr(regist_ptr, 'E')) //EAX
            {
                number = model.t32_eax.eax;
            }
            else if (strchr(regist_ptr,'X')) //AX
            {
                number = model.t32_eax.u32_16_eax.t16_eax.ax;
            }
            else if (strchr(regist_ptr,'H')) //AH
            {
                number = model.t32_eax.u32_16_eax.t16_eax.u16_8_eax.ah;
            }
            else //AL
            {
                number = model.t32_eax.u32_16_eax.t16_eax.u16_8_eax.al;
            }
        }
    else if (strchr(regist_ptr,'C'))
    {
        if (strchr(regist_ptr, 'E')) //ECX
        {
            number = model.t32_ecx.ecx;
        }
        else if (strchr(regist_ptr,'X')) //CX
        {
            number = model.t32_ecx.u32_16_ecx.t16_ecx.cx;

        }
        else if (strchr(regist_ptr,'H')) //CH
        {
            number = model.t32_ecx.u32_16_ecx.t16_ecx.u16_8_ecx.ch;
        }
        else //CL
        {
            number = model.t32_ecx.u32_16_ecx.t16_ecx.u16_8_ecx.cl;
        }
    }
    else
    {
        if (strchr(regist_ptr, 'E')) //EDX
        {
            number = model.t32_edx.edx;
        }
        else if (strchr(regist_ptr,'X')) //DX
        {
            number = model.t32_edx.u32_16_edx.t16_edx.dx;
        }
        else if (strchr(regist_ptr,'H')) //DH
        {
            number = model.t32_edx.u32_16_edx.t16_edx.u16_8_edx.dh;
        }
        else //DL
        {
            number = model.t32_edx.u32_16_edx.t16_edx.u16_8_edx.dl;
        }
    }

    return number;
}

void mov(char* regist_ptr, char* arg_ch_ptr)
{
    int arg;
    if (arg_ch_ptr[0] == '0') //if arg is number
    {
        arg = strtol(arg_ch_ptr,NULL,0);
        if (strchr(regist_ptr,'A'))
        {
            if (strchr(regist_ptr, 'E')) //EAX
            {
                model.t32_eax.eax = arg;
            }
            else if (strchr(regist_ptr,'X')) //AX
            {
                model.t32_eax.u32_16_eax.t16_eax.ax = arg;
            }
            else if (strchr(regist_ptr,'H')) //AH
            {
                model.t32_eax.u32_16_eax.t16_eax.u16_8_eax.ah = arg;
            }
            else //AL
            {
                model.t32_eax.u32_16_eax.t16_eax.u16_8_eax.al = arg;
            }
        }
        else if (strchr(regist_ptr,'C'))
        {
            if (strchr(regist_ptr, 'E')) //ECX
            {
                model.t32_ecx.ecx = arg;
            }
            else if (strchr(regist_ptr,'X')) //CX
            {
                model.t32_ecx.u32_16_ecx.t16_ecx.cx = arg;

            }
            else if (strchr(regist_ptr,'H')) //CH
            {
                model.t32_ecx.u32_16_ecx.t16_ecx.u16_8_ecx.ch = arg;
            }
            else //CL
            {
                model.t32_ecx.u32_16_ecx.t16_ecx.u16_8_ecx.cl = arg;
            }
        }
        else
        {
            if (strchr(regist_ptr, 'E')) //EDX
            {
                model.t32_edx.edx = arg;
            }
            else if (strchr(regist_ptr,'X')) //DX
            {
                model.t32_edx.u32_16_edx.t16_edx.dx = arg;
            }
            else if (strchr(regist_ptr,'H')) //DH
            {
                model.t32_edx.u32_16_edx.t16_edx.u16_8_edx.dh = arg;
            }
            else //DL
            {
                model.t32_edx.u32_16_edx.t16_edx.u16_8_edx.dl = arg;
            }
        }
    }
    else //if arg is regist
    {
        arg = regtoi(arg_ch_ptr);
        if (strchr(regist_ptr,'A'))
        {
            if (strchr(regist_ptr, 'E')) //EAX
            {
                model.t32_eax.eax = arg;
            }
            else if (strchr(regist_ptr,'X')) //AX
            {
                model.t32_eax.u32_16_eax.t16_eax.ax = arg;
            }
            else if (strchr(regist_ptr,'H')) //AH
            {
                model.t32_eax.u32_16_eax.t16_eax.u16_8_eax.ah = arg;
            }
            else //AL
            {
                model.t32_eax.u32_16_eax.t16_eax.u16_8_eax.al = arg;
            }
        }
        else if (strchr(regist_ptr,'C'))
        {
            if (strchr(regist_ptr, 'E')) //ECX
            {
                model.t32_ecx.ecx = arg;
            }
            else if (strchr(regist_ptr,'X')) //CX
            {
                model.t32_ecx.u32_16_ecx.t16_ecx.cx = arg;

            }
            else if (strchr(regist_ptr,'H')) //CH
            {
                model.t32_ecx.u32_16_ecx.t16_ecx.u16_8_ecx.ch = arg;
            }
            else //CL
            {
                model.t32_ecx.u32_16_ecx.t16_ecx.u16_8_ecx.cl = arg;
            }
        }
        else
        {
            if (strchr(regist_ptr, 'E')) //EDX
            {
                model.t32_edx.edx = arg;
            }
            else if (strchr(regist_ptr,'X')) //DX
            {
                model.t32_edx.u32_16_edx.t16_edx.dx = arg;
            }
            else if (strchr(regist_ptr,'H')) //DH
            {
                model.t32_edx.u32_16_edx.t16_edx.u16_8_edx.dh = arg;
            }
            else //DL
            {
                model.t32_edx.u32_16_edx.t16_edx.u16_8_edx.dl = arg;
            }
        }
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
            printf("%s %s %s\n",command, regist, arg_ch);
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
    input = fopen("test.txt","r");
    command_handler(input);
    //printf("%x\n%x\n%x\n%x\n", model.t32_edx.edx, model.t32_eax.u32_16_eax.t16_eax.ax, model.t32_eax.u32_16_eax.t16_eax.u16_8_eax.ah, model.t32_eax.u32_16_eax.t16_eax.u16_8_eax.al);

    return 0;
}