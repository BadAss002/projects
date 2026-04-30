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

}model;

__uint32_t eip;

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

void commands(char* regist_ptr, char* arg_ch_ptr, int command) //0-mov 1-add 2-sub 3-shw
{
    int arg;
    eip++;

    if (arg_ch_ptr[0] == '0') //if arg is number
        arg = strtol(arg_ch_ptr,NULL,0);
    else    //if arg is registr
        arg = regtoi(arg_ch_ptr);
    
    if (strchr(regist_ptr,'A'))
    {
        if (strchr(regist_ptr, 'E')) //EAX
        {
            switch (command)
            {
            case 0:
                model.t32_eax.eax = arg;
                break;
            case 1:
                model.t32_eax.eax += arg;
                break;
            case 2:
                model.t32_eax.eax -= arg;
                break;
            case 3:
                printf("0x%x\n", model.t32_eax.eax);
            default:
                break;
            }
        }
        else if (strchr(regist_ptr,'X')) //AX
        {
            switch (command)
            {
            case 0:
                model.t32_eax.u32_16_eax.t16_eax.ax = arg;
                break;
            case 1:
                model.t32_eax.u32_16_eax.t16_eax.ax += arg;
                break;
            case 2:
                model.t32_eax.u32_16_eax.t16_eax.ax -= arg;
                break;
            case 3:
                printf("0x%x\n", model.t32_eax.u32_16_eax.t16_eax.ax);
            default:
                break;
            }
        }
        else if (strchr(regist_ptr,'H')) //AH
        {
            switch (command)
            {
            case 0:
                model.t32_eax.u32_16_eax.t16_eax.u16_8_eax.ah = arg;
                break;
            case 1:
                model.t32_eax.u32_16_eax.t16_eax.u16_8_eax.ah += arg;
                break;
            case 2:
                model.t32_eax.u32_16_eax.t16_eax.u16_8_eax.ah -= arg;
                break;
            case 3:
                printf("0x%x\n", model.t32_eax.u32_16_eax.t16_eax.u16_8_eax.ah);
            default:
                break;
            }
        }
        else //AL
        {
            switch (command)
            {
            case 0:
                model.t32_eax.u32_16_eax.t16_eax.u16_8_eax.al = arg;
                break;
            case 1:
                model.t32_eax.u32_16_eax.t16_eax.u16_8_eax.al += arg;
                break;
            case 2:
                model.t32_eax.u32_16_eax.t16_eax.u16_8_eax.al -= arg;
                break;
            case 3:
                printf("0x%x\n", model.t32_eax.u32_16_eax.t16_eax.u16_8_eax.al);
            default:
                break;
            }
        }
    }
    else if (strchr(regist_ptr,'C'))
    {
        if (strchr(regist_ptr, 'E')) //ECX
        {
            switch (command)
            {
            case 0:
                model.t32_ecx.ecx = arg;
                break;
            case 1:
                model.t32_ecx.ecx += arg;
                break;
            case 2:
                model.t32_ecx.ecx -= arg;
                break;
            case 3:
                printf("0x%x\n", model.t32_ecx.ecx);
            default:
                break;
            }
        }
        else if (strchr(regist_ptr,'X')) //CX
        {
            switch (command)
            {
            case 0:
                model.t32_ecx.u32_16_ecx.t16_ecx.cx = arg;
                break;
            case 1:
                model.t32_ecx.u32_16_ecx.t16_ecx.cx += arg;
                break;
            case 2:
                model.t32_ecx.u32_16_ecx.t16_ecx.cx -= arg;
                break;
            case 3:
                printf("0x%x\n", model.t32_ecx.u32_16_ecx.t16_ecx.cx);
            default:
                break;
            }
        }
        else if (strchr(regist_ptr,'H')) //CH
        {
            switch (command)
            {
            case 0:
                model.t32_ecx.u32_16_ecx.t16_ecx.u16_8_ecx.ch = arg;
                break;
            case 1:
                model.t32_ecx.u32_16_ecx.t16_ecx.u16_8_ecx.ch += arg;
                break;
            case 2:
                model.t32_ecx.u32_16_ecx.t16_ecx.u16_8_ecx.ch -= arg;
                break;
            case 3:
                printf("0x%x\n", model.t32_ecx.u32_16_ecx.t16_ecx.u16_8_ecx.ch);
            default:
                break;
            }
        }
        else //CL
        {
            switch (command)
            {
            case 0:
                model.t32_ecx.u32_16_ecx.t16_ecx.u16_8_ecx.cl = arg;
                break;
            case 1:
                model.t32_ecx.u32_16_ecx.t16_ecx.u16_8_ecx.cl += arg;
                break;
            case 2:
                model.t32_ecx.u32_16_ecx.t16_ecx.u16_8_ecx.cl -= arg;
                break;
            case 3:
                printf("0x%x\n", model.t32_ecx.u32_16_ecx.t16_ecx.u16_8_ecx.cl);
            default:
                break;
            }
        }
    }
    else
    {
        if (strchr(regist_ptr, 'E')) //EDX
        {
            switch (command)
            {
            case 0:
                model.t32_edx.edx = arg;
                break;
            case 1:
                model.t32_edx.edx += arg;
                break;
            case 2:
                model.t32_edx.edx -= arg;
                break;
            case 3:
                printf("0x%x\n", model.t32_edx.edx);
            default:
                break;
            }
        }
        else if (strchr(regist_ptr,'X')) //DX
        {
            switch (command)
            {
            case 0:
                model.t32_edx.u32_16_edx.t16_edx.dx = arg;
                break;
            case 1:
                model.t32_edx.u32_16_edx.t16_edx.dx += arg;
                break;
            case 2:
                model.t32_edx.u32_16_edx.t16_edx.dx -= arg;
                break;
            case 3:
                printf("0x%x\n", model.t32_edx.u32_16_edx.t16_edx.dx);
            default:
                break;
            }
        }
        else if (strchr(regist_ptr,'H')) //DH
        {
            switch (command)
            {
            case 0:
                model.t32_edx.u32_16_edx.t16_edx.u16_8_edx.dh = arg;
                break;
            case 1:
                model.t32_edx.u32_16_edx.t16_edx.u16_8_edx.dh += arg;
                break;
            case 2:
                model.t32_edx.u32_16_edx.t16_edx.u16_8_edx.dh -= arg;
                break;
            case 3:
                printf("0x%x\n", model.t32_edx.u32_16_edx.t16_edx.u16_8_edx.dh);
            default:
                break;
            }
        }
        else //DL
        {
            switch (command)
            {
            case 0:
                model.t32_edx.u32_16_edx.t16_edx.u16_8_edx.dl = arg;
                break;
            case 1:
                model.t32_edx.u32_16_edx.t16_edx.u16_8_edx.dl += arg;
                break;
            case 2:
                model.t32_edx.u32_16_edx.t16_edx.u16_8_edx.dl -= arg;
                break;
            case 3:
                printf("0x%x\n", model.t32_edx.u32_16_edx.t16_edx.u16_8_edx.dl);
            default:
                break;
            }
        }
    }
}


void command_handler(FILE* input_copy)
{
    char line[20] ="";
    char command[4] ="";
    char regist[4] ="";
    char arg_ch[11] ="";
    int arg;
    char state = 0;
    char ch = 0;
    eip = 1;

    while (fgets(line,20,input_copy))
    {
        //printf("%s\n", line);
        for (int i=0;i<=strlen(line);i++)
        {
            if (line[i] == '\n' || line[i] == '\0')
            {
                if (state == 1)
                    regist[ch] = '\0';
                else if (state == 2)
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
        //printf("%s %s %s\n",command, regist, arg_ch);
        // printf("%s\n", regist);
        // printf("%d\n", strcmp(regist,"EIP"));
        if ((strcmp(command,"shw") == 0) && (strcmp(regist,"EIP") == 0))
        {
            printf("%#x\n",eip);
            eip++;
            // for (int i=0;i<4;i++)
            // {
            //     command[i] = ' ';
            //     regist[i] = ' ';
            // }
            // for (int i=0;i<11;i++)
            //     arg_ch[i] = ' ';
            continue;
        }

        if (strcmp(command,"mov") == 0)
        {
            commands(regist, arg_ch, 0);
        }
        else if (strcmp(command,"add") == 0)
            commands(regist, arg_ch, 1);
        else if (strcmp(command,"sub") == 0)
            commands(regist, arg_ch, 2);
        else if(strcmp(command,"shw") == 0)
            commands(regist, arg_ch, 3);

        // for (int i=0;i<4;i++)
        // {
        //     command[i] = ' ';
        //     regist[i] = ' ';
        // }
        // for (int i=0;i<11;i++)
        //     arg_ch[i] = ' ';
    }
    
}


int main(void)
{
    FILE* input;
    input = fopen("commands.txt","r");
    command_handler(input);
    //printf("%x\n%x\n%x\n%x\n", model.t32_edx.edx, model.t32_eax.u32_16_eax.t16_eax.ax, model.t32_eax.u32_16_eax.t16_eax.u16_8_eax.ah, model.t32_eax.u32_16_eax.t16_eax.u16_8_eax.al);

    return 0;
}