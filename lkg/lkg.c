#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#define MACHINE_WORD 64
#define NUMBERS 10000000 
#define NUMBER_OF_INTERVALS 15
#define t 3 //количество чисел в группе перестановок

struct intervals {
    unsigned long long border_value;
    unsigned long long count;
};

unsigned long long lehmer_index(unsigned long long* A,int r)
{
    unsigned long long f = 0;
    unsigned long long mx = A[0];
    int index = 0;
    unsigned long long temp;

    for (int i=1;i<r;i++) //поиск максимума
    {
        if (A[i]>mx)
        {
            mx = A[i];
            index = i;
        }
    }

    f = r*f+index-1;
    temp = A[t];
    A[t] = A[index];
    A[index] = temp;

    if (r>0)
        lehmer_index(A,r-1);
    else
        return f;
}

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
    double chi_squared_expected[7] = {5.229,7.261,11.04,14.34,18.25,25.00,30.58};
    int chi_squared_probabilities[7] = {1,5,25,50,75,95,99};
    long double expected_count[15];
    long double V = 0;
    unsigned long long window[t]; 
    unsigned long long lehmer_indexes[(int)ceil(NUMBERS/t)];
    int index_count = 0;

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

    int j = 0;
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

        if (i%t == t-1) //подсчёт индексов Лемера для перестановок
        {
            window[j]=x;
            lehmer_indexes[index_count++] = lehmer_index(lehmer_indexes,t);
            j=0;
        }
        else
            window[j++]=x;

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
        V=V+(array[i].count-expected_count[i])*((array[i].count-expected_count[i])/expected_count[i]);
        //printf("%Lf\n", V);
    }
    
    printf("V = %Lf\n",V);

    for (int i = 0;i<7;i++)
    {
        if (V <= chi_squared_expected[i])
        {
            printf("Chi squared probability = %d%%\n", chi_squared_probabilities[i]);
            break;
        }
    }

    for (int i = 0;i<index_count;i++)
    {
        printf("Lehmer index: %llu\n", lehmer_indexes[i]);
    }
    
    printf("period >= %llu\n", (unsigned long long)NUMBERS);

    // for (int i=0;i<NUMBER_OF_INTERVALS;i++)
    // {
    //     printf("%d interval: %llu\n",i+1,array[i].count);
    // }


    return 0;
}