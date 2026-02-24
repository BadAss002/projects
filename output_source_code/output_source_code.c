#include <stdio.h>
#define LENGTH 100

int main(void)
{
    FILE* input;
    input = fopen("output_source_code.c", "r");

    char ch;

    while((ch = fgetc(input)) != EOF)
    {
        printf("%c", ch);
    }

    printf("%c", ch);

    fclose(input);

    return 0;
}