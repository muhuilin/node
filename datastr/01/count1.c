/*************************************************************************
	> File Name: count1.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年01月30日 星期二 16时03分56秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int count_arr[256];

int count_binary(unsigned int x) {
    unsigned char *p = (unsigned char *) (&x);
    #define CP(n) count_arr[p[n]]
    return CP(0) + CP(1) + CP(2) + CP(3);
    #define CP
}

int main()
{
    
}
