/*************************************************************************
	> File Name: cengxubianli2.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年01月20日 星期六 15时46分48秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    char data;
    struct Node *lchild, *rchild;
}Node;

Node *init(char data) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->lchild = node->rchild = NULL;
    return node;
}

void clear(Node *node) {
    if(node == NULL) return ;
    clear(node->lchild);
    clear(node->rchild);
    free(node);
    return ;
}

Node *build(const char *str) {
    int k = 0, i = 0;
    Node *p = NULL,* root;
    #define MAX_S 100
    static Node *s[MAX_S];
    static int top = -1;
    while(str[i]) {
        switch (str[i]) {
            case '(' : 
                   s[++top] = p;
                   p = NULL;
                   k = 1;
                   break;
            case ')' :
            if(top == -1) {
                fprintf(stderr,"ERROR\n");
                return NULL;
            }
                top -= 1;
                
            case ',' : k = 2; break;
            case ' ' :break;
            default  :
                p = init(str[i]);
            if(k == 0) {
                root = p;
            }
            else if(s[top] == NULL) {
                fprintf(stderr, "ERROR\n");
                return NULL;
            }
            else if(k == 1) {
                s[top]->lchild = p;
            }
            else {
                s[top]->rchild = p;
            }
        }
        i++;
    }
    if(top != -1) {
        fprintf(stderr, "ERROR\n");
        return NULL;
    }
    #undef MAX_S
    return root;
}

int output(Node *root) {
    if(root == NULL) return 1;
    printf("%c ",root->data);
    root->lchild && output(root->lchild);
    root->rchild && output(root->rchild);
}

int main() {
    char str[100];
    Node *root = NULL;
    while(~scanf("%[^\n]s",str)) {
        getchar();
        root = build(str);
        output(root),printf("\n");
    }
    

    return 0;
}
