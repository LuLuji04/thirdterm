#include<stdio.h>
#define maxsize 1000

int check(int num)
{
    while(num>0)
    {
        if(num%10==7)
        return 1;
        num/=10;
    }
    return 0;
}
int main()
{
    int n,m,t;
    scanf("%d %d %d",&n,&m,&t);
    int list[maxsize]={0};
    int idx=m,num=t,length=n;
    while(n>1)
    {
        if(list[idx]==-1)
        {
            idx++;
            continue;
        }
        if(idx==length+1)
            idx=1;
        else if(num%7==0 || check(num))
        {
            list[idx]=-1;
            num++;
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
    char name[maxsize];
    for(int i=1;i<=length;i++)
    {
        scanf("%s",name);
        if(list[i]!=-1)
        {
            printf("%s",name);
            return 0;
        }
        
    }

}