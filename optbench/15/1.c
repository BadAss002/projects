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

/* ───────────────────────────────────────────────────── *
	│  Функция: jump_compression                            │
        │           Эта программа полезна для демонстрации      │
        │           сжатия цепочки переходов. goto end_1 может  │
        │           быть заменен на прямой переход на beg_1.    │
        * ───────────────────────────────────────────────────── */

       int jump_compression( i, j, k, l, m )
       int i, j, k, l, m;
           {
       beg_1:
               if( i < j )
                   if( j < k )
                       if( k < l )
			   if( l < m )
                               l += m;
                           else
                               goto end_1;
                       else
                           k += l;
                   else {
                       j += k;
end_1:
                       goto beg_1;
                   }
               else
                   i += j;
               return( i + j + k + l + m );
           } /* Конец jump_compression */

      int /* cdecl */  main( argc, argv )           /* optbench */
         int argc;
         char **argv;
      {
           	int x = jump_compression(1, 2, 3, 4, 5);
            printf("%d\n" , x);


      }