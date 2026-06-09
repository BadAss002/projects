#include <stdio.h>
#include <string.h>
#include <wchar.h>

int main(void)
{
    char a = 'b';
    char b = '\n';
    char c = '\\';
    char d = '\'';
    wchar_t e = L'ъ';

    char string[] = "Hello";
    strchr(string, 'e');

    if ('e' == 101)
    {
        printf("This is not symbol in single quotes: \'a\'");
    }

    
    
    



    unsigned value = '𰀐';


    return 0;
}