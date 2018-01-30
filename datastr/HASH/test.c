/*************************************************************************
	> File Name: test.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年01月28日 星期日 15时44分19秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int bkdrhash(char *str) {
    int seed = 16;
    int hash = 0;
    while(*str ) {
        hash = hash * seed + (*str++);
    }
    return hash;
}

int main()
{
    char s1[] = "caabcdefg";
    char s2[] = "aaabcdefg";
    printf("%d\n", bkdrhash(s1));
    printf("%d\n", bkdrhash(s2));
    printf("%ld\n", sizeof(long long));
}
