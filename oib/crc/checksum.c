#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>


#define MAX_LENGTH 40000
#define const_poly  0xEDB88320u

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

// CRC-32 как нахуй просят в методичке, математически верный на 1000%(поменять глобальную poly на 0x04C11DB7u)
uint32_t crc32(const unsigned char *text, size_t current_length)
{
    uint32_t crc = 0xFFFFFFFFu;

    for (size_t i=0;i<current_length; i++)
    {
        crc ^= ((uint32_t)text[i] << 24);

        for(int j = 0; j < 8; j++)
        {
            if(crc & 0x80000000u)
                crc = (crc << 1) ^ const_poly;
            else
                crc <<= 1;
        }
    }

    return crc ^ 0xFFFFFFFF;
}
//delenie
// uint32_t crc32(const unsigned char *text, size_t current_length)
// {
//     uint32_t remainder = 0xFFFFFFFFu;

//     for (size_t i = 0; i < current_length; i++)
//     {
//         remainder ^= ((uint32_t)text[i] << 24);

//         for (int bit = 0; bit < 8; bit++)
//         {
//             if (remainder & 0x80000000u)
//                 remainder = (remainder << 1) ^ const_poly;
//             else
//                 remainder <<= 1;
//         }
//     }

//     return remainder;
// }
// CRC-32 как в стандарте, крутой классный, переносимый, одобряемый
uint32_t crc32(const unsigned char *text, size_t current_length)
{
    uint32_t crc = 0xFFFFFFFFu;

    for (size_t i=0;i<current_length; i++)
    {
        crc ^= (uint32_t)text[i];
        for(int j = 0; j < 8; j++)
        {
            if(crc & 1)
                crc = (crc >> 1) ^ const_poly;
            else
                crc >>= 1;
        }
    }

    return crc ^ 0xFFFFFFFFu;
}
//0x82F63B78 - замена для 15
// unsigned int crc_file(const char *filename)
// {
//     FILE *fp = fopen(filename, "rb");
//     if (!fp) return 0;

//     unsigned int crc = 0xFFFFFFFF;
//     int c;

//     while ((c = fgetc(fp)) != EOF)
//     {
//         crc ^= (unsigned char)c;

//         for (int i = 0; i < 8; i++)
//         {
//             if (crc & 1)
//                 crc = (crc >> 1) ^ 0xEDB88320;
//             else
//                 crc >>= 1;
//         }
//     }

//     fclose(fp);
//     return crc;
// } хуйня
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

    f = fopen("test.txt","rb");

    unsigned char text[MAX_LENGTH];
    length = fread(text, 1, MAX_LENGTH, f);
//     printf("%zu\n", length);
//     for (size_t i = 0; i < length; i++)
// {
//     printf("%02X ", text[i]);
// }
// printf("\n");




    print_line(text,length);

    int c1 = checksum(text,length); //эталонная контрольная сумма
    unsigned int s1 = crc32(text,length);

    // Замена символа
    int shift = rand()%length;

    char temp = text[shift];
    text[shift] = 'Z';

    print_line(text,length);

    int c2 = checksum(text,length); //контрольная сумма с заменой буквы
    unsigned int s2 = crc32(text,length);

    text[shift] = temp;

    // Копирование строки
    char text_temp[MAX_LENGTH];
    for (int i=0;i<length;i++)
        text_temp[i]=text[i];
    
    line_double(text_temp);

    print_line(text_temp,length*2);
    //printf("%s\n\n",text_temp);

    int c3 = checksum(text_temp,length*2); //контрольная сумма с копией строки
    unsigned int s3 = crc32(text_temp,length*2);


    // Перестановка символов
    int first_ch = rand()%length;
    int second_ch = rand()%length;

    temp = text[first_ch];
    text[first_ch] = text[second_ch];
    text[second_ch] = temp;

    print_line(text,length);
    printf("\t%c(%d) <-> %c(%d)\n\n",text,text[first_ch],first_ch,text[second_ch],second_ch);

    int c4 = checksum(text,length); //контрольная сумма с перестановкой символов
    unsigned int s4 = crc32(text,length);

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
