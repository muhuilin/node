/*************************************************************************
	> File Name: biaodashi.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年01月18日 星期四 15时43分54秒
 ************************************************************************/

#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f

int calc(const char *str, int left, int right) {
    int min_pos = -1, prior = INF - 1, temp_prior = 0;
    for(int i = left; i <= right; i++) {
        int cur_prior = INF;
        switch (str[i]) {
            case '(' : temp_prior += 100; break;
            case ')' : temp_prior -= 100; break;
            case '+' :
            case '-' : cur_prior = temp_prior + 1;break;
            case '*' :
            case '/' : cur_prior = temp_prior + 2;break;
        }
    if(cur_prior <= prior) {
        prior = cur_prior;
        min_pos = i;
    }
    }
    if(min_pos == -1) {
        int num = 0;
        for(int i = left; i <= right; i++) {
            if(str[i] > '9' || str[i] < '0') continue;
            num = num * 10 + str[i] - '0';
        }
        return num;
    }
    int a = calc(str, left, min_pos - 1);
    int b = calc(str, min_pos + 1, right);
    switch (str[min_pos]) {
        case '+' : return a + b;
        case '-' : return a - b;
        case '*' : return a * b;
        case '/' : return a / b;
    }
    return 0;
}

int main()
{
    char *s = (char *)malloc(sizeof(s));
    while(~scanf("%[^\n]s", s)) {
        getchar();
        printf("%d\n",calc(s,0,strlen(s) - 1));
    }
}
