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

             /* ────────────────────────────────────────────────────── *
        │  Функция: loop_unrolling                               │
        │           Цикл в этой функции должен быть заменен      │
        │           тремя присваиваниями с использованием        │
	│           константной индексации массива или машинно-  │
        │           зависимыми командами для инициализации       │
        │           блока памяти.                                │
        * ────────────────────────────────────────────────────── */

       void loop_unrolling( x )
            int x;
            {
                for( i = 0; i < 6; i++ )
                    ivector4[ i ] = 0;
	    } /* Конец loop_unrolling */

      int /* cdecl */  main( argc, argv )           /* optbench */
         int argc;
         char **argv;
      {
           	loop_unrolling();


      }