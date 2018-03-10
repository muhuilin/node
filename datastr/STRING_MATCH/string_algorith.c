/*************************************************************************
	> File Name: string_algorith.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年02月01日 星期四 11时17分56秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int brute_force(const char *str, const char *targe) {
    int len1 = strlen(str);
    int len2 = strlen(targe);
    for(int i = 0; i <= len1 - len2; i++) {
        int flag = 1;
        for(int j = 0; j < len2 && flag; j++) {
            flag = str[i + j] == targe[j];
        }
        if(flag) return 1;
    }
    return 0;
}



int kmp(const char *str, const char *targe ) {
    int len1 = strlen(str);
    int len2 = strlen(targe);
    int *next = (int *)malloc(sizeof(int ) * len2);
    next[0] = -1;
    int j = -1;
    for(int i = 1; i < len2; i++) { /// 
        while(j != -1 && targe[j + 1] != targe[i]) {
            j = next[j];
        }
        if(targe[j + 1] == targe[i]) {
            j += 1;
        }
        next[i] = j;
    }
    int i = 0;
    j = -1;
    while(i < len1) {
        if(str[i] == targe[j + 1]) j += 1, i += 1;
        else {
            while(str[i] != targe[j + 1] && j != -1) {
                j = next[j];
            }
            if(str[i] != targe[j + 1]) {
                i += 1;
            }
            
        }
        if(j + 1 == len2 ) {
            break;
        }
    }

    free(next);
    return (j + 1 == len2);

}

int sunday(const char *str, const char *targe) {
    int len1 = strlen(str);
    int len2 = strlen(targe);
    int ch_ind[128] = {0};
    for(int i = 0; i < 128; i++) {
        ch_ind[i] = len2 + 1; /// zhongdiand
    }
    for(int i = 0; i < len2; i++) {
        ch_ind[targe[i]] = len2 - i;
    }
    for(int i = 0; i < len1;) {
        int j = 0;
        for(; j < len2 && str[i + j] == targe[j]; j++) ;
        if(j == len2) return 1;
        i += ch_ind[str[i + len2]];
    }
    return 0;
}

int shift_and(const char *str, const char *targe) {
    int ch_code[128];
    int len2 = 0;
    for (len2 = 0; targe[len2]; len2++) {
        ch_code[targe[len2]] |= (1 << len2);
    }
    int p = 0, limit = ((1 << (len2 - 1)) - 1);
    for(int i = 0; str[i] ;i ++) {
        p = (p << 1 | 1) & ch_code[str[i]];
        if(p > limit) return  1;
    }
    return 0;
}
int shift_and_M(const char *str, const char *targe) {
    int len2 = strlen(targe);
    int **ch_code = (int **)malloc(sizeof(int *) * 256);
    for(int i = 0; i < 256; i++) {
        ch_code[i] = (int *)malloc(sizeof(int) * (len2 / 30 + 1));
    }
    int *p = (int *)calloc ((len2 / 30 + 1), sizeof(int));
    for(int i = 0; i < len2; i++) {
        int x = i / 30, y = i % 30, cur = targe[i];
        ch_code[cur][x] |= (1 << y);
    }
    int limit1 = len2 / 30, limit2 = (len2 % 30) - 1;
    for(int i = 0; str[i]; i++) {
        int flag = 1, jin = 0;
        for(int j = 0; j < (len2 / 30 + 1); j++) {
            jin = (p[j] & (1 << 29));
            p[j] = (p[j] << 1 | flag);
            flag = jin;
        }
        for(int j = 0; j < (len2 / 30 + 1); j++) {
            p[j] &= ch_code[targe[i]][j];
            if (limit1 == j && p[j] & (1 << limit2)) return 1;
        }
    }
    return 0;
}

#define TEST(func) { \
    printf("%s = %d\n", #func, func);\
}

int main()
{
    char str1[100], str2[100];
    while(~scanf("%s%s", str1, str2)) {
        TEST(brute_force(str1,str2));
        TEST(kmp(str1,str2));
        TEST(sunday(str1,str2));
        TEST(shift_and_M(str1,str2));
    }
    return 0;
}
