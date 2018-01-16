/*************************************************************************
	> File Name: danlianbiaodezhuanzhi.c
	> Author: 
	> Mail: 
	> Created Time: 2018年01月12日 星期五 19时12分25秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef struct Link {
    char data;
    struct Link *next;
} LinkNode, *LinkedList;

LinkNode *get_node(char c) {
    LinkNode *node = (LinkNode *)malloc(sizeof(LinkNode));
    node->data = c;
    node->next = NULL;
    return node;
}

LinkedList insert(LinkedList head, LinkNode *node) {
    LinkNode ret, *p;
    ret.next = head;
    p = &ret;
    while(p->next != NULL) {
        p = p->next;
    }
    p->next = node;
    return ret.next;
}

LinkedList delete_node(LinkedList head) {
    if (head == NULL) return head;
    LinkNode *p;
    p = head;
    head = head->next;
    free(p);
    return head;
}

void output(LinkedList head) {
    if(head == NULL) return ;
    LinkNode *p = head->next;
    printf("%c", head->data);
    while(p != NULL) {
        printf(" ");
        printf("%c",p->data);
        p = p->next;
        
    }
    printf("\n");
}

LinkedList rev(LinkedList head) {
    if(head == NULL) return head;
    LinkNode ret, *p;
    ret.next = head;
    while (head->next != NULL) {
        p = head->next;
        head->next = p->next;
        p->next = ret.next;
        ret.next = p;
    }
    return ret.next;
}

int main()
{
    LinkedList head = NULL;
    int n;
    scanf("%d", &n);
    char s[2];
    for(int i = 0; i < n; i++) {
        scanf("%s", s);
        head = insert(head, get_node(s[0]));
    }
    //output(head);
    head = rev(head);
    output(head);
}
