/*************************************************************************
	> File Name: 19.c
	> Author: 
	> Mail: 
	> Created Time: 2018年01月13日 星期六 00时13分41秒
 ************************************************************************/

#include<stdio.h>
struct ListNode {
int val;
ListNode *next;
ListNode(int x) : val(x), next(NULL) {}
};
ListNode* removeNthFromEnd(ListNode* head, int n) {
    if(n <= 0) return head;
    ListNode ret, *p;
    ret.next = head;
    p = &ret;
    int cnt = 0;
    while(p->next != NULL) {
        cnt++;
        p = p->next;
    }
    int ind = cnt - n;
    p = &ret;
    while(ind != 0 && p->next != NULL) {
        ind--;
        p = p->next;
    }
    ListNode *del = p->next;
    p->next = del->next;
    free(del);
    return ret.next;
}
