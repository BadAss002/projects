#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <uchar.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdint.h>

#define MAX_STRING_LEN 100
#define STRINGS_START_SIZE 20

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
    unsigned char mbc[5];
    char ** strings;
    unsigned int count;
    unsigned key;
    struct node* parent;
    struct node* left;
    struct node* right;
};


//condition for func: child != NULL && parent != NULL
void rotate(struct node* child, struct node* parent)
{
    struct node* gparent = parent->parent;

    if (gparent != NULL)
    {
        if (gparent->left == parent)
        {
            gparent->left = child;
            child->parent = gparent;
        }
        else
        {
            gparent->right = child;
            child->parent = gparent;
        }
    }
    else
        child->parent = gparent;


    if (parent->left == child)
    {
        parent->left = child->right;
        if (child->right != NULL)
            child->right->parent = parent;
        
        child->right = parent;
        parent->parent = child;
    }
    else
    {
        parent->right = child->left;
        if (child->left != NULL)
            child->left->parent = parent;
        
        child->left = parent;
        parent->parent = child;
    }
}


struct node* splay(struct node* x)
{
    if (x->parent == NULL)
        return x;
    
    struct node* parent = x->parent;
    struct node* gparent = parent->parent;

    //rotate
    if (gparent == NULL)
    { 
        rotate(x,parent);
        return x;
    }
    else
    {
        //zig-zig
        if ((gparent->left==parent && parent->left==x) || (gparent->right==parent && parent->right==x))
        {
            rotate(parent,gparent);
            rotate(x,parent);
        }
        //zig-zag
        else
        {
            rotate(x,parent);
            rotate(x,gparent);
        }
    }

    return splay(x);
}


//поиск
struct node* search(struct node* x, int key, char * string)
{
    if (x == NULL)
        return NULL;
    
    if (x->key == key)
    {
        x->count++;
        strcpy(x->strings[x->count-1], string);
        return splay(x);
    }

    if (key < x->key && x->left != NULL)
        return search(x->left, key, string);
    if (key > x->key && x->right != NULL)
        return search(x->right, key, string);

    return splay(x);
}


//subtrees[] = {left subtree, right subtree}
struct node* split(struct node** subtrees,struct node* root, int key, char * string)
{
    if (root == NULL)
    {
        subtrees[0] = NULL;
        subtrees[1] = NULL;
        return NULL;
    }

    root = search(root, key, string);

    if (root->key == key)
    {
        subtrees[0] = root->left;
        subtrees[1] = root->right;
        return root;
    }
    if (key < root->key)
    {
        subtrees[0] = root->left;
        subtrees[1] = root;
        if (root->left != NULL)
            root->left->parent = NULL;
        root->left = NULL;
        return root;
    }
    if (key > root->key)
    {
        subtrees[0] = root;
        subtrees[1] = root->right;
        if (root->right != NULL)
            root->right->parent = NULL;
        root->right = NULL;
        return root;
    }
    
    return NULL;
}


//вставка
struct node* insert(unsigned char* mbc, struct node* root, unsigned mbc_length, char * string)
{

    //reverse little endian to big endian
    unsigned int key = 0;
    for (int i=0;i<mbc_length;i++)
    {
        key = key << 8;
        key = key | mbc[i];
    }


    struct node* subtrees[2] = {NULL, NULL};
    root = split(subtrees,root,key, string);

    //if count++
    if (root != NULL)
        if (root->left == subtrees[0] && root->right == subtrees[1])
            return root;

    
    //making new root
    root = (struct node*)calloc(1,sizeof(struct node));
    root->strings = calloc(STRINGS_START_SIZE, sizeof(char*));
    for (int i=0;i<STRINGS_START_SIZE; i++)
        root->strings[i] = malloc(sizeof(char)*MAX_STRING_LEN);
    root->count = 1;
    root->key = key;
    for (int i=0;i<mbc_length;i++)
        root->mbc[i] = mbc[i];
    strcpy(root->strings[root->count-1], string);

    root->left = subtrees[0];
    if (subtrees[0] != NULL)
        subtrees[0]->parent = root;

    root->right = subtrees[1];
    if (subtrees[1] != NULL)
        subtrees[1]->parent = root;


    return root;
}   


void print_tree(struct node* x, int height)
{
    printf("height:%d\tchar:", height);
    for (int i=0; i<x->count;i++)
        printf("\'%s\' ", x->strings[i]);
    printf("\nkey=%u\t\tcount:%d\n\n", x->key, x->count);

    if (x->left != NULL)
        print_tree(x->left, height+1);
    if (x->right != NULL)
        print_tree(x->right, height+1);
}


//convert letter after \ to ASCII number
_Bool BaseEscapeSequences(int * letter_ptr)
{
    if (*letter_ptr == '\''){ *letter_ptr = 0x27; return 1; }
    else if (*letter_ptr == '\"'){ *letter_ptr = 0x22; return 1; }
    else if (*letter_ptr == '\?'){ *letter_ptr = 0x3f; return 1; }
    else if (*letter_ptr == '\\'){ *letter_ptr = 0x5c; return 1; }
    else if (*letter_ptr == 'a'){ *letter_ptr = 0x07; return 1; }
    else if (*letter_ptr == 'b'){ *letter_ptr = 0x08; return 1; }
    else if (*letter_ptr == 'f'){ *letter_ptr = 0x0c; return 1; }
    else if (*letter_ptr == 'n'){ *letter_ptr = 0x0a; return 1; }
    else if (*letter_ptr == 'r'){ *letter_ptr = 0x0d; return 1; }
    else if (*letter_ptr == 't'){ *letter_ptr = 0x09; return 1; }
    else if (*letter_ptr == 'v'){ *letter_ptr = 0x0b; return 1; }
    else
        return 0;
}



void AvoidStringConstant(FILE * input)
{
    int letter;
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



_Bool ProcessEscapeSequence(FILE * input, int * letter_ptr, char * string, unsigned * string_len_ptr)
{

    if (BaseEscapeSequences(letter_ptr))
        return 1;

    
    //octal and hex ES
    char * all_octal_numbers = "01234567";
    char octal_number[4];
    char * all_hex_numbers = "0123456789abcdefABCDEF";
    char hex_number[3];

    if (strchr(all_octal_numbers, *letter_ptr))
    {
        int i = 0;
        while (i < 3)
        {
            octal_number[i++] = *letter_ptr;

            *letter_ptr = fgetc(input);
            string[(*string_len_ptr)++] = *letter_ptr;

            if (!strchr(all_octal_numbers, *letter_ptr) || i == 3)
            {
                ungetc(*letter_ptr, input);
                string[(*string_len_ptr)--] = '\0';
                break;
            }
        }

        octal_number[i] = '\0';

        *letter_ptr = (int)strtol(octal_number, NULL, 8);

        if (i <= 0) return 0;
    }
    else if (*letter_ptr == 'x')
    {
        int j = 0;
        //*letter_ptr =...
        while (j < 2)
        {
            *letter_ptr = fgetc(input);
            string[(*string_len_ptr)++] = *letter_ptr;

            hex_number[j++] = *letter_ptr;

            if (!strchr(all_hex_numbers, *letter_ptr))
            {
                ungetc(*letter_ptr, input);
                string[(*string_len_ptr)--] = '\0';
                j--;
                break;
            }
        }

        hex_number[j] = '\0';

        *letter_ptr = (int)strtol(hex_number, NULL, 16);

        if (j <= 0) return 0;
    }
    else
        return 0;


    return 1;
}



_Bool GetMBC(
    FILE * input, 
    unsigned char * mbc, 
    unsigned * mbc_length_ptr, 
    char * string, 
    unsigned * string_len_ptr, 
    int * letter_ptr)
{
    int fl_slpicing_lines = 0;

    while ((*letter_ptr = fgetc(input)) != EOF)
    {
        fl_slpicing_lines = 0;

        if (*letter_ptr == '\'')
            break;

        if (*letter_ptr == '\n')
            return 0;

        string[(*string_len_ptr)++] = *letter_ptr;

        if (*letter_ptr == '\\')
        {
            *letter_ptr = fgetc(input);
            string[(*string_len_ptr)++] = *letter_ptr;

            if (*letter_ptr == '\n')
            {
                fl_slpicing_lines = 1;
            }
            else if (ProcessEscapeSequence(input, letter_ptr, string, string_len_ptr) == 0)
            {   
                return 0;
            }
        }


        if (fl_slpicing_lines == 0)
        {
            if (*mbc_length_ptr == 4)
                return 0;
            else
                mbc[(*mbc_length_ptr)++] = *letter_ptr;
        }
    }

    string[*string_len_ptr] = '\0';

    if (*mbc_length_ptr > 0)
        return 1;
    else
        return 0;
}


struct node* GetCharacterConstants(char* filename, struct node* root)
{
    FILE* input;
    input = fopen("input.c", "r");
    
    //delete comments
    if (comment_deletion(input) != 0) printf("comment_deletion_error\n");

    //reopen file without comments
    input = fopen("temp.c", "r");
    
    int letter;
    unsigned integer_character_constant_max_size = sizeof(int);
    unsigned char * mbc = malloc(sizeof(unsigned char)*integer_character_constant_max_size);
    char string[MAX_STRING_LEN];
    unsigned string_len = 0;
    unsigned mbc_length = 0;

    while ((letter = fgetc(input)) != EOF)
    {
        if (letter == '"') 
        { 
            AvoidStringConstant(input);
        }
        else if (letter == '\'')
        {
            memset(mbc, 0, sizeof(unsigned char)*integer_character_constant_max_size);
            mbc_length = 0;
            memset(string, 0, sizeof(char)*MAX_STRING_LEN);
            string_len = 0;

            if (GetMBC(input, mbc, &mbc_length, string, &string_len, &letter) == 0)
            {
                printf("Character constant error\n");
                while (letter != '\'' && letter != '\n' && letter != EOF) letter = fgetc(input);
            }
            else if (letter == '\'')
                root = insert(mbc, root, mbc_length, string);
        }
    }

    fclose(input);
    return root;
}


int main(void)
{
    setlocale(LC_ALL, "");

    struct node* root = NULL;

    char filename[] = "input.c";

    root = GetCharacterConstants(filename,root);

    // unsigned char mbc[] = "а";
    // root = insert(mbc, root, 2);

    if (root == NULL)
        printf("The tree is empty\n");
    else
        print_tree(root,0);


    return 0;
}