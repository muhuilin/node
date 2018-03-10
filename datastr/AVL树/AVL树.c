/*************************************************************************
	> File Name: AVL树.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年03月09日 星期五 14时13分12秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int key;
    int high;
    struct Node *lchild, *rchild;
}Node;

Node NIL;
#define NIL (&NIL)

int static_init() {
    NIL->lchild = NIL->rchild = NIL;
    NIL->high = 0;
    return 0;
}

int ____temp = static_init();


Node *init(int key) {
    Node* p = (Node *)malloc(sizeof(Node) * 1);
    p->key = key;
    p->high = 1;
    p->lchild = p->rchild = NIL;
    return p;
}
#define max(a, b) ({\
    __typeof(a)  __temp = (a);\
    a = b; b = __temp;\
    __temp;\
})

inline void Up(Node *root) {
    root->high = max(root->lchild->high, root->rchild->high);
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
    if(flag) {
        if(root ->lchild->rchild->high > root->lchild->lchild->high) {
            root->lchild = left_rotate(root->lchild);
        }
        root = right_rotate(root);
    }
    else {
        if(root->rchild->lchild->high > root->rchild->rchild->high) {
            root->lchild = right_rotate(root->lchild);
        }
        root = left_rotate(root);
    }
}

Node *maintain (Node *root) {
    if (abs(root->lchild->high - root->rchild->high)) return root;
    root = __maintain(root, root->lchild->high > root->rchild->high);
}

Node *insert(Node *root, int key) {
    if(root == NIL) return init(key);
    if(key == root->key) return root;
    if(key < root->key) {
        root->lchild = insert(root->lchild, key);
    }
    else {
        root->rchild = insert(root->rchild, key);
    }
    Up(root);
    root = maintain(root);
    return root;
}


void clear(Node *tree) {
    if(tree == NIL) return ;
    clear(tree->lchild);
    clear(tree->rchild);
    free(tree);
    return ;
}


void pre_order(Node *root) {
    if(root == NIL) return ;
    printf("%d (%d,%d)", root->key, root->lchild->key, root->rchild);
    pre_order(root->lchild);
    pre_order(root->rchild);
    return ;
}

int main() {
    int n, a;
    Node *root = NIL;
}
