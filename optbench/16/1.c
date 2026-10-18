#include <stdio.h>

short A[30];
short B[15];
short D[20];

short c,q,t;

void func()
{
    for (int i=0;i<10;i++)
    {
        B[i] = A[i]*c + q;
        D[i] = A[i+1]*c;
        printf("okak\n");
    }

    return;
}


int main(void)
{
    func();

    return 0;
}