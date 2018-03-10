/*************************************************************************
	> File Name: doubleTrie.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年02月24日 星期六 11时04分18秒
 ************************************************************************/

#include "haffman.h"

typedef struct TrieNode {
    int flag;
    struct TrieNode *next[2];
}TrieNode, *Trie;

TrieNode *getTrienode() {
    TrieNode *p = (TrieNode *)malloc(sizeof(TrieNode) * 1);
    p->flag = 0;
    p->next[0] = p->next[1] = NULL;
    return p;
}

int inserttoTrie(Trie tree, const char *str, int *encode) {
    TrieNode *p = tree;
    printf("**************************\n");
    while(*str) {
        int val = encode[str[0]];
        int code[16], n = 0;
        printf("val = %d  :",val);
        while(val) {
            code[n++] = val % 2;
            val /= 2;
        }
        for(int i = n - 2; i >= 0; i--) {
            printf("%d", code[i]);
            if(p->next[code[i]] == NULL) {
                p->next[code[i]] = getTrienode();
            }
            p = p->next[code[i]];
        }
        printf("\n");
        p->flag = 1;
        str++;
    } 
    printf("**************************\n");
    p->flag = 2;
    return 1;
}

int search(Trie tree, const char *str, int *encode) {
    TrieNode *p = tree;
    printf("********************************\n");
    while(*str) {
        int val = encode[str[0]];
        int code[16], n = 0;
        printf("val = %d :", val);
        while(val) {
            code[n++] = val & 1;
            val >>= 1;
        }
        for(int i = n - 2; i >= 0; i--) {
            printf("%d", code[i]);
            if(p->next[code[i]] == NULL) {
                return 0;
            }
            p = p->next[code[i]];
        }
        printf("\n");
        str++;
    }
    printf("********************************\n");
    return p->flag == 2;
}

int main()
{
    Heap *heap = init(10000);
    char *str = (char *)malloc(sizeof(char ) * 10000);
    int *freq = (int *)calloc(256 , sizeof(int));
    int *hashtable = (int *)malloc(sizeof(int ) * 65536);
    int *encode = (int *)malloc(sizeof(int ) * 256);
    char *str1 = (char *)malloc(sizeof(char ) * 256);
    memset(encode, -1, sizeof(int ) * 256);
    memset(hashtable, -1, sizeof(int) * 65536);
    char *stra[20];
    for(int i = 0; i < 20; i++) {
        stra[i] = (char *)malloc(sizeof(char ) * 1000);
    }
    for(int times = 0; times < 3; times++) {
    scanf("%s", stra[times]);
        for(int j = 0; stra[times][j];j++) {
            printf("%d",(unsigned int)stra[times][j]);
        }
        printf("\n");
    printf("%s\n", stra[times]);
    for(int i = 0; stra[times][i]; i++) {
        freq[(unsigned int)stra[times][i]]++;
    }
    }
    for(int i = 0; i < 256; i++) {
        if(!freq[i]) continue;
        Node *p = getnewnode();
        p->data = (char)(i);
        p->val = freq[i];
        insert(heap, p);
    }
    Node *root;
    root = build(heap);
    printf("%p\n", root);
    getEncode(root, 1, 1, hashtable, encode, 0,str1);
    for(int i = 0; i < 256; i++) {
        if(i % 16 == 0) printf("\n");
        printf("%d ",encode[i]);
    }
    printf("\n");
    Trie tree = getTrienode();
    for(int i = 0; i < 3; i++) {
        inserttoTrie(tree, stra[i], encode);
    }
    for(int i = 0;i < 3; i++) {
        scanf("%s", str);
        printf("FIND : %d\n", search(tree,str, encode));
    }
    
}
