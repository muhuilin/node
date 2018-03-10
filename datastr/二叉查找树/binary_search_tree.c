/*************************************************************************
	> File Name: binary_search_tree.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年03月02日 星期五 11时43分49秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BSTNode {
    int key;
    struct BSTNode *lchild, *rchild;
}BSTNode;

BSTNode *getNewNode(int key) {
    BSTNode *p = (BSTNode *)malloc(sizeof(BSTNode) * 1);
    p->lchild = p->rchild = NULL;
    p->key = key;
    return p;
}

BSTNode *insert(BSTNode *tree, int key) {
    if (tree == NULL) return getNewNode(key);
    if(tree->key == key) return tree;
    if (key < tree->key) tree->lchild = insert(tree->lchild, key);
    else tree->rchild = insert(tree->rchild, key);
    return tree;
}

BSTNode *predecessor(BSTNode *tree) {
    BSTNode *temp = tree->lchild;
    while(temp->rchild) {
        temp = temp->rchild;
    }
    return temp;
}

BSTNode *delete_node(BSTNode *tree, int key) {
    if (tree == NULL) return NULL;
    if (key < tree->key) {
        tree->lchild = delete_node(tree->lchild, key);
    }
    else if(key > tree->key){
        tree->rchild = delete_node(tree->rchild, key);
    } else {
        if(tree->lchild == NULL && tree->rchild == NULL) {
            free(tree);
            return NULL;
        }
        else if (tree->lchild == NULL || tree->rchild == NULL) {
            BSTNode *ret_tree = (tree->lchild ? tree->lchild : tree->rchild);
            free(tree);
            return ret_tree;
        }
        else {
            BSTNode *p = predecessor(tree);
            tree->key = p->key;
            tree->lchild = delete_node(tree->lchild, p->key);
        }
    }
}

int search(BSTNode *tree, int key) {
    if(tree == NULL) return 0;
    if(tree->key == key) return 1;
    if(key < tree->key) return search(tree->lchild, key);
    return search(tree->rchild, key);
}


void clear(BSTNode *tree) {
    
}

void inorder(BSTNode *tree) {
    if(tree == NULL) return ;
    inorder(tree->lchild);
    printf("%d ", tree->key);
    inorder(tree->rchild);
    return;
}

int main()
{
    int op, val;
    BSTNode *tree = NULL;
    while(scanf("%d%d", &op, &val) != EOF) {
        switch (op) {
            case 1: tree = insert(tree, val); break;
            case 2: tree = delete_node(tree, val); break;
            case 3: printf("search %d = %d\n", val, search(tree,val));break;
            case 4: inorder(tree); printf("\n"); break;
        }
    }
    return 0;
}
