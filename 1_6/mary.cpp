#include<stdio.h>
#include<stdlib.h>
#define maxsize 10000 

typedef struct Milk
{
    int price;
    int amount;
}Milk;

int cmp_price(const void* e1, const void* e2)
{
	//本质是比较整形
	return ((Milk *)e1)->price - ((Milk *)e2)->price;
}

int main()
{
    int N,M;
    scanf("%d %d",&N,&M);
    int i;
    Milk milk[maxsize];
    for(i=0;i<M;i++)
    {
        int p,x;
        scanf("%d %d",&p,&x);
        milk[i].price=p;
        milk[i].amount=x;
    }
    //int sz = sizeof(milk) /sizeof(milk[0]);
    qsort(milk, M, sizeof(milk[0]), cmp_price);
    
    int total=0;
    i=0;
    while(N>0 && i<M)
    {
        if(milk[i].amount<=N)
        {
            total+=milk[i].price * milk[i].amount;
            N-=milk[i].amount;
        }
        else
        {
            total+=milk[i].price * N;
            N-=N;
        }
        i++;
    }
    printf("%d",total);
}