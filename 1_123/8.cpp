#include<stdio.h>
#define maxsize 100
int main()
{
    int n;
    char *list[maxsize]={0};
    scanf("%d",&n);
    while(n--)
    {
        int grade;
        char name[maxsize];
        scanf("%s",name);
        scanf("%d",&grade);
        list[grade-1]=name;
    }
    int i;
    for(i=99;i>=0;i--)
    {
        if(list[i]!=NULL)
            printf("%s\n",list[i]);
    }
    return 0;
}