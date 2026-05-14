#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define a 4294967296
#define b 65536
#define c 256

struct model{
union t32_eax{
    uint32_t eax;
    struct u32_16_eax{   
        union t16_eax{
            uint16_t ax;
            struct u16_8_eax{
                uint8_t al;
                uint8_t ah;
            }u16_8_eax;
        }t16_eax;  
        uint16_t none;
    }u32_16_eax;
}t32_eax;

union t32_ecx{
    uint32_t ecx;
    struct u32_16_ecx{   
        union t16_ecx{
            uint16_t cx;
            struct u16_8_ecx{
                uint8_t cl;
                uint8_t ch;
            }u16_8_ecx;
        uint16_t none;
        }t16_ecx;  
    }u32_16_ecx;  
}t32_ecx;

union t32_edx{
    uint32_t edx;
    struct u32_16_edx{   
        union t16_edx{
            uint16_t dx;
            struct u16_8_edx{
                uint8_t dl;
                uint8_t dh;
            }u16_8_edx;
        uint16_t none;
        }t16_edx;  
    }u32_16_edx;  
}t32_edx;

}model;

int error = 0;

uint32_t eip;

uint32_t regtoi(char * regist_ptr) //converts string registr to int
{
    uint32_t number;
    int fl = 1;
    if (strchr(regist_ptr,'A'))
        {
            if (strcmp(regist_ptr, "EAX") == 0) //EAX
            {
                number = model.t32_eax.eax;
            }
            else if (strcmp(regist_ptr,"AX") == 0) //AX
            {
                number = model.t32_eax.u32_16_eax.t16_eax.ax;
            }
            else if (strcmp(regist_ptr,"AH") == 0) //AH
            {
                number = model.t32_eax.u32_16_eax.t16_eax.u16_8_eax.ah;
            }
            else if (strcmp(regist_ptr,"AL") == 0)//AL
            {
                number = model.t32_eax.u32_16_eax.t16_eax.u16_8_eax.al;
            }
            else
                fl=0;
        }
    else if (strchr(regist_ptr,'C'))
    {
        if (strcmp(regist_ptr, "ECX") == 0) //ECX
        {
            number = model.t32_ecx.ecx;
        }
        else if (strcmp(regist_ptr,"CX") == 0) //CX
        {
            number = model.t32_ecx.u32_16_ecx.t16_ecx.cx;

        }
        else if (strcmp(regist_ptr,"CH") == 0) //CH
        {
            number = model.t32_ecx.u32_16_ecx.t16_ecx.u16_8_ecx.ch;
        }
        else if (strcmp(regist_ptr,"CL") == 0)//CL
        {
            number = model.t32_ecx.u32_16_ecx.t16_ecx.u16_8_ecx.cl;
        }
        else
            fl=0;
    }
    else if (strchr(regist_ptr,'D'))
    {
        if (strcmp(regist_ptr, "EDX") == 0) //EDX
        {
            number = model.t32_edx.edx;
        }
        else if (strcmp(regist_ptr,"DX") == 0) //DX
        {
            number = model.t32_edx.u32_16_edx.t16_edx.dx;
        }
        else if (strcmp(regist_ptr,"DH") == 0) //DH
        {
            number = model.t32_edx.u32_16_edx.t16_edx.u16_8_edx.dh;
        }
        else if (strcmp(regist_ptr,"DL") == 0)//DL
        {
            number = model.t32_edx.u32_16_edx.t16_edx.u16_8_edx.dl;
        }
        else
            fl=0;
    }
    else
        fl = 0;

    if (fl==1)
        return number;
    else
    {
        error = 1;
        return -1;
    }
}

void commands(char* regist_ptr, char* arg_ch_ptr, int command) //0-mov 1-add 2-sub 3-shw
{
    uint32_t arg;
    eip++;
    if (strlen(regist_ptr) > 3) return; //if regist is invalid by length
    if (arg_ch_ptr[0] != ' ') //is there arg
    {
        if (arg_ch_ptr[0] == '0') //if arg is number
            arg = strtoul(arg_ch_ptr,NULL,0);
        else    //if arg is registr
            arg = regtoi(arg_ch_ptr);
    }
    //printf("%d\n",strlen(regist_ptr));
    if (error == 1) //if arg is invalid
    {
        error = 0;
        return;
    }
    if (strchr(regist_ptr,'A'))
    {
        if (strcmp(regist_ptr, "EAX") == 0) //EAX
        {
            switch (command)
            {
            case 0:
                model.t32_eax.eax = arg%a;
                break;
            case 1:
                model.t32_eax.eax = (model.t32_eax.eax+arg)%a;
                break;
            case 2:
                model.t32_eax.eax = (model.t32_eax.eax-arg)%a;
                break;
            case 3:
                printf("0x%x\n", model.t32_eax.eax);
            default:
                break;
            }
        }
        else if (strcmp(regist_ptr,"AX") == 0) //AX
        {
            switch (command)
            {
            case 0:
                model.t32_eax.u32_16_eax.t16_eax.ax = arg%b;
                break;
            case 1:
                model.t32_eax.u32_16_eax.t16_eax.ax = (model.t32_eax.u32_16_eax.t16_eax.ax+arg)%b;
                break;
            case 2:
                model.t32_eax.u32_16_eax.t16_eax.ax = (model.t32_eax.u32_16_eax.t16_eax.ax-arg)%b;
                break;
            case 3:
                printf("0x%x\n", model.t32_eax.u32_16_eax.t16_eax.ax);
            default:
                break;
            }
        }
        else if (strcmp(regist_ptr,"AH") == 0) //AH
        {
            switch (command)
            {
            case 0:
                model.t32_eax.u32_16_eax.t16_eax.u16_8_eax.ah = arg%c;
                break;
            case 1:
                model.t32_eax.u32_16_eax.t16_eax.u16_8_eax.ah = (model.t32_eax.u32_16_eax.t16_eax.u16_8_eax.ah+arg)%c;
                break;
            case 2:
                model.t32_eax.u32_16_eax.t16_eax.u16_8_eax.ah = (model.t32_eax.u32_16_eax.t16_eax.u16_8_eax.ah-arg)%c;
                break;
            case 3:
                printf("0x%x\n", model.t32_eax.u32_16_eax.t16_eax.u16_8_eax.ah);
            default:
                break;
            }
        }
        else if (strcmp(regist_ptr,"AL") == 0)//AL
        {
            switch (command)
            {
            case 0:
                model.t32_eax.u32_16_eax.t16_eax.u16_8_eax.al = arg%c;
                break;
            case 1:
                model.t32_eax.u32_16_eax.t16_eax.u16_8_eax.al = (model.t32_eax.u32_16_eax.t16_eax.u16_8_eax.al+arg)%c;
                break;
            case 2:
                model.t32_eax.u32_16_eax.t16_eax.u16_8_eax.al = (model.t32_eax.u32_16_eax.t16_eax.u16_8_eax.al-arg)%c;
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
        if (strcmp(regist_ptr, "ECX") == 0) //ECX
        {
            switch (command)
            {
            case 0:
                model.t32_ecx.ecx = arg%a;
                break;
            case 1:
                model.t32_ecx.ecx = (model.t32_ecx.ecx+arg)%a;
                break;
            case 2:
                model.t32_ecx.ecx = (model.t32_ecx.ecx-arg)%a;
                break;
            case 3:
                printf("0x%x\n", model.t32_ecx.ecx);
            default:
                break;
            }
        }
        else if (strcmp(regist_ptr,"CX") == 0) //CX
        {
            switch (command)
            {
            case 0:
                model.t32_ecx.u32_16_ecx.t16_ecx.cx = arg%b;
                break;
            case 1:
                model.t32_ecx.u32_16_ecx.t16_ecx.cx = (model.t32_ecx.u32_16_ecx.t16_ecx.cx+arg)%b;
                break;
            case 2:
                model.t32_ecx.u32_16_ecx.t16_ecx.cx = (model.t32_ecx.u32_16_ecx.t16_ecx.cx-arg)%b;
                break;
            case 3:
                printf("0x%x\n", model.t32_ecx.u32_16_ecx.t16_ecx.cx);
            default:
                break;
            }
        }
        else if (strcmp(regist_ptr,"CH") == 0) //CH
        {
            switch (command)
            {
            case 0:
                model.t32_ecx.u32_16_ecx.t16_ecx.u16_8_ecx.ch = arg%c;
                break;
            case 1:
                model.t32_ecx.u32_16_ecx.t16_ecx.u16_8_ecx.ch = (model.t32_ecx.u32_16_ecx.t16_ecx.u16_8_ecx.ch+arg)%c;
                break;
            case 2:
                model.t32_ecx.u32_16_ecx.t16_ecx.u16_8_ecx.ch = (model.t32_ecx.u32_16_ecx.t16_ecx.u16_8_ecx.ch-arg)%c;
                break;
            case 3:
                printf("0x%x\n", model.t32_ecx.u32_16_ecx.t16_ecx.u16_8_ecx.ch);
            default:
                break;
            }
        }
        else if (strcmp(regist_ptr,"CL") == 0)//CL
        {
            switch (command)
            {
            case 0:
                model.t32_ecx.u32_16_ecx.t16_ecx.u16_8_ecx.cl = arg%c;
                break;
            case 1:
                model.t32_ecx.u32_16_ecx.t16_ecx.u16_8_ecx.cl = (model.t32_ecx.u32_16_ecx.t16_ecx.u16_8_ecx.cl+arg)%c;
                break;
            case 2:
                model.t32_ecx.u32_16_ecx.t16_ecx.u16_8_ecx.cl = (model.t32_ecx.u32_16_ecx.t16_ecx.u16_8_ecx.cl-arg)%c;
                break;
            case 3:
                printf("0x%x\n", model.t32_ecx.u32_16_ecx.t16_ecx.u16_8_ecx.cl);
            default:
                break;
            }
        }
    }
    else if (strchr(regist_ptr,'D'))
    {
        if (strcmp(regist_ptr, "EDX") == 0) //EDX
        {
            switch (command)
            {
            case 0:
                model.t32_edx.edx = arg%a;
                break;
            case 1:
                model.t32_edx.edx = (model.t32_edx.edx+arg)%a;
                break;
            case 2:
                model.t32_edx.edx = (model.t32_edx.edx-arg)%a;
                break;
            case 3:
                printf("0x%x\n", model.t32_edx.edx);
            default:
                break;
            }
        }
        else if (strcmp(regist_ptr,"DX") == 0) //DX
        {
            switch (command)
            {
            case 0:
                model.t32_edx.u32_16_edx.t16_edx.dx = arg%b;
                break;
            case 1:
                model.t32_edx.u32_16_edx.t16_edx.dx = (model.t32_edx.u32_16_edx.t16_edx.dx+arg)%b;
                break;
            case 2:
                model.t32_edx.u32_16_edx.t16_edx.dx = (model.t32_edx.u32_16_edx.t16_edx.dx-arg)%b;
                break;
            case 3:
                printf("0x%x\n", model.t32_edx.u32_16_edx.t16_edx.dx);
            default:
                break;
            }
        }
        else if (strcmp(regist_ptr,"DH") == 0) //DH
        {
            switch (command)
            {
            case 0:
                model.t32_edx.u32_16_edx.t16_edx.u16_8_edx.dh = arg%c;
                break;
            case 1:
                model.t32_edx.u32_16_edx.t16_edx.u16_8_edx.dh = (model.t32_edx.u32_16_edx.t16_edx.u16_8_edx.dh+arg)%c;
                break;
            case 2:
                model.t32_edx.u32_16_edx.t16_edx.u16_8_edx.dh = (model.t32_edx.u32_16_edx.t16_edx.u16_8_edx.dh-arg)%c;
                break;
            case 3:
                printf("0x%x\n", model.t32_edx.u32_16_edx.t16_edx.u16_8_edx.dh);
            default:
                break;
            }
        }
        else if (strcmp(regist_ptr,"DL") == 0)//DL
        {
            switch (command)
            {
            case 0:
                model.t32_edx.u32_16_edx.t16_edx.u16_8_edx.dl = arg%c;
                break;
            case 1:
                model.t32_edx.u32_16_edx.t16_edx.u16_8_edx.dl = (model.t32_edx.u32_16_edx.t16_edx.u16_8_edx.dl+arg)%c;
                break;
            case 2:
                model.t32_edx.u32_16_edx.t16_edx.u16_8_edx.dl = (model.t32_edx.u32_16_edx.t16_edx.u16_8_edx.dl-arg)%c;
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
            for (int i=0;i<4;i++) //clear
            {
                command[i] = ' ';
                regist[i] = ' ';
            }
            for (int i=0;i<11;i++)
                arg_ch[i] = ' ';
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
        {
            if (regist[0] == '0') //shw of const (hex only?)
            {
                printf("%s\n",regist);
                eip++;
            }
            else
                commands(regist, arg_ch, 3);
        }

        for (int i=0;i<4;i++) //clear
        {
            command[i] = ' ';
            regist[i] = ' ';
        }
        for (int i=0;i<11;i++)
            arg_ch[i] = ' ';
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