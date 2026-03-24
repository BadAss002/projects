#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 400

FILE* f;
int length = 0; //длина файла

// Контрольная сумма
int checksum(char * text,int current_length)
{
    int T = 0; //сумма входных данных
    int M = UCHAR_MAX; //максимально допустимое значение контрольной суммы
    int C; //эталонная контрольная сумма
    fseek(f,0,SEEK_SET);

    for(int i=0;i<current_length;i++)
    {
        T += text[i];
    }

    C = T % (M+1);

    return C;
}

// SRC32 (CRC-32)
unsigned int src32(char *text,int current_length)
{
    unsigned int crc = 0xFFFFFFFF;

    for (int i=0;i<current_length;i++)
    {
        crc ^= (unsigned char)text[i];

        for(int j = 0; j < 8; j++)
        {
            if(crc & 1)
                crc = (crc >> 1) ^ 0xEDB88320;
            else
                crc >>= 1;
        }
    }

    return crc;
}

void print_line(char * text,int current_length)
{
    for (int i=0;i<current_length;i++)
        printf("%c",text[i]);
    printf("\n\n");
}

void line_double(char * text)
{
    for (int i=0;i<length;i++)
    {
        text[length+i] = text[i];
    }
}

int main(void)
{
    srand(time(NULL));

    f = fopen("test.txt","r");

    unsigned char text[MAX_LENGTH];
    char ch;

    while ((ch = fgetc(f)) != EOF)
    {
        text[length++] = ch;
    }

    print_line(text,length);

    int c1 = checksum(text,length); //эталонная контрольная сумма
    unsigned int s1 = src32(text,length);

    // Замена символа
    int shift = rand()%length;

    char temp = text[shift];
    text[shift] = 'Z';

    print_line(text,length);

    int c2 = checksum(text,length); //контрольная сумма с заменой буквы
    unsigned int s2 = src32(text,length);

    text[shift] = temp;

    // Копирование строки
    char text_temp[MAX_LENGTH];
    for (int i=0;i<length;i++)
        text_temp[i]=text[i];
    
    line_double(text_temp);

    print_line(text_temp,length*2);
    //printf("%s\n\n",text_temp);

    int c3 = checksum(text_temp,length*2); //контрольная сумма с копией строки
    unsigned int s3 = src32(text_temp,length*2);


    // Перестановка символов
    int first_ch = rand()%length;
    int second_ch = rand()%length;

    temp = text[first_ch];
    text[first_ch] = text[second_ch];
    text[second_ch] = temp;

    print_line(text,length);
    printf("\t%c(%d) <-> %c(%d)\n\n",text,text[first_ch],first_ch,text[second_ch],second_ch);

    int c4 = checksum(text,length); //контрольная сумма с перестановкой символов
    unsigned int s4 = src32(text,length);

    printf("Checksums:\n\
Standard: %d\n\
Ch_replace: %d\n\
Str_copy: %d\n\
Ch_permutation: %d\n\n",c1,c2,c3,c4);

    printf("SRC32:\n\
Standard: %#x\n\
Ch_replace: %#x\n\
Str_copy: %#x\n\
Ch_permutation: %#x\n",s1,s2,s3,s4);

    fclose(f);

    return 0;
}
