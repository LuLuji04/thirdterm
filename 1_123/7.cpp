#include<stdio.h>
#include<string.h>
#define maxsize 100000
char a[maxsize],b[maxsize];
int judge (int as,int ae,int bs,int be)
{
    if(as==ae || bs==be)
    {
        if(a[as]==b[bs])
            return 1;
        else
            return 0;
    }
    //if( (ae-as+1)% 2==1 || (be-bs+1)%2 ==1 )
    //return 0;
    int l,r;
    l=judge(as,(as+ae)/2,bs,(bs+be)/2) && judge((as+ae)/2+1,ae,(bs+be)/2+1,be);
    r=judge(as,(as+ae)/2,(bs+be)/2+1,be) && judge((as+ae)/2+1,ae,bs,(bs+be)/2);
    return l||r;
}

int main()
{
    scanf("%s",a);
    scanf("%s",b);

    if(strlen(a)%2==1||strlen(b)%2==1)
    {
        printf("NO");
        return 0;
    }
    if(judge(0,strlen(a)-1,0,strlen(b)-1))
        printf("YES");
    else
        printf("NO");
    return 0;
}