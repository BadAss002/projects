#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>


#define MAX_LENGTH 40000
#define const_poly  0xEDB88320u
#define CRC_WIDTH 32
#define POLY 0x104C11DB7u

FILE* f;
FILE* g;
int length = 0; //длина файла

// Контрольная сумма
int checksum(char * text,long long current_length)
{
    long long T = 0; //сумма входных данных
    long long M = UCHAR_MAX; //максимально допустимое значение контрольной суммы
    long long C; //эталонная контрольная сумма
    fseek(f,0,SEEK_SET);

    for(long long i=0;i<current_length;i++)
    {
        T += text[i];
    }

    C = T % (M+1);

    return C;
}

// CRC-32 как нахуй просят в методичке, математически верный на 1000%(поменять глобальную poly на 0x04C11DB7u)
// uint32_t crc32(const unsigned char *text, size_t current_length)
// {
//     uint32_t crc = 0xFFFFFFFFu;

//     for (size_t i=0;i<current_length; i++)
//     {
//         crc ^= ((uint32_t)text[i] << 24);

//         for(int j = 0; j < 8; j++)
//         {
//             if(crc & 0x80000000u)
//                 crc = (crc << 1) ^ const_poly;
//             else
//                 crc <<= 1;
//         }
//     }

//     return crc ^ 0xFFFFFFFF;
// }
//delenie
// uint32_t crc32(uint8_t* data, size_t len) {
//     size_t total_bits = len * 8 + CRC_WIDTH;
//     size_t total_bytes = (total_bits + 7) / 8;

//     // Буфер с исходными данными + 32 нуля (CRC_WIDTH)
//     uint8_t* message = calloc(total_bytes, sizeof(uint8_t));
//     if (!message) return 0;
//     memcpy(message, data, len);

//     // Делимое в битах
//     uint8_t* dividend = malloc(total_bytes);
//     if (!dividend) { free(message); return 0; }
//     memcpy(dividend, message, total_bytes);

//     // Деление в столбик по битам
//     for (size_t bit_pos = 0; bit_pos <= total_bits - (CRC_WIDTH + 1); bit_pos++) {
//         size_t byte_idx = bit_pos / 8;
//         int bit_in_byte = 7 - (bit_pos % 8);

//         int current_bit = (dividend[byte_idx] >> bit_in_byte) & 1;

//         if (current_bit) {
//             // XOR по всем битам полинома
//             for (int i = 0; i < CRC_WIDTH + 1; i++) {
//                 size_t xor_byte = (bit_pos + i) / 8;
//                 int xor_bit = 7 - ((bit_pos + i) % 8);

//                 int poly_bit = (POLY >> (CRC_WIDTH - i)) & 1;
//                 if (poly_bit) dividend[xor_byte] ^= (1 << xor_bit);
//             }
//         }
//     }

//     // Извлечение CRC (последние 32 бита)
//     uint32_t crc = 0;
//     for (int i = 0; i < CRC_WIDTH; i++) {
//         size_t bit_pos = total_bits - CRC_WIDTH + i;
//         size_t byte_idx = bit_pos / 8;
//         int bit_in_byte = 7 - (bit_pos % 8);
//         if ((dividend[byte_idx] >> bit_in_byte) & 1) {
//             crc |= (1 << (CRC_WIDTH - 1 - i));
//         }
//     }

//     free(message);
//     free(dividend);

//     return crc;
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

void line_double_safe(char *text, size_t text_size, const char *src, size_t src_len) {
    if (2 * src_len > text_size) {
        fprintf(stderr, "Error: buffer too small to double the string\n");
        exit(1);
    }
    for (size_t i = 0; i < src_len; i++) {
        text[i] = src[i];
        text[src_len + i] = src[i];
    }
}


int main(void)
{
    srand(time(NULL));

    char file_name[] = "big_file.docx";
    f = fopen(file_name,"rb");
    g = fopen("results.txt","a");
    // if (!f) {
    // perror("Cannot open file");
    // return 1;}

    unsigned char text[MAX_LENGTH];
    length = fread(text, 1, MAX_LENGTH, f);
//     printf("%zu\n", length);
//     for (size_t i = 0; i < length; i++)
// {
//     printf("%02X ", text[i]);
// }
// printf("\n");






    int c1 = checksum(text,length); //эталонная контрольная сумма
    unsigned int s1 = crc32(text,length);

    // Замена символа
    int shift = rand()%length;

    char temp = text[shift];
    text[shift] = 'Z';


    int c2 = checksum(text,length); //контрольная сумма с заменой буквы
    unsigned int s2 = crc32(text,length);

    text[shift] = temp;

    // Копирование строки
    char text_temp[MAX_LENGTH * 2];
    for (int i=0;i<length;i++)
        text_temp[i]=text[i];
    
    line_double_safe(text_temp, sizeof(text_temp), text, length);

    //printf("%s\n\n",text_temp);

    int c3 = checksum(text_temp,length*2); //контрольная сумма с копией строки
    unsigned int s3 = crc32(text_temp,length*2);


    // Перестановка символов
    int first_ch = rand()%length;
    int second_ch = rand()%length;

    temp = text[first_ch];
    text[first_ch] = text[second_ch];
    text[second_ch] = temp;

    printf("\t%c(%d) <-> %c(%d)\n\n",
       text[first_ch], first_ch,
       text[second_ch], second_ch);

    int c4 = checksum(text,length); //контрольная сумма с перестановкой символов
    unsigned int s4 = crc32(text,length);

    fprintf(g,"%s\n",file_name);
    fprintf(g,"Checksums:\n\
Standard: %d\n\
Ch_replace: %d\n\
Str_copy: %d\n\
Ch_permutation: %d\n\n",c1,c2,c3,c4);
    fprintf(g,"SRC32:\n\
Standard: %#x\n\
Ch_replace: %#x\n\
Str_copy: %#x\n\
Ch_permutation: %#x\n",s1,s2,s3,s4);
    fprintf(g,"================================\n\n");

    fclose(f);
    fclose(g);

    return 0;
}
