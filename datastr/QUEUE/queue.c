/*************************************************************************
	> File Name: queue.c
	> Author: 
	> Mail: 
	> Created Time: 2018年01月16日 星期二 15时30分27秒
 ************************************************************************/
/// 实现一个可以储存任意类型的队列
#include<stdio.h>

typedef struct Queue {
    void  *data;
    int head, tail, length;
} Queue;
