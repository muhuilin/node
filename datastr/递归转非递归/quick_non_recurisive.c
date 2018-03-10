/*************************************************************************
   > File Name: 14.binary_non_recursive.cpp
   > Author: hug
   > Mail:   hug@haizeix.com
   > Created Time: 三  2/28 10:26:37 2018
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "any_stack.h"

/*
typedef struct Node {
    int *num;
    int x, y, z, l, r;
} Node;

Node *getnewnode(int *num, int l, int r) {
    Node *p = malloc(sizeof(Node ) * 1);
    p->num = num;
    p->l = l;
    p->r = r;
    p->mid = 0;
    return p;
}
*/
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
    //lowquick_sort(num, l, x - 1);
    //lowquick_sort(num, x + 1, r);
    return ;
}

typedef struct PreOrderArgs {
    int *num;
	int l, r, mid;
    int status;
} PreOrderArgs;

PreOrderArgs *getNewArgs(int *num, int l, int r) {
    PreOrderArgs *p = (PreOrderArgs *)malloc(sizeof(PreOrderArgs) * 1);
    p->l = l;
    p->r = r;
	p->mid = 0;
    p->status = 0;
    return p;
}

void __pre_order(int *nums, int l, int r) {
    Stack *s = init_stack(1000, PreOrderArgs);
    PreOrderArgs *temp_args = getNewArgs(nums,l,r), *p_args;
    push_stack(s, temp_args);
    while (!empty_stack(s)) {
        p_args = top_stack(s, PreOrderArgs);
        //printf("l = %d r = %d status = %d\n", p_args->l, p_args->r, p_args->status);
        switch (p_args->status) {
            case 0: {
                if (p_args->l >= p_args->r) {
                    p_args->status = 100;
                } else {
                    p_args->status = 1;
                }
            } break;
            case 1: {
          //      printf("%d %d\n",p_args->l, p_args->r);
                int l = p_args->l, r = p_args->r,  *num = p_args->num;
                int x = l, y = r, z = num[l];
				while(x < y) {
        			while(x < y && num[y] >= z) y--;
        			if(x < y) num[x] = num[y], x++;
        			while(x < y && num[x] <= z) x++;
        			if(x < y) num[y] = num[x], y--;
    			}
    			num[x] = z;
                //printf("case 1 mid = %d\n", x);
                p_args->mid = x;
                p_args->status = 2;
            } break;
            case 2: {
                temp_args->l = p_args->l;
                temp_args->r = p_args->mid - 1;
                temp_args->num = p_args->num;
                temp_args->status = 0;
                push_stack(s, temp_args);
                p_args->status = 3;
            } break;
            case 3: {
                temp_args->l = p_args->mid + 1;
                temp_args->r = p_args->r;
                temp_args->num = temp_args->num;
                temp_args->status = 0;
                push_stack(s, temp_args);
                p_args->status = 100;
            } break;
            case 100: {
                pop_stack(s);
            } break;
        }
    }
    //free(temp_args);
    //clear_stack(s);
    return ;
}



int main() {
    int *num = (int *)malloc(sizeof(int ) * 10000);
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
       scanf("%d", num + i);
    }
    __pre_order(num, 0, n - 1);
    for(int  i = 0; i < n; i++) {
        printf("%d\n",num[i]);
    }
    return 0;
}

