/*************************************************************************
	> File Name: cengxubianli.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年01月19日 星期五 19时13分18秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct Node {
    int data;
    struct Node *lchild, *rchild;
}Node;

Node *init(int data) {
    Node *node =(Node *)malloc(sizeof(sizeof(Node)));
    node->data = data;
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}

typedef struct Queue {
    Node **data;
    int tail, head, count, size;
}Queue;

Queue *initq(int n) {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->data = (Node **)malloc(sizeof(Node *) * n);
    q->head = q->tail = q->count = 0;
    q->size = n;
    return q;
}

int empty(Queue *q) {
    if(q == NULL) {
        return 0;
    }
    return q->count == 0;
}

int expand(Queue *q) {
    if(q == NULL) return 0;
    Node **node = (Node **)malloc( q->size * sizeof(Node *) * 2);
    if(node == NULL) return 0;
    int i = q->head, j = 0;
    do {
        *(node + (j++)) = q->data[i];
        i = (i + 1) % q->size;
    }while(i != q->tail);
    free(q->data);
    q->data = node;
    q->head = 0;
    q->tail = j;
    q->size *= 2;
    return 1;
}

int push(Queue *q, Node *node) {
    if(q == NULL) return 0;
    if(q->size == q->count && !expand(q)) return 0;
    q->data[q->tail] = node;
    q->tail = (q->tail + 1) % q->size;
    q->count += 1;
    return 1;
}

int pop(Queue *q) {
    if(q == NULL) return 0;
    if(empty(q)) return 0;
    q->head = (q->head + 1) % q->size;
    q->count -= 1;
    return 1;
}

Node *front(Queue *q) {
    if(q == NULL) return 0;
    return q->data[q->head];
}

void clearq(Queue *q) {
    free(q->data);
    free(q);
    return;
}

int clearn(Node *node) {
    if(node == NULL) return 0;
    node->lchild && clearn(node->lchild);
    node->rchild && clearn(node->rchild);
    free(node);
    return 1;
}

Node *bfs(Queue *q, Node *root, char x) {
    while(!empty(q)) pop(q);
    push(q, root);
    while(!empty(q)) {
        Node *tmp = front(q);
        pop(q);
        if(tmp->data == x) return tmp;
        tmp->lchild && push(q, tmp->lchild);
        tmp->rchild && push(q, tmp->rchild);
    }
    return NULL;
}

int output(Node *node) {
    if(node == NULL) return 1;
    printf("%c",node->data);
    if(node->lchild || node->rchild) {
        printf("(");
        node->lchild && output(node->lchild);
        node->rchild && printf(","),output(node->rchild);
        printf(")");
    }
}

Node *build(Queue *q, Node *root, char *s) {
    Node *node = init(s[1]);
    if(s[0] == '^') {
        return node;
    }
    Node *father = bfs(q, root, s[0]);
    if(s[2] == 'L') {
        father->lchild = node;
    }
    else {
        father->rchild = node;
    }
    return root;
}

int main()
{
    char *s = (char *)malloc(sizeof(char ) * 4);
    Node *root = NULL;
    Queue *queue = initq(100);
    while(scanf("%s", s) && s[1] != '^') {
        root = build(queue, root, s);
    }
    if(root == NULL) return 0;
    output(root),printf("\n");
}
