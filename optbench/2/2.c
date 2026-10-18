#include <stdio.h>
#include <windows.h>

#define ITERATIONS 10000000

int    i, j, k, l, m;
int    i2, j2, k2;
int    g3, h3, i3, k3, m3;
int    i4, j4;
int    i5, j5, k5;
double flt_1, flt_2, flt_3, flt_4, flt_5, flt_6;



int main(void)
{
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    LARGE_INTEGER ticks_start;
    QueryPerformanceCounter(&ticks_start);
    
    for (int r=0; r<ITERATIONS;r++)
    {
        
           /* ────────────────────────────────────────── *
	    │ Свертка констант, арифметические тождества │
            │ и излишние операции загрузки/сохранения    │
            * ────────────────────────────────────────── */

            i3 = 1 + 2;
            flt_1 = 2.4 + 6.3;
            i2 = 5;
            j2 = i + 0;
            k2 = i / 1;
            i4 = i * 1;
            i5 = i * 0;

       #ifndef NO_ZERO_DIVIDE
	    /*
             *   Некоторые компиляторы распознают ошибку
             *   деления на нуль и не генерируют объектный код
             */
            i2 = i / 0;
            flt_2 = flt_1 / 0.0;
       #else
            printf( "This compiler handles divide-by-zero as \
                    an error\n");
       #endif
            flt_3 = 2.4 / 1.0;
            flt_4 = 1.0 + 0.0000001;
            flt_5 = flt_6 * 0.0;
	    flt_6 = flt_2 * flt_3;
    }
    /*end of block of code*/

    LARGE_INTEGER ticks_end;
    QueryPerformanceCounter(&ticks_end);

    double time_elapsed = (double)(ticks_end.QuadPart - ticks_start.QuadPart) * 1000000000 / freq.QuadPart;
    time_elapsed /= ITERATIONS;

    printf("execution time = %.4f ns\n", time_elapsed);

}