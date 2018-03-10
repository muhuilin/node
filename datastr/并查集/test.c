/*************************************************************************
	> File Name: test.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年03月01日 星期四 23时16分22秒
 ************************************************************************/

#include<stdio.h>

int main()
{
    char a[20][20], b[20][20];
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            char tmp[20];
            scanf("%s", tmp);
            a[i][j] = tmp[0];
        }
    }
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            char tmp[20];
            scanf("%s", tmp);
            b[i][j] = tmp[0];
        }
    }
    for(int i = 0; i < 10; i ++) {
        for(int j = 0; j < 10; j++) {
            if(a[i][j] == b[i][j]) {
                printf("%c ",a[i][j]);
            }
            else {
                printf("# ");
            }
        }
        printf("\n");
    }
}
