/*************************************************************************
	> File Name: diguishanchu.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年01月19日 星期五 14时44分03秒
 ************************************************************************/

//////QAQ 这个是错的具体看cengxu.c的写法

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node{
    int data;
    struct Node *lchild, *rchild;
}Node;

Node *init(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}

Node *build(char *s, int len) {
    Node *node = init(s[0]);
    int pos = -1, val = 0;
    for(int i = 0; i <= len; i++) {
        if(s[i] == '(') {
            val++;
        }
        if(s[i] == ')') {
            val--;
        }
        if(s[i] == ',' && val == 1) {
            pos = i;
            break;
        }
    }
    if(pos > 2 && pos != -1) {
        node->lchild = build(s + 2, pos - 3);
    }
    if(len - pos > 1 && pos != -1) {
        node->rchild = build(s + pos + 1,len - 1 - pos);
    }
    return node;
}

void print(Node *node) {
    printf("%c", node->data);
    if(node->lchild || node->rchild) {
        printf("(");
    
    if(node->lchild ) {
        print(node->lchild);
    }
    if(node->rchild != NULL) {
    printf(",");
    if(node->rchild) {
        print(node->rchild);
    }
    }
    printf(")");
    }
}

int clear(Node *node) {
    node->lchild && clear(node->lchild);
    node->rchild && clear(node->rchild);
    free(node);
    return 1;
}

Node *del(Node *node, char val) {
    if(node->data == val) {
        clear(node);
        return NULL;
    }
    node->lchild && (node->lchild = del(node->lchild, val),1);
    node->rchild && (node->rchild = del(node->rchild, val),1);
    return node;
}

int main()
{
    char *s = (char *)malloc(sizeof(char) * 31);
    scanf("%[^\n]s", s);
    Node *root = build(s, strlen(s) - 1);
    getchar();
    char x;
    scanf("%c", &x);
    root = del(root, x);
    if(root == NULL)  return 0;
    if(strlen(s) == 0) {
        return 0;
    }
    print(root),
    printf("\n");
}
