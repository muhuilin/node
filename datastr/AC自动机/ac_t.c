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
    struct TrieNode *fail;
    struct TrieNode *next[26];
} TrieNode, *Trie;

typedef struct DoubleArrayTrieNode {
    int n;
    int *base, *check, *fail;
}DoubleArrayTrieNode, *DATrie;

TrieNode *getnode();
int insert(Trie, const char *);
int search(Trie, const char *);

DATrie init_DATrie(int n) {
    n = 100;
    DATrie tree = (DATrie)malloc(sizeof(DoubleArrayTrieNode) * 1);
    tree->base = (int *)malloc(sizeof(int ) * n * 2);
    tree->check = (int *)malloc(sizeof(int ) * n * 2);
    tree->fail = (int *)calloc(n * 2, sizeof(int));
    memset(tree->base, 0 ,sizeof(int) * n * 2);
    memset(tree->check, 0 , sizeof(int) * n * 2);
    tree->check[1] = -1; //为什么要这么写？原来写的是1是错的 因为check 1作为根节点会造成不知道是 第一次找到根节点 还是在根节点里面循环了 
 /// 二次 注： 上一个注释是错了 错在 误把check当作fail进行转移
    // check 设置成 1 是最合理的 因为在寻找经过多少个点的时候 省去一步判断 check 1 在之后的操作中 永远不会访问到 
    // 原因是 要想访问到 有两种情况 1 要对他赋值 因为已经有值了 不可以 
    // 2 是 查看 1 号节点的
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
    ftree->base[ind] = val;
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
    return ret;
}

int build_actree(Trie tree, int sum) {
    TrieNode **queue = (TrieNode **)malloc(sizeof(TrieNode*) * (sum + 5));
    int head = 0, tail = 1;
    queue[0] = tree;
    printf("Lalala\n");
    while(head < tail) {
       // printf("%d %d  \n", head, tail);
        TrieNode *q = queue[head++];
        for(int i = 0; i < 26; i++) {
            if(q->next[i] == NULL) continue;
            printf("%c ",'a' + i);
            TrieNode * p = q->fail;
            while(p != NULL && p->next[i] == NULL) p = p->fail;
            if(p  == NULL) p = tree;
            else p = p->next[i];
            q->next[i]->fail = p;
            queue[tail++] = q->next[i];
        }
    }
    free(queue);
    return 1;
}
int build_acdatree(DATrie tree, int sum) {
    //printf("Jinlaile\n");
    int *queue = (int *)malloc(sizeof(int ) * (sum + 5));
    int head = 0, tail = 0;
    queue[tail++] = 1;
    while(head < tail) {
       // printf(" a  %d %d\n", head, tail);
        int p = queue[head++];
        for(int i = 0; i < 26; i++) {
            int val = tree->base[p];
            if(abs(tree->check[val + i]) != p) continue;
         //   printf("%d ",val + i);
            int q = tree->fail[p];
            while(q  && abs(tree->check[tree->base[q] + i]) != q ) q = tree->fail[q];
            if(q == 0) q = 1;
            else q = tree->base[q] + i;
            //printf("%d %d\n",p, q);
            tree->fail[val + i] = q;
            queue[tail++] = val + i;
        }
        
    }
    printf("OUT\n");
    return 1;
}

int search_acdatree(DATrie tree, const char *str) {
    int ret = 0, p = 1;
    while(str[0]) {
        printf("%c \n", str[0]);
        while(p  && abs(tree->check[tree->base[p] + str[0] - 'a']) != p) p = tree->fail[p];
        if(p == 0) p = 1;
        else p = tree->base[p] + str[0] - 'a';
        int q = p;
        printf("%d\n", q);
        while(q != 0) ret += tree->check[q] < 0 && q != 1, q = tree->fail[q];
        str++;
    }
    return ret;
}

int search_ac(Trie tree, const char *str) {
    TrieNode *q = tree, *p;
    int ret = 0;
    while(str[0]) {
        printf("%c ",str[0]);
        while(q != NULL && q->next[str[0] - 'a'] == NULL) q = q->fail;
        if(q == NULL)  {
            q = tree;
            continue;
        }
        q = q->next[str[0] - 'a'];
        p = q;
        while(p != NULL) ret += p->flag, p = p->fail;
        str++;
    }
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
    //build_actree(tree, 100);
    DATrie ftree = init_DATrie(nodesum);
    //int ret  = insert_DATrie(ftree,tree);
    int ret = transToDATrie(tree, 1, ftree);
    build_acdatree(ftree, 100);
    for(int i = 1; i <= ret + 5; i++) {
        
        printf("%3d%3d%3d%3d, ",i, ftree->base[i], ftree->check[i], ftree->fail[i]);
        if(i % 6 == 0) printf("\n");
    }
    printf("\n");
    for(int i = 0; i < m; i++) {
        scanf("%s", str);
        printf("%s = %d \n", str, search_acdatree(ftree, str));
    }
}

TrieNode *getnode() {
    TrieNode * p = (TrieNode *)malloc(sizeof(TrieNode) * 1);
    p->flag = 0;
    p->loc = 0;
    p->fail = NULL;
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

