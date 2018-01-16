/*************************************************************************
	> File Name: nagetongxue.c
	> Author: 
	> Mail: 
	> Created Time: 2018年01月12日 星期五 16时24分47秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef struct Link {
    int data;
    struct Link *next;
} *LinkedList, LinkNode;

LinkNode * get_node(int val) {
    LinkNode *node = (LinkNode *)malloc(sizeof(LinkNode) * 1);
    node->next = NULL;
    node->data = val;
    return node;
}

LinkedList insert(LinkedList head, int ind, LinkNode *node) {
    if(ind < 0) return head;
    LinkNode ret;
    ret.next = head;
    int cur = 0;
    LinkNode *p = &ret;
    while(ind != 0 && p != NULL) {
        p = p->next;
        ind--;
    }
    if ( p == NULL) {
        return head;
    }
    node->next = p->next;
    p->next = node;
    return ret.next;
}

LinkedList delete_node(LinkedList head, int ind ) {
    if(ind < 0) return head;
    LinkNode ret;
    ret.next = head;
    int cur = 0;
    LinkNode *p = &ret;
    while(ind != 0 && p != NULL) {
        p = p->next;
        ind--;
    }
    if(p == NULL) {
        return head;
    }
    LinkNode * tmpnode = p->next;
    p->next = tmpnode->next;
    free(tmpnode);
    return ret.next;
}

void output(LinkedList head, int ind) {
    if (head == NULL) return ;
    LinkNode *p = head;
    while(p != NULL && ind != 0) {
        ind--;
        p = p->next;
    }
    if(p == NULL) return ;
    printf("%d\n", p->data);
    return ;
}

void output1(LinkedList head) {
    if (head == NULL) return ;
    LinkNode *p = head;
    while(p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
    return ;
}
int main()
{
    LinkedList head = NULL; ///////竟然不可避免 因为否则初始的next就没有指向空了
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) {
        LinkNode *node = get_node(i + 1);
        head = insert(head, i, node);
    }
    for(int i = 0; i < m; i++) {
        int tmp;
        scanf("%d", &tmp);
        head = delete_node(head, tmp - 1);
    }
    output(head, (n - m) / 2);
}
