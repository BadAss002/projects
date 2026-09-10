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

    // this is not also
    // char a = 'e';
    /*
        'l' '\n'
        'dsfdsffsd'
    */
    unsigned value = '𰀐';

    //unsigned value2 = '𰀐𰀐';
    //unsigned value3 = '𰀐𰀐';
    unsigned okak = '\0\0';

    unsigned value4 = 'ab\
cd';

    unsigned okak2 = '\0\
\0\0\0';

    unsigned okak3 = '\t\t\t\t';

    unsigned value6 = 'abcd\
';

    unsigned value5 = 'abcd';


    return 0;
}