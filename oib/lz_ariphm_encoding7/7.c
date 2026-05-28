#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define MAX_DICT 4096
#define MAX_STR 256

typedef struct {
    int index;
    char symbol;
} Pair;

char dictionary[MAX_DICT][MAX_STR];
int dict_size = 1;

struct intervals
{
    long double left;
    long double right;
    char letter;
    struct intervals* next;
};

void arithmetic_encode(FILE* input,FILE* g)
{
    // FILE* input;
    // input = fopen(name_of_file, "r");

    char ch;
    int number_of_characters = 0; //символов в файле
    int count_table[256];

    for (int i =0;i<256;i++)
        count_table[i] = 0;
    while ((ch = getc(input)) != EOF)
    {
        count_table[ch]++;
        number_of_characters++;
    }

    struct intervals* intervals = malloc(sizeof(struct intervals));
    struct intervals* root = intervals;

    long double left = 0;
    //long double right = 1;
    //делаем таблицу интервалов в завимисости от частот
    for (int i = 0;i<256;i++)
    {
        if (count_table[i] != 0)
        {
            intervals->left = left;
            intervals->right = left+((long double)count_table[i]/number_of_characters);
            left = intervals->right;
            intervals->letter = i;
            intervals->next = malloc(sizeof(struct intervals));
            intervals = intervals->next;
        }
    }


    struct intervals* ptr = root;
    while (ptr->next != NULL)
    {
        printf("letter:%c left:%Lf right:%Lf\n", ptr->letter,ptr->left,ptr->right);
        ptr = ptr->next;
    }
    
    //высчитываем сужение интервала
    ptr = root;
    long double currleft, currsize, prevleft, prevsize;
    prevleft = 0;
    prevsize = 1;
    long double newleft, newright, newsize; //считаемый интервал
    fseek(input,0,SEEK_SET);
    while ((ch = getc(input)) != EOF)
    {
        //сетап
        ptr = root;
        while (ptr->next != NULL)
        {
            if (ptr->letter == ch)
            {
                currleft = ptr->left;
                currsize = ptr->right - ptr->left;
                break;
            }
            else
                ptr = ptr->next;
        }
        //формула
        newleft = prevleft + currleft*prevsize;
        newsize = currsize * prevsize;
        newright = newleft + newsize;
        //переход к след шагу
        prevleft = newleft;
        prevsize = newsize;
    }
    printf("[%Lf;%Lf] size=%.*Lf\n",newleft,newright,__LDBL_MANT_DIG__,newsize);
    //выбор случайного числа из полученного интервала
    long double special_number;
    int very_special_number;
    int exponent;
    char fl = 1;
    for (int i=1;i<1000;i++)
    {
        for(int j=1;j<30;j++)
        {
            special_number = (long double)i/pow(2,j);
            //printf("%f\n",special_number);
            if (special_number > newleft && special_number < newright)
            {
                fl = 0;
                very_special_number = i;
                exponent = j;
                break;
            }
        }
        if (fl == 0)
            break;
    }
    if (fl == 1)
    {
        printf("fix_this_shit\n");
    }
    printf("%Lf %d\n", special_number,exponent);

    //запись закодированного файла
    // FILE* g;
    // g = fopen("encoded_a.txt", "w");

    char binary_length = 0;
    very_special_number = very_special_number;
    int k = very_special_number;
    char special_binary[256];
    while(k)
    {
        if (k%2)
            special_binary[binary_length] = '1';
        else
            special_binary[binary_length] = '0';
        k/=2;
        binary_length++;
    }
    special_binary[binary_length] = '\0'; // 0 влияет на strlen!

    //запись выбранного числа из интервала
    for (int i=0;i<(exponent-binary_length);i++)
        fputc('0',g);
    for (int i=binary_length-1;i>-1;i--)
        fputc(special_binary[i],g);
    fputc(' ',g);

    //запись букв и интервалов
    ptr = root;
    char buffer[50];
    while (ptr->next != NULL)
    {
        fputc(ptr->letter,g);
        fprintf(g,"%Lf",ptr->left);
        fprintf(g,"%Lf",ptr->right);
        ptr = ptr->next;
    }



    // fclose(g);
    // fclose(input);
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