#include <stdio.h>
#include <uchar.h>
#include <locale.h>
#include <string.h>

int main(void) {
    setlocale(LC_ALL, ".UTF-8");
    
    
    mbstate_t state = {0};
    char32_t ch = 0xFFFFFFFF;
    unsigned value = '𰀐';
    const char* ptr = (const char*)&value;
    unsigned char mbc[5] = {0,0,0,0,0};
    int j = 0;
    for (int i=3;i>=0 && j<4;i--) 
    {
        mbc[i] = (unsigned char)ptr[j];
        j++;
    }

    for (int i=0;i<4;i++) printf("%x ", mbc[i]);
    printf("\n");

    //char c[] = "ᠠ";
   
    // unsigned lol[] = 'a \
    // b';

    size_t res = 1;
    res = mbrtoc32(&ch, mbc, 4, &state);
        //ptr++;
        //printf("%d\n", strlen(ptr));
    printf("Прочитано байт: %d\n", res);
        //printf("Код символа: U+%04X\n", ch);
        // printf("Это символ: ");
    for (int i=0;i<4;i++)
    {
        printf("%x ", (unsigned char)ptr[i]);
    }
    printf("U+%04X\n", ch);
    //printf("%d", sizeof(char32_t));

    //char string[100];

    //c32rtomb(string,ch,&state);

    //printf("%s\n", string);
    
    return 0;
}