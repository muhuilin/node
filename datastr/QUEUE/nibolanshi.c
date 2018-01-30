/*************************************************************************
	> File Name: nibolanshi.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年01月17日 星期三 21时18分34秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef struct Stack{
    int *data;
    int top, size;
}Stack;

int empty(Stack *s) {
    if(s == NULL) return 0;
    return s->top == 0;
}

Stack *init(int n) {
    Stack *s = (Stack *)malloc(sizeof(Stack) * 1);
    s->data = (int *)malloc(sizeof(int ) * n);
    s->top = 0;
    s->size = n;
    return s;
}

int expand(Stack *s) {
    int *data = (int *)realloc(s->data, s->size * 2 * sizeof(int));
    if(data == NULL) return 0;
    s->size *= 2;
    s->data = data;
    return 1;
}

int push(Stack *s, int val) {
    if(s == NULL) return 0;
    if(s->top == s->size && !expand(s)) return 0; 
    s->data[s->top] = val;
    s->top += 1;
    return 1;
}

int top(Stack *s) {
    if(s == NULL || empty(s)) return 0;
    return s->data[s->top - 1];
}
int pop(Stack *s) {
    if(s == NULL || empty(s)) return 0;
    s->top -= 1;
    return 1;
}

void clear(Stack *s) {
    free(s->data);
    free(s);
    return ;
}

int main()
{
    Stack *stack = init(10);
    char *s1 = (char *)malloc(sizeof(char) * 100);
    scanf("%s", s1);
    for(int i = 0; s1[i] != '@'; i++) {
        push(stack, s1[i]);
    }
    int flag = 0;
    for(int i = 0; s1[i] != '@'; i++) {
        if(s1[i] != top(stack)){
            flag = 1;
            break;
        }
        pop(stack);
    }
    if(flag) {
        printf("false\n");
    }
    else {
        printf("true\n");
    }
    clear(stack);
}
