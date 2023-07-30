#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxsize 100000

typedef struct 
{
    long long top,now;
    char *data[maxsize];
}stack;

void visit(stack *st,char* web)
{
    st->now++;
    st->data[st->now]=web;
    st->top=st->now;
}
int forward(stack *st,char** web)
{
    if(st->now==st->top)
    return 0;
    st->now++;
    *web=st->data[st->now];
    return 1;
}

int back(stack *st,char **web)
{
    if(st->now==0||st->now==-1)
    return 0;
    st->now--;
    *web=st->data[st->now];
    
    return 1;
}

int main()
{
    stack *st;
    st=(stack *)malloc(sizeof(stack));
    st->top=-1;
    st->now=-1;
    long long n;
    scanf("%lld",&n);
    while(n>0)
    {
        char op[10];
        scanf("%s",op);
        if(strcmp(op,"VISIT")==0)
        {
            char *web=(char *)malloc(sizeof(char)*100);
            scanf("%s",web);
            printf("%s\n",web);
            visit(st,web);
        }
        else if(strcmp(op,"FORWARD")==0)
        {
            char *tmp;
            if(forward(st,&tmp)==0)
            printf("Ignore\n");
            else
            printf("%s\n",tmp);
        }
        else if(strcmp(op,"BACK")==0)
        {
            char *tmp;
            if(back(st,&tmp)==0)
            printf("Ignore\n");
            else
            printf("%s\n",tmp);
        }

        n--;
    }
    return 0;
}