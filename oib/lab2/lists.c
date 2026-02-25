#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>

struct CharFreq {
    wchar_t ch;
    int count;
    struct CharFreq *next;
};

int main(void)
{
    // FILE * input;
    // input = fopen("input.txt", "r");

    struct CharFreq *start = malloc(sizeof(struct CharFreq));
    (*start).count = 0;
    printf("%d\n", (*start).count);

    //fclose(input);


    

    return 0;
}