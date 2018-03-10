/*************************************************************************
	> File Name: nailao.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年02月28日 星期三 23时11分19秒
 ************************************************************************/

#include<stdio.h>
#include<stdio.h>
#include<stdlib.h>

typedef struct UnionSet{
    int n;
    int *father;
    int *size;
}UnionSet;

typedef struct Node {
    int x, y, z;
}Node;

Node *initn(int n) {
    Node *p = (Node *)malloc(sizeof(Node) * (n + 100));
    return p;
}

UnionSet *initu(int n) {
    UnionSet *u = (UnionSet *)malloc(sizeof(UnionSet) * 1);
    u->n = n;
    u->father = (int *)malloc(sizeof(int ) * n);
    u->size = (int *)malloc(sizeof(int ) * n);
    for(int i = 0; i < n; i++) {
        u->father[i] = i;
        u->size[i] = 1;
    }
    return u;
}

int find(UnionSet *u, int ind) {
    if(u->father[ind] == ind) return ind;
    return u->father[ind] = find(u, u->father[ind]);
}

void Union(UnionSet *u, int a, int b) {
    int father_a = find(u, a);
    int father_b = find(u, b);
    if(father_a == father_b) return ;
    if(father_a > father_b) {
        u->father[father_b] = father_a;
        u->size[father_a] += u->size[father_b];
    }
    else {
        u->father[father_a] = father_b;
        u->size[father_b] += u->size[father_a];
    }
    return ;
}

int jugdist(Node a, Node b, int r, int h) {
    if(a.z - r <= 0 && b.z - r <= 0) return 0;
    if(a.z + r >= h && b.z + r >= h) return 0;
    int dist = (a.x - b.x) * (a.x -b.x) + (a.y - b.y) * (a.y - b.y) 
        + (a.z - b.z) * (a.z - b.z)
    ;
    return dist - r * r * 4 > 0;
}


int main()
{
    int t, n, h, r;
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d%d", &n, &h, &r);
        Node *p = initn(n + 100);
       // printf("n == %d\n", n);
        //Node *p = (Node *)malloc(sizeof(Node ) * (n + 100));
        //Node p[10000];
        UnionSet *u = initu(n + 100);
        int start = n + 1, end = n + 2;
       // printf("Hello\n");
        for(int i = 0; i < n; i++) {
            scanf("%d%d%d", &(p[i].x), &(p[i].y), &(p[i].z));
            if(p[i].z <= r) {
                start = i;
            }
            if(p[i].z >= h - r) {
                end = i;
            }
        }
        printf("%d %d\n", start, end);
        fflush(stdout);
        // printf("IN\n");
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                if(jugdist(p[i], p[j], r, h)) continue;
                Union(u, i, j);
         //       printf("%d %d\n", i, j);
            }
        }
        if(find(u, start) == find(u, end)) {
            printf("Yes\n");
        }
        else {
            printf("No\n");
        }
    }
}
