/*************************************************************************
	> File Name: vector.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年01月11日 星期四 16时45分54秒
 ************************************************************************/



#include<stdio.h>
#include<stdlib.h>

typedef struct Vector {
    int *data;
    int length, size;
} Vector;

#define DEFVAL(n,defval) ((#n[0] ? n : defval))
#define init(n) __init(DEFVAL(n,1))
Vector *__init(int n) {
    Vector *ret = (Vector *)malloc(sizeof(Vector) * 1);
    ret->data = (int *)malloc(sizeof(int) * n);
    ret->size = n;
    ret->length = 0;

    return ret;
}

void clear(Vector *vec) {
    if(vec == NULL) return ;
    if(vec->data != NULL) {
        free(vec->data);
        return ;
    }
    free(vec);
    return ;
}

int expand(Vector *vec) {
    int *p = (int *)realloc(vec->data, vec->size * 2 * sizeof(int));
    //printf("p = %p\n",p);
    if (p == NULL) return 0;
    vec->data = p;
    vec->size *= 2;
    //printf("chenggong\n");
    return 1;
}

int insert(Vector *vec, int value_comp, int ind) {
    if(vec == NULL ) return 0;
    if(ind > vec->length || ind < 0) return 0;
    if(vec->length == vec->size && !expand(vec)) {
        printf("HHHH\n");
        return 0;
    }

    for (int i = vec->length; i > ind; i--) {
        vec->data[i] = vec->data[i - 1];
    }
    vec->data[ind] = value_comp;
    vec->length += 1;
    //printf("%d\n",vec->length);
    return 1;
}

void output(Vector *vec) {
    for(int i = 0; i < vec->length; i++) {
        printf("%d",vec->data[i]);
        if(i != vec->length - 1) printf(" ");
    }
    printf("\n");
}

int delete_node(Vector *vec, int  ind) {
    if(vec == NULL) return 0;
    if(ind < 0 || ind >= vec->length) return 0;
    for (int i =  ind + 1; i < vec->length; i++) {
        vec->data[i - 1] = vec->data[i];
    }
    vec->length -= 1;
    return 1;
}

void xunhuan(Vector *vec,int k) {
    for(int i = 0; i < k; i++) {
        insert(vec,vec->data[0],vec->length);
        delete_node(vec, 0);
    }
}

int main()
{
    Vector *vec = init(1);
    int n, k;
    scanf("%d%d", &n,&k);
    for(int i = 0; i < n; i++) {
        int tmp;
        scanf("%d", &tmp);
        insert(vec, tmp, i);
    }
    //output(vec);
    xunhuan(vec,k);
    output(vec);
}
