/*************************************************************************
	> File Name: test.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年01月19日 星期五 09时23分20秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
void f(int **x) {
    *x = (int *)malloc(sizeof(int ) *10);
    (*(*x+1)) = 5;
    (*(*x)) = 4;
    return;
}
void ff(char *s) {
    s[0] = 'a';
    s[1] = '\0';
}
int main()
{/*
    int **x ;
    x = (int **)malloc(sizeof(int *)  * 10);
    *x = (int *)malloc(sizeof(int ) * 1);
    *(*x + 1) = 1;
    f(x + 1);*/
    char now[120];
    ff(now);
    printf("%s\n",now);
    //printf("%d %d %d",*(*(x + 1)), *(*(x + 1) + 1), *(*x + 1));
}
