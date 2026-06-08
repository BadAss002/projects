#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <uchar.h>


int comment_deletion(FILE* f1) {

    FILE* f2 = fopen("temp.c", "w");

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

    return 0;
}


//узел
struct node {
    unsigned char mbs[5]; //char mbs[] = {0xF0, 0xB0, 0x80, 0x90};
    char32_t unicode_codepoint; //U+xxxx
    int count;
    struct node* parent;
    struct node* left;
    struct node* right;
};

void splay()
{

}


//поиск
void search()
{

}

//вставка
void insert(unsigned char* mbs, char32_t unicode_codepoint)
{
    for (int i=0;i<4;i++)
        printf("%x\n", mbs[i]);
    printf("U+%04X\n", unicode_codepoint);    
}


void file_handler(char* filename)
{
    FILE* input;
    input = fopen(filename, "r");
    //delete comments
    if (comment_deletion(input) != 0) printf("comment_deletion_error");
    //reopen file without comments
    input = fopen("temp.c", "r");
    
    int letter;
    unsigned char value[5];
    const char* ptr = (const char*)value;
    char32_t ch = 0xFFFFFFFF;
    size_t result = 1;
    mbstate_t state = {0};

    while ((letter = fgetc(input)) != EOF)
    {
        //avoid string constants
        if (letter == '"') { 
            while ((letter = fgetc(input)) != EOF) {
                if (letter == '"') {break;}
                if (letter == '\\') {
                    int temp = fgetc(input);
                }
                else if (letter == '\n') {
                    break;
                }
            }
        }
        //main block
        else if (letter == '\'')
        {
            for (int i=0;i<4;i++)
            {
                letter = fgetc(input);
                if (letter == '\\')
                {
                    letter = fgetc(input);
                }
                else if (letter == EOF)
                {
                    break;
                }

                const unsigned char* s = (const unsigned char*)&letter;
                printf("%d\n", *s);
                result = mbrtoc32(&ch,s,1,&state);

                if (result == (size_t)-1)
                {
                    printf("mbrtoc32 error\n");
                    break;
                }
                else if (result == (size_t)-2)
                {
                    value[i] = (unsigned char)letter;
                }
                else if (result == (size_t)-3)
                {
                    printf("surrogate pair?");
                    break;
                }
                else if (result > 0)
                {
                    value[i] = (unsigned char)letter;
                    value[i+1] = '\0';
                    insert(value, ch);
                }
            }
        }
        //printf("%x\n", (unsigned char)letter);
    }
    // value[i] = '\0';
    // mbstate_t state = {0};
    // size_t res = mbrtoc32(&ch, ptr, 4, &state);

    //printf("U+%04X", ch);
}


int main(void)
{
    setlocale(LC_ALL, ".UTF-8");

    file_handler("test.txt");

    


    return 0;
}