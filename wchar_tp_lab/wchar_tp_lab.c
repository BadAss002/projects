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

wchar_t * line_assignment (wchar_t* start,wchar_t* curr, wchar_t* next,wchar_t* beginning_of_last_word, int state)
{
    wchar_t* curr_line_ptr;
    wchar_t* next_line_ptr;
    if (state == 1) // не в начале
    {
        if (curr_line_ptr = wcschr(beginning_of_last_word, L' '))
        {
            *curr_line_ptr = L'\0';
            wcscpy(next, beginning_of_last_word);
        }
        else if (curr_line_ptr = wcschr(beginning_of_last_word, L'\n'))
        {
            *curr_line_ptr = '\0';
            wcscpy(next, beginning_of_last_word);
            return 0;
        }
        else
        {
            curr_line_ptr = wcschr(beginning_of_last_word, L'\n');
            *curr_line_ptr = '\0';
            wcscpy(next, beginning_of_last_word);
            return 0;
        }
        return curr_line_ptr;
    }
    else if (state == 3) // в начале
    {
        curr_line_ptr = wcschr(start, L' ');
        *curr_line_ptr++ = L'\0';
        wcscpy(curr, start);

        if (next_line_ptr = wcschr(curr_line_ptr, L' '))
        {
            *next_line_ptr++ = L'\0';
            wcscpy(next, curr_line_ptr); 
        }
        else if (next_line_ptr = wcschr(curr_line_ptr, L'\n'))
        {
            *next_line_ptr = L'\0';
            wcscpy(next, curr_line_ptr);
            return 0;
        }
        else
        {
            next_line_ptr = wcschr(curr_line_ptr, L'\0');
            *next_line_ptr = L'\0';
            wcscpy(next, curr_line_ptr);
            return 0;
        }

        return next_line_ptr;
    }

    return start;
}

int main(void)
{
    setlocale(LC_ALL, "");
    wchar_t start_line[LENGTH];
    wchar_t line[LENGTH];
    wchar_t next_line[LENGTH];
    wchar_t final_line[LENGTH] = L"";
    wchar_t *where_to_copy; // указывает на next_line часть которую надо оставить
    wchar_t *beginning_of_last_word;
    wchar_t *temp;
    int state = 3;


    if (fgetws(start_line, LENGTH, stdin) == NULL)
        return 1;

    beginning_of_last_word = line_assignment(start_line, line, next_line,0,state);
    //wprintf(L"%ls\n%ls\n", line, next_line);

    do
    {
        where_to_copy = common_part_find(line, next_line);

        if (where_to_copy && state == 3)
        {
            wcscat(line, where_to_copy);
            wcscat(final_line, line);
            wcscpy(line, next_line);
            state = 2;
        }
        else if (where_to_copy && state == 2)
        {
            wcscat(final_line,where_to_copy);
            wcscpy(line, next_line);
        }
        else
        {
            wcscat(line, next_line);
            wcscat(final_line, line);
            wcscpy(line, next_line);
            state = 2;
        }

        // костыль на выход
        if (beginning_of_last_word == 0)
            break;
        else
        {
            //wprintf(L"%ls\n", beginning_of_last_word);
            temp = line_assignment(start_line, line, next_line,beginning_of_last_word,1);
            beginning_of_last_word = temp;
            //printf("fsdofjisd");
        }

    } while (1);

    wprintf(L"%ls\n", final_line);
    
    return 0;
}