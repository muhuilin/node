/*************************************************************************
	> File Name: rand.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年01月26日 星期五 20时04分27秒
 ************************************************************************/

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int main()
{
    srand(time(0));
    printf("%d\n", rand() % 540);
}
