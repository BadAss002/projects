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

struct student
{
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
};

struct bjj {
    int index; //номер сборника
    int start_pos; //начало строки в файле
    wchar_t surname[LENGTH_OF_NAME];
    wchar_t name[LENGTH_OF_NAME];
    wchar_t patronymic[LENGTH_OF_NAME];
    wchar_t course;
    union team_member
    {
        int spo;
        struct student student;
    } team_member;
    wchar_t direction[CODE_LENGTH];
    wchar_t group_number[GROUP_NUM_LENGTH];
    int wins;
    int defeats;
    float percentage_of_wins;
};

void clear_buffer()
{
    wchar_t c;
    while ((c = getwchar()) != L'\n' && c != WEOF); //очистка stdin
}


struct bjj* read_file(FILE* input_copy, struct bjj* ptr_bjj_copy)
{
    wchar_t ch;
    char wins_temp[5];
    char defeats_temp[5];
    char conversion[2];
    int state = 0;
    int i = 0;
    int starting_point;
    //ptr_bjj_copy = realloc(ptr_bjj_copy,sizeof(struct bjj)*100);
    while ((ch = fgetwc(input_copy)) != WEOF)
    {
        //wprintf(L"%lc",ch);
        if (ch == L'\n')
        {
            if (state == 9)
            {
                defeats_temp[i] = '\0';
                (ptr_bjj_copy+base_count)->wins=atoi(wins_temp);
                (ptr_bjj_copy+base_count)->defeats=atoi(defeats_temp);
                (ptr_bjj_copy+base_count)->percentage_of_wins=(float)(ptr_bjj_copy+base_count)->wins/((ptr_bjj_copy+base_count)->wins+(ptr_bjj_copy+base_count)->defeats);
            }
            (ptr_bjj_copy+base_count)->start_pos=ftell(input_copy)+1;
            (ptr_bjj_copy+base_count)->index=base_count;
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
                conversion[0] = ch;
                conversion[1] = '\0';
                if (ch == L'4')
                    (ptr_bjj_copy+base_count)->team_member.spo = -1;
                else    
                    (ptr_bjj_copy+base_count)->team_member.student.course_type = atoi(conversion);
                break;
            case 5:
                conversion[0] = ch;
                conversion[1]= '\0';
                if (!((ptr_bjj_copy+base_count)->team_member.spo == -1))
                    (ptr_bjj_copy+base_count)->team_member.student.institute = atoi(conversion);
                else 
                    (ptr_bjj_copy+base_count)->team_member.student.institute = 10;
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

    struct bjj* new_ptr = bjj_copy+base_count; //check
    for (int i = 0;i<base_count;i++)
        if (bjj_copy+i==NULL)
            new_ptr = bjj_copy+i;
    
    wprintf(L"Введите нового члена сборной по следующей форме:\n\
Фамилия Имя Отчество Курс Тип_Обучения Институт Код_Направления Номер_Группы Победы Поражения\n\
(0 - бакалавриат 1 - магистратура 2 - специалитет 3 - аспирантура 4 - СПО)\n\
0 - ФизМех\n1 - ИКНК\n2 - ИПМЭиТ\n3 - ГИ\n4 - ИММиТ\n5 - ИСИ\n6 - ИБСиБ\n7 - ИФКСТ\n8 - ИЭиТ\n9 - ИЭ\n* - СПО\n");
    
    wchar_t string[100];
    //clear_buffer();
    if (!fgetws(string, 100, stdin))
    {
        wprintf(L"Ошибка синтаксиса");
        return NULL;
    }
    int pos = ftell(input_copy); 
    fwprintf(input_copy,string);
    fseek(input_copy,pos,SEEK_SET);
    read_file(input_copy,bjj_copy);

    return bjj_copy;
}

void delete(struct bjj* bjj_copy, int index)
{
    struct bjj* bjj_delete=bjj_copy+index;
    for (int i = 0; i<LENGTH_OF_NAME;i++)
    {
        bjj_delete->surname[i]=L'\0';
        bjj_delete->name[i]=L'\0';
        bjj_delete->patronymic[i]=L'\0';
    }
    
    base_count--;
}

void show(struct bjj* bjj_copy, int i)
{
    wprintf(L"%d %ls %ls %ls %lc ",
    (bjj_copy+i)->index,
    (bjj_copy+i)->surname,
    (bjj_copy+i)->name,
    (bjj_copy+i)->patronymic,
    (bjj_copy+i)->course);
    if ((bjj_copy+i)->team_member.student.course_type == бакалавриат) wprintf(L"бакалавриат ");
    else if ((bjj_copy+i)-> team_member.student.course_type == магистратура) wprintf(L"магистратура ");
    else if ((bjj_copy+i)-> team_member.student.course_type == специалитет) wprintf(L"специалитет ");
    else if ((bjj_copy+i)-> team_member.student.course_type == аспирантура) wprintf(L"аспирантура ");
    else wprintf(L"СПО ");
    if ((bjj_copy+i)->team_member.student.institute == ФизМех) wprintf(L"ФизМех ");
    else if ((bjj_copy+i)->team_member.student.institute == ИКНК) wprintf(L"ИКНК ");
    else if ((bjj_copy+i)->team_member.student.institute == ИПМЭиТ) wprintf(L"ИПМЭиТ ");
    else if ((bjj_copy+i)->team_member.student.institute == ГИ) wprintf(L"ГИ ");
    else if ((bjj_copy+i)->team_member.student.institute == ИММиТ) wprintf(L"ИММиТ ");
    else if ((bjj_copy+i)->team_member.student.institute == ИСИ) wprintf(L"ИСИ ");
    else if ((bjj_copy+i)->team_member.student.institute == ИБСиБ) wprintf(L"ИБСиБ ");
    else if ((bjj_copy+i)->team_member.student.institute == ИФКСТ) wprintf(L"ИФКСТ ");
    else if ((bjj_copy+i)->team_member.student.institute == ИЭиТ) wprintf(L"ИЭиТ ");
    else if ((bjj_copy+i)->team_member.student.institute == ИЭ) wprintf(L"ИЭ ");
    wprintf(L"%ls\\%ls %d\\%d Процент побед:%.2f%%\n",
    (bjj_copy+i)->direction,
    (bjj_copy+i)->group_number,
    (bjj_copy+i)->wins,
    (bjj_copy+i)->defeats,
    (bjj_copy+i)->percentage_of_wins*100);
}

void search(struct bjj* bjj_copy)
{
    wchar_t string[LENGTH_OF_NAME];
    int *founded = malloc(sizeof(int)*(memory+1)*START_MEMORY);
    int count_of_founded = 0;
    wprintf(L"Введите фамилию:\n");

    if (!fgetws(string,LENGTH_OF_NAME,stdin))
        wprintf(L"Ошибка");
    
    string[wcslen(string)-1] = L'\0'; //убираем \n

    for (int i=0;i<base_count;i++)
    {
        int fl = 1;
        for (int j=0;j<wcslen(string);j++)
            if (string[j] != (bjj_copy+i)->surname[j]) fl=0;
        if (fl)
        {
            founded[count_of_founded] = i;
            count_of_founded++; 
        }
    }

    for (int i = 0;i<count_of_founded;i++)
    {
        show(bjj_copy,founded[i]);
    }
}

int menu(struct bjj* bjj_copy, FILE* input_copy)
{
    wchar_t state;
    wprintf(L"Введите комманду:\n(0-показать всех 1-добавить сборника 2-удалить сборника 3-поиск по фамилии)\n");
    
    fflush(stdin);
    state = getwchar();
    getwchar(); //чтобы убрать \n из stdin

    if (state == L'0')
        for (int i =0;i<base_count;i++)
            show(bjj_copy,i);
    else if (state == L'1')
        insert(input_copy,bjj_copy);
    else if (state == L'2')
    {
        wprintf(L"Введите номер сборника:");
        int length = (floor(log10((double)base_count)) + 1);
        int index;
        char *number = malloc(sizeof(wchar_t)*length);
        if (!fgets(number,length,stdin))
            wprintf(L"Неправильно набран номер");
        index = atoi(number);
        delete(bjj_copy,index);
    }
    else if (state == L'3')
        search(bjj_copy);


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
    while (1)
        menu(ptr_bjj,input);

    //допиши удаление сборника и актуализацию файла

    fclose(input);

    return 0;
}