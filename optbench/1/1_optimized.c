#include <stdio.h>

int    i, j, k, l, m;
int    i2, j2, k2;
int    g3, h3, i3, k3, m3;
int    i4, j4;
int    i5, j5, k5;

int main(void)
{
    /* ──────────────────────────── *
            │ Размножение констант и копий │
            *──────────────────────────────*/

    j4 = 2;
    if( i2 < 2 && i4 < 2 )
        i2 = 2;

    j4 = k5;
    if( i2 < k5 && i4 < k5 )
        i5 = 3;
}