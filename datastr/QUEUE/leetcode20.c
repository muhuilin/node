/*************************************************************************
	> File Name: leetcode20.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年01月18日 星期四 10时15分14秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
int pan(char c) {
    switch(c) {
        case '(' : return -1;
        case '{' : return -2;
        case '[' : return -3;
        case ')' : return 1;
        case '}' : return 2;
        case ']' : return 3;
        default : return 0;
    }
}

int dfs(char *s, int x, int y) {
    if(pan(s[y]) < 0) {
        int tmp = dfs(s, y, y + 1);
        if(tmp == -1) return -1;
        return dfs(s,x, tmp + 1);
    }
    return pan(s[x]) + pan(s[y]) == 0 ? y : -1;
}

int isValid(char* s) {
    int i = 0;
    while(s[i] != '\0') {
        i = dfs(s,i,i+1);
        if(i == -1) {
            return 0;
        }
        i++;
    }
    if(s[i] == '\0') return 1;
    return 0;
}
int main()
{
    char *s = (char *)malloc(sizeof(char) * 100);
    while(scanf("%s", s)) {
        //printf("hhhhhhhhhhhhhhh\n");
        //printf("ans == %d\n", isValid(s));
        //printf("aaaaaaaaaaaaaaaa\n");
    }
}
