
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define swap(a,b) {\
    __typeof(a) __temp = a;\
    a = b; b = __temp;\
}

typedef struct Node {
    unsigned char data;
    int val;
    struct Node *lchild, *rchild;
}Node, *Tree;

typedef struct Heap {
    Node **data;
    int n, size;
}Heap;

typedef struct TrieNode {
    int flag;
    struct TrieNode *next[2];
}TrieNode, *Trie;



Node *getnewnode() {
    Node * p = (Node *)malloc(sizeof(Node) * 1);
    p->data =  p->val = 0;
    p->lchild = p->rchild = NULL;
    return p;
}

Heap *init(int n) {
    Heap *h = (Heap *)malloc(sizeof(Heap) * 1);
    h->data = (Node **)malloc(sizeof(Node*) * n);
    h->n = 0;
    h->size;
    return h;
}

int insert(Heap *h, Node *p) {
    h->size += 1;
    h->data[h->size] = p;
    int loc = h->size, father = loc / 2;
    while(father > 0 && h->data[father]->val > h->data[loc]->val) {
        swap(h->data[father],h->data[loc]);
        loc = father;
        father = loc / 2;
    }
    return 1;
}

int pop(Heap *h) {
    swap(h->data[1],h->data[h->size]);
    h->size -= 1;
    int loc = 1;
    while(loc * 2 <= h->size) {
        int l = loc * 2;
        int r = l + 1;
        int pos = loc;
        if(l <= h->size && h->data[pos]->val > h->data[l]->val) {
            pos = l;
        }
        if(r <= h->size && h->data[pos]->val > h->data[r]->val) {
            pos = r;
        }
        if(pos == loc) break;
        swap(h->data[pos], h->data[loc]);
        loc = pos;
    }

} 

int empty(Heap *h) {
    return h->size == 0;
}

Node *top(Heap *h) {
    return h->data[1];
}

int heapsize(Heap *heap) {
    return heap->size;
}

Node *build(Heap *heap) {
    Node *root;
    while(heapsize(heap) > 1) {
        root = getnewnode();
        Node *tempa = top(heap);
        pop(heap);
        printf("l = %d ", tempa->val);
        root->lchild = tempa;
        //if(empty(heap)) continue;
        Node *tempb = top(heap);
        pop(heap);
        printf("r = %d size = %d\n", tempb->val, heap->size);
        root->rchild = tempb;
        root->val = tempa->val + tempb->val;
        insert(heap, root);
    }
    root = top(heap);
    pop(heap);
    return root;
}

void getEncode(Node *root, int k, int m,  int *hashtable, int *encode, int now, unsigned char * str) {
    if(root == NULL) return ;
    //printf("%p %p\n",root->lchild, root->rchild);
    printf("aa = %d %d\n", k,root->data);
    if(root->lchild == NULL) {
        printf("%c %d\n", root->data, k);
        str[now] = '\0';
        printf("%s\n", str);
        hashtable[k] = root->data;
        encode[root->data] = k;
        return ;
    }
    //printf("AAA\n");
    str[now] = '0';
    getEncode(root->lchild, k * 2, m, hashtable,  encode, now + 1, str);
    str[now] = '1';
    getEncode(root->rchild, k * 2 + 1, m , hashtable, encode,now + 1,  str);
    return ;
}


TrieNode *getTrienode() {
    TrieNode *p = (TrieNode *)malloc(sizeof(TrieNode) * 1);
    p->flag = 0;
    p->next[0] = p->next[1] = NULL;
    return p;
}

int inserttoTrie(Trie tree, const unsigned char *str, int *encode) {
    TrieNode *p = tree;
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
    p->flag = 2;
    return 1;
}

int search(Trie tree, const unsigned char *str, int *encode) {
    TrieNode *p = tree;
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
    return p->flag == 2;
}

int main()
{
    Heap *heap = init(10000);
    unsigned char *str = (unsigned char *)malloc(sizeof(unsigned char ) * 10000);
    int *freq = (int *)calloc(256 , sizeof(int));
    int *hashtable = (int *)malloc(sizeof(int ) * 65536);
    int *encode = (int *)malloc(sizeof(int ) * 256);
    unsigned char *str1 = (unsigned char *)malloc(sizeof(unsigned char ) * 256);
    memset(encode, -1, sizeof(int ) * 256);
    memset(hashtable, -1, sizeof(int) * 65536);
    unsigned char *stra[20];
    for(int i = 0; i < 20; i++) {
        stra[i] = (unsigned char *)malloc(sizeof(unsigned char ) * 1000);
    }
    for(int times = 0; times < 3; times++) {
    scanf("%s", stra[times]);
        for(int j = 0; stra[times][j];j++) {
            printf("%d ",stra[times][j]);
        }
        printf("\n");
    printf("%s\n", stra[times]);
    for(int i = 0; stra[times][i]; i++) {
        freq[stra[times][i]]++;
    }
    }
    for(int i = 0; i < 256; i++) {
        if(!freq[i]) continue;
        Node *p = getnewnode();
        p->data = (i);
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
