/*************************************************************************
   > File Name: 13.trie.cpp
   > Author: hug
   > Mail:   hug@haizeix.com
   > Created Time: 五  2/ 2 09:56:06 2018
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TrieNode {
    int flag;
    struct TrieNode *next[26];
} TrieNode, *Trie;

typedef struct DoubleArrayTrieNode {
    int n;
    int *base, *check;
} DoubleArrayTrieNode, *DATrie;

DATrie initDATrie(int n) {
    DATrie p = (DATrie)malloc(sizeof(DoubleArrayTrieNode) * 1);
    p->base = (int *)calloc(n, sizeof(int));
    p->check = (int *)calloc(n, sizeof(int));
    p->n = n;
    p->check[1] = -1;
    return p; 
}

TrieNode *getNewNode() {
    TrieNode *p = (TrieNode *)malloc(sizeof(TrieNode) * 1);
    p->flag = 0;
    for (int i = 0; i < 26; i++) {
        p->next[i] = NULL;
    }
    return p;
}

int insert(Trie tree, const char *str) {
    TrieNode *p = tree;
    int times = 0;
    while (str[0]) {
        if (p->next[str[0] - 'a'] == NULL) {
            p->next[str[0] - 'a'] = getNewNode();
            times += 1;
        }
        p = p->next[str[0] - 'a'];
        str++;
    }
    p->flag = 1;
    return times;
}

int search(Trie tree, const char *str) {
    TrieNode *p = tree;
    while (str[0] && p) {
        p = p->next[str[0] - 'a'];
        str++;
    }
    return p && p->flag;
}

int transToDATrie(Trie ftree, int ind, DATrie ttree) {
    int val = 0, flag = 1, ret = ind;
    while (flag) {
        flag = 0;
        val += 1;
        for (int i = 0; i < 26; i++) {
            if (ftree->next[i] == NULL) continue;
            if (ttree->check[val + i] == 0) continue;
            flag = 1;
            break;
        }
    }
    if (ftree->flag) ttree->check[ind] = -ttree->check[ind];
    ttree->base[ind] = val;
    for (int i = 0; i < 26; i++) {
        if (ftree->next[i] == NULL) continue;
        ttree->check[val + i] = ind;
    }
    for (int i = 0; i < 26; i++) {
        if (ftree->next[i] == NULL) continue;
        int temp = transToDATrie(ftree->next[i], val + i, ttree);
        ret = (ret > temp ? ret : temp);
    }
    return ret;
}

int search_DATrie(DATrie tree, const char *str) {
    int p = 1;
    while(str[0]) {
        int val = tree->base[p];
        if(abs(tree->check[val + str[0] - 'a']) != p) return 0;
        p = val + str[0] - 'a';
        str++;
    }
    
    return tree->check[p] < 0;
}

void clear(Trie tree) {
    if (tree == NULL) return ;
    for (int i = 0; i < 26; i++) {
        if (tree->next[i] == NULL) continue;
        clear(tree->next[i]);
    }
    free(tree);
    return ;
}

void clearDATrie(DATrie tree) {
    if (tree == NULL) return ;
    free(tree->base);
    free(tree->check);
    free(tree);
    return ;
}

int main() {
    int n, m, node_cnt = 0;
    char str[100];
    Trie tree = getNewNode();
    scanf("%d%d", &n, &m);
    while (n--) {
        scanf("%s", str);
        node_cnt += insert(tree, str);
    }
    DATrie da_tree = initDATrie(2 * (26 + node_cnt));
    int max_node_ind = transToDATrie(tree, 1, da_tree);
    for (int i = 1; i <= max_node_ind; i++) {
        printf("(%3d%3d%3d) ", i, da_tree->base[i], da_tree->check[i]);
        if (i % 6 == 0) printf("\n");
    }
    printf("\n");
    while (m--) {
        scanf("%s", str);
        printf("%d : %s\n", search_DATrie(da_tree, str), str);
    }   
    clear(tree);
    clearDATrie(da_tree);
    return 0;
}

