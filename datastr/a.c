#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Trie {
     int data;
     int flag;
     struct Trie *child;
     struct Trie* next;
     int sum_child;
} Trie;


Trie* init(int val) {
     Trie* tree = (Trie*)malloc(sizeof(Trie));
     tree->data = val;
     tree->flag = 0;
     tree->child = NULL;
     tree->next = NULL;
     tree->sum_child = 0;
}

void insert(Trie* tree, char* str) {
     Trie* p = tree;
     while(str[0]) {
         //printf("+++++++++++\n");
         int ind = (int)str[0];
         if(p->child == NULL) p->child = init(ind);
         else {
             if(p->child->data == ind) p = p->child;
             else {
                 Trie* tmp = p->child;
                 while(p->next && p->next->data != ind) {
                     p = p->next;
                 }
                 if(p->next == NULL) {
                     p->next = init(ind);
                     tmp->sum_child += 1;
                 }
                 p = p->next;
             }
         }
         str++;
     }
     p->flag = 1;
}


void build(Trie* tree) {
     Trie* p = tree->child;
     while(p) {
         while(p && p->child == NULL) {
			printf("+%c\n", p->data); 
             p = p->next;
         }
         if(p == NULL) break;
         Trie* next_hang = p->child;
         Trie* q = p->next;
         while(q && q->child == NULL) {
             q = q->next;
         }
         if(q == NULL) {
             p->next = next_hang;
             p = next_hang;
             continue;
         }
         else {
             Trie* tmpp = p->child;
             while(tmpp && tmpp->next) {
                 tmpp = tmpp->next;
             }
             tmpp->next = q->child;
             p = q;
         }
     }
}


void output(Trie* tree) {
     Trie* p = tree->child;
     while(p) {
         printf("%c\n", p->data);
         p = p->next;
     }
     return;
}

int main()
{
     Trie* tree = init(0);
     int n;
     char ss[100];
     scanf("%d", &n);
     for(int i = 0; i < n; i++) {
         memset(ss, 0, sizeof(ss));
         scanf("%s", ss);
         insert(tree, ss);
     }
     build(tree);
     printf("*********************\n");
     output(tree);
}

