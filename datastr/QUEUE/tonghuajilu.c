/*************************************************************************
	> File Name: tonghuajilu.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年01月17日 星期三 10时08分53秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef struct Queue {
    long  *data;
    int head, tail, count, size;
}Queue;

Queue *init(int n) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (long *) malloc (sizeof(long) * (n));
    q->head = 0;
    q->tail = 0;
    q->count = 0;
    q->size = n;
    return q;
}

int expand(Queue *q) {
    if(q == NULL) return 0;
    long *tmp = (long *)malloc(q->size * 2 * sizeof(long));
    if(tmp == NULL) return 0;
    int i = q->head;
    int j = 0;
    do {
        tmp[j++] = q->data[i];
        i =(i + 1) % q->size;
    }while(i != q->tail);
    q->data = tmp;
    q->size *= 2;
    q->head = 0;
    q->tail = j;
    return 1;
}

int empty(Queue *q) {
    if(q == NULL) return 0;
    return q->count == 0;
}

int push(Queue *q, long val) {
    if(q == NULL) return 0;
    if(q->count == q->size && !expand(q)) return 0;
    q->data[q->tail] = val;
    q->tail =(q->tail + 1) % q->size;
    q->count++;
}

long front(Queue *q) {
    if(q == NULL || empty(q)) return 0;
    return q->data[q->head];
}

int pop(Queue *q) {
    if(q == NULL || empty(q)) return 0;
    q->head = (q->head + 1) % q->size;
    q->count -= 1;
    return 1;
}

void clear(Queue *q) {
    free(q->data);
    free(q);
    return ;
}

int main()
{
    Queue *queue[3];
    for(int i = 0; i < 3; i++) {
        queue[i] = init(3);
    }
    int a;
    long b;
    for(int i = 0; i < 10; i++) {
        scanf("%d%ld", &a, &b);
        push(queue[a],b);
    }
    for(int i = 0; i < 10; i++) {
        printf("%ld %ld %ld\n",front(queue[0]), front(queue[1]), front(queue[2]));
        for(int j = 0; j < 3; j++) {
            pop(queue[j]);
        }
    }
    for(int i = 0; i < 3; i++) {
        free(queue[i]);
    }
}
