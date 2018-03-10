/*************************************************************************
	> File Name: sort.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年02月28日 星期三 14时43分46秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

int main()
{
    int *num = (int *)malloc(sizeof(int ) * 10000);
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", num + i);
    }
    lowquick_sort(num, 0, n - 1);
    for(int i = 0; i < n; i++) {
        printf("%d\n",num[i]);
    }
}
