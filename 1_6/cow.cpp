#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxsize 1010

int main()
{
    int i,n;
    scanf("%d",&n);
    int ol=0,el=0,a;
    for(i=0;i<n;i++)
    {
        scanf("%d",&a);
        if(a%2==1)
            ol++;
        else
            el++;
    }
    int l,gnum;
    if(ol>el)
    {
        l=ol-el;
        gnum=2*el;
        gnum += (l/3)*2;
        l = l%3;
        switch (l)
        {
        case 1:
            gnum--;
            break;
        case 2:
            gnum++;
        default:
            break;
        }
    }
    else if(ol<el)
    {
        l=el-ol;
        gnum=2*ol+1;
    }
    else
    {
        gnum=ol;
    }
    printf("%d",gnum);
}