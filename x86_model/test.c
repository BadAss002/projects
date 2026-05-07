#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

int main(void)
{
    //идея - сделать регистр длиной 32*3 чтоб проще был доступ
    t32_eax.eax = 4294967297;
    printf("0x%x", t32_eax.eax);

    return 0;
}