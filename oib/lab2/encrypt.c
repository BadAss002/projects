#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>
#include <string.h>

#define shift 10

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
    wchar_t encoded_char;

    while ((c = fgetwc(input)) != WEOF)
    {
        c = towupper(c);

        for (int i =0;i<33;i++)
        {
            if (iswalpha(c))
            {
                if (c+shift <= last_alpha)
                    encoded_char = c+shift-1;
                else
                    encoded_char = first_alpha + (c+shift-last_alpha) -1;
            }
            else
                encoded_char = c;
        }
        fputwc(encoded_char,output);
    }
    fclose(input);
    fclose(output);
}