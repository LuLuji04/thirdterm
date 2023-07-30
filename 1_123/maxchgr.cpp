#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxsize 100

int main()
{
    long long m,n,num[maxsize][maxsize],output[2][2];
    scanf("%lld %lld",&m,&n);
    long long i,j;
    long long max=0;
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%lld",&num[i][j]);
        }    
    }
    for(i=0;i<m-1;i++)
    {
        for(j=0;j<n-1;j++)
        {
            long long tmp = num[i][j]*num[i+1][j]*num[i][j+1]*num[i+1][j+1];
            if(tmp > max)
            {
                max=tmp;
                output[0][0]=num[i][j];
                output[1][0]=num[i+1][j];
                output[0][1]=num[i][j+1];
                output[1][1]=num[i+1][j+1];
            }
        }    
    }
    printf("%lld\n",max);
    for(i=0;i<2;i++)
    {
        for(j=0;j<2;j++)
        {
            printf("%lld ",output[i][j]);
        }    
        printf("\n");
    }
    return 0;
}