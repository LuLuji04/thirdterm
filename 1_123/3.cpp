#include<stdio.h>
int main()
{
    int n;
    char a;
    scanf("%d",&n);
    //getchar();
    char max;
    scanf(" %c",&max);
    for(int i=1;i<n;i++)
    {
        scanf(" %c",&a);
         if(a>max)
            max=a;
    }
    printf("%c",max+1);
    return 0;
}