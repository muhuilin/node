/*************************************************************************
	> File Name: xunhuanlianbiaobianshuangxiang.c
	> Author: 
	> Mail: 
	> Created Time: 2018年01月12日 星期五 23时01分02秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef struct Link {
    int data;
    struct Link *pre, *next;
}LinkNode, *LinkedList;

LinkNode * get_node(int val) {
    LinkNode * node = (LinkNode *)malloc(sizeof(LinkNode) * 1);
    node->next = NULL;
    node->data = val;
    return node;
}

LinkedList insert(LinkedList head,LinkNode *node) {
    if(head == NULL) head = node;
    node->next = head->next;
    head->next = node;
    node->pre = head;
    node->next->pre = node;
    return node;
}

void output(LinkedList head, int m) {
    if(head == NULL) return ;
    LinkNode *p = head->next;
    while(p != head) {
        if(p->data == m) break;
        p = p->next;
    }
    head = p->next;
    while(p != head) {
        printf("%d ", p->data);
        p = p->pre;
    }
    printf("%d\n",head->data);
    return;
    
}

int main()
{
    LinkedList head = NULL;
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int tmp ;
        scanf("%d", &tmp);
        head = insert(head, get_node(tmp));
    }
    int m;
    scanf("%d", &m);
    output(head,m);
}
