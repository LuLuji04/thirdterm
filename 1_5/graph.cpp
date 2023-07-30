#include<stdio.h>
#include<stdlib.h>
#define maxsize 10001
typedef struct node
{
    int data;
    struct node *next;
}node; 

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    node *head[maxsize];
    for(int i=1;i<=n;i++)
    {
        head[i]=(node*)malloc(sizeof(node));
        head[i]->next=NULL;
    }
    
    node *tail[maxsize]={0};
    for(int i=1;i<=n;i++)
    {
        tail[i]=head[i];
    }
    int idx,data;
    while(m>0)
    {
        scanf("%d %d",&idx,&data);
        node *newp=(node*)malloc(sizeof(node));
        newp->data=data;
        newp->next=NULL;
        tail[idx]->next=newp;
        tail[idx]=newp;
        m--;
    }
    for(int i=1;i<=n;i++)
    {
        node *p=head[i]->next;
 
        while(p!=NULL)
        {
            printf("%d ",p->data);
            p=p->next;
        } 
        printf("\n");

    }
    return 0;
}