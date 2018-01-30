/*************************************************************************
	> File Name: mofaji.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年01月17日 星期三 15时29分03秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef struct Stack{
    int *data;
    int top, size;
}Stack;

Stack * init(int n) {
    Stack * s = (Stack *)malloc(sizeof(Stack) * 1);
    s->data = (int *)malloc(sizeof(int ) * n);
    s->size = n;
    s->top = 0;
    return s;
}

int empty(Stack *s) {
    if(s == NULL) return 0;
    return s->top == 0;
}

int expand(Stack *s) {
    if(s == NULL ) return 0;
    int *data = (int *)realloc(s->data, s->size * 2 * sizeof(int));
    if(data == NULL) return 0;
    s->data = data;
    s->size *= 2;
    return 1;
}

int push(Stack *s, int val) {
    if(s == NULL ) return 0;
    if(s->size == s->top && !expand(s)) return 0;
    s->data[s->top] = val;
    s->top += 1;
    return 1;
}
int pop(Stack *s) {
    if(s == NULL) return 0;
    if(empty(s)) return 0;
    s->top -= 1;
    return 1;
}

int top(Stack *s) {
    if(s == NULL || empty(s)) return 0;
    return s->data[s->top - 1];
}

int main()
{
    int n;
    scanf("%d", &n);
    int cur = 0, *num = (int *)malloc(sizeof(int ) *120);
    Stack *stack = init(10);
    int flag = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d", num + i);
    }
    for(int i = 1; i <= n; i++) {
        push(stack, i);
        while(!empty(stack) && top(stack) == num[cur]) {
            pop(stack);
            cur++;
        }
    }
    while(!empty(stack) && top(stack) == num[cur]) {
        pop(stack);
        cur++;
    }
    //printf("%d %d\n", cur, top(stack));
    if(empty(stack) && cur == n) {
        printf("YES\n");
    }
    else {
        printf("NO\n");
    }

}



/*
int dfs(int x,int y) {
    if(s[y] == '(') {
        return dfs(x,dfs(y,y+1));
    }

        return jug(s[x],s[y]);
}

*/




