#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_DICT 4096
#define MAX_STR 256

typedef struct {
    int index;
    char symbol;
} Pair;

char dictionary[MAX_DICT][MAX_STR];
int dict_size = 1;

void arithmetic_encode(FILE *in, FILE *out)
{
    // 
}

void arithmetic_decode(FILE *in, FILE *out)
{
    // 
}



int find_in_dict(char *str)
{
    for(int i = 1; i < dict_size; i++)
        if(strcmp(dictionary[i], str) == 0)
            return i;
    return -1;
}

void lz_encode(FILE *in, FILE *out)
{
    char buffer[MAX_STR] = "";
    int c;

    while((c = fgetc(in)) != EOF)
    {
        char temp[MAX_STR];
        strcpy(temp, buffer);

        int len = strlen(temp);
        temp[len] = c;
        temp[len+1] = '\0';

        int idx = find_in_dict(temp);

        if(idx != -1)
        {
            strcpy(buffer, temp);
        }
        else
        {
            int prefix = 0;

            if(strlen(buffer) > 0)
                prefix = find_in_dict(buffer);

            Pair p = {prefix, c};
            fwrite(&p, sizeof(Pair), 1, out);

            strcpy(dictionary[dict_size++], temp);

            buffer[0] = '\0';
        }
    }

    if(strlen(buffer) > 0)
    {
        int prefix = find_in_dict(buffer);
        Pair p = {prefix, 0};
        fwrite(&p, sizeof(Pair), 1, out);
    }
}


void lz_decode(FILE *in, FILE *out)
{
    Pair p;

    while(fread(&p, sizeof(Pair), 1, in))
    {
        char str[MAX_STR] = "";

        if(p.index != 0)
            strcpy(str, dictionary[p.index]);

        int len = strlen(str);

        if(p.symbol != 0)
        {
            str[len] = p.symbol;
            str[len+1] = '\0';
        }

        fputs(str, out);

        strcpy(dictionary[dict_size++], str);
    }
}

long file_size(FILE *f)
{
    fseek(f, 0, SEEK_END);
    long s = ftell(f);
    fseek(f, 0, SEEK_SET);
    return s;
}

int main(int argc, char *argv[])
{
    if(argc != 5)
    {
        printf("Usage:\n");
        printf("prog [a|l] [e|d] input output\n");
        return 1;
    }

    FILE *in = fopen(argv[3], "rb");
    FILE *out = fopen(argv[4], "wb");

    if(!in || !out)
    {
        printf("File error\n");
        return 1;
    }

    clock_t start = clock();

    if(argv[1][0] == 'a')
    {
        if(argv[2][0] == 'e')
            arithmetic_encode(in, out);
        else
            arithmetic_decode(in, out);
    }

    if(argv[1][0] == 'l')
    {
        if(argv[2][0] == 'e')
            lz_encode(in, out);
        else
            lz_decode(in, out);
    }

    clock_t end = clock();

    fclose(in);
    fclose(out);

   double time_spent = (double)(end-start)/CLOCKS_PER_SEC;
   FILE *f1 = fopen(argv[3], "rb");
   FILE *f2 = fopen(argv[4], "rb");
   long s1 = file_size(f1);
   long s2 = file_size(f2);

    fclose(f1);
    fclose(f2);

    printf("\nSTATISTICS\n");
    printf("Input size:  %ld bytes\n", s1);
    printf("Output size: %ld bytes\n", s2);
    printf("Time: %.6f sec\n", time_spent);

    if(s1 != 0)
        printf("Compression ratio: %.6f\n", (double)s2 / s1);
    else
        printf("Compression ratio: undefined (input size = 0)\n");

    return 0;
}