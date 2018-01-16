/*************************************************************************
	> File Name: xishuduoxiangshi.c
	> Author: 
	> Mail: 
	> Created Time: 2018年01月12日 星期五 11时57分28秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

#define DEFVAL(n,val) ((#n[0] ? n : val))
#define init(n) __init(DEFVAL(n,100))

typedef struct Vector {
    int length,size;
    int *c;
    int *e;
} Vector;

Vector * __init(int n) {
    Vector *ret = (Vector *)malloc(sizeof(Vector) * 1);
    ret->c = (int *)malloc(sizeof(int) * n);
    ret->e = (int *)malloc(sizeof(int) * n);
    ret->length = n;
    ret->size = 0;
    return ret;
}

int exten(Vector *vec) {
    int *p1 = (int *)realloc(vec->c, vec->size * 2 * sizeof(int ));
    int *p2 = (int *)realloc(vec->e, vec->size * 2 * sizeof(int ));
    if (p1 == NULL || p2 == NULL) return 0;
    vec->size *= 2;
    vec->c = p1;
    vec->e = p2;
    return 1;
}

int insert(Vector *vec, int a, int b) {
    if (vec == NULL) return 0;
    if (vec->length == vec->size && !exten(vec)) {
        return 0;
    }
    vec->c[vec->length] = a;
    vec->e[vec->length] = b;
    vec->length += 1;
    return 1;
}
int mypow(int x,int m) {
    int ret = 1;
    for(int i = 0; i < m; i++) {
        ret *= x;
    }
    return ret;
}
void output(Vector * vec, int x) {
    int ret = 0;
    for(int i = 0; i < vec->length; i++) {
        ret += mypow(x, vec->e[i]) * vec->c[i];
    }
    printf("%d\n",ret);
    return ; 
}

int main()
{
    Vector* vec = init(100);
    int n, a, b;
    scanf("%d",&n);
    for(int i = 0; i < n; i++) {
        scanf("%d%d", &a, &b);
        insert(vec, a, b);
    }
    int x;
    scanf("%d", &x);
    output(vec, x);
}
