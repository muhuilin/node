#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;
}Node, *LinkedList;

LinkedList insert(LinkedList head, Node *node, int index) {
    if (head == NULL) {
        if (index != 0) {
            printf("failed\n");
            return head;
        }
        head = node;
        printf("success\n");
        return head;
    }
    if (index == 0) {
        node->next = head;
        head = node;
        printf("success\n");
        return head;
    }
    Node *current_node = head;
    int count = 0;
    while (current_node->next != NULL && count < index - 1) {
        current_node = current_node->next;
        count++;
    }
    if (count == index - 1) {
        node->next = current_node->next;
        current_node->next = node;
        printf("success\n");
        return head;
    }
    printf("failed\n");
    return head;
}

void output(LinkedList head) {
    if (head == NULL) {
        return;
    }
    Node *current_node = head;
    while (current_node != NULL) {
        printf("%d ", current_node->data);
        current_node = current_node->next;
    }
    printf("\n");
}

LinkedList delete_node(LinkedList head, int index) {
    if(index < 0) return head;
    index++;
    Node ret, *p;
    ret.next = head;
    p = &ret;
    while (index != 0 && p->next != NULL) {
        index--;
        p=p->next;
    }
    if (p->next != NULL) {
        Node *tmp = p->next;
        p->next = tmp->next;
        free(tmp);
        printf("success\n");
        return ret.next;
    }
    else {
        printf("failed\n");
        return head;
    }
}

LinkedList reverse(LinkedList head) {
    Node ret;
    ret.next = head;
    Node *current_node = head, *next_node;
    while (current_node->next != NULL) {
        next_node = current_node->next;
        current_node->next = next_node->next;
        next_node->next=ret.next;
        ret.next=next_node;
    }
    return ret.next;
}

void clear(LinkedList head) {
    Node *current_node = head;
    while (current_node != NULL) {
        Node *delete_node = current_node;
        current_node = current_node->next;
        free(delete_node);
    }
}

int main() {
    LinkedList linkedlist = NULL;
    int m;
    scanf("%d", &m);
    while(m--) {
        int t, a, b;
        scanf("%d", &t);
        if(t == 1) {
            scanf("%d%d", &a, &b);
            Node *node;
            node = (Node *)malloc(sizeof(Node));
            node->data = b;
            node->next = NULL;
            linkedlist = insert(linkedlist, node, a);
        }
        else if(t == 2) {
            output(linkedlist);
        }
        else if(t == 3) {
            scanf("%d", &a);  
            linkedlist = delete_node(linkedlist, a);
        }
        else {
            linkedlist = reverse(linkedlist);
            //output(linkedlist);
        }
    }
    clear(linkedlist);
    return 0;
}
