#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>
#include <string.h>

#define MAX_TEXT 200000
#define MAX_HISTORY 1000
#define ALPHABET 33
#define SHIFT 1

wchar_t text[MAX_TEXT];

wchar_t substitution[65536];

typedef struct
{
    wchar_t cipher;
    wchar_t plain;
} History;

History history[MAX_HISTORY];
int history_size = 0;

//частоты русских букв

wchar_t russian_letters[] =
L"ОЕАИНТСРВЛКМДПУЯЫЬГЗБЧЙХЖШЮЦЩЭФЪ";

wchar_t russian_alphabet[] = L"АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";

double russian_freq[ALPHABET] =
{
0.1097,0.0845,0.0801,0.0735,0.0670,
0.0632,0.0547,0.0473,0.0454,0.0440,
0.0349,0.0321,0.0298,0.0281,0.0262,
0.0201,0.0190,0.0174,0.0165,0.0159,
0.0144,0.0121,0.0097,0.0094,0.0073,
0.0064,0.0048,0.0036,0.0032,0.0026,
0.0026,0.0004
};

typedef struct
{
    wchar_t letter;
    int count;
} Freq;

Freq freq_table[65536];

void load_text()
{
    FILE *f = fopen("encoded_text.txt","r");

    if(!f)
    {
        printf("Ошибка открытия файла\n");
        exit(1);
    }

    int i=0;
    wint_t c;

    while((c=fgetwc(f))!=WEOF && i<MAX_TEXT-1)
    {
        text[i++] = towupper(c);
    }

    text[i]=L'\0';

    fclose(f);
}

void show_cipher()
{
    wprintf(L"\nКриптограмма:\n%ls\n",text);
}

//частотный анализ

void analyze_frequency()
{
    int total=0;

    for(int i=0;i<65536;i++)
        freq_table[i].count=0;

    for(int i=0;text[i];i++)
    {
        wchar_t c=text[i];

        if(iswalpha(c))
        {
            freq_table[c].letter=c;
            freq_table[c].count++;
            total++;
        }
    }

    wprintf(L"\nЧастоты букв:\n");

    for(int i=0;i<65536;i++)
    {
        if(freq_table[i].count>0)
        {
            wprintf(L"%lc : %.4f\n",
            i,
            (double)freq_table[i].count/total);
        }
    }
}

//сортировка по убыванию частоты встречаемости

void sort_freq(Freq *arr,int n)
{
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
            if(arr[j].count>arr[i].count)
            {
                Freq t=arr[i];
                arr[i]=arr[j];
                arr[j]=t;
            }
}

//предполагаемые замены

void suggest_substitutions()
{
    Freq arr[ALPHABET];
    int n=0;

    for(int i=0;i<65536;i++)
    {
        if(freq_table[i].count>0)
        {
            arr[n].letter=i;
            arr[n].count=freq_table[i].count;
            n++;
        }
    }

    sort_freq(arr,n);

    wprintf(L"\nПредполагаемые замены:\n");

    for(int i=0;i<n && i<ALPHABET;i++)
    {
        wprintf(L"%lc -> %lc\n",
        arr[i].letter,
        russian_letters[i]);
    }
}

// показать расшифровку

void show_decryption()
{
    wprintf(L"\nКриптограмма:\n%ls\n",text);

    wprintf(L"\nРасшифровка:\n");

    for(int i=0;text[i];i++)
    {
        wchar_t c=text[i];

        if(substitution[c])
            wprintf(L"%lc",substitution[c]);
        else if(iswalpha(c))
            wprintf(L"%lc",text[i]);
        else
            wprintf(L"%lc",c);
    }

    wprintf(L"\n");
}

//меняю буквы

void add_substitution()
{
    wchar_t c,p;

    wprintf(L"Введите букву криптограммы: ");
    wscanf(L" %lc",&c);

    wprintf(L"Введите замену: ");
    wscanf(L" %lc",&p);

    c=towupper(c);
    p=towlower(p);

    substitution[c]=p;

    if(history_size<MAX_HISTORY)
    {
        history[history_size].cipher=c;
        history[history_size].plain=p;
        history_size++;
    }

    wprintf(L"Замена добавлена\n");
}

//откат замен

void undo_substitution()
{
    if(history_size==0)
    {
        wprintf(L"История пуста\n");
        return;
    }

    history_size--;

    wchar_t c=history[history_size].cipher;

    substitution[c]=0;

    wprintf(L"Последняя замена отменена\n");
}

//показ истории

void show_history()
{
    if(history_size==0)
    {
        wprintf(L"История пуста\n");
        return;
    }

    wprintf(L"\nИстория замен:\n");

    for(int i=0;i<history_size;i++)
    {
        wprintf(L"%d) %lc -> %lc\n",
        i+1,
        history[i].cipher,
        history[i].plain);
    }
}

//группировка слов по длине

void group_words_by_length()
{
    wchar_t words[100][100];
    int lens[100];
    int counts[100];

    int groups=0;

    wchar_t word[100];
    int len=0;

    for(int i=0;;i++)
    {
        wchar_t c=text[i];

        if(iswalpha(c))
        {
            word[len++]=c;
        }
        else
        {
            if(len>0)
            {
                word[len]=0;

                int g=-1;

                for(int j=0;j<groups;j++)
                    if(lens[j]==len)
                        g=j;

                if(g==-1)
                {
                    lens[groups]=len;
                    counts[groups]=0;
                    g=groups++;
                }

                wcscpy(words[g*10 + counts[g]],word);
                counts[g]++;

                len=0;
            }

            if(c==0) break;
        }
    }

    for(int i=0;i<groups;i++)
        for(int j=i+1;j<groups;j++)
            if(lens[j]<lens[i])
            {
                int tl=lens[i];
                lens[i]=lens[j];
                lens[j]=tl;
            }

    wprintf(L"\nСлова по длине:\n");

    for(int i=0;i<groups;i++)
    {
        wprintf(L"%d: ",lens[i]);

        for(int j=0;j<counts[i];j++)
        {
            wprintf(L"%ls",words[i*10 + j]);

            if(j<counts[i]-1)
                wprintf(L", ");
        }

        wprintf(L"\n");
    }
}

// слова по неизвестным БуквАм

void group_words_by_unknown()
{
    wchar_t word[100];
    int len=0;

    wprintf(L"\nСлова по неизвестным буквам:\n");

    for(int i=0;;i++)
    {
        wchar_t c=text[i];

        if(iswalpha(c))
        {
            word[len++]=c;
        }
        else
        {
            if(len>0)
            {
                int unknown=0;

                for(int j=0;j<len;j++)
                    if(!substitution[word[j]])
                        unknown++;

                word[len]=0;

                wprintf(L"%d неизвестных : %ls\n",
                unknown,
                word);

                len=0;
            }

            if(c==0)
                break;
        }
    }
}

// авто .... замена

void auto_substitution()
{
    Freq arr[ALPHABET];
    int n=0;
    int succesful_sub = 0;
    wchar_t expected_letter;

    for(int i=0;i<65536;i++)
        if(freq_table[i].count>0)
        {
            arr[n].letter=i;
            arr[n].count=freq_table[i].count;
            n++;
        }

    sort_freq(arr,n);

    for(int i=0;i<n && i<ALPHABET;i++)
    {
        for (int j=0;j<ALPHABET;j++) //проверка успешности автозамены
        {
            if (arr[i].letter == russian_alphabet[j] && j+SHIFT <= ALPHABET-1)
                expected_letter = russian_alphabet[j+SHIFT];
            else if (arr[i].letter == russian_alphabet[j])
                expected_letter = russian_alphabet[j+SHIFT-ALPHABET];
        }
        wprintf(L"%lc %lc\n", expected_letter, russian_letters[i]);
        if (expected_letter == russian_letters[i])
            succesful_sub++;
        substitution[arr[i].letter]=towlower(russian_letters[i]);
    }

    wprintf(L"Автоматическая замена выполнена\n");
    wprintf(L"%d\n", succesful_sub);
}

//меню

void menu()
{
    wprintf(L"\nКРИПТОАНАЛИЗ\n");
    wprintf(L"1 Показать криптограмму\n");
    wprintf(L"2 Частотный анализ\n");
    wprintf(L"3 Предполагаемые замены\n");
    wprintf(L"4 Показать расшифровку\n");
    wprintf(L"5 Слова по длине\n");
    wprintf(L"6 Слова по неизвестным\n");
    wprintf(L"7 Добавить замену\n");
    wprintf(L"8 Отменить замену\n");
    wprintf(L"9 Автоматическая замена\n");
    wprintf(L"0 История замен\n");
}

int main()
{
    setlocale(LC_ALL,"");

    for(int i=0;i<65536;i++)
        substitution[i]=0;

    load_text();

    analyze_frequency();

    wchar_t cmd;
    wchar_t buffer[10];

    while(1)
    {
        menu();

        wprintf(L"\nВведите команду: ");
        wscanf(L" %lc", &cmd);

        switch(cmd)
        {
            case L'1': show_cipher(); break;
            case L'2': analyze_frequency(); break;
            case L'3': suggest_substitutions(); break;
            case L'4': show_decryption(); break;
            case L'5': group_words_by_length(); break;
            case L'6': group_words_by_unknown(); break;
            case L'7': add_substitution(); break;
            case L'8': undo_substitution(); break;
            case L'9': auto_substitution(); break;
            case L'0': show_history(); break;
        }
    }
}