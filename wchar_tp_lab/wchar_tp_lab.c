#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#define LENGTH 81

wchar_t* common_part_find(wchar_t* first, wchar_t* second)
{
    wchar_t* final_ptr = 0;
    size_t max_length;
    size_t len_fisrt = wcslen(first);
    size_t len_second = wcslen(second);

    if (len_fisrt>len_second)
        max_length = len_second;
    else
        max_length = len_fisrt;

    first += len_fisrt;
    first--;

    for (size_t common_length = 1; common_length <= max_length; common_length++)
    {
        if (wcsncmp(first,second,common_length) == 0)
        {
            final_ptr = second+common_length;
            //printf("%ld\n", common_length);
        }
        first--;
    }

    
    return final_ptr;
}

int main(void)
{
    setlocale(LC_ALL, "");
    wchar_t line[LENGTH];
    wchar_t next_line[LENGTH];
    wchar_t final_line[LENGTH];
    wchar_t *where_to_copy;

    if (wscanf(L"%ls", line) == EOF)
        return -1;
    if (wscanf(L"%ls", next_line) == EOF)
        return -1;

    while (1)
    {
        where_to_copy = common_part_find(line, next_line);

        if (where_to_copy)
        {
            wcscat(line, where_to_copy);
            wcscat(final_line, line);
            wcscpy(line,next_line);
            if (wscanf(L"%ls", next_line))
                break;
        }
        else
        {
            wcscat(final_line, line);
            wcscpy(line, next_line);
            if (wscanf(L"%ls", next_line))
            {
                wcscat(final_line, line);
                break;
            }
        }
    }

    wprintf(L"%ls\n", final_line);


    






    return 0;
}