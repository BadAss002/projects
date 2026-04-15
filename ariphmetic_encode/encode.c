#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define min 65 // 65 = A

void file_generator()
{
    FILE* f;
    f = fopen("text.txt", "w");
    for (int i = 0; i<150000;i++)
    {
        char ch = min + rand()%5;
        fputc(ch,f);
    }
}

struct intervals
{
    double left;
    double right;
    char letter;
    struct intervals* next;
};

void encode(char* name_of_file)
{
    FILE* input;
    input = fopen(name_of_file, "r");

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

    double left = 0;
    //double right = 1;
    //делаем таблицу интервалов в завимисости от частот
    for (int i = 0;i<256;i++)
    {
        if (count_table[i] != 0)
        {
            intervals->left = left;
            intervals->right = left+((double)count_table[i]/number_of_characters);
            left = intervals->right;
            intervals->letter = i;
            intervals->next = malloc(sizeof(struct intervals));
            intervals = intervals->next;
        }
    }

    // while (root->next != NULL)
    // {
    //     printf("letter:%c left:%f right:%f\n", root->letter,root->left,root->right);
    //     root = root->next;
    // }

    //высчитываем сужение интервала
    struct intervals* ptr = root;
    double currleft, currsize, prevleft, prevsize;
    prevleft = 0;
    prevsize = 1;
    double newleft, newright, newsize; //считаемый интервал
    while (ptr->next != NULL)
    {
        //сетап
        currleft = ptr->left;
        currsize = ptr->right - ptr->left;
        //формула
        newleft = prevleft + currleft*prevsize;
        newsize = currsize * prevsize;
        newright = newleft + newsize;
        //переход к след шагу
        prevleft = newleft;
        prevsize = newsize;
        ptr = ptr->next;
    }
    printf("[%f;%f] size=%f\n",newleft,newright,newsize);
    //выбор случайного числа из полученного интервала
    double special_number;
    int very_special_number;
    int exponent;
    char fl = 1;
    for (int i=1;i<1000;i++)
    {
        for(int j=1;j<30;j++)
        {
            special_number = (double)i/pow(2,j);
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
        printf("fix_this_with_frexp\n");
    }

    int add_zeros;
    for (int i=0;i<30;i++)
    {
        if (very_special_number < pow(2,i))
        {
            add_zeros = i - (floor(log10(very_special_number))+1);
        }
    }



    //запись закодированного файла
    FILE* g;
    g = fopen("encoded_a.txt", "w");

    for (int i=0;i<add_zeros;i++)
        fputc(0,g);
    //допиши
}

int main(void)
{   
    //file_generator();
    encode("text.txt");

    return 0;
}