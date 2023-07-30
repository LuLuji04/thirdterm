#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1005

typedef struct node {
    struct node* front;
    char name[25];
    int id;
    struct node* late;
}Node;


int is_lucky(int num); // 判断是否是幸运数字

int main() {
    int n, m, t;
    scanf("%d %d %d", &n, &m, &t);
    Node *x[n];
    x[0] = (Node *)malloc(sizeof(Node));
    for (int i = 1; i < n-1; i++) 
    { // 构建循环链表
        x[i] = (Node *)malloc(sizeof(Node));
        scanf("%s",x[i] -> name);
        x[i] -> id = i;
        x[i] -> front = x[i - 1];

        x[i] -> late = x[i + 1];
    }
    x[n - 1] -> front = x[n-2];
    x[n - 1] -> late = x[0];
    x[0] -> late = x[1];
    x[0] -> front = x[n - 1];
    Node *p = x[m - 1];
    int count = n;
    while (count > 3)
    {
        if (is_lucky(t))
        {
            p -> front -> late = p -> late;
            p -> late -> front = p -> front;
            count--;
            p = p -> late;
        }
        else
        {
            p = p -> late;
        }
        t++;
        if(p==p->late)
        break;
    }
    
    printf("%s", p -> name);
    return 0;
}

int is_lucky(int num) {
    if (num % 7 == 0 ) { 
        return 1;
    }
    while (num>0)
    {
        if(num % 10 == 7)
        return 1;
        num = num / 10;
    }
        return 0;
    
}