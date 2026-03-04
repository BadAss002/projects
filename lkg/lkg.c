#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#define MACHINE_WORD 64
#define NUMBERS 1000000
#define NUMBER_OF_INTERVALS 15

struct intervals {
    unsigned long long border_value;
    unsigned long long count;
};


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
    struct intervals array[NUMBER_OF_INTERVALS]; //массив элементов структур с интервалами
    double chi_squared_expected[7] = {0.03424,0.1244,0.3412,0.5500,0.7926,1.1773,1.4606};
    double exp_chi_squared[7];
    unsigned long long expected_count[15];
    double V;

    while (a % 8 != 5) a++; //вычисление множителя

    //printf("%llu\n", a);

    //расчёт мощности (потенциала)
    int twos = 0; //двоек в разложенном виде a-1
    unsigned long long b = a-1;
    while (b % 2 == 0)
    {
        b/=2;
        twos++;
    }
    s = ceil(MACHINE_WORD/twos);
    printf("Potency: %d\n",s);

    //присваивание границ интервалам
    unsigned long long first_border = floor(ULLONG_MAX/NUMBER_OF_INTERVALS);
    for (int i =0;i<NUMBER_OF_INTERVALS;i++)
    {
        if (i==NUMBER_OF_INTERVALS-1)
            array[i].border_value = ULLONG_MAX;
        else
            array[i].border_value = first_border*(i+1);
        array[i].count = 0;
    }


    unsigned long long first = next_x(a,m,c,x);
    for (unsigned long long i = 0;i < NUMBERS;i++)
    {
        x = next_x(a,m,c,x);
        for (int j = 0;j<NUMBER_OF_INTERVALS;j++) //считаем попадания в интервалы
        {
            if (x <= array[j].border_value)
            {
                array[j].count++;
                break;
            }
        }
        if (x == first && i != 0) //проверяем не закончился ли период
        {
            printf("period < %d ;(\n", NUMBERS);
            return 0;
        }
        // else
        //     printf("%llu\n",x);
    }

    for (int i=0;i<NUMBER_OF_INTERVALS;i++) //массив ожидаемых попаданий в интервалы
        expected_count[i] = NUMBERS/NUMBER_OF_INTERVALS;
    

    //почини переполнение при делении (воспользуйся алтернативной формулой)
    for (int i =0;i<NUMBER_OF_INTERVALS;i++)
    {
        V= V + powl(array[i].count-expected_count[i],2)/(long double)expected_count[i];
        printf("%Lf\n", (array[i].count-expected_count[i])/(long double)expected_count[i]);
    }
    
    
    printf("V = %f\n",V);
    
    printf("period >= %d\n", NUMBERS);

    // for (int i=0;i<NUMBER_OF_INTERVALS;i++)
    // {
    //     printf("%d interval: %llu\n",i+1,array[i].count);
    // }


    return 0;
}