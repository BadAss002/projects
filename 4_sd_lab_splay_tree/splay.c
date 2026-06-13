#include <stdio.h>
#include <stdlib.h>
#include <uchar.h>

//узел
struct node {
    unsigned char mbc[5]; //char mbs[] = {0xF0, 0xB0, 0x80, 0x90};
    //char32_t unicode_codepoint; //U+xxxx
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
        return splay(x);
    }

    if (key < x->key && x->left != NULL)
        return search(x->left, key);
    if (key > x->key && x->right != NULL)
        return search(x->right, key);

    return splay(x);
}


//subtrees[] = {left subtree, right subtree}
void split(struct node** subtrees,struct node* root, uint32_t key)
{
    if (root == NULL || root->key == 0)
    {
        subtrees[0] = NULL;
        subtrees[1] = NULL;
        return;
    }

    root = search(root, key);

    if (root->key == key)
    {
        subtrees[0] = root->left;
        subtrees[1] = root->right;
        return;
    }
    if (key < root->key)
    {
        subtrees[0] = root->left;
        subtrees[1] = root;
        if (root->left != NULL)
            root->left->parent = NULL;
        root->left = NULL;
        return;
    }
    if (key > root->key)
    {
        subtrees[0] = root;
        subtrees[1] = root->right;
        if (root->right != NULL)
            root->right->parent = NULL;
        root->right = NULL;
        return;
    }
}


//вставка
struct node* insert(unsigned char* mbc, struct node* root)
{
    uint32_t key;
    memcpy(&key,mbc,4);
    // for (int i=0;i<4;i++)
    // {
    //     printf("%x ", mbc[i]);
    // }
    // printf("\t");
    // printf("%lu", key);
    // printf("\n");
    struct node* subtrees[2] = {NULL, NULL};
    split(subtrees,root,key);

    if (root != NULL && root->count != 0)
        if (root->left == subtrees[0] && root->right == subtrees[1])
            return root;

    root = (struct node*)calloc(1,sizeof(struct node));
    root->parent = NULL;
    root->count = 1;
    root->key = key;
    for (int i=0;mbc[i];i++)
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
    printf("height:%d\tparent:0x%p\tptr:0x%p\tcount:%d\tchar:\'%s\'\tkey=%u\n\t\t\tleft:0x%p\t\tright:0x%p\n\n", height,x->parent,x, x->count,x->mbc,x->key, x->left, x->right);
    if (x->left != NULL)
        print_tree(x->left, height+1);
    if (x->right != NULL)
        print_tree(x->right, height+1);
}


int main(void)
{
    unsigned char mbc[] = {'a','b','c','d',0x00};//{0xF0, 0xB0, 0x80, 0x90, 0x00};
    struct node* root = NULL;

    root = insert(mbc, root);
    print_tree(root,0);


    return 0;
}