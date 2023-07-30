#include<stdio.h>
#include<stdlib.h>
#define maxsize 100000

typedef struct 
{
    char ch;
    long long idx;
}element;

typedef struct 
{
    long long top;
    element data[maxsize];
}stack;

void push(stack *st,char c,long long i)
{
    st->top++;
    (st->data[st->top]).ch=c;
    (st->data[st->top]).idx=i;
}
long long pop(stack *st,char *c,long long *i)
{
    if(st->top==-1)
    return 0;
    *c=st->data[st->top].ch;
    *i=st->data[st->top].idx;
    st->top--;
    return 1;
}
long long judge(long long  *output[maxsize],long long *length)
{
    stack *st;
    st=(stack *)malloc(sizeof(stack));
    st->top=-1;
    char bracket[maxsize];
    scanf("%s",bracket+1);

    

    long long i=1,j=0;
    while(bracket[i]!='\0')
    {
        switch (bracket[i])
        {
        case '(':
            push(st,bracket[i],i);
            break;

        case ')':
        {
            char tmpch;
            long long tmpidx;
            if(pop(st,&tmpch,&tmpidx)==0)
            return 0;
            long long  *tmp=(long long*)malloc(sizeof(long)*2);
            tmp[0]=tmpidx;
            tmp[1]=i;
            output[tmpidx-1]=tmp;
            //j++;
            break;
        }
            

        default:
            return 0;
            break;
        }
        i++;
    }

    if(st->top==-1)
    {
        *length=j;
        return 1;
    }
    
    else
    return 0;


}
long long main()
{
    long long *output[maxsize]={0};
    long long length;
    if(judge(output,&length))
    {
        printf("Yes\n");
        for (long long j=0;j<maxsize;j++)
        {
            if(output[j]!=0)
            printf("%d %d\n",output[j][0],output[j][1]);
        }
    }
    else
    printf("No");

    return 0;
}
