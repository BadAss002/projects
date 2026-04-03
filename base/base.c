#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <math.h>
#define START_MEMORY 20
#define LENGTH_OF_NAME 100
#define CODE_LENGTH 8 // длина кода направления
#define GROUP_NUM_LENGTH 6 // длина номера группы

int base_count = 0;
int memory = 0; // количество увеличений памяти

struct bjj {
    wchar_t surname[LENGTH_OF_NAME];
    wchar_t name[LENGTH_OF_NAME];
    wchar_t patronymic[LENGTH_OF_NAME];
    wchar_t course;
    enum course_type {
        бакалавриат,
        магистратура,
        специалитет,
        аспирантура
    } course_type;
    enum institute {
        ФизМех,
        ИКНК,
        ИПМЭиТ,
        ГИ,
        ИММиТ,
        ИСИ,
        ИБСиБ,
        ИФКСТ,
        ИЭиТ,
        ИЭ
    } institute;
    wchar_t direction[CODE_LENGTH];
    wchar_t group_number[GROUP_NUM_LENGTH];
    int wins;
    int defeats;
    float percentage_of_wins;
    FILE* starting_point;
};


struct bjj* read_file(FILE* input_copy, struct bjj* ptr_bjj_copy)
{
    wchar_t ch;
    char wins_temp[5];
    char defeats_temp[5];
    int state = 0;
    int i = 0;
    //ptr_bjj_copy = realloc(ptr_bjj_copy,sizeof(struct bjj)*100);
    while ((ch = fgetwc(input_copy)) != WEOF)
    {
        //wprintf(L"%lc",ch);
        if (ch == L'\n')
        {
            //(ptr_bjj_copy+base_count)->starting_point=ftell(input_copy)+1;
            base_count++;
            if (base_count >= START_MEMORY)
            {
                memory++;
                ptr_bjj_copy = realloc(ptr_bjj_copy,sizeof(struct bjj)*START_MEMORY*(memory+1));
            }
            state = 0;
            i=0;
        }
        else if (ch == L' ')
        {
            if (state == 0)
                (ptr_bjj_copy+base_count)->surname[i]=L'\0';
            else if(state == 1)
                (ptr_bjj_copy+base_count)->name[i]=L'\0';
            else if(state == 2)
                (ptr_bjj_copy+base_count)->patronymic[i]=L'\0';
            else if (state == 6)
                (ptr_bjj_copy+base_count)->direction[i]=L'\0';
            else if (state == 7)
                (ptr_bjj_copy+base_count)->group_number[i]=L'\0';
            else if (state == 8)
                wins_temp[i] = '\0';
            else if (state == 9)
            {
                defeats_temp[i] = '\0';
                (ptr_bjj_copy+base_count)->wins=atoi(wins_temp);
                (ptr_bjj_copy+base_count)->defeats=atoi(defeats_temp);
                (ptr_bjj_copy+base_count)->percentage_of_wins=(float)(ptr_bjj_copy+base_count)->wins/((ptr_bjj_copy+base_count)->wins+(ptr_bjj_copy+base_count)->defeats);
            }
            state++;
            i=0;
        }
        else
        {
            switch (state)
            {
            case 0:
                (ptr_bjj_copy+base_count)->surname[i++]=ch;
                break;
            case 1:
                (ptr_bjj_copy+base_count)->name[i++]=ch;
                break;
            case 2:
                (ptr_bjj_copy+base_count)->patronymic[i++]=ch;
                break;
            case 3:
                (ptr_bjj_copy+base_count)->course=ch;
                break;
            case 4:
                (ptr_bjj_copy+base_count)->course_type=(enum course_type)ch;
                break;
            case 5:
                (ptr_bjj_copy+base_count)->institute=(enum institute)ch;
                break;
            case 6:
                (ptr_bjj_copy+base_count)->direction[i++]=ch;
                break;
            case 7:
                (ptr_bjj_copy+base_count)->group_number[i++]=ch;
                break;
            case 8:
                wins_temp[i++]=(char)ch;
                break;
            case 9:
                defeats_temp[i++]=(char)ch;
                break;
            
            default:
                break;
            }
        }
    }

    return ptr_bjj_copy;
}

struct bjj* insert(FILE* input_copy,struct bjj* bjj_copy)
{
    if (base_count >= START_MEMORY*(memory+1))
    {
        memory++;
        bjj_copy = realloc(bjj_copy,sizeof(struct bjj)*START_MEMORY*(memory+1));
    }

    struct bjj* new_ptr = bjj_copy+base_count;
    for (int i = 0;i<base_count;i++)
        if (bjj_copy+i==NULL)
            new_ptr = bjj_copy+i;
    
    wprintf(L"Введите нового члена сборной по следующей форме:\n\
Фамилия Имя Отчество Курс Тип_Обучения Институт Код_Направления Номер_Группы Победы Поражения\n\
(0 - бакалавриат 1 - магистратура 2 - специалитет 3 - аспирантура)\n\
0 - ФизМех\n1 - ИКНК\n2 - ИПМЭиТ\n3 - ГИ\n4 - ИММиТ\n5 - ИСИ\n6 - ИБСиБ\n7 - ИФКСТ\n8 - ИЭиТ\n9 - ИЭиТ\n10 - ИЭ\n");
    
    wchar_t string[100];
    fgetws(string, 100, stdin);
    // int pos = ftell(input_copy); 
    // fwprintf(input_copy,string);
    // fseek(input_copy,pos,SEEK_SET);
    read_file(input_copy,bjj_copy);

    return bjj_copy;
}

void delete(struct bjj* bjj_copy, int index)
{
    struct bjj* bjj_delete=bjj_copy+index;
    for (int i = 0; i<LENGTH_OF_NAME;i++)
        bjj_delete->surname[i]=NULL;
    
    base_count--;
}

void search(struct bjj* bjj_copy)
{
    wprintf(L"Укажите объект поиска\n\
0-Фамилия 1-Имя 2-Отчество 3-Курс 4-Тип_Обучения\
 5-Институт 6-Код_Направления 7-Номер_Группы 8-Победы 9-Поражения\n");

    wchar_t state;
    state = getwchar();
    wchar_t string[LENGTH_OF_NAME];
    int *founded = malloc(sizeof(int)*(memory+1)*START_MEMORY);
    int count_of_founded = 0;

    if (state == L'0')
    {
        wprintf(L"Введите фамилию:\n");
        wchar_t c;
        while ((c = getwchar()) != '\n' && c != EOF);
        fgetws(string,LENGTH_OF_NAME,stdin);
        string[wcslen(string)-1] = L'\0';
        for (int i=0;i<base_count;i++)
        {
            int fl = 1;
            for (int j=0;j<wcslen(string);j++)
                if (string[j] != (bjj_copy+i)->surname[j]) fl=0;
            if (fl)
            {
                founded[count_of_founded] = i;
                count_of_founded++; 
                wprintf(L"%d",i);
            }
        }
    }
    else if (state == L'1')
    {
        wprintf(L"Введите имя:\n");
        wchar_t c;
        while ((c = getwchar()) != '\n' && c != EOF);
        fgetws(string,LENGTH_OF_NAME,stdin);
        string[wcslen(string)-1] = L'\0';
        for (int i=0;i<base_count;i++)
        {
            int fl = 1;
            for (int j=0;j<wcslen(string);j++)
                if (string[j] != (bjj_copy+i)->name[j]) fl=0;
            if (fl)
            {
                founded[count_of_founded] = i;
                count_of_founded++; 
                wprintf(L"%d",i);
            }
        }
    }
    if (state == L'2')
    {
        wprintf(L"Введите отчество:\n");
        wchar_t c;
        while ((c = getwchar()) != '\n' && c != EOF);
        fgetws(string,LENGTH_OF_NAME,stdin);
        string[wcslen(string)-1] = L'\0';
        for (int i=0;i<base_count;i++)
        {
            int fl = 1;
            for (int j=0;j<wcslen(string);j++)
                if (string[j] != (bjj_copy+i)->patronymic[j]) fl=0;
            if (fl)
            {
                founded[count_of_founded] = i;
                count_of_founded++; 
                wprintf(L"%d",i);
            }
        }
    }
    
}


int main(void)
{
    setlocale(LC_ALL, "");
    FILE* input;
    input = fopen("text.txt", "r+");

    struct bjj * ptr_bjj;
    ptr_bjj = (struct bjj*)malloc(START_MEMORY*sizeof(struct bjj));
    //ptr_bjj = realloc(ptr_bjj, sizeof(struct bjj)*100);
    ptr_bjj = read_file(input, ptr_bjj);

    //ptr_bjj = insert(input,ptr_bjj);

    //delete(ptr_bjj, 1);

    search(ptr_bjj);

    //wprintf(L"%ls %ls %ls\n",(ptr_bjj)->surname,(ptr_bjj+1)->surname,(ptr_bjj+18)->surname);

    fclose(input);

    return 0;
}