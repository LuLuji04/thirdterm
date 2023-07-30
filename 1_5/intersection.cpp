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
ListNode* findIntersectionListNode(ListNode *head1, ListNode *head2) {
    ListNode *p=head1,*q=head2;
    int plen=0,qlen=0;
    while(p!=NULL)
    {
        p=p->next;
        plen++;
    } 
    while(q!=NULL)
    {
        q=q->next;
        qlen++;
    }
        
    p=head1;
    q=head2;
    int n=0;
    if(plen>qlen)
    {
        while(n++ < plen-qlen)
        {
            p=p->next;
        }
    }
    else if(plen<qlen)
    {
        while(n++ < qlen-plen)
        {
            q=q->next;
        }
    }
    while(p!=q && p!=NULL && q!=NULL)
    {
        p=p->next;
        q=q->next;
    }
    if(p==q)
        return p;
    else
        return NULL;
}
int main() {
    int n, m, x;
    scanf("%d %d %d", &n, &m, &x);
    ListNode *head = (ListNode*)malloc(sizeof(ListNode));
    head->val = 0;
    head->next = NULL;
    ListNode *temp = head;
    ListNode *ans = NULL;
    for (int i = 0; i < n; ++i) {
        temp->next = (ListNode*)malloc(sizeof(ListNode));
        temp->next->val = 0;
        temp->next->next = NULL;
        temp = temp->next;
        if (i == x) {
            ans = temp;
        }
    }
    temp = head;
    head = head->next;
    free(temp);
    ListNode *head2 = (ListNode*)malloc(sizeof(ListNode));
    head2->val = 0;
    head2->next = NULL;
    temp = head2;
    for (int i = 0; i < m; ++i) {
        temp->next = (ListNode*)malloc(sizeof(ListNode));
        temp->next->val = 0;
        temp->next->next = NULL;
        temp = temp->next;
    }
    temp->next = ans;
    temp = head2;
    head2 = head2->next;
    free(temp);
    temp = findIntersectionListNode(head, head2);
    if(temp == ans) {
        printf("Accept\n");
    } else {
        printf("Wrong answer\n");
    }
    return 0;
}