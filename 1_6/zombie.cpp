#include<stdio.h>
#include<stdlib.h>
#define maxsize 10000

typedef struct Zombie
{
    int hide;
    int blood;
}Zombie;

int cmp_blood(const void* e1, const void* e2)
{
	//本质是比较整形
	return ((Zombie *)e1)->blood - ((Zombie *)e2)->blood;
}

int main()
{
    int n,m,h,b;
    scanf("%d %d %d %d",&n,&m,&h,&b);
    int i,kzlen=0;
    Zombie zombie[maxsize];
    for(i=0;i<n;i++)
    {
        int x,y;
        scanf("%d %d",&x,&y);
        if(x<=h+b)
        {
            zombie[kzlen].hide=x;
            zombie[kzlen].blood=y;
            kzlen++;
        }
        
    }
    //int sz = sizeof(Zombie) /sizeof(Zombie[0]);
    qsort(zombie, kzlen, sizeof(zombie[0]), cmp_blood);

    i=0;
    int zonkill=0;
    while(m>=0 && i<kzlen)
    {
        m-=zombie[i].blood;
        zonkill++;
        i++;
    }
    if(m>=0)
    printf("%d",zonkill);
    else
    printf("%d",zonkill-1);
    return 0;
}