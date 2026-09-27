#include <stdio.h>

int main(void)
{
    FILE * input = fopen("stats.txt", "r");
    FILE * assembly = fopen("1.s", "r");

    long number;
    long sum = 0;
    
    for (int i=0;i<10;i++)
    {
        fscanf(input, "%ld\n", &number);
        //printf("%ld\n", number);
        sum += number;
    }

    long average = sum / 10;

    fclose(input);
    remove("stats.txt");

    char ch;
    int lines_count = 0;
    while ((ch = fgetc(assembly)) != EOF)
    {
        if (ch == '\n')
            lines_count++;
    }

    printf("avg: %ld lines: %d\n", average, lines_count);

    fclose(assembly);
}