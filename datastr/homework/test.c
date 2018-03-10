/*************************************************************************
	> File Name: test.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年02月10日 星期六 18时40分15秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int hash(char c) {
    return c + 1000;
}

char unhash(int a) {
    return a - 1000 +'\0';
}

int main()
{
    char s[120];
    char ans[120]; 
    int *tmp = (int *)calloc(10,sizeof(int));
    free(tmp);
    while(scanf("%s", s) != EOF) {
        for(int i = 0; s[i]; i++) {
            ans[i] = unhash(hash(s[i]));
        }
        printf("%s\n", ans);
    }
}
