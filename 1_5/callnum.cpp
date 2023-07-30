#include<stdio.h>
#define maxsize 1000

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int list[maxsize]={0};
    int idx=1,num=1,length=n;
    while(n>1)
    {
        if(list[idx]==-1)
        {
            idx++;
            continue;
        }
        if(idx==length+1)
            idx=1;
        else if(num==m)
        {
            list[idx]=-1;
            num=1;
            idx++;
            n--;
        }
        else 
        {
            list[idx]=num;
            num++;
            idx++;
        }
    }

    for(int i=1;i<=length;i++)
    {
        if(list[i]!=-1)
        {
            printf("%d",i);
            return 0;
        }
        
    }
    
}