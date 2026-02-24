#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#define MACHINE_WORD 64

int main(void)
{
    srand(time(NULL));
    int x = rand();
    __uint128_t a = 3935559000370003845; // множитель
    __uint128_t m = powl(2, MACHINE_WORD); // модуль
    int c = 1; // приращение

    __uint128_t result;



    
    




    return 0;
}