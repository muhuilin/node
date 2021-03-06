/*************************************************************************
	> File Name: sort.c
	> Author:  muhuilin 
    > Mail: Created Time :  
	> Created Time: 2018年01月23日 星期二 19时07分09秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define swap(a, b) { \
    __typeof(a) __temp = a; \
    a = b; \
    b = __temp;\
}

void insert_sort(int *num, int n) {
    int ind = 0;
    for(int i = 1; i < n; i ++) {
        if(num[i] < num[ind]) ind = i;
    }
    while(ind) {
        swap(num[ind], num[ind - 1]);
        --ind;
    }
    for (int i = 1; i < n; i++) {
        for(int j = i; num[j] < num[j - 1]; j--) {
            if(num[j + 1] < num[j]) {
                swap(num[j + 1], num[j]);
            }
            else break;
        }
    }
}
///非监督插入排序mZvoid insert_sort(int *num, int n) {
    
//}

void bubble_sort(int *num, int n) {
    int times = 1;
    for(int i = 0; i < n - 1 && times; i++) {

        for(int j = 0; j < n - i - 1; j++) {
            if(num[j] > num[j + 1]) swap(num[j], num[j + 1]);
        }
    }
}

void merge_sort(int *num, int l, int r) {
    if(l == r) return ;
    int mid = (l + r) >> 1;
    merge_sort(num, l, mid);
    merge_sort(num, mid + 1, r);
    int *temp = (int *)calloc((r - l + 1),sizeof(int ));
    int ind1 = l, ind2 = mid + 1, k = 0;
    while(ind1 <= mid || ind2 <= r) {
        if(ind2 > r || (ind1 <= mid && num[ind1] <= num[ind2])) {
            temp[k++] = num[ind1++];
        } else {
            temp[k++] = num[ind2++];
        }
    }
    memcpy(num + l, temp, sizeof(int) * (r - l + 1));
    free(temp);
    return ;
}

void select_sort(int *num, int n) {
    for(int i = 0; i < n - 1; i++) {
        int ind = i;
        for(int j = i + 1; j < n; j++) {
            if(num[j] < num[ind]) ind = j;
        }
        swap(num[i], num[ind]);
    }
    return ;
}

void lowquick_sort(int *num, int l, int r) {
    if (l >= r) return ;
    int x = l, y = r, z = num[l];
    while(x < y) {
        while(x < y && num[y] >= z) y--;
        if(x < y) num[x] = num[y], x++;
        while(x < y && num[x] <= z) x++;
        if(x < y) num[y] = num[x], y--;
    }
    num[x] = z;
    lowquick_sort(num, l, x - 1);
    lowquick_sort(num, x + 1, r);
    return ;
}

#define TEST(n, func) { \
    int *num = (int *)malloc(sizeof(int) * n); \
    for(int i = 0; i < n; i++) { \
        num[i] = rand() % 100; \
    }\
    func;\
    printf("%s :", #func);\
    for(int i = 0; i < n; i++) {\
        printf("%d ",num[i]);\
    }\
    printf("\n");\
}

void quick_sort(int *num, int l, int r) {
    if (l >= r) return ;
    while(l < r) {
        int x = l, y = r, z = num[(l + r )  / 2];
        while(x <= y) {
            printf("%d %d %d %d %d --",z, x, num[x], y, num[y]);
            fflush(stdout);
            while(x <= y && num[x] < z) ++x;
            while(x <= y && num[y] > z) --y;
            if(x <= y) {
                printf("%d %d\n",x , y);
                swap(num[x], num[y]);
                ++x;
                --y;
            }
        }
        quick_sort(num, x, r);
        r = x - 1;
    }
    return ;
}
/*
    do {
        while(num[x] <= z) ++x;
        while(num[y] >= z) --y;
        if(x <= y) {
            swap(num[x], num[y]);
            ++x;
            --y;
        }
    }while(x < y);*/
    /*while(x < y) {
        while(x < y && num[y] >= z) y--;
        if(x < y) num[x] = num[y], x++;
        while(x < y && num[x] <= z) x++;
        if(x < y) num[y] = num[x], y--;
    }*/
    //num[x] = z;
 /*       while(x < y) {
            while(num[x] < z && x < y) ++x;
            while(num[y] > z && x < y) --y;
            if(x < y) {
                swap(num[x], num[y]);
                ++x;
                --y;
            }
        }
        quick_sort(num, y, r);*/
void count_sort(int *num, int n) {
    #define MAX_N 1000
    int *temp = (int *)calloc(MAX_N + 1,sizeof(int ));
    for(int i = 0; i < n; i++) {
        temp[num[i]] ++;
    }
    for(int i = 0; i <= MAX_N; i++) {
        if(temp[i] == 0) continue;
        while(temp[i] --) {
            printf("%d ", i);
        }
    }
    printf("\n");
    free(temp);
    #undef MAX_N
    return ;
}

void radix_sort(int *num, int n) {
    #define MAX_N 65536
    int *cnt = (int *)calloc(MAX_N + 1, sizeof(int));
    int *temp = (int *)malloc(sizeof(int ) * n);
    for(int i = 0; i < n; i++) {
        cnt[(num[i] & 65535) + 1] += 1;
    }
    for(int i = 1; i <= 65535; i++) {
        cnt[i] += cnt[i - 1];
    }
    for(int i = 0; i < n; i++) {
        temp[cnt[num[i] & 65535] ++] = num[i];  //**//
    }
    memset(cnt, 0, sizeof(int) * (MAX_N + 1));
    int *p = temp;
    temp = num;
    num = p;
    for(int i = 0; i < n; i++) {
        cnt[((num[i] >> 16) & 65535) + 1] += 1;
    }
    for(int i = 0; i < 65535; i++) {
        cnt[i] += cnt[i -  1];
    }
    for(int i = 0; i < n; i++) {
        temp[cnt[(num[i] >> 16) & 65535] ++] = num[i];
    }
    #undef MAX_N 
    return ;
}

int main() {
    srand(time(0));
    //TEST(20, insert_sort(num, 20));
    //TEST(20, bubble_sort(num, 20));
    //TEST(20, merge_sort(num, 0, 19));
    //TEST(20, select_sort(num, 20));
    TEST(20, quick_sort(num, 0, 19));
    //TEST(20, radix_sort(num, 20));
    return 0;
    
}
