#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <math.h>

#define NUMBER_OF_ELEMENTS 1000

int A[NUMBER_OF_ELEMENTS][NUMBER_OF_ELEMENTS];
int B[NUMBER_OF_ELEMENTS][NUMBER_OF_ELEMENTS];
double C[NUMBER_OF_ELEMENTS][NUMBER_OF_ELEMENTS];


static inline __attribute__((always_inline)) double function_to_measure()
{
    double average = 0.0;

    //заполнение матриц
    for (int i=0;i<NUMBER_OF_ELEMENTS;i++)
        for (int j=0;j<NUMBER_OF_ELEMENTS;j++)
        {
            A[i][j] = rand()%(int)(sqrt(INT_MAX));
            B[i][j] = rand()%(int)(sqrt(INT_MAX));
            C[i][j] = 0;    
        }
    
    //перемножение матриц
    for (int i=0;i<NUMBER_OF_ELEMENTS;i++)
    {
        for (int j=0;j<NUMBER_OF_ELEMENTS;j++)
        {
            for (int k = 0;k<NUMBER_OF_ELEMENTS;k++)
            {
                C[i][j] += (double)A[i][k] * B[k][j];
            }
        }
    }

    //логарифмирование каждого элемента по основанию 10
    for (int i=0;i<NUMBER_OF_ELEMENTS;i++)
    {
        for (int j=0;j<NUMBER_OF_ELEMENTS;j++)
        {
            C[i][j] = log(C[i][j]);
        }
    }

    //среднее арифмитическое всех элементов матрицы C
    for (int i=0;i<NUMBER_OF_ELEMENTS;i++)
    {
        for (int j=0;j<NUMBER_OF_ELEMENTS;j++)
        {
            average += C[i][j];
        }
    }    
    average /= NUMBER_OF_ELEMENTS*NUMBER_OF_ELEMENTS;

    return average;
}

int main(void)
{
    srand(time(NULL));

    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    LARGE_INTEGER ticks_start;
    QueryPerformanceCounter(&ticks_start);

    //measuring
    double result;

    result = function_to_measure();

    printf("result: %f\n", result);

    LARGE_INTEGER ticks_end;
    QueryPerformanceCounter(&ticks_end);

    double time_elapsed = (double)(ticks_end.QuadPart - ticks_start.QuadPart) * 1000 / freq.QuadPart;

    printf("execution time = %f ms\n", time_elapsed);

}