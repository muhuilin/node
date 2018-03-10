/*************************************************************************
   > File Name: 18.AVL.cpp
   > Author: hug
   > Mail:   hug@haizeix.com
   > Created Time: 五  3/ 9 14:06:06 2018
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define max(a, b) ({ \
    __typeof(a) tempa = (a), tempb = (b); \
    tempa > tempb ? tempa : tempb; \
})

typedef struct Node {
    int key, height;
    struct Node *lchild, *rchild;
} Node;

Node __NIL;
#define NIL (&__NIL)

int static_init() {
    NIL->lchild = NIL->rchild = NIL;
    NIL->height = 0;
    return 0;
}

int _______temp = static_init();

Node *init(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->lchild = p->rchild = NIL;
    p->height = 1;
    return p;
}

inline void Up(Node *root) {
    root->height = max(root->lchild->height, root->rchild->height) + 1;
}

Node *left_rotate(Node *root) {
    Node *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    Up(root);
    Up(temp);
    return temp;
}

Node *right_rotate(Node *root) {
    Node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    Up(root);
    Up(temp);
    return temp;
}

Node *__maintain(Node *root, int flag) {
    if (flag) {
        if (root->lchild->rchild->height > root->lchild->lchild->height) {
            root->lchild = left_rotate(root->lchild);
        }
        root = right_rotate(root); 
    } else {
        if (root->rchild->lchild->height > root->rchild->rchild->height) {
            root->rchild = right_rotate(root->rchild);
        }
        root = left_rotate(root);
    }
    return root;
}

Node *maintain(Node *root) {
    if (abs(root->lchild->height - root->rchild->height) < 2) return root;
    root = __maintain(root, root->lchild->height > root->rchild->height);
    return root;
}

Node *insert(Node *root, int key) {
    if (root == NIL) {
        return init(key);
    }
    if (key == root->key) return root;
    if (key < root->key) {
        root->lchild = insert(root->lchild, key);
    } else {
        root->rchild = insert(root->rchild, key);
    }
    Up(root);
    root = maintain(root);
    return root;
}

Node *predecessor(Node *tree) {
    
}

Node *delete_node(Node *root, int key) {
    if(root == NIL) return NIL;
    if(key == root->key) {
        if(root->lchild == NIL && root->rchild == NIL) {
            free(root);
            return NIL;
        }
        else if(root->lchild != NIL && root->rchild != NIL) {
            
        }
        else if(root->lchild != NIL) {
            
        }
        else {

        }
        
    }
    
}

void clear(Node *node) {
    if (node == NIL) return ;
    clear(node->lchild);
    clear(node->rchild);
    free(node);
    return ;
}

void pre_order(Node *root) {
    if (root == NIL) return ;
    printf("%d (%d, %d)\n", root->key, root->lchild->key, root->rchild->key);
    pre_order(root->lchild);
    pre_order(root->rchild);
    return ;
}

int main() {
    int n, a;
    Node *root = NIL;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        root = insert(root, a);
        printf("Tree info : \n");
        pre_order(root);
        printf("---------------\n");
    }
    clear(root);
    return 0;
}
