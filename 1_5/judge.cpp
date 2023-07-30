#include<stdio.h>
#define maxsize 10
int com(long long x)
{
    if(x==1||x==2)
        return 1;
    long long i;
    for(i=2;i<=x/2;i++)
    {
        if(x%i==0)
            return 1;
    }
    return 0;
}
int round(long long x)
{
    int num[maxsize],i=0;
    while(x>0)
    {
        num[i]=x%10;
        x/=10;
        i++;
    }
    long long j=i-1;
    i=0;
    while(i<j)
    {
        if(num[i]!=num[j])
            return 0;

        i--;
        j++;
    }
    return 1;
}

int main()
{
    long long n;
    scanf("%lld",&n);
    long long i,op,x,numyes=0;
    for(i=0;i<n;i++)
    {
        scanf("%lld %lld",&op,&x);
        switch(op)
        {
               case 1:
                if(com(x))
                    numyes++;

                break;
            case 2:
                if(round(x))
                    numyes++;

                break;
            case 3:
                if(com(x)==1&&round(x)==1)
                    numyes++;

                break;
            default:
            break; 
        }
            
    }
    printf("%lld",numyes);
    return 0;
}