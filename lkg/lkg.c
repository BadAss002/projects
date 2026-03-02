#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#define MACHINE_WORD 64

__uint128_t next_x(unsigned long long a, __uint128_t m, int c, unsigned long long x)
{
    __uint128_t next_x;
    next_x = (a*x + c) % m;

    return next_x;
}

int main(void)
{
    srand(time(NULL));
    unsigned long long x = rand();
    __uint128_t m = powl(2,MACHINE_WORD); // модуль (2^64)
    unsigned long long a = floorl(0.01 * m); // множитель
    int c = 5; // приращение
    int s; //мощность

    while (a % 8 != 5) a++; //вычисление множителя (184467440737095525)

    //printf("%llu\n", a);

    int twos = 0; //двоек в разложенном виде a-1
    unsigned long long b = a-1;
    while (b % 2 == 0)
    {
        b/=2;
        twos++;
    }
    s = ceil(MACHINE_WORD/twos); // расчёт мощности (потенциала)
    printf("Potency: %d\n",s);


    return 0;
}