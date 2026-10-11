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
      uchar  ivector2[ 3 ];
      short  ivector4[ 6 ];
      int    ivector5[ 100 ];

      int /* cdecl */  main( argc, argv )           /* optbench */
         int argc;
         char **argv;
      {
	    /* ───────────── *
             │  Простой цикл │
             * ───────────── */

            j5 = 0;
            k5 = 10000;
            do {
                k5 = k5 - 1;
                j5 = j5 + 1;
                i5 = (k5 * 3) / (j5 * constant5);
               } while ( k5 > 0 );


      }