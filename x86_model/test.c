#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int mask = 0b00000000000000000000000000000000;
    int result = mask | 0xfffffffff;

    for (int i =0;i<32;i++)
    {
    if (result & 1)
        printf("1");
    else
        printf("0");
    result >>= 1;
    }

    printf("\n");

    return 0;
}