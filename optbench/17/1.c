#include <stdio.h>

int x,y,k;

int func(int x, int y)
{
    k = 100;
    while (k>0)
    {
        if (x==y) k--;
        else k -= x;
    }

    return x+y+k;
}

int main(void)
{
    printf("%d\n", func(10,15));

    return 0;
}