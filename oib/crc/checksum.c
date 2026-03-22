#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 300

FILE* f;
int length = 0; //длина файла с EOF

int checksum(char * text)
{
    unsigned char in;
    int T = 0; //сумма входных данных
    int M = UCHAR_MAX; //максимально допустимое значение контрольной суммы
    int C; //эталонная контрольная сумма
    length = 0;
    fseek(f,0,SEEK_SET);
    while((in = *text++))
    {
        T+=in;
        length++;
    }
    length--;

    C = T%(M+1);

    return C;
}


int main(void)
{
    srand(time(NULL));
    f = fopen("test.txt","r+");
    unsigned char text[MAX_LENGTH];
    if (!fgets(text,MAX_LENGTH,f))
        return -1;

    printf("%s\n\n",text);
    int c1 = checksum(text); //эталонная контрольная сумма
    int shift = rand()%length;
    char temp = text[shift];
    text[shift] = 'Z';

    printf("%s\n\n",text);
    int c2 = checksum(text); //контрольная сумма с заменой буквы
    text[shift] = temp;
    char text_temp[MAX_LENGTH];
    strcpy(text_temp,text);
    strcat(text, text_temp);

    printf("%s\n\n",text);
    int c3 = checksum(text); //контрольная сумма с копией строки
    strcpy(text,text_temp);
    int first_ch = rand()%length;
    int second_ch = rand()%length;
    temp = text[first_ch];
    text[first_ch] = text[second_ch];
    text[second_ch]= temp;

    printf("%s\t%c <-> %c\n\n",text,text[first_ch],text[second_ch]);
    int c4 = checksum(text); //контрольная сумма с перестановкой символов

    printf("Checksums:\n\
Standard: %d\n\
Ch_replace: %d\n\
Str_copy: %d\n\
Ch_permutation: %d\n",c1,c2,c3,c4);
    
    

    fclose(f);
    return 0;
}