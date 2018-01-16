/*************************************************************************
	> File Name: stack.c
	> Author: 
	> Mail: 
	> Created Time: 2018年01月16日 星期二 16时45分38秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef struct Stack {
    int *data;
    int size, top;
}Stack;

Stack * init(int);
void clear(Stack *);
int empty(Stack *);
int push(Stack *,int);
int pop(Stack *);
int top(Stack *);
int main()
{
    Stack *s = init(10);
    int op, val;
    while(scanf("%d",&val) != EOF) {
        push(s, val);
    }
    while(!empty(s)) {
        printf("%d \n", top(s));
        pop(s);
    }
}

Stack *init(int n) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (int *)malloc(sizeof(int) * n);
    s->top = -1;
    s->size = n;
    return s;
}

void clear(Stack *s) {
    if(s == NULL) return;
    free(s->data);
    free(s);
    return;
}

int empty(Stack *s) {
    return s->top == -1;
}

int push(Stack *s, int val) {
    if (s->top == s->size - 1) return 0;
    
    s->top += 1;
    s->data[s->top] = val;
    return 1;
}

int pop(Stack *s) {
    if(empty(s) ) return 0;
    s->top -= 1;
    return 1;
}

int top(Stack *s) {
    if(empty(s)) return 0;
    return s->data[s->top];
}
