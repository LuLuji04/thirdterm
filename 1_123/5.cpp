#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxsize 100

int main()
{
    int m,n,num[maxsize][maxsize];
    scanf("%d %d",&m,&n);
    int i,j;
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%d",&num[i][j]);
        }    
    }
    i=j=0;
    while(1)
    {
        while(i!=-1&&j!=n)
        {
            printf("%d ",num[i][j]);
            i--;
            j++;
        } 
          
        if(j==n)
        {
            i+=2;
            j--;
        }
        else if(i==-1)
            i++;

        while(j!=-1&&i!=m)
        {
            printf("%d ",num[i][j]);
            i++;
            j--;
        }
        if(i==m && j==n-2)
        return 0;  

         if(i==m)
        {
            i--;
            j+=2;
        }       
        else if(j==-1)
            j++;   
    }
    return 0;
}
