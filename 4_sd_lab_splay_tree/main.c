#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <uchar.h>
#include <stdlib.h>
#include <string.h>


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
    int count;
    uint32_t key; //inverted mbc cauase of little endian
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
struct node* search(struct node* x, uint32_t key)
{
    if (x == NULL)
        return NULL;
    
    if (x->key == key)
    {
        x->count++;
        //printf("wallahi = %d %p\n", x->count, x);
        return splay(x);
    }

    if (key < x->key && x->left != NULL)
        return search(x->left, key);
    if (key > x->key && x->right != NULL)
        return search(x->right, key);

    return splay(x);
}


//subtrees[] = {left subtree, right subtree}
struct node* split(struct node** subtrees,struct node* root, uint32_t key)
{
    if (root == NULL)
    {
        subtrees[0] = NULL;
        subtrees[1] = NULL;
        return NULL;
    }

    root = search(root, key);

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
struct node* insert(unsigned char* mbc, struct node* root, unsigned mbc_length)
{
    // uint32_t key = 0;
    // memcpy(&key,mbc,mbc_length);
    // printf("%d\n", mbc_length);

    //reverse little endian to big endian
    uint32_t key = 0;
    for (int i=0;i<mbc_length;i++)
    {
        key = key << 8;
        key = key | mbc[i];
    }
    // for (int i=0;i<32;i++)
    // {
    //     if (key & 2147483648)
    //         printf("1");
    //     else
    //         printf("0");
    //     key = key << 1;
    // }
    // printf("\n");

    struct node* subtrees[2] = {NULL, NULL};
    root = split(subtrees,root,key);

    //if count++
    if (root != NULL)
        if (root->left == subtrees[0] && root->right == subtrees[1])
            return root;

    root = (struct node*)calloc(1,sizeof(struct node));
    root->count = 1;
    root->key = key;
    for (int i=0;i<mbc_length;i++)
        root->mbc[i] = mbc[i];

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
    printf("height:%d\tparent:\'%s\'\tchar:\'%s\'\tkey=%u\tcount:%d\n\t\tleft:\'%s\'\tright:\'%s\'\n\n", height,x->parent->mbc,x->mbc,x->key,x->count, x->left->mbc, x->right->mbc);
    if (x->left != NULL)
        print_tree(x->left, height+1);
    if (x->right != NULL)
        print_tree(x->right, height+1);
}


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
    else if (*ch == '0') *ch = 0x0;
    else printf("escape sequence error");
}

struct node* file_handler(char* filename, struct node* root)
{
    FILE* input;
    input = fopen(filename, "r");
    
    //delete comments
    if (comment_deletion(input) != 0) printf("comment_deletion_error");

    //reopen file without comments
    input = fopen("temp.c", "r");
    
    int letter;
    unsigned char mbc[5];
    unsigned mbc_length = 0;

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
                    if (letter == '\n')
                    {
                        i--;
                        continue;
                    }
                    else
                        escape_sequences(&letter);
                }
                else if (letter == '\'')
                {
                    mbc[i] = '\0';
                    mbc_length = i;
                    break;
                }

                mbc[i] = (unsigned char)letter;   
                mbc_length = i;             
            }

            if (letter == '\'')
            {
                if (mbc_length == 0)
                    printf("Single quotes must contain at least 1 character\n");
                else
                {
                    root = insert(mbc, root, mbc_length);
                }
            }
            else
            {
                printf("Symbol in single quotes more than 4 bytes\n");
                while ((letter = fgetc(input)) != '\'');
            }

            mbc_length = 0;
        }
    }

    return root;
}


int main(void)
{
    setlocale(LC_ALL, "");

    struct node* root = NULL;

    char filename[] = "input2.c";

    root = file_handler(filename,root);

    if (root == NULL)
        printf("The tree is empty\n");
    else
        print_tree(root,0);


    return 0;
}