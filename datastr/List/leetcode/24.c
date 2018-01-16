/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* swapPairs(struct ListNode* head) {
    if(head == NULL) return head;
    struct ListNode ret, *p, *tmp;
    ret.next = head;
    p = &ret;
    while(p->next != NULL && p->next->next != NULL) {
        tmp = p->next;
        p->next = tmp->next;
        tmp->next = tmp->next->next;
        p->next->next = tmp;
    }
    return ret.next;
}
