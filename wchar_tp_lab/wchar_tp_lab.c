#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main(void)
{
    setlocale(LC_ALL, "");
    wchar_t a[100];
    /* wscanf(L"%ls", a);
    wprintf(L"%ls\n", a); */
    printf("%d\n", sizeof(wchar_t));
    //commit2


    return 0;
}