/*************************************************************************
	> File Name: youxujihejiaoyunsuan.c
	> Author: 
	> Mail: 
	> Created Time: 2018年01月12日 星期五 15时37分04秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

#define DEFVAL(n,val) ((#n[0] ? n : val))
#define init(n) __init(DEFVAL(n,100))

typedef struct Vector {
    int length,size;
    int *data;
} Vector;

int expern (Vector *vec) {
    int *p = (int *)realloc(vec->data, vec->size * 2 * sizeof(int ));
    if(p == NULL ) return 0;
    vec->size *= 2;
    vec->data = p;
    return 1;
}

Vector* __init(int n) {
    Vector * ret = (Vector *)malloc(sizeof(Vector) * 1);
    ret->data = (int *)malloc(sizeof(int ) * n);
    ret->length = 0;
    ret->size = n;///// 为什么忘记返回值还可以
    printf("")
}

int insert(Vector *vec, int val) {
    if(vec == NULL) return 0;
    if(vec->size == vec->length && !expern(vec)) {
        return 0;
    }
    vec->data[vec->length] = val;
    vec->length += 1;
    return 1;
}


int jiaoji(Vector *veca, Vector * vecb , Vector *vecc) {
    if(veca == NULL && vecb == NULL) return 0;
    int cura = 0, curb = 0;
    while(cura < veca->length && curb < vecb->length) {
        if(veca->data[cura] > vecb->data[curb]) {
            curb++;
        }
        else {
            if(veca->data[cura] == vecb->data[curb]) {
            insert(vecc, veca->data[cura]);
                curb++;
            }
            cura++;
        }
    }
    return 1;
}

void output(Vector *vec) {
    if (vec == NULL) return ;
    printf("%d\n", vec->length);
    for(int i = 0; i < vec->length; i++) {
        printf("%d", vec->data[i]);
        if(i != vec->length - 1) printf(" ");
    }
    printf("\n");
}

int main()
{
    Vector * veca = init();
    Vector * vecb = init();
    Vector *vecc = init();
    int n, m , tmp;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &tmp);
        insert(veca, tmp);
    }
    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        scanf("%d", &tmp);
        insert(vecb, tmp);
    }
    jiaoji(veca, vecb, vecc);
    output(vecc);
}




