/*************************************************************************
	> File Name: queue1.c
	> Author: 
	> Mail: 
	> Created Time: 2018年01月16日 星期二 14时45分52秒
 ************************************************************************/
/// 实现可以存取任意格式类型的队列 
#include<stdio.h>

#include<stdlib.h>
#include<string.h>

#define DEFVAL(n) ((#n[0] ? n : 10))
#define init(T,n) (__init(sizeof(T),10))
#define push(q,val) ((__push(q, &val)))
#define front(q, T) (*((T *)__front(q)))

typedef struct Queue {
    void *data;
    int data_size ;
    int head, tail, length;
}Queue;

Queue *__init(int ,int);
int __push(Queue *, void *);
int pop(Queue *);
int empty(Queue *);
int expand(Queue *);
void clear(Queue *);
void output(Queue *, int);
void *__front(Queue *);

Queue *__init(int data_size, int n) {
   Queue *p = (Queue *) malloc(sizeof(Queue)) ;
    p->data = malloc(data_size * n);
    p->length = n;
    p->head = p->tail = 0;
    p->data_size = data_size;
    return p;
}

void *__front(Queue *q) {
    if(empty(q)) return NULL;
    return (char *) (q->data ) + q->head * q->data_size;
}

void clear(Queue *q) {
    if(q == NULL) return;
    free(q->data);
    free(q);
    return ;
}

int expand(Queue *q) {
    void *tmp_data = (void *)realloc(q->data, q->data_size * q->length * 2);
    if(tmp_data == NULL) {
        return 0;
    }
    q->data = tmp_data;
    q->length *= 2;
}

int __push(Queue *q, void *val_p) {
    if(q->tail == q->length && !expand(q)) return 0;
    char *data = (char *)(q->data);
    memcpy(data + q->tail * q->data_size, val_p, q->data_size);
    q->tail += 1;
    return 1;
} 

int empty(Queue *q) {
    return q->head == q->tail;
}

int pop(Queue *q) {
    if(q == NULL) return 0 ;
    if(empty(q)) return 0;
    q->head += 1;
    return 1;
}

void output(Queue *q, int data_size) {
    printf("Queue = : ");
    for(int i = q->head; i < q->tail; i++){
    //    printf("%d ", q->data[i]);
    }
    printf("\n");
    return ;
}

int main()
{
    Queue *q = init(4,100);
    int op, val;
    while(scanf("%d", &op)) {
        if(op == 1) {
            scanf("%d", &val);
            push(q,val);
        }
        else if(op == 2) {
            pop(q);
        }
        else {
            int tmp =  front(q, int);
            printf("%d\n", tmp);
        }
        output(q);
    }
    clear(q);
}
