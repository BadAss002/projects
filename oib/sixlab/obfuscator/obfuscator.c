#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void string_constant_skip(FILE** input_ptr, FILE** output_ptr, char *ch_ptr)
{
    FILE* f1 = *input_ptr;
    FILE* f2 = *output_ptr;
    char c = *ch_ptr;
    if (c == '"') {
        fputc(c, f2);
        while ((c = fgetc(f1)) != EOF) {
            fputc(c, f2);
            if (c == '"') {break;}
            if (c == '\\') {
                int temp = fgetc(f1);
                if (temp != EOF) {fputc(temp, f2);}
            }
            else if (c == '\n') {
                break;
            }
        }
        *ch_ptr = fgetc(f1);
    }
    else if (c == '\'') {
        fputc(c, f2);
        while ((c = fgetc(f1)) != EOF) {
            fputc(c, f2);
            if (c == '\'') {break;}
            if (c == '\\') {
                int temp = fgetc(f1);
                if (temp != EOF) {fputc(temp, f2);}
            }
            else if (c == '\n') {
                break;
            }
        }
        *ch_ptr = fgetc(f1);
    }
}


int comment_deletion(FILE* f1) {
    FILE* f2 = fopen("temp.wc", "w");
    if (f1 == NULL || f2 == NULL) {
        if (f1) {fclose(f1);}
        return 1;

    }
    int c, next;
    while ((c = fgetc(f1)) != EOF) {
        if (c == '"') {
            fputc(c, f2);
            while ((c = fgetc(f1)) != EOF) {
                fputc(c, f2);
                if (c == '"') {break;}
                if (c == '\\') {
                    int temp = fgetc(f1);
                    if (temp != EOF) {fputc(temp, f2);}
                }
                else if (c == '\n') {
                    break;
                }
            }
        }
        else if (c == '\'') {
            fputc(c, f2);
            while ((c = fgetc(f1)) != EOF) {
                fputc(c, f2);
                if (c == '\'') {break;}
                if (c == '\\') {
                    int temp = fgetc(f1);
                    if (temp != EOF) {fputc(temp, f2);}
                }
                else if (c == '\n') {
                    break;
                }
            }
        }
        else if (c == '/') {
            next = fgetc(f1);
            if (next == '/') {
                while ((c = fgetc(f1)) != EOF) {
                    if (c == '\n') {
                        fputc(c, f2);
                        break;
                    }
                    else if (c == '\r') {
                        fputc(c, f2);
                        int temp = fgetc(f1);
                        if (temp == '\n') {
                            fputc(temp, f2);
                        }
                        else if (temp != EOF) {
                            ungetc(temp, f1);
                        }
                        break;
                    }
                    if (c == '\\') {
                        int temp = fgetc(f1);
                        if (temp == '\n' || temp == '\r') {
                            if (temp == '\r') {
                                int temp2 = fgetc(f1);
                                if (temp2 == '\n') {
                                }
                                else if (temp2 != EOF) {
                                    ungetc(temp2, f1);
                                }
                            }
                        }
                        else if (temp != EOF) {
                            ungetc(temp, f1);
                        }
                    }
                }
            }
            else if (next == '*') {
                while ((c = fgetc(f1)) != EOF) {
                    if (c == '\n') {
                        fputc(c, f2);
                    }
                    else if (c == '\r') {
                        fputc(c, f2);
                        int temp = fgetc(f1);
                        if (temp == '\n') {
                            fputc(temp, f2);
                        }
                        else if (temp != EOF) {
                            ungetc(temp, f1);
                        }
                    }
                    else if (c == '*') {
                        next = fgetc(f1);
                        if (next == '/') break;
                        if (next != EOF) ungetc(next, f1);
                    }
                }
            }
            else {
                fputc(c, f2);
                if (next != EOF) ungetc(next, f1);
            }
        }
        else {
            fputc(c, f2);
        }
    }

    fclose(f1);
    fclose(f2);
    remove("prog.c");
    rename("temp.wc", "prog.c");

    return 0;
}

char variables[100][100];
int variable_number = 0;
void new_variable(FILE* input, FILE* output, char* ch_ptr) // last getc() = ' '
{
    while ((*ch_ptr = getc(input)))
    {
        if (isalpha(*ch_ptr))
        {
            break;
        }
        putc(*ch_ptr, output);
    }

    int i = 0;
    while (isalpha(*ch_ptr) || *ch_ptr == '_')
    {
        variables[variable_number][i++] = *ch_ptr;
        putc(*ch_ptr, output);
        *ch_ptr = getc(input);
    }
    variables[variable_number][i] = '\0';
    variable_number++;
}

void keyword_check(FILE** input_ptr, FILE** output_ptr, char* flags, char* ch_ptr, int prev_ch)
{
    if (*ch_ptr == 'c' && flags[0] == 0 && isalpha(prev_ch) == 0)
        {flags[0]++;}
    else if (*ch_ptr == 'h' && flags[0] == 1)
        {flags[0]++;}
    else if (*ch_ptr == 'a' && flags[0] == 2)
        {flags[0]++;}
    else if (*ch_ptr == 'r' && flags[0] == 3)
        {flags[0]++;}
    else if (*ch_ptr == ' ' && flags[0] == 4)
    {
        putc(*ch_ptr, *output_ptr);
        flags[0] = 0;
        //new_variable(*input_ptr,*output_ptr,ch_ptr);
    }
    else
    {
        flags[0] = 0;
    }

    if (*ch_ptr == 'i' && flags[1] == 0 && isalpha(prev_ch) == 0)
        {flags[1]++;}
    else if (*ch_ptr == 'n' && flags[1] == 1)
        {flags[1]++;}
    else if (*ch_ptr == 't' && flags[1] == 2)
        {flags[1]++;}
    else if (*ch_ptr == ' ' && flags[1] == 3)
    {
        putc(*ch_ptr, *output_ptr);
        flags[1] = 0;
        //new_variable(*input_ptr,*output_ptr,ch_ptr);
    }
    else
    {
        flags[1] = 0;
    }

    if (*ch_ptr == 'l' && flags[2] == 0 && isalpha(prev_ch) == 0)
        {flags[2]++;}
    else if (*ch_ptr == 'o' && flags[2] == 1)
        {flags[2]++;}
    else if (*ch_ptr == 'n' && flags[2] == 2)
        {flags[2]++;}
    else if (*ch_ptr == 'g' && flags[2] == 3)
        {flags[2]++;}
    else if (*ch_ptr == ' ' && flags[2] == 4)
    {
        putc(*ch_ptr, *output_ptr);
        flags[2] = 0;
    }
    else
    {
        flags[2] = 0;
    }

    if (*ch_ptr == 'u' && flags[3] == 0 && isalpha(prev_ch) == 0)
        {flags[3]++;}
    else if (*ch_ptr == 'n' && flags[3] == 1)
        {flags[3]++;}
    else if (*ch_ptr == 's' && flags[3] == 2)
        {flags[3]++;}
    else if (*ch_ptr == 'i' && flags[3] == 3)
        {flags[3]++;}
    else if (*ch_ptr == 'g' && flags[3] == 4)
        {flags[3]++;}
    else if (*ch_ptr == 'n' && flags[3] == 5)
        {flags[3]++;}
    else if (*ch_ptr == 'e' && flags[3] == 6)
        {flags[3]++;}
    else if (*ch_ptr == 'd' && flags[3] == 7)
        {flags[3]++;}
    else if (*ch_ptr == ' ' && flags[3] == 8)
    {
        putc(*ch_ptr, *output_ptr);
        flags[3] = 0;
    }
    else
    {
        flags[3] = 0;
    }

    if (*ch_ptr == 's' && flags[4] == 0 && isalpha(prev_ch) == 0)
        {flags[4]++;}
    else if (*ch_ptr == 'i' && flags[4] == 1)
        {flags[4]++;}
    else if (*ch_ptr == 'g' && flags[4] == 2)
        {flags[4]++;}
    else if (*ch_ptr == 'n' && flags[4] == 3)
        {flags[4]++;}
    else if (*ch_ptr == 'e' && flags[4] == 4)
        {flags[4]++;}
    else if (*ch_ptr == 'd' && flags[4] == 5)
    {
        flags[4]++;
    }
    else if (*ch_ptr == ' ' && flags[4] == 6)
    {
        fputc(*ch_ptr, *output_ptr);
        flags[4] = 0;
    }
    else
    {
        flags[4] = 0;
    }

    if (*ch_ptr == 'c' && flags[5] == 0 && isalpha(prev_ch) == 0)
        {flags[5]++;}
    else if (*ch_ptr == 'o' && flags[5] == 1)
        {flags[5]++;}
    else if (*ch_ptr == 'n' && flags[5] == 2)
        {flags[5]++;}
    else if (*ch_ptr == 's' && flags[5] == 3)
        {flags[5]++;}
    else if (*ch_ptr == 't' && flags[5] == 4)
    {
        flags[5]++;
    }
    else if (*ch_ptr == ' ' && flags[5] == 5)
    {
        fputc(*ch_ptr, *output_ptr);
        flags[5] = 0;
    }
    else
    {
        flags[5] = 0;
    }

    if (*ch_ptr == 'r' && flags[6] == 0 && isalpha(prev_ch) == 0)
        {flags[6]++;}
    else if (*ch_ptr == 'e' && flags[6] == 1)
        {flags[6]++;}
    else if (*ch_ptr == 't' && flags[6] == 2)
        {flags[6]++;}
    else if (*ch_ptr == 'u' && flags[6] == 3)
        {flags[6]++;}
    else if (*ch_ptr == 'r' && flags[6] == 4)
        {flags[6]++;}
    else if (*ch_ptr == 'n' && flags[6] == 5)
    {
        flags[6]++;
    }
    else if (*ch_ptr == ' ' && flags[6] == 6)
    {
        fputc(*ch_ptr, *output_ptr);
        flags[6] = 0;
    }
    else
    {
        flags[6] = 0;
    }

    // if (*ch_ptr == 'F' && flags[7] == 0 && isalpha(prev_ch) == 0)
    //     {flags[7]++;}
    // else if (*ch_ptr == 'I' && flags[7] == 1)
    //     {flags[7]++;}
    // else if (*ch_ptr == 'L' && flags[7] == 2)
    //     {flags[7]++;}
    // else if (*ch_ptr == 'E' && flags[7] == 3)
    // {
    //     putc(*ch_ptr, *output_ptr);
    //     *ch_ptr = getc(*input_ptr);
    //     putc(*ch_ptr, *output_ptr);
    //     flags[7] = 0;
    //     //new_variable(*input_ptr,*output_ptr,ch_ptr);
    // }
    // else
    // {
    //     flags[7] = 0;
    // }

    if (*ch_ptr == 'e' && flags[8] == 0 && isalpha(prev_ch) == 0)
        {flags[8]++;}
    else if (*ch_ptr == 'l' && flags[8] == 1)
        {flags[8]++;}
    else if (*ch_ptr == 's' && flags[8] == 2)
        {flags[8]++;}
    else if (*ch_ptr == 'e' && flags[8] == 3)
    {
        flags[8]++;
    }
    else if (*ch_ptr == ' ' && flags[8] == 4)
    {
        fputc(*ch_ptr, *output_ptr);
        flags[8] = 0;
    }
    else
    {
        flags[8] = 0;
    }

    if (*ch_ptr == 'v' && flags[9] == 0 && isalpha(prev_ch) == 0)
        {flags[9]++;}
    else if (*ch_ptr == 'o' && flags[9] == 1)
        {flags[9]++;}
    else if (*ch_ptr == 'i' && flags[9] == 2)
        {flags[9]++;}
    else if (*ch_ptr == 'd' && flags[9] == 3)
    {
        flags[9]++;
    }
    else if (*ch_ptr == ' ' && flags[9] == 4)
    {
        fputc(*ch_ptr, *output_ptr);
        flags[9] = 0;
        new_variable(*input_ptr,*output_ptr,ch_ptr);
    }
    else
    {
        flags[9] = 0;
    }

    if (*ch_ptr == 'd' && flags[10] == 0 && isalpha(prev_ch) == 0)
        {flags[10]++;}
    else if (*ch_ptr == 'o' && flags[10] == 1)
        {flags[10]++;}
    else if (*ch_ptr == 'u' && flags[10] == 2)
        {flags[10]++;}
    else if (*ch_ptr == 'b' && flags[10] == 3)
        {flags[10]++;}
    else if (*ch_ptr == 'l' && flags[10] == 4)
        {flags[10]++;}
    else if (*ch_ptr == 'e' && flags[10] == 5)
    {
        flags[10]++;
    }
    else if (*ch_ptr == ' ' && flags[10] == 6)
    {
        fputc(*ch_ptr, *output_ptr);
        flags[10] = 0;
    }
    else
    {
        flags[10] = 0;
    }

    if (*ch_ptr == 'f' && flags[11] == 0 && isalpha(prev_ch) == 0)
        {flags[11]++;}
    else if (*ch_ptr == 'l' && flags[11] == 1)
        {flags[11]++;}
    else if (*ch_ptr == 'o' && flags[11] == 2)
        {flags[11]++;}
    else if (*ch_ptr == 'a' && flags[11] == 3)
        {flags[11]++;}
    else if (*ch_ptr == 't' && flags[11] == 4)
        {flags[11]++;}
    else if (*ch_ptr == ' ' && flags[11] == 5)
    {
        fputc(*ch_ptr, *output_ptr);
        flags[11] = 0;
    }
    else
    {
        flags[11] = 0;
    }
}

void space_deletion(FILE* input)
{
    FILE* output;
    output = fopen("temp.wc", "w");

    char flags[100];
    for (int i = 0; i < 100; i++)
    {
        flags[i] = 0;
    }
    int prev_ch = 0;
    char ch;
    char fl;
    while ((ch = getc(input)) != EOF)
    {
        fl = 1;
        
        string_constant_skip(&input,&output,&ch);

        if (ch == '#')
        {
            putc(ch, output);
            while ((ch = getc(input)) != '\n') putc(ch, output);
            putc(ch, output);
        }

        keyword_check(&input, &output, flags, &ch, prev_ch);

        if (ch != '\n' && ch != ' ' && ch != '\t') {putc(ch, output);}
        prev_ch = ch;
    }

    fclose(input);
    fclose(output);
    remove("prog.c");
    rename("temp.wc", "prog.c");
}

void variable_rename(FILE* input)
{
    FILE* output;
    output = fopen("temp.wc", "w");
    char string[20000]; //Memory? didnt heard
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";


    char* ptr;
    while (fgets(string,20000,input))
    {
        for (int i=0;i<variable_number;i++)
        {
            while (ptr = strstr(string, variables[i]))
            {
                int j=0;
                while (variables[i][j] != '\0')
                {
                    *ptr = alphabet[variables[i][j]%26];
                    ptr++;
                    j++;
                }
            }
        }
        fputs(string, output);
    }



    fclose(input);
    fclose(output);
    remove("prog.c");
    rename("temp.wc", "prog.c");
}


void random_func_insert(FILE* input)
{

    int x=0;
    char ch;
    while (x < 5)
    {
        if (x == 0)
            {fputs("void SecretAccess(){int lol=100;while(lol){lol--;}}", input);}
        else if (x == 1)
            {fputs("void generateArray(int* arr, int n) {for (int i = 0; i < n; i++) {arr[i] = 0;}}", input);}
        else if (x == 2)
            {fputs("void copyArray(int* src, int* dest, int n) {for (int i = 0; i < n; i++) {dest[i] = src[i];}}", input);}
        else if (x == 3)
            {fputs("int isSortedArray(int* arr, int n) {for (int i = 0; i < n - 1; i++) {if (arr[i] > arr[i + 1]) {return 0;}}return 1;}", input);}
        else if (x == 4)
            {fputs("void password_func(char*input_password){char password[]=\"polytech > itmo\";int i=0;while(password[i++]!='\\0'){if (password[i]==input_password[i]) printf(\"nice job\");}}", input);}
        x++;
    }

    fclose(input);
}

int main()
{
    srand(time(NULL));
    FILE* input;
    FILE* output;
    input = fopen("prog.c", "r");

    comment_deletion(input);
    input = fopen("prog.c", "r"); //reopen after comment_deletion

    space_deletion(input);
    input = fopen("prog.c", "r"); //reopen after space_deletion

    variable_rename(input);
    input = fopen("prog.c", "a+"); //reopen after variable_rename

    random_func_insert(input);

    // for (int i =0;i<100;i++)
    // {
    //     printf("%s\n", variables[i]);
    // }


    return 0;
}