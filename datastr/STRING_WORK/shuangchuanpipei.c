/*************************************************************************
	> File Name: shuangchuanpipei.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年02月11日 星期日 13时11分29秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXN (1e6 + 5)

int *getnext(char *s, int n) {
    int *next = (int *)malloc(sizeof(int) * n);
    next[0] = -1;
    int i = -1, j = 1;
    while(s[j] && s[j - 1]) { //不能处理空串
        while(i != -1 && s[i + 1] != s[j]) {
            i = next[i];
        }
        if(s[i + 1] == s[j]) i++;
        next[j++] = i;
    }
    for(int i = 0; i < j; i++) {
        printf("%d ", next[i]);
    }
    printf("\n");
    return next;
}

int kmp(char *str, char *targer, int j, int *next, int len_str, int len_targer) {
    printf("j == %d %d\n", j,len_targer);
    fflush(stdout);
    int i = next[j];
    while(j < len_targer) {
        printf("%d %d\n", i ,j);
        fflush(stdout);
        while(i != -1 && str[i + 1] != targer[j]) {
            i = next[i];
        }
        if(str[i + 1] == targer[j]) i++;
        if(i == len_str - 1) {
            return j;
        }
        j++;
    }
    return -1;
}

int main()
{
    char *sa = (char *)malloc(sizeof(char) * (MAXN));
    char *sb = (char *)malloc(sizeof(char) * (MAXN));
    char *s = (char *)malloc(sizeof(char) * (1e3 + 5));
    scanf("%[^\n]s", sa);
    getchar();
    scanf("%[^\n]s", sb);
    getchar();
    scanf("%[^\n]s", s);
    getchar();
    int lena = strlen(sa);
    int lenb = strlen(sb);
    int len = strlen(s);
    printf("%s\n%s\n%s\n",sa,sb,s);
    int *nexta = getnext(sa, lena);
    int *nextb = getnext(sb, lenb);
    printf("%d\n",nexta[0]);
    fflush(stdout);
    int ya = kmp(s,sa,0,nexta,len,lena);
    printf("ok\n");
    int yb = kmp(s,sb,0,nextb,len,lenb);
    int ans = 0;
    while(1) {
        if(ya == -1 || yb == -1) break;
        if(ya == yb) {
            ans = ya + 2 - len;
            break;
        }
        else if(ya > yb) {
            yb = kmp(s,sb,yb,nextb,len,lenb);
        }
        else {
            ya = kmp(s,sa,ya,nexta,len,lena);
        }
    }
    printf("%d\n",ans);
}
