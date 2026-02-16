#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#define LENGTH 81

wchar_t* word_connector(wchar_t* first, wchar_t* second)
{
    wcscat(first,second);
    wprintf(L"%ls\n", first);
}

int main(void)
{
    setlocale(LC_ALL, "");
    wchar_t line[LENGTH];
    wchar_t next_line[LENGTH];

    while (wscanf(L"%ls", line) != EOF) 
    {
        if (wscanf(L"%ls", next_line) == EOF)
            break;
        word_connector(line, next_line);
    }


    






    return 0;
}