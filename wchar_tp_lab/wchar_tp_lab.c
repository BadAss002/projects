#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#define LENGTH 81
#define MAX_LENGTH 81*4

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

wchar_t* word_counter(wchar_t* start)
{
    wchar_t* ptr;
    if (ptr = wcschr(start, L' '))
    {
        *ptr++ = L'\0';
        return ptr;
    }
    else
    {
        return 0; // перепиши если будут валиться тесты с непонятными пробелами
    }
}

int main(void)
{
    //FILE * input;
    //input = fopen("example.txt", "r");
    setlocale(LC_ALL, "");
    wchar_t start_line[MAX_LENGTH];
    wchar_t word[LENGTH];
    wchar_t next_word[LENGTH];
    wchar_t final_word[LENGTH] = L"";
    wchar_t* word_ptrs[LENGTH]; // массив указателей на слова в start_line
    wchar_t *where_to_copy; // указывает на next_word часть которую надо оставить

    if (fgetws(start_line, LENGTH, stdin) == NULL)
        return 1;

    int i = 0;
    word_ptrs[i++] = start_line;
    while (word_ptrs[i] = word_counter(word_ptrs[i-1])) i++;

    i = 0;
    while (word_ptrs[i+1])
    {
        wcscpy(word, word_ptrs[i]);
        wcscpy(next_word, word_ptrs[i+1]);
        if (i == 0)
            wcscat(final_word, word);
        if (where_to_copy = common_part_find(word, next_word))
        {
            wcscat(final_word, where_to_copy);
        }
        else
        {
            wcscat(final_word, next_word);
        }
        for (int j=0;j<81;j++)
            {
                word[j] = L' ';
                next_word[j] = L' ';
            }
        i++;
    }


    wprintf(L"%ls", final_word); //убери лишний \n если тесты не пройдут
    
    //fclose(input);

    return 0;
}