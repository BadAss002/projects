#include <stdio.h>
#include <ctype.h>

int comment_deletion(FILE* f1) {
    FILE* f2 = fopen("temp.wc", "w");
    if (f1 == NULL || f2 == NULL) {
        if (f1) fclose(f1);
        return 1;
    
    }
    int c, next;
    while ((c = fgetc(f1)) != EOF) {
        if (c == '"') {
            fputc(c, f2);
            while ((c = fgetc(f1)) != EOF) {
                fputc(c, f2);
                if (c == '"') break;
                if (c == '\\') {
                    int temp = fgetc(f1);
                    if (temp != EOF) fputc(temp, f2);
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
                if (c == '\'') break;
                if (c == '\\') {
                    int temp = fgetc(f1);
                    if (temp != EOF) fputc(temp, f2);
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

int keyword_check(FILE** input_ptr, FILE**output_ptr, char* flags, char* ch_ptr, int prev_ch)
{
    if (*ch_ptr == 'c' && flags[0] == 0 && isalpha(prev_ch) == 0)
            flags[0]++;
        else if (*ch_ptr == 'h' && flags[0] == 1)
            flags[0]++;
        else if (*ch_ptr == 'a' && flags[0] == 2)
            flags[0]++;
        else if (*ch_ptr == 'r' && flags[0] == 3)
        {
            putc(*ch_ptr,*output_ptr);
            *ch_ptr = getc(*input_ptr);
            putc(*ch_ptr,*output_ptr);
            flags[0] = 0;
        }
        else
        {
            flags[0] = 0;
        }
    
    if (*ch_ptr == 'i' && flags[1] == 0 && isalpha(prev_ch) == 0)
            flags[1]++;
        else if (*ch_ptr == 'n' && flags[1] == 1)
            flags[1]++;
        else if (*ch_ptr == 't' && flags[1] == 2)
        {
            putc(*ch_ptr,*output_ptr);
            *ch_ptr = getc(*input_ptr);
            putc(*ch_ptr,*output_ptr);
            flags[1] = 0;
        }
        else
        {
            flags[1] = 0;
        }

    if (*ch_ptr == 'l' && flags[2] == 0 && isalpha(prev_ch) == 0)
            flags[2]++;
        else if (*ch_ptr == 'o' && flags[2] == 1)
            flags[2]++;
        else if (*ch_ptr == 'n' && flags[2] == 2)
            flags[2]++;
        else if (*ch_ptr == 'g' && flags[2] == 3)
        {
            putc(*ch_ptr,*output_ptr);
            *ch_ptr = getc(*input_ptr);
            putc(*ch_ptr,*output_ptr);
            flags[2] = 0;
        }
        else
        {
            flags[2] = 0;
        }
    
    if (*ch_ptr == 'u' && flags[3] == 0 && isalpha(prev_ch) == 0)
            flags[3]++;
        else if (*ch_ptr == 'n' && flags[3] == 1)
            flags[3]++;
        else if (*ch_ptr == 's' && flags[3] == 2)
            flags[3]++;
        else if (*ch_ptr == 'i' && flags[3] == 3)
            flags[3]++;
        else if (*ch_ptr == 'g' && flags[3] == 4)
            flags[3]++;
        else if (*ch_ptr == 'n' && flags[3] == 5)
            flags[3]++;
        else if (*ch_ptr == 'e' && flags[3] == 6)
            flags[3]++;
        else if (*ch_ptr == 'd' && flags[3] == 7)
        {
            putc(*ch_ptr,*output_ptr);
            *ch_ptr = getc(*input_ptr);
            putc(*ch_ptr,*output_ptr);
            flags[3] = 0;
        }
        else
        {
            flags[3] = 0;
        }

        if (*ch_ptr == 's' && flags[4] == 0 && isalpha(prev_ch) == 0)
            flags[4]++;
        else if (*ch_ptr == 'i' && flags[4] == 1)
            flags[4]++;
        else if (*ch_ptr == 'g' && flags[4] == 2)
            flags[4]++;
        else if (*ch_ptr == 'n' && flags[4] == 3)
            flags[4]++;
        else if (*ch_ptr == 'e' && flags[4] == 4)
            flags[4]++;
        else if (*ch_ptr == 'd' && flags[4] == 5)
        {
            putc(*ch_ptr,*output_ptr);
            *ch_ptr = getc(*input_ptr);
            putc(*ch_ptr,*output_ptr);
            flags[4] = 0;
        }
        else
        {
            flags[4] = 0;
        }

        if (*ch_ptr == 'c' && flags[5] == 0 && isalpha(prev_ch) == 0)
            flags[5]++;
        else if (*ch_ptr == 'o' && flags[5] == 1)
            flags[5]++;
        else if (*ch_ptr == 'n' && flags[5] == 2)
            flags[5]++;
        else if (*ch_ptr == 's' && flags[5] == 3)
            flags[5]++;
        else if (*ch_ptr == 't' && flags[5] == 4)
        {
            putc(*ch_ptr,*output_ptr);
            *ch_ptr = getc(*input_ptr);
            putc(*ch_ptr,*output_ptr);
            flags[5] = 0;
        }
        else
        {
            flags[5] = 0;
        }

        if (*ch_ptr == 'r' && flags[6] == 0 && isalpha(prev_ch) == 0)
            flags[6]++;
        else if (*ch_ptr == 'e' && flags[6] == 1)
            flags[6]++;
        else if (*ch_ptr == 't' && flags[6] == 2)
            flags[6]++;
        else if (*ch_ptr == 'u' && flags[6] == 3)
            flags[6]++;
        else if (*ch_ptr == 'r' && flags[6] == 4)
            flags[6]++;
        else if (*ch_ptr == 'n' && flags[6] == 5)
        {
            putc(*ch_ptr,*output_ptr);
            *ch_ptr = getc(*input_ptr);
            putc(*ch_ptr,*output_ptr);
            flags[6] = 0;
        }
        else
        {
            flags[6] = 0;
        }
}

void space_deletion(FILE* input)
{
    FILE* output;
    output = fopen("temp.wc", "w");

    char flags[10];
    for (int i=0;i<10;i++)
    {
        flags[i] = 0;
    }
    int prev_ch = 0;
    char ch;
    char fl;
    while ((ch = getc(input)) != EOF)
    {
        fl = 1;
        if (ch == '"')
        {
            putc(ch,output);
            while ((ch = getc(input)) != '"') putc(ch,output);
        }
        else if (ch == '\'')
        {
            putc(ch,output);
            while ((ch = getc(input)) != '\'') putc(ch,output);
        }
        else if (ch == '#')
        {
            putc(ch,output);
            while ((ch = getc(input)) != '\n') putc(ch,output);
            putc(ch,output);
        }

        keyword_check(&input, &output, flags, &ch, prev_ch);

        if (ch != '\n' && ch != ' ') putc(ch,output);
        prev_ch = (int)ch;
    }

    fclose(input);
    fclose(output);
    remove("prog.c");
    rename("temp.wc", "prog.c");
}

int main(void)
{
    FILE* input;
    FILE* output;
    input=fopen("prog.c","r");

    comment_deletion(input);
    input = fopen("prog.c", "r"); //reopen after comment_deletion

    space_deletion(input);


    return 0;
}