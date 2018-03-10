/*************************************************************************
	> File Name: trie1.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年02月02日 星期五 09时57分35秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct TrieNode {
    int flag;
    struct TrieNode *fail;
    struct TrieNode *next[26];
}TrieNode, *Trie;

typedef struct DoubleArratTrieNode {
    int n;
    int *base, *check;
} DoubleArratTrieNode, *DATrie;

DATrie init_DATrie(int n) {
    DoubleArratTrieNode *p = (DoubleArratTrieNode *)malloc(sizeof(DoubleArratTrieNode) * 1);
    p->base = (int *)malloc(sizeof(int ) * n);
    p->check = (int *)calloc(n, sizeof(int ));
    p->n = n; 
    p->check[1] = -1;
    return p;
}

TrieNode *getNewNode() {
    TrieNode *p = (TrieNode *)malloc(sizeof(TrieNode) * 1);
    p->flag = 0;
    p->fail =  NULL;
    for(int i = 0; i < 26; i++) {
        p->next[i] = NULL;
    }
    return p;
}
void clear(Trie tree) {
    if(tree == NULL) return ;
    for(int i = 0; i < 26; i++) {
        if(tree->next[i] != NULL) {
            clear(tree->next[i]);
        }
    }
    free(tree);
}

int insert(Trie tree, const char * str) {
    TrieNode * p = tree;
    int times = 0;
    while(str[0]) {
        if(p->next[str[0] - 'a'] == NULL) {
            p->next[str[0] - 'a'] = getNewNode();
            times++;
        }
        p = p->next[str[0] - 'a'];
        str++;
    }
    p->flag = 1;
    return times;
}
int search(Trie tree, const char *str) {
    TrieNode *p = tree;
    while(str[0] && p) {
        p = p->next[str[0] - 'a'];
        str++;
    }
    return p && p->flag;
}

int transToDATrie(Trie ftree, int ind, DATrie ttree) {
    int val = 0, flag = 1;
    int ret = ind;
    while(flag) {
        flag = 0;
        val += 1;
        for(int i = 0; i < 26; i++) {
            if(ftree->next[i] == NULL) continue;
            if(ttree->check[val + i] == 0) continue;
            flag = 1;
            break;
        }
    }
    if(ftree->flag) ttree->check[ind] = -ttree->check[ind];
    ttree->base[ind] = val;
    for(int  i = 0; i < 26; i++) {
        if(ftree->next[i] == NULL) continue;
        ttree->check[val + i] = ind;

    }
    for(int i = 0; i < 26; i++) {
        if(ftree->next[i] = NULL) continue;
        int tmp = transToDATrie(ftree->next[i], val + i, ttree);
        ret = (ret > tmp ? ret : tmp);
    }
    return ret;
}

void clearDATrie(DATrie tree) {
    if(tree == NULL) return ;
    free(tree->base);
    free(tree->check);
    free(tree);
    return ;
}

void build_automation(Trie tree, int n) {
    if(tree == NULL) return ;
    tree->fail = NULL;
    TrieNode **queue = (TrieNode **)malloc(sizeof(TrieNode *) * n);
    int head = 0, tail = 0;
    queue[tail ++] = tree;
    while(head < tail) {
        TrieNode *p = queue[head ++], *q;
        for(int i = 0; i < 26; i++) {
            if(p->next[i] == NULL) continue;
            q = p->fail;
            while(q != NULL && q->next[i] == NULL) {
                q = q->fail;
            }
            if(q == NULL) q = tree;
            p->next[i]->fail = q;
            queue[tail++] = p->next[i];
        }
    }
    
    free(queue);
}

int search_automation(Trie ac_tree, const char *str) {
    int ret = 0;
    TrieNode *p = ac_tree;
    while(str[0]) {
        while(p != NULL && p->next[str[0] -  'a'] == NULL) p = p->fail;
        if(p) p = p->next[str[0] - 'a'];
        else p = ac_tree;
        ret += p->flag;
        str++;
    }
    return ret;
}

int main()
{
    int n, m, node_cnt = 0;
    scanf("%d%d", &n, &m);
    char str[100];
    Trie tree = getNewNode();
    for(int i = 0 ; i < n; i++) {
        scanf("%s", str);
        node_cnt += insert(tree, str);
    }
    build_automation(tree, node_cnt);
    DATrie da_tree = init_DATrie(2 * node_cnt);
    int max_node_ind = transToDATrie(tree, 1, da_tree);
    for(int i = 1; i <= max_node_ind; i++) {
        printf("(%3d%3d%3d) ", i, da_tree->base[i],da_tree->check[i]);
        if(i % 6 == 0) printf("\n");
    }
    printf("\n");
    for(int i = 0; i < m; i++) {
        scanf("%s", str);
        printf("%s : %d \n",str, search(tree, str));
    }
    
}
