/*************************************************************************
	> File Name: heapsorp.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年01月23日 星期二 15时24分13秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

#define swap(a, b) { \
    int tmp = a;\
        a = b;\
        b = tmp;\
}

typedef struct pq {
    int *data;
    int size, n;
}pq;

pq *init (int n) {
    pq * p = (pq *)malloc(sizeof(pq) * 1);
    p->n = 0;
    p->size = n + 1;
    p->data = (int *)malloc(sizeof(int ) * n + 1);
    return p;
}

int empty(pq *p) {
    return p->n == 0;
}

int front(pq *p) {
    return p->data[1];
}

int push(pq *p, int val) {
    if(p->size <= p->n + 1) {
        return 0;
    }
    p->n += 1;
    p->data[p->n] = val;
    int ind = p->n;
    while(ind > 1 && p->data[ind >> 1] < p->data[ind]) {
        swap(p->data[ind >> 1], p->data[ind]);
        ind = (ind >> 1);
    }
    return 1;
}



int pop(pq *p) {
    if(empty(p)) {
        return 0;
    }
    p->data[1] = p->data[p->n];
    p->n -= 1;
    int ind = 1;
    while(ind * 2 <= p->n) {
        int ind1 = ind * 2;
        int ind2 = ind * 2 + 1;
        int max_ind = ind;
        if(p->data[ind1] > p->data[ind]) max_ind = ind1;
        if(ind2 <= p->n && p->data[ind2] > p->data[ind]) max_ind = ind2;
        if(max_ind == ind) break;
        swap(p->data[ind], p->data[max_ind]);
        ind = max_ind;
    }
    return 1;
}

void clear(pq * p) {
    if(p == NULL) return ;
    free(p->data);
    free(p);
    return ;
}

int main()
{
    int n,a;
    scanf("%d", &n);
    pq *p = init(n);
    for(int i = 0; i < n; i++) {
        scanf("%d",&a);
        push(p,a);
        printf("%d\n", front(p));
    }
    while(!empty(p)) {
        printf("%d \n",front(p));
        pop(p);
    }
    return 0;
}
