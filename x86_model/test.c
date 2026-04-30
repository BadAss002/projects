#include <stdio.h>
#include <stdlib.h>

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

int main(void)
{
    //идея - сделать регистр длиной 32*3 чтоб проще был доступ

    return 0;
}