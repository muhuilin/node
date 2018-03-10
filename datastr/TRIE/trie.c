/*************************************************************************
	> File Name: trie.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年02月06日 星期二 11时28分58秒
 ************************************************************************/
// 在已有一棵字典树的情况下构造双数组字典树

    
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct TrieNode {
    int flag;
    int loc;
    struct TrieNode *next[26];
} TrieNode, *Trie;

typedef struct DoubleArrayTrieNode {
    int n;
    int *base, *check;
}DoubleArrayTrieNode, *DATrie;

TrieNode *getnode();
int insert(Trie, const char *);
int search(Trie, const char *);

DATrie init_DATrie(int n) {
    n = 100;
    DATrie tree = (DATrie)malloc(sizeof(DoubleArrayTrieNode) * 1);
    tree->base = (int *)malloc(sizeof(int ) * n * 2);
    tree->check = (int *)malloc(sizeof(int ) * n * 2);
    memset(tree->base, 0 ,sizeof(int) * n * 2);
    memset(tree->check, 0 , sizeof(int) * n * 2);
    tree->check[1] = 1;
    return tree;
}

int insert_DATrie(DATrie ftree, Trie ttree) {
    int n = 100;
    TrieNode **q = (TrieNode **)malloc(sizeof(TrieNode *) * (100 + 1));
    int tail = 1, head = 0;
    ttree->loc = 1;
    int ret = 0;
    q[0] = ttree;
    while(tail > head) {
       // printf("%d\n",head);
        TrieNode *p = q[head++];
        if(p->flag == 1) { 
            ftree->check[p->loc] *= -1;
        }
        int x = 0;
        for(int i = 1; i < n; i++) {
            int flag = 0;
            for(int j = 0; j < 26; j++) {
                if(p->next[j] == NULL) continue;
                if(ftree->check[i + j] == 0) continue;
                flag = 1; break;
            }
            if(flag == 0) {
                printf("jinlaile\n");
                x = i;
                break;
            }
        }
        int flag = 0;
        for(int i = 0; i < 26; i++) {
            if(p->next[i] == NULL) continue;
            p->next[i]->loc = x + i;
            ftree->check[x + i] = p->loc;
            q[tail++] = p->next[i];
            if(x + i > ret ) ret = x + i;
            flag = 1;
        }
        if(flag) ftree->base[p->loc] = x;
    }
    return ret;
    
}

int transToDATrie(Trie tree, int ind, DATrie ftree) {
    int flag = 1, val = 0;
    while(flag) {
        flag = 0;
        val += 1;
        for(int i = 0; i < 26; i++) {
            if(tree->next[i] == NULL) continue;
            if(ftree->check[val + i] == 0) continue;
            flag = 1;
            break;
        }
    }
    if(tree->flag) ftree->check[ind] *= -1;
    for(int i = 0; i < 26; i++) {
        if(tree->next[i] == NULL) continue;
        ftree->check[val + i] = ind;
    }
    int ret = ind;
    for(int i = 0; i < 26; i++) {
        if(tree->next[i] == NULL) continue;
        int tmp = transToDATrie(tree->next[i], val + i, ftree);
        ret = (ret > tmp ? ret : tmp);
    }
    if(ret == ind) ftree->base[ind] = val;
    return ret;
}


int main()
{
    char * str = (char *)malloc(sizeof(char ) * 100);
    Trie tree = getnode();

    int n, m;
    int nodesum = 0;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) {
        scanf("%s", str);
        nodesum += insert(tree, str);
    }
    DATrie ftree = init_DATrie(nodesum);
    //int ret  = insert_DATrie(ftree,tree);
    int ret = transToDATrie(tree, 1, ftree);
    for(int i = 1; i <= ret + 5; i++) {
        
        printf("%3d%3d%3d, ",i, ftree->base[i], ftree->check[i]);
        if(i % 6 == 0) printf("\n");
    }
    printf("\n");
   /* for(int i = 0; i < m; i++) {
        scanf("%s", str);
        printf("%s = %d \n", str, search(tree, str));
    }*/
}

TrieNode *getnode() {
    TrieNode * p = (TrieNode *)malloc(sizeof(TrieNode) * 1);
    p->flag = 0;
    p->loc = 0;
    for(int i = 0; i < 26; i++) {
        p->next[i] = NULL;
    }
    return p;
}

int insert(Trie tree, const char *str) {
    TrieNode *p = tree;
    int sum = 0;
    while(str[0]) {
        if(p->next[str[0] - 'a'] == NULL) {
            p->next[str[0] - 'a'] = getnode();
            sum++;
        }
        p = p->next[str[0] - 'a'];
        str++;
    }
    p->flag = 1;
    return sum;
}
int search(Trie tree, const char *str) {
    TrieNode * p = tree;
    while(str[0]) {
        //printf("%c\n", str[0]);
        if(p->next[str[0] - 'a'] == NULL) return 0;
        //printf("%c ", str[0]);
        p = p->next[str[0] - 'a'];
        str++;
    } 
    printf("\n");
    return p->flag;
}

