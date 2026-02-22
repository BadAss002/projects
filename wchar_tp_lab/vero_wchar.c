#include <wchar.h>
#include <stdio.h>
#include <locale.h>

int min(int a, int b) {
    if (a < b) {
        return(a);
    }
    else {
        return(b);
    }
}


int main()
{
    setlocale(LC_ALL, "");
    wchar_t s[91];
    wchar_t n[81];//new s

    int lim = 162;//ограничитель
    fgetws(s, lim, stdin);

    int space_orig[80];//индексы пробелов, последним должен быть индекс от \n



    int l_space_orig = 0, l_s = 0, l_n = 0;//длины,

    int ind_n;//индекс последнего на данный момент элемента в новой строке

    int k, i, j, q, w, e;

    int a, b;

    int gap, match, shield;

    for (k = 0; k < 80; k++) {
        l_s++;
        if (s[k] == ' ' || s[k] == '\n') {
            space_orig[l_space_orig] = k;
            l_space_orig++;
        }
        if (s[k] == '\n') {
            break;
        }
    }


    l_n = space_orig[0];
    for (j = 0; j < l_n; j++) {
        n[j] = s[j];
    }
    ind_n = l_n - 1;
    shield = l_n;

    for (i = 0; i < l_space_orig - 1; i++) {
        a = space_orig[i + 1] - space_orig[i] - 1;
        gap = min(shield, a);
        /*printf("%d \n", gap);*/
        for (j = gap; j > 0; j--) {
            match = 1;

            for (q = j; q > 0; q--) {
                /*printf("|%lc-%d, %lc|", n[ind_n - q+1], ind_n - q+1, s[space_orig[i] + 1 + (j - q)]);*/
                if (n[ind_n - q + 1] != s[space_orig[i] + 1 + (j - q)]) {
                    match = 0;
                }
            }

            if (match == 1) {
                /*printf("WOW!");*/
                for (w = space_orig[i] + 1 + j; w < space_orig[i + 1]; w++) {
                    ind_n++;
                    n[ind_n] = s[w];
                    
                }
                break;
            }

        }
        if (match == 0) {
            for (w = space_orig[i] + 1; w < space_orig[i + 1]; w++) {
                ind_n++;
                n[ind_n] = s[w];
            }
        }
        shield = a;

    }

    ind_n++;
    n[ind_n] = '\0';
    ind_n++;
    n[ind_n] = L'\0';
    wprintf(L"%ls", n);



    return 0;
}
