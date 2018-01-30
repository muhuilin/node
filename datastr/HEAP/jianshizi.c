/*************************************************************************
	> File Name: jianshizi.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年01月26日 星期五 15时16分46秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Heap {
    int *id, *loc;
    int size;
}Heap;

int push()
