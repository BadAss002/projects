#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#define MACHINE_WORD 64
#define NUMBERS 1000000
#define NUMBER_OF_INTERVALS 15
#define t 3 //количество чисел в группе перестановок
#define lkg_iterations 100 //количество итераций алгоритма подсчёта критериев

unsigned long long window[t]; //вариант перестановок из t чисел

unsigned long long factorial(unsigned long long x)
{
    unsigned long long fact = 1;
    for (int i=1;i<=x;i++)
    {
        fact*=i;
    }
    return fact;
}

struct intervals {
    unsigned long long border_value;
    unsigned long long count;
};

unsigned long long next_x(unsigned long long a, unsigned long long m, int c, unsigned long long x)
{
    unsigned long long next_x;
    next_x = (a*x + c) % m;

    return next_x;
}

long double recoil_criteria(unsigned long long m, unsigned long long a, int c, unsigned long long x)
{
    struct intervals array[NUMBER_OF_INTERVALS]; //массив элементов структур с интервалами
    long double Vr = 0;

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
    }

    //подсчёт V для разброса
    long double expected_count = NUMBERS/NUMBER_OF_INTERVALS;
    for (int i =0;i<NUMBER_OF_INTERVALS;i++)
        Vr=Vr+(array[i].count-expected_count)*((array[i].count-expected_count)/expected_count);
    
    return Vr; 
}

unsigned long long lehmer_index(int rang, int permutation_index) //непосредственно подсчёт уникального индекса перестановки
{
    int count = 0; //сколько чисел справа меньше текущего числа
    // rang - порядок (индекс) числа в перестановке
    for (int i=rang+1;i<t;i++)
    {
        if (window[i] < window[rang])
            count++;
    }

    permutation_index+=count*factorial(t-rang-1);

    if (rang == t-1)
        return permutation_index;
        //printf("%d\n",permutation_index);
    else
        lehmer_index(rang+1,permutation_index);
}

long double permutations_criteria(unsigned long long m, unsigned long long a, int c, unsigned long long x)
{
    long double Vp = 0;
    unsigned long long mem = factorial(t); //кол-во возможных индексов лемера
    unsigned long long count_of_lehmer_indexes[6]; //массив кол-ва встречаемых индексов лемера

    int index_count = 0;
    int j = 0;
    unsigned long long first = next_x(a,m,c,x);
    for (int i =0;i<mem;i++)
        count_of_lehmer_indexes[i]=0;
    for (unsigned long long i = 0;i < NUMBERS;i++)
    {
        x = next_x(a,m,c,x);
        if (i%t == t-1) //каждый t-ый раз вызываем подсчёт индекса перестановки
        {
            window[j]=x;
            count_of_lehmer_indexes[lehmer_index(0,0)]++;
            j=0;
        }
        else
            window[j++]=x;

        if (x == first && i != 0) //проверяем не закончился ли период
        {
            printf("period < %d ;(\n", NUMBERS);
            return 0;
        }
    }

    //подсчёт V для перестановок
    long double expected_count_lehmer = (NUMBERS/t)/mem;
    for (int i=0;i<mem;i++)
        Vp=Vp+(count_of_lehmer_indexes[i]-expected_count_lehmer)*((count_of_lehmer_indexes[i]-expected_count_lehmer)/expected_count_lehmer);
    
    return Vp;
}

int main(void)
{
    srand(time(NULL));
    unsigned long long x;
    unsigned long long m = ULLONG_MAX; // модуль 2^64-1
    unsigned long long a = floorl(0.01 * m); // множитель
    int c = 5; // приращение
    int s; //мощность
    long double VrExpected[6] = {4.660425,6.570631,7.789534,21.06414,23.68479,29.14124};
    long double VpExpected[6] = {0.554298,1.145476,1.610308,9.236357,11.0705,15.08627};
    int VrTotal[4] = {0,0,0,0}; // 0-bad 1-suspicious 2-almost suspicious 3-normal
    int VpTotal[4] = {0,0,0,0}; // 0-bad 1-suspicious 2-almost suspicious 3-normal

    while (a % 8 != 5) a++; //вычисление множителя

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

    long double Vr;
    long double Vp;
    for(int i=0;i<lkg_iterations;i++)
    {
        x = rand();
        Vr = recoil_criteria(m,a,c,x);
        Vp = permutations_criteria(m,a,c,x);
        // printf("%Lf\n",Vr);
        if (Vr < VrExpected[0] || Vr > VrExpected[5])
            VrTotal[0]++;
        else if (Vr < VrExpected[1] || Vr > VrExpected[4])
            VrTotal[1]++;
        else if (Vr < VrExpected[2] || Vr > VrExpected[3])
            VrTotal[2]++;
        else
            VrTotal[3]++;

        if (Vp < VpExpected[0] || Vp > VpExpected[5])
            VpTotal[0]++;
        else if (Vp < VpExpected[1] || Vp > VpExpected[4])
            VpTotal[1]++;
        else if (Vp < VpExpected[2] || Vp > VpExpected[3])
            VpTotal[2]++;
        else
            VpTotal[3]++;
    }

    //вывод в консоль
    printf("Vrecoil\nBad:%d Suspicious:%d Almost Suspicious:%d Normal:%d\n\n",VrTotal[0],VrTotal[1],VrTotal[2],VrTotal[3]);
    
    printf("Vpermutations\nBad:%d Suspicious:%d Almost Suspicious:%d Normal:%d\n\n",VpTotal[0],VpTotal[1],VpTotal[2],VpTotal[3]);

    printf("period >= %llu\n", (unsigned long long)NUMBERS);

    // for (int i=0;i<NUMBER_OF_INTERVALS;i++)
    // {
    //     printf("%d interval: %llu\n",i+1,array[i].count);
    // }

    // for (int i = 0;i<mem;i++)
    // {
    //     printf("Lehmer indexes count %d: %llu\n",i, count_of_lehmer_indexes[i]);
    // }


    return 0;
}