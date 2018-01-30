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
int jug(char c) {
    if(c >= 'A' && c <= 'Z') return 1;
    return 0;
}
Node *build(char *s, int len) {
    Node *node = init(s[0]);
    if(len == 0) return node;
    int pos = len, val = 0;
    for(int i = 0; i <= len; i++) {
        if(s[i] == '(') {
            val++;
        }
        if(s[i] == ')') {
            val--;
        }
        if(val == 1 && s[i] == ',') {
            pos = i;
            break;
        }
    }
    if(pos > 2 && jug(s[2] )) {
        node->lchild = build(s + 2, pos - 3);
    }
    if(len - pos > 1) {
        node->rchild = build(s + pos + 1, len - pos - 2);
    }
    return node;
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

void bfs(Queue *q, Node *node) {
    push(q, node);
    while(!empty(q)) {
        Node *tmp = front(q);
        pop(q);
        printf("%c", tmp->data);
        tmp->lchild && push(q, tmp->lchild);
        tmp->rchild && push(q, tmp->rchild);
        if(!empty(q)) printf(" ");
    }
    printf("\n");
    return ;
}

int main()
{
    char *s = (char *)malloc(sizeof(char ) * 200);
    scanf("%s", s);
    Node *root = NULL;
    Queue *queue = initq(100);
    getchar();
    if(strlen(s) == 0) return 0 ;
    root = build(s, strlen(s) - 1);
    bfs(queue, root);
}
