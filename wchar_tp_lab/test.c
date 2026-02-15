#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#define MAX_LEN 81
size_t find(const wchar_t *a, const wchar_t *b){
    size_t len_a = wcslen(a);
    size_t len_b = wcslen(b);
    size_t max = (len_a < len_b) ? len_a : len_b;
    for (size_t k = max; k > 0; k--)
    {
        if (wcsncmp(a + len_a - k, b, k) == 0)
            return k;
    }
    return 0;
}
void soedinit(wchar_t *result, const wchar_t *prev, const wchar_t *curr){
    size_t obsh = find(prev, curr);
    wcscat(result, curr + obsh);
}
int main()
{
    setlocale(LC_ALL, "");
    wchar_t input[MAX_LEN];
    wchar_t word[MAX_LEN];
    wchar_t prev[MAX_LEN] = L"";
    wchar_t result[MAX_LEN] = L"";
    if (fgetws(input, MAX_LEN, stdin) == NULL)
        return 1;
    input[wcscspn(input, L"\n")] = L'\0';
    const wchar_t *veldan = input;
    int first = 1;
    while (*veldan)
    {
        while (*veldan == L' ')
            veldan++;
        if (*veldan == L'\0')
            break;
        int i = 0;
        while (*veldan != L' ' && *veldan != L'\0' && i < MAX_LEN - 1)
            word[i++] = *veldan++;
        word[i] = L'\0';

        if (first)
        {
            wcscpy(result, word);
            wcscpy(prev, word);
            first = 0;
        }
        else
        {
            soedinit(result, prev, word);
            wcscpy(prev, word);
        }
    }
    wprintf(L"%ls\n", result);
    return 0;
}