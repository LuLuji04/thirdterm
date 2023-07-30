#include<stdio.h>
#include<stdlib.h>
#define maxsize 100010

typedef struct Line
{
    long long l;
    long long r;
}Line;

int cmp_r(const void* e1, const void* e2)
{
	//本质是比较整形
	return ((Line *)e1)->r - ((Line *)e2)->r;
}

int main()
{
    long long n;
    scanf("%lld",&n);
    long long i;
    Line line[n];
    for(i=0;i<n;i++)
    {
        long long x,y;
        scanf("%lld %lld",&x,&y);
        line[i].l=x;
        line[i].r=y;
    }
    //long long sz = sizeof(Line) /sizeof(Line[0]);
    qsort(line, n, sizeof(line[0]), cmp_r);
    long long left=0,top=0;
    for(i=0;i<n;i++)
    {
        if(line[i].l>=top)
        {
            left++;
            top=line[i].r;
        }
    }
    printf("%lld",left);
    return 0;
}