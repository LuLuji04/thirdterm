#include<stdio.h>
#include<stdlib.h>

#define maxsize 100
typedef struct BTnode
{
    int data;
    struct BTnode *lchild; 
    struct BTnode *rchild; 
}BTnode;

BTnode* create()
{
    BTnode *add[maxsize]={0};
    int i,n,x,y;
    while(n--)
    {
        scanf("%d %d",&x,&y);
        if(add[x]==NULL)
        {
            BTnode *bt=(BTnode*)malloc(sizeof(BTnode));
            add[x]=bt;
        }
        if(add[y]==NULL)
        {
            BTnode *bt=(BTnode*)malloc(sizeof(BTnode));
            add[y]=bt;
        }
        
    }
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        BTnode *bt=create();
        
    }
}