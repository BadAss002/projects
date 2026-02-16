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

int line_assignment (wchar_t* start,wchar_t* curr, wchar_t* next, int state)
{
    wchar_t* curr_line_ptr;
    wchar_t* next_line_ptr;
    if (state == 1) // если соединяем
    {
        
    }
    else if (state == 3) // в начале
    {
        curr_line_ptr = wcschr(start, ' ');
        *curr_line_ptr++ = '\0';
        wcscpy(curr, start);

        if (next_line_ptr = wcschr(curr_line_ptr, ' '))
        {
            *next_line_ptr++ = '\0';
            wcscpy(next, curr_line_ptr); 
        }
        else
        {
            next_line_ptr = wcschr(curr_line_ptr, '\n');
            *next_line_ptr++ = '\0';
            wcscpy(next, curr_line_ptr);
            return 4;
        }

        return 1;
    }
}

int main(void)
{
    setlocale(LC_ALL, ".UTF-8");
    wchar_t start_line[LENGTH];
    wchar_t line[LENGTH];
    wchar_t next_line[LENGTH];
    wchar_t final_line[LENGTH] = L"";
    wchar_t *where_to_copy;
    int state = 3;


    fgetws(start_line, LENGTH, stdin);
    state = line_assignment(start_line, line, next_line,state);
    //wprintf(L"%ls\n%ls\n", line, next_line);

    do
    {
        where_to_copy = common_part_find(line, next_line);

        if (where_to_copy)
        {
            //возможные траблы с памятью   вроде пофикшено
            wcscat(line, where_to_copy);
            wcscat(final_line, line);
            
        }
        else
        {
            wcscat(final_line, line);
        }

        // костыль на выход
        if (state == 4)
            break;
        else
            state = 1;

    } while (line_assignment(start_line, line, next_line,state));

    wprintf(L"%ls\n", final_line);
    
    return 0;
}