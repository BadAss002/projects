#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <float.h>

#define ITERATIONS 10000000
static inline __attribute__((always_inline)) float function_to_measure()
{
    double x = 0.97;

    double PI = 3.141592653589793;
    double sum = 0;
    double elem = 1;
    unsigned long long fact = 1;
    int banned_number = 3;

    for (unsigned long long i = 1; fabs(elem) >= DBL_EPSILON; i++)
    {
        if (i == banned_number)
        {
            banned_number+=6;
            continue;
        }

        for (unsigned long long j = i / 7; j > i/13; j--)
            fact *= j;  

        elem = (pow(-1, i) * pow(x, 2 * i + 1) * cos(i * PI / 6) / fact); // 3 9 15 21...

        //printf("%f\n", pow(-1, i) * pow(x, 2 * i + 1) * cos(i * PI / 6) / fact);
        //printf("%.30f %.30f %.30f\n", elem, DBL_EPSILON, cos(i * PI / 6));
        sum += elem;
    }

    return sum;
}

int main(void)
{
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    LARGE_INTEGER ticks_start;
    QueryPerformanceCounter(&ticks_start);

    //measuring
    double result;
    for (int j=0;j<ITERATIONS;j++)
    {
        result = function_to_measure();
    }
    printf("%f\n", result);

    LARGE_INTEGER ticks_end;
    QueryPerformanceCounter(&ticks_end);

    double time_elapsed = (double)(ticks_end.QuadPart - ticks_start.QuadPart) * 1000000000 / freq.QuadPart;
    time_elapsed /= ITERATIONS;

    printf("execution time = %f ns\n", time_elapsed);

}