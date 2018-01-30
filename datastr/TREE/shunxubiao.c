/*************************************************************************
	> File Name: shunxubiao.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年01月19日 星期五 15时57分54秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node {
    char data;
    int index;
    struct Node *lchild, *rchild;
}Node;

Node *init(char data, int x) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->data = data;
    node->index = x;
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}

Node *build(Node *node, char data, int x,int c) {
    if(node == NULL) {
        Node *ret = init(data, x);
        return ret;
    }
    if(!(x & (1 << c))) {
        node->lchild = build(node->lchild, data, x, c - 1);
    }
    else {
        node->rchild = build(node->rchild, data, x, c - 1);
    }
    return node;
}

void output(Node *node) {
    printf("%c", node->data);
    if(node->lchild || node->rchild) {
        printf("(");
        if(node->lchild)
        output(node->lchild);

        if(node->rchild){
            printf(",");
            output(node->rchild);
        }
        printf(")");
    }
}

int main()
{
    char *s = (char *)malloc(sizeof(char) * 2);
    int x = 1;
    Node *root = NULL;
    int ceng = 1;
    int sum = 1;
    while(scanf("%s", s) && s[0] != '$') {
        if(x > 2 * ceng + 1) ceng = ceng * 2 + 1, sum++;
        root = build(root, s[0], x, sum - 1);
        x++;
    }
    if(root)
    output(root),
    printf("\n");
}
