#include <stdio.h>
#include <wchar.h>
#include <locale.h>

#define MAX_LEN 81

void soedi(wchar_t *result, const wchar_t *next)
{
    size_t len_res = wcslen(result);
    size_t len_next = wcslen(next);
    size_t sovpad = 0;
    size_t max_check = (len_res < len_next) ? len_res : len_next;
    for (size_t overlap = max_check; overlap > 0; overlap--)
    {
        if (wcsncmp(result + len_res - overlap, next, overlap) == 0)
        {
            sovpad = overlap;
            break;
        }
    }
    wcscat(result, next + sovpad);
}

int main()
{
    setlocale(LC_ALL, ".UTF-8");
    wchar_t input[MAX_LEN];
    wchar_t result[MAX_LEN] = L"";
    wchar_t word[MAX_LEN];
    if (fgetws(input, MAX_LEN, stdin) == NULL)
        return 1;
    input[wcscspn(input, L"\n")] = L'\0';
    const wchar_t *ptr = input;
    while (*ptr)
    {
        while (*ptr == L' ')
            ptr++;
        if (*ptr == L'\0')
            break;
        int i = 0;
        while (*ptr != L' ' && *ptr != L'\0')
            word[i++] = *ptr++;
        word[i] = L'\0';
        if (result[0] == L'\0')
            wcscpy(result, word);
        else
            soedi(result, word);
    }
    wprintf(L"%ls\n", result);
    return 0;
}
