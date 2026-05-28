#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

#define min 65 // 65 = A

void file_generator()
{
    FILE* f;
    f = fopen("text.txt", "w");
    for (int i = 0; i<25;i++)
    {
        char ch = min + rand()%3;
        fputc(ch,f);
    }
    fclose(f);
}

struct intervals
{
    long double left;
    long double right;
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
    FILE* g;
    g = fopen("encoded_a.txt", "w");

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



    fclose(g);
    fclose(input);
}

void decode(char *name_of_file)
{
    FILE* input;
    FILE* output;
    input = fopen(name_of_file,"r");
    output = fopen("decoded_a.txt", "w");
    int length_of_message = 17;

    //получаем выбранное число
    char ch;
    char special_binary[50];
    char binary_length = 0;
    while((ch = getc(input)) != ' ')
        special_binary[binary_length++] = ch;
    special_binary[binary_length] = '\0';
    int very_special_number = strtol(special_binary,NULL,2);
    int exponent = strlen(special_binary);
    long double special_number = (long double)very_special_number / pow(2,exponent);
    printf("%Lf\n", special_number);

    
    //получаем буквы и их интервалы
    struct intervals* root = malloc(sizeof(struct intervals));
    struct intervals* ptr = root;
    int k = 0;
    char left_ch[10];
    char right_ch[10];
    while((ch = getc(input)) != EOF)
    {
        ptr->letter = ch;
        fgets(left_ch,9,input);
        fgets(right_ch,9,input);
        //printf("[%s;%s]\n",left_ch,right_ch);
        ptr->left = atof(left_ch);
        ptr->right = atof(right_ch);
        ptr->next = malloc(sizeof(struct intervals));
        ptr = ptr->next;
    }

    ptr = root;
    while(ptr->next != NULL)
    {
        printf("%lc [%Lf;%Lf]\n",ptr->letter,ptr->left,ptr->right);
        ptr = ptr->next;
    }
    //return 0;

    //декодирование по формуле
    ptr = root;
    long double currleft, currsize, prevleft, prevsize;
    prevleft = 0;
    prevsize = 1;
    int count;
    long double newleft, newright, newsize; //считаемый интервал
    while (ptr->letter != '~')
    {
        //сетап
        ptr = root;
        for (int i=0;i<5;i++)
        {
            if (special_number > ptr->left && special_number < ptr->right)
            {
                putc(ptr->letter, output);
                currleft = ptr->left;
                currsize = ptr->right - ptr->left;
                count++;
                break;
            }
            else
                ptr = ptr->next;
            if (count >= 0 && count < 10)
            {
                printf("[%Lf;%Lf]\n",newleft,newright);
            }
            else
                return 0;
        }
        //формула
        newleft = prevleft + currleft*prevsize;
        printf("%Lf + %Lf * %Lf\n", prevleft, currleft, prevsize);
        newsize = currsize * prevsize;
        newright = newleft + newsize;
        //переход к след шагу
        prevleft = newleft;
        prevsize = newsize;
    }
    

}



int main(void)
{   
    //file_generator();
    //encode("easy.txt");

    decode("encoded_a.txt");

    return 0;
}