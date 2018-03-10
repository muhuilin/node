/*************************************************************************
    > File Name: 006.cpp
    > Author:    hug
    > Mail:      hug@haizeix.com
    > Created Time: 二  8/15 17:14:32 2017
************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int BF(char *s, char *t) {
    int i = 0, j = 0;
    int times = 0;
    while (s[i]) {
        while (s[i + j] && t[j] && s[i + j] == t[j]) {
            j++; times += 4;
        }
        if (t[j] == '\0') {
            printf("BF YES : %d\n", times);
            return times;
        }
        times += 3;
        j = 0;
        i++;
    }
    printf("BF NO : %d\n", times);
    return times;
}

void get_next(char *t, int *next) {
    int j = 1, match = -1;
    next[0] = -1;
    while (t[j]) {
        while (match != -1 && t[match + 1] != t[j]) {
            match = next[match];
        }
        if (t[match + 1] == t[j]) {
            match++;
        }
        next[j] = match;
        j++;
    }
    return ;
}

void kmp_match(char *s, char *t, int *next) {
    int i = 0, match = -1;
    int times = 0;
    while (s[i]) {
        while (match != -1 && t[match + 1] != s[i]) {
            times += 3;
            match = next[match];
        }
        if (t[match + 1] == s[i]) {
            times += 2;
            match++;
        }
        if (t[match + 1] == '\0') {
            printf("KMP YES : %d\n", times);
            return ;
        }
        times += 2;
        i++;
    }
    printf("KMP NO : %d\n", times);
    return ;
}
 

void sunday(char *s, char *t) {
    int str_index[256] = {0};
    int len_t = strlen(t);
    int len_s = strlen(s);
    for (int i = 0; i < 256; i++) {
        str_index[i] = len_t + 1;
    }
    for (int i = 0; t[i]; i++) {
        str_index[t[i]] = len_t - i;   
    }
    int i = 0, j = 0;
    int times = 0;
    while (i + len_t <= len_s) {
        if (s[i + j] != t[j]) {
            times += 3;
            i += str_index[s[i + len_t]];
            j = 0;
        } else {
            times += 2;
            j++;
        }
        if (t[j] == '\0') {
            printf("sunday YES : %d\n", times);
            return ;
        }
    }
    printf("sunday NO : %d\n", times);
    return ;
}

void shift_and(char *s, char *t) {
    int str_encode[256] = {0};
    int p = 0, n;
    int times = 0;
    for (n = 0; t[n]; n++) {
        str_encode[t[n]] |= (1 << n);
    }
    for (int i = 0; s[i]; i++) {
        times += 3;
        p = (p << 1 | 1) & str_encode[s[i]];
        if (p & (1 << (n - 1))) {
            printf("SHIFT AND : %d\n", times);
            return ;
        }
    }
    printf("SHIFT AND : %d\n", times);
    return ;

}


int main() {
    char s[] = "aecaeaecaed";
    char t[] = "aecaed";
    int next[100];
    BF(s, t);
    get_next(t, next);
    kmp_match(s, t, next);
    sunday(s, t);
    shift_and(s, t);
    return 0;

}

 
