/*************************************************************************
	> File Name: linklist.c
	> Author: 
	> Mail: 
	> Created Time: 2018年01月11日 星期四 18时55分25秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef struct LinkNode {
    int data;
    struct LinkNode *next;
}LinkNode, *Linkedlist;

LinkNode *get_node(int val) {
    LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode) * 1);
    p->data = val;
    p->next = NULL;
    return p;
}

Linkedlist insert(Linkedlist head, int val, int ind) {
    if (ind < 0) return head;
    LinkNode ret , *p;
    ret.next = head;
    p = &ret; /// 申请一个前置节点 以后ind == 多少就走几步
    while (ind != 0 && p != NULL) {
        ind--;
        p = p->next;
    }
    if (p == NULL) return head;
    LinkNode *new_node = get_node(val);
    new_node->next = p->next;
    p->next = new_node;
    return ret.next;
}

Linkedlist delete_node(Linkedlist head, int ind) {
    if (ind < 0) return head;
    LinkNode ret , *p;
    ret.next = head;
    p = &ret;
    while (ind != 0 && p->next != NULL) {
        ind--;
        p = p->next;
    }
    if (p->next == NULL) return head; ///p 指的是要删除节点的上一个节点
    LinkNode *node = p->next;
    p->next = p->next->next;
    free(node);
    return ret.next;
}

void clear(Linkedlist head) {
    Linkedlist p = head , q;
    while (p != NULL) {
        q = p;
        p = p->next;
        free(q);
    }
    return ;
}

void output(Linkedlist head) {
    Linkedlist p = head;
    while (p != NULL) {
        printf("%d -> ", p->data);
        p = p->next;
    }
    return ;
}

int main()
{
    Linkedlist head = NULL;
    int op, val, ind;
    while (scanf("%d", &op) != EOF) {
        if( op == 1 ) {
            scanf("%d%d", &val, &ind);
            head = insert(head, val, ind);
        }
        else {
            scanf("%d", &ind);
            head = delete_node(head, ind);
            
        }
        output(head);
    }
}
