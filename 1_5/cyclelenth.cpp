#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int val;
    struct Node *next;
} ListNode;
/**
 * 已经定义的 ListNode 结点
 * typedef struct Node {
 *     int val;
 *     struct Node *next;
 * } ListNode;
 */
int linkedListCycleLength(ListNode *head) {
    ListNode *p=head,*q=head->next;
    while(p!=q && p!=NULL && q!=NULL&&q->next!=NULL)
    {
        p=p->next;
        q=q->next->next;
    }
    if(p==NULL || q==NULL || q->next==NULL)
        return 0;
    p=p->next;
    q=q->next->next;
    int plen=1,qlen=2;
    while(p!=q)
    {
        p=p->next;
        plen++;
        q=q->next->next;
        qlen+=2;
    }
    return qlen-plen;
}
/*
10
15 22 17 29 3 8 1 8 22 28
11

*/
int main() {
    int n;
    scanf("%d", &n);
    ListNode *head = (ListNode*)malloc(sizeof(ListNode));
    head->val = 0;
    head->next = NULL;
    ListNode *temp = head;
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        temp->next = (ListNode*)malloc(sizeof(ListNode));
        temp->next->val = x;
        temp->next->next = NULL;
        temp = temp->next;
    }
    int d;
    scanf("%d", &d);
    ListNode *Nth = head;
    while (d--) {
        Nth = Nth->next;
    }
    temp->next = Nth;
    temp = head;
    head = head->next;
    free(temp);
    printf("%d\n", linkedListCycleLength(head));
    return 0;
}