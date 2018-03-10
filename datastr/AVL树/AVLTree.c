/*************************************************************************
	> File Name: AVLTree.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年03月02日 星期五 17时21分20秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct AVLTreeNode {
    int key;
    int highl,highr;
    int high;
    struct AVLTreeNode *lchild, *rchild;
}AVLTreeNode;

AVLTreeNode *getnewnode(int key) {
    AVLTreeNode *p = (AVLTreeNode *)malloc(sizeof(AVLTreeNode) * 1);
    p->key = key;
    p->highl =  p->highr = p->high = 0;
    p->lchild = p->rchild = NULL;
    return p;
}
#define rotate(a,b,c,d,e) __rotate(&a, &b, &c, &d, &e)
#define max(a, b) ((a > b ? a : b))
AVLTreeNode * __rotate(AVLTreeNode **k1, AVLTreeNode **k2, AVLTreeNode **k3, AVLTreeNode **k4, AVLTreeNode **k5) {

    *k1 = *k2;
    *k3 = *k4;
    return *k5;
}

int updata(AVLTreeNode *tree) {
    if(tree == NULL) return 0;
    return tree->high;
}

void gethigh(AVLTreeNode *tree) {
    tree->highl = updata(tree->lchild);
    tree->highr = updata(tree->rchild);
    tree->high = max(updata(tree->lchild), updata(tree->rchild)) + 1;
    return ;
}

AVLTreeNode *changebalance(AVLTreeNode *tree) {
    if(abs(tree->highl - tree->highr) <= 1) return tree;
    if(tree->highl > tree->highr) {
        AVLTreeNode *p = tree->lchild;
        if(p->highl > p->highr) {
            tree->lchild = p->rchild;
            p->rchild = tree;
            gethigh(tree);
            gethigh(p);
            return p;
        }
        else {
            AVLTreeNode *q = p->rchild;
            p->rchild = q->lchild;
            q->lchild = p;
            tree->lchild = q;
            gethigh(p);
            gethigh(q);
            tree->lchild = q->rchild;
            q->rchild = tree;
            gethigh(tree);
            gethigh(q);
            return q;
        }
    }
    else {
        AVLTreeNode *p = tree->rchild;
        if(p->highl > p->highr) {
            AVLTreeNode *q = p->lchild;
            p->lchild = q->rchild;
            q->rchild = p;
            tree->rchild = q->lchild;
            q->lchild = tree;
            gethigh(p);
            gethigh(tree);
            gethigh(q);
            return q;
        }
        else {
            tree->rchild = p->lchild;
            p->lchild = tree;
            gethigh(tree);
            gethigh(p);
            return p;
        }
    }
}

AVLTreeNode *Delete(AVLTreeNode *tree, int key){
    if(tree == NULL) return NULL;
    if(tree->key == key) {
        AVLTreeNode *l = tree->lchild;
        AVLTreeNode *r = tree->rchild;
        if(l == NULL && r == NULL){
            free(tree);
            return NULL;
        } 
        else if(l == NULL) {
            AVLTreeNode *p = tree->rchild;
            free(tree);
            return p;
        } 
        else if(r == NULL) {
            AVLTreeNode *p = tree->lchild;
            free(tree);
            return p;
        }
        else {
            
        }
    }
    if(key < tree->key) {
        tree->lchild = Delete(tree->lchild, key);
    }
    else {
        tree->rchild = Delete(tree->rchild, key);
    }
    gethigh(tree);
    return changebalance(tree);
}
AVLTreeNode *insert(AVLTreeNode *tree, int key) {
    if(tree == NULL) {
        AVLTreeNode *ret = getnewnode(key);
        gethigh(ret);
        return ret;
    }
    if(key == tree->key) return tree;
    if(key < tree->key) {
        tree->lchild = insert(tree->lchild, key);
    }
    else {
        tree->rchild = insert(tree->rchild, key);
    }
    gethigh(tree);
    return changebalance(tree);
}

void pre_order(AVLTreeNode *tree) {
    if(tree == NULL) return;
    pre_order(tree->lchild);
    printf("%d ",tree->key);
    pre_order(tree->rchild);
    return ;
}

int main()
{
    srand(time(0));
    AVLTreeNode *tree = NULL;
    for(int i = 0 ;i < 10 ; i++) {
        tree = insert(tree, rand() % 100);
        
        pre_order(tree);
        printf("\n");
    }
}
