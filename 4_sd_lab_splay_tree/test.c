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
    //char c[] = "ᠠ";
   
    // unsigned lol[] = 'a \
    // b';

    size_t res = 1;
    while (res > 0)
    {
        res = mbrtoc32(&ch, ptr, 1, &state);
        ptr++;
        //printf("%d\n", strlen(ptr));
        //printf("Прочитано байт: %zu\n", res);
        //printf("Код символа: U+%04X\n", ch);
        // printf("Это символ: ");
        // for (int i=0;i<4;i++)
        // {
        //     printf("%x ", ptr[i]);
        // }
        printf("U+%04X\n", ch);
    }
    //printf("%d", sizeof(char32_t));

    //char string[100];

    //c32rtomb(string,ch,&state);

    //printf("%s\n", string);
    
    return 0;
}