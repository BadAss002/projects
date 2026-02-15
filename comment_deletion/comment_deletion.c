#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 1000
int backslashes[MAX_LENGTH]; // backslahes[номер_строки] = индекс_в_строке
char current_str[MAX_LENGTH];
char changed_str[MAX_LENGTH];
char prev_str[MAX_LENGTH];

FILE* f;
FILE* g;

//записываем все обратные слеши
void get_quotes()
{
    int line_number = 0;
    int character_number = 0;
    for (int i = 0; i<1000; i++)
    {
        backslashes[i] = -1;
    }

    while (fgets(current_str, 1000, f) != NULL)
    {
        //printf("%s", current_str);
        //создание массива обратных слешей
        while (current_str[character_number])
        {
            if(current_str[character_number] == '\\' && current_str[character_number+1] == '\n') //&& current_str[character_number-1] != '\\'
            {
                backslashes[line_number] = character_number;
            }

            character_number++;
        }
        line_number++;
        character_number = 0;
    }
}

int main(int argc, char* argv[])
{
    f = fopen("test.c", "r");
    g = fopen("test.wc", "w");
    get_quotes();
    fseek(f,SEEK_SET,0);

    int i = 0;
    int chnumb = 0;
    int line_number = 0;
    int fl_string_const = 0;
    int fl_single_string_const = 0;
    int fl_base = 0;
    int prolongation_base = 0; //если после //
    int prolongation_next = 0; // если после очередного переноса комм
    int fl_prolongation = 0;
    int fl_star_comment = 0;
    int fl_multiline_str_const = 0;
    int fl_multiline_single_str_const = 0;
    int end_of_str = 0;
    int fl = 1;
    int b;
    int backslashes_counter = 0;
    int quote_start[2]; // quote_start[0 - номер строки 1 - индекс кавычки в строке]
    
    while (fgets(current_str, 1000, f) != NULL)
    {
        //printf("%s\n", current_str);
        while (current_str[i])
        {
        
            //флаг пропуск последующих условий при строковой константе
            if (fl_string_const)
            {
                if (current_str[i] == '"' && i > quote_start[1] && line_number == quote_start[0]) // если в той же строке кавычка закрывается
                {
                    //проверка на escape-последовательность \"
                    b = i-1;
                    while (current_str[b--] == '\\')
                        backslashes_counter++;
                    if (backslashes_counter % 2 == 0)
                    {
                        fl_string_const = 0;
                        fl = 0;
                    }
                    backslashes_counter = 0;
                }
                else if (line_number > quote_start[0]) // если закрывается на следующей или отсутствует обратный слеш
                {
                    //проверка на escape-последовательность
                    b = 2;
                    while (prev_str[end_of_str-b] == '\\')
                    {
                        b++;
                        backslashes_counter++;
                    }
                    if (backslashes_counter % 2 == 0)
                        fl_string_const = 0;
                    else if (current_str[i] == '"')
                    {
                        fl_string_const = 0;
                        fl = 0;
                    }
                    backslashes_counter = 0;
                }
            }
            // аналогично fl_string_const
            else if (fl_single_string_const)
            {
                if (current_str[i] == '\'' && i > quote_start[1] && line_number == quote_start[0]) // если в той же строке кавычка закрывается
                {
                    //проверка на escape-последовательность \"
                    b = i-1;
                    while (current_str[b--] == '\\')
                        backslashes_counter++;
                    if (backslashes_counter % 2 == 0)
                    {
                        fl_single_string_const = 0;
                        fl = 0;
                    }
                    backslashes_counter = 0;
                }
                else if (line_number > quote_start[0]) // если закрывается на следующей или отсутствует обратный слеш
                {
                    //проверка на escape-последовательность
                    b = 2;
                    while (prev_str[end_of_str-b] == '\\')
                    {
                        b++;
                        backslashes_counter++;
                    }
                    if (backslashes_counter % 2 == 0)
                        fl_single_string_const = 0;
                    else if (current_str[i] == '\'')
                    {
                        fl_string_const = 0;
                        fl = 0;
                    }
                    backslashes_counter = 0;
                }
            }

            //блок условий строковых констант
            if (!fl_string_const && !fl_single_string_const && !fl_base && !fl_prolongation && !fl_star_comment && fl)
            {
                if (current_str[i] == '"')
                {
                    fl_string_const = 1;
                    quote_start[0] = line_number;
                    quote_start[1] = i;
                }
                else if (current_str[i] == '\'')
                {
                    fl_single_string_const = 1;
                    quote_start[0] = line_number;
                    quote_start[1] = i;
                }
            }
            else
                fl = 1;
        
            //блок условий комментариев (основной)
            if (!(fl_string_const || fl_single_string_const))
            {
                if (current_str[i] == '/' && current_str[i+1] == '/' && !fl_star_comment && !fl_prolongation)
                    fl_base = 1;
                else if (backslashes[line_number] != -1 && fl_base)
                    prolongation_base = 1;
                else if (backslashes[line_number] != -1 && fl_prolongation)
                    prolongation_next = 1;
                else if (current_str[i] == '/' && current_str[i+1] == '*' && !fl_base && !fl_prolongation && !fl_star_comment)
                {
                    fl_star_comment = 1;
                    current_str[i] = 1;
                    current_str[i+1] = 1;
                }
                else if (current_str[i] == '*' && current_str[i+1] == '/' && !fl_base && !fl_prolongation && fl_star_comment)
                {
                    fl_star_comment = 0;
                    current_str[i] = 1;
                    current_str[i+1] = 1;
                }
            }

            //блок переписи строки
            if (!(fl_base || fl_prolongation || fl_star_comment) && current_str[i] != 1)
            {
                changed_str[chnumb] = current_str[i];
                chnumb++;
            }
            else if (current_str[i] == '\n')
            {
                changed_str[chnumb++] = '\n';
                break;
            }

                
            i++;
        }
        changed_str[chnumb] = '\0';
        end_of_str = i;
        for (int j = 0; j<=end_of_str; j++)
        {
            prev_str[j] = changed_str[j];
        }

        // блок обнуления флагов
        i = 0;
        chnumb = 0;
        fl_base = 0;
        if (prolongation_base || prolongation_next)
        {
            fl_prolongation = 1;
            prolongation_base = 0;
            prolongation_next = 0;
        }
        else
            fl_prolongation = 0;

        // запись строки в файл

        fputs(changed_str,g);

        for (int j = 0; j<1000; j++)
        {
            changed_str[j] = ' ';
        }

        line_number++;
    }



    fclose(f);
    fclose(g);

    return 0;
}
