      /* ────────────────────────────────────────────────────────── *
      │                                                            │
      │   Серия тестов PC Tech Journal                             │
      │   Тест оптимизации кода Си                                 │
      │                                                            │
      │   Copyright (c) 1988 Ziff-Devis Publishing Company         │
      │                                                            │
      │   Эта  программа-тест  была  разработана  для  проверки    │
      │   методов оптимизации  кода,  применяемых  компилятором    │
      │   Си. Она  не  вырабатывает  разумные  результаты  и  не   │
      │   представляет хороший стиль программирования.             │
      │                                                            │
      * ────────────────────────────────────────────────────────── */


      #include <stdio.h>
      #include <string.h>
      #define max_vector    2
      #define constant5     5

      typedef unsigned char    uchar;

      int    i, j, k, l, m;
      int    i2, j2, k2;
      int    g3, h3, i3, k3, m3;
      int    i4, j4;
      int    i5, j5, k5;

      double flt_1, flt_2, flt_3, flt_4, flt_5, flt_6;

      int    ivector[ 3 ];
      volatile uchar  ivector2[ 3 ];
      short  ivector4[ 6 ];
      int    ivector5[ 100 ];

void func()
{
      for( i4 = 0; i4 <= max_vector; i4++)
      {
            ivector2[ i4 ] = j * k;
            printf("okak\n");
      }

}


      int /* cdecl */  main( argc, argv )           /* optbench */
         int argc;
         char **argv;
      {
            /* ────────────────────────────────────── *
             │  Вынесение инвариантного кода          │
             │  (j * k) может быть вынесено из цикла  │
	     * ────────────────────────────────────── */

            func();


      }