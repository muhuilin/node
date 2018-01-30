/*************************************************************************
	> File Name: huffman.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年01月20日 星期六 19时57分00秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    char data;
    int freq;
    struct Node *lchild, *rchild;
}Node;

#define swap(x, y) { \
}

Node *build(Node *halfman_node, int n ) {
    #define hswap(x, y) { \
        swap
    }
    Node *root ;
    for(int  i = 0; i < n - 1; i++) {
        int ind1 = n - i - 1;
        int ind2 = n - i - 2;
        if(halfman_node[ind1].freq > halfman_node[ind2].freq) {
            hswap(ind1,ind2);
        }
        for(int j = 0; j < n -i - 2; j++) {
            if(halfman_node[j].freq < halfman_node[ind1].freq) {
                swap(halfman_node[ind1],halfman_node[ind2]);
                swap(halfman_node[j],halfman_node[ind1]);
            } else if(halfman_node[j].freq < halfman_node[ind2].freq) {
                hswap(j, ind2);
            }
        }
    root = (Node *) malloc(sizeof(Node ));
    root->data = 0;
    root->lchild = halfman_node[ind1];
    root->rchild = halfman_node[ind2];
    root->freq = halfman_node[ind1].freq + halfman_node[ind2].freq;
    halfman_node[ind2] = root;
    }
    return 
}

void getEncode(Node *root, int k, char *str) {
    if(root == NULL) return ;
    if(root->lchild == NULL) {
        printf("%c - > %s", root->dat, str);
        return ;
    }
    str[k] = '0'; 
    getEncode(root->lchild, k + 1, str);
    str[k] = '1';
    getEncode(root->rchild, k + 1, str);
    return;
}

int main() {
    char str[10];
    int freq;
    int n;
    scanf("%d", &n);
    Node **halfman_node = (Node **)malloc(sizeof(Node*) * n);

    for(int i = 0; i < n; i++) {
        scanf("%s%d", str, &freq);
        halfman_node[i].data = str[0];
        halfman_node[i].freq = freq;
    }
    Node *root = build(halfman_node, n);
    char encode[100];
    getEncode(root, 0 , encode);
}
