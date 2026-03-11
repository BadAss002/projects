#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>
#include <string.h>

#define shift 1

int main(void)
{
    setlocale(LC_ALL,"");
    FILE* input;
    FILE* output;
    input = fopen("source_text.txt", "r");
    output = fopen("encoded_text.txt","w");
    wchar_t c;
    wchar_t first_alpha = L'А';
    wchar_t last_alpha = L'Я';
    wchar_t e = L'ё';
    wchar_t E = L'Ё';
    wchar_t normal_e = L'е';
    wchar_t encoded_char;

    while ((c = fgetwc(input)) != WEOF)
    {
        if (c == e || c == E)
            c = normal_e;

        c = towupper(c);
        
        if (iswalpha(c))
        {
            if (c+shift <= last_alpha)
                encoded_char = c+shift;
            else
                encoded_char = first_alpha + (c+shift-last_alpha)-1;
        }
        else
            encoded_char = c;

        fputwc(encoded_char,output);
    }
    fclose(input);
    fclose(output);
}