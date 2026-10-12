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
        │  Функция: dead_code                                    │
        │           Проверка недостижимого кода и лишних         │
        │           присваиваний. Не должен генерироваться код.  │
        * ────────────────────────────────────────────────────── */

       void dead_code( a, b )
            int a;
            char *b;
            {
              int idead_store;

              idead_store = a;
              if( 0 )
                  printf( "%s\n", b );
            } /* Конец dead_code */

      int /* cdecl */  main( argc, argv )           /* optbench */
         int argc;
         char **argv;
      {
            	    /* ───────────────────────────── *
	     │  Вызов функции с аргументами  │
	     * ───────────────────────────── */

	    dead_code( 1, "This line should not be printed" );


      }