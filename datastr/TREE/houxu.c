/*************************************************************************
	> File Name: houxu.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年01月19日 星期五 10时45分20秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node {
    int data;
    struct Node *lchild, *rchild;
}Node ;

Node *init(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}

Node *build(char *pre, char *in, int len) {
    Node *node = init(pre[0] );
    int pos = strchr(in, pre[0]) - in;
    if(pos > 0) {
        node->lchild = build(pre + 1, in, pos);
    }
    if(len - pos - 1 > 0) {
        node->rchild = build(pre + pos + 1, in + pos + 1, len - pos - 1);
    }
    return node;
}

int postorder(Node *node) {
    node->lchild && postorder(node->lchild);
    node->rchild && postorder(node->rchild);
    printf("%c", node->data);
    return 1;
}

int repostorder(Node *node) {
    node->rchild && repostorder(node->rchild);
    node->lchild && repostorder(node->lchild);
    printf("%c", node->data);
    return 1;
}
int main()
{
    char *pre = (char *)malloc(sizeof(char) * 51);
    char *in = (char *)malloc(sizeof(char) * 51);
    scanf("%s%s", pre, in);
    Node *root = build(pre, in, strlen(pre));
    postorder(root),
    printf("\n");
    repostorder(root),
    printf("\n");
}
