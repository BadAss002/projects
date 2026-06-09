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
    unsigned char mbc[5]; //char mbs[] = {0xF0, 0xB0, 0x80, 0x90};
    //char32_t unicode_codepoint; //U+xxxx
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
void insert(unsigned char* mbc)
{
    for (int i=0;mbc[i];i++)   
        printf("0x%X\n", mbc[i]);
    printf("\n");
}   


// char32_t mbctocodepoint(unsigned char* mbc, char32_t* ch_ptr)
// {
//     size_t result = 1;
//     mbstate_t state = {0};
//     //printf("%d\n", *s);

//     for (int i=0;i<4;i++)
//     {
//         result = mbrtoc32(ch_ptr,mbc[i],1,&state);
//         if (result == (size_t)-1)
//         {
//             printf("mbrtoc32 error\n");
//             break;
//         }
//         else if (result == (size_t)-2)
//         {
//             continue;
//         }
//         else if (result == (size_t)-3)
//         {
//             printf("surrogate pair?");
//             break;
//         }
//         else if (result > 0)
//         {
            
//         }
//     }
// }

//convert letter after \ to ASCII number
void escape_sequences(int* ch)
{
    if (*ch == '\'') *ch = 0x27;
    else if (*ch == '\"') *ch = 0x22;
    else if (*ch == '\?') *ch = 0x3f;
    else if (*ch == '\\') *ch = 0x5c;
    else if (*ch == 'a') *ch = 0x07;
    else if (*ch == 'b') *ch = 0x08;
    else if (*ch == 'f') *ch = 0x0c;
    else if (*ch == 'n') *ch = 0x0a;
    else if (*ch == 'r') *ch = 0x0d;
    else if (*ch == 't') *ch = 0x09;
    else if (*ch == 'v') *ch = 0x0b;
    else printf("escape sequence error");
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
    unsigned char mbc[5];

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
        //symbol(s) in signle quotes
        else if (letter == '\'')
        {
            for (int i=0;i<5;i++) mbc[i] = 0;
            for (int i=0;i<5;i++)
            {
                letter = fgetc(input);
                if (letter == EOF) break;
                if (letter == '\\')
                {
                    letter = fgetc(input);
                    escape_sequences(&letter);
                }
                else if (letter == '\'')
                {
                    mbc[i] = '\0';
                    break;
                }

                mbc[i] = (unsigned char)letter;                
            }
            if (letter == '\'')
            {
                insert(mbc);
            }
            else
            {
                printf("Symbol in single quotes more than 4 bytes\n");
                while ((letter = fgetc(input)) != '\'');
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

    file_handler("input.c");

    


    return 0;
}