#include <stdio.h>

void test(FILE* f)
{
    getc(f);
    getc(f);
    getc(f);
}

int main(void)
{
    FILE* input;
    input = fopen("test.txt", "r");

    getc(input);
    printf("%c %d", ftell(input));

    return 0;
}