#include <stdio.h>
#include <windows.h>

#define ITERATIONS 10000000

int    i, j, k, l, m;
int    i2, j2, k2;
int    g3, h3, i3, k3, m3;
int    i4, j4;
int    i5, j5, k5;



int main(void)
{
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    LARGE_INTEGER ticks_start;
    QueryPerformanceCounter(&ticks_start);
    
    /* ──────────────────────────── *
            │ Размножение констант и копий │
            *──────────────────────────────*/
    for (int r=0; r<ITERATIONS;r++)
    {
        i2 = 0;
        i4 = 0;
        i5 = 5;
        k5 = 5;


        j4 = 2;
        if( i2 < j4 && i4 < j4 )
            i2 = 2;

        j4 = k5;
        if( i2 < j4 && i4 < j4 )
            i5 = 3;
    }
    /*end of block of code*/

    LARGE_INTEGER ticks_end;
    QueryPerformanceCounter(&ticks_end);

    double time_elapsed = (double)(ticks_end.QuadPart - ticks_start.QuadPart) * 1000000000 / freq.QuadPart;
    time_elapsed /= ITERATIONS;

    printf("execution time = %.4f ns\n", time_elapsed);

}