#include<stdio.h>
#include<stdlib.h>

#define maxsize 110
int main()
{
    int n,i,j;
    int a[maxsize][maxsize];
    scanf("%d",&n);
    for (i=0;i<n;i++)
    {
        for (j=0;j<n;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    for (i=0;i<n;i++)
    {
        for (j=0;j<n;j++)
        {
            if(a[i][j]<a[j][i])
                a[i][j]=a[j][i];

            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    return 0;
}
