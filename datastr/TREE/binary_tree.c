/*************************************************************************
	> File Name: binary_tree.c
	> Author:  muhuilin 
	> Mail: muhuilin@outlook.com
	> Created Time: 2018年01月18日 星期四 18时45分54秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>


typedef struct Node {
    int data;
    struct Node *lchild, *rchild;
}Node, *Tree;

Node *init(int val) {
    Node *p = (Node *)malloc(sizeof(Node) * 1);
    p->data = val;
    p->rchild = NULL;
    p->lchild = NULL;
    return p;
}

int pre_order(Tree tree) {
    if(tree == NULL) return 1;
    printf("%d ", tree->data);
    tree->lchild && pre_order(tree->lchild);
    tree->rchild && pre_order(tree->rchild);
    return 1;
}
int in_order(Tree tree) {
    if(tree == NULL) return 1;
    tree->lchild && in_order(tree->lchild);
    printf("%d ", tree->data);
    tree->rchild && in_order(tree->rchild);
    return 1;
}
int post_order(Tree tree) {
    if(tree == NULL) return 1;
    tree->lchild && post_order(tree->lchild);
    tree->rchild && post_order(tree->rchild);
    printf("%d ", tree->data);
    return 1;
}


void clear(Tree tree) {
    clear(tree->lchild);
    clear(tree->rchild);
    free(tree);
    return ;
}

int main()
{
    Tree tree = init(7);
    tree->lchild = init(5);
    tree->rchild = init(10);
    tree->lchild->lchild = init(3);
    tree->lchild->rchild = init(6);
    tree->rchild->lchild = init(9);
    tree->rchild->rchild = init(13);
    pre_order(tree), printf("\n");
    in_order(tree), printf("\n");
    in_order(tree), printf("\n");
}
