#include <stdio.h>

int x = 10;
int y = 15;

int func()
{
int k = 100;
while (k>0)
{
    if (x==y) {k--; printf("okak\n");}
    else k -= x;

    //printf("okak\n");
}

return x+y+k;
}

int main(void)
{
    int a = func();

    printf("%d\n", a);

    return 0;
}