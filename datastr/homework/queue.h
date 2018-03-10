/*************************************************************************
	> File Name: haffmantrie.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年02月12日 星期一 23时38分46秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define swap(a,b) {\
    __typeof(a) __temp = a;\
    a = b; b = __temp;\
}

typedef struct Node {
    char data;
    int val;
    struct Node *lchild, *rchild;
}Node, *Tree;

typedef struct Heap {
    Node **data;
    int n, size;
}Heap;

Node *getnewnode() {
    Node * p = (Node *)malloc(sizeof(Node) * 1);
    p->data =  p->val = 0;
    p->lchild = p->rchild = NULL;
    return p;
}

Heap *init(int n) {
    Heap *h = (Heap *)malloc(sizeof(Heap) * 1);
    h->data = (Node **)malloc(sizeof(Node*) * n);
    h->n = 0;
    h->size;
    return h;
}

int insert(Heap *h, Node *p) {
    h->size += 1;
    h->data[h->size] = p;
    int loc = h->size, father = loc / 2;
    while(father > 0 && h->data[father]->val > h->data[loc]->val) {
        swap(h->data[father],h->data[loc]);
        loc = father;
        father = loc / 2;
    }
    return 1;
}

int pop(Heap *h) {
    swap(h->data[1],h->data[h->size]);
    h->size -= 1;
    int loc = 1;
    while(loc * 2 <= h->size) {
        int l = loc * 2;
        int r = l + 1;
        int pos = loc;
        if(l <= h->size && h->data[pos]->val > h->data[l]->val) {
            pos = l;
        }
        if(r <= h->size && h->data[pos]->val > h->data[r]->val) {
            pos = r;
        }
        if(pos == loc) break;
        swap(h->data[pos], h->data[loc]);
        loc = pos;
    }

} 

int empty(Heap *h) {
    return h->size == 0;
}

Node *top(Heap *h) {
    return h->data[1];
}

int heapsize(Heap *heap) {
    return heap->size;
}

/*
int main()
{
    Heap *heap = init(100);
    for(int i = 0; i < 10; i++) {
        Node * p = getnewnode();
        p->val = 10 - i;
        p->data = 'a' + i;
        insert(heap, p);
        printf("%d ", top(heap));
    }
    printf("\n");
    for(int i = 1; i <= 10; i++) {
        printf("%d ",heap->data[i]->val);
    }
    printf("\n");
    for(int i = 0; i < 10; i++) {
        pop(heap);
        printf("%d ",top(heap));
    }
    printf("\n");
}*/
