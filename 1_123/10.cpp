#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxsize 100
typedef struct
{
    int grade;
    char *name;
}stu;
int main()
{
    int n,i,j;
    stu *list[maxsize];
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        list[i]=(stu*)malloc(sizeof(stu));
        char *s;
        s=(char *)malloc(sizeof(char)*maxsize);
        scanf("%s",s);
        list[i]->name=s;
        scanf("%d",&list[i]->grade);
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(list[j]->grade<list[j+1]->grade || 
            list[j]->grade==list[j+1]->grade && strcmp(list[j]->name,list[j+1]->name)>0)
            {
                stu *tmp=list[j+1];
                list[j+1]=list[j];
                list[j]=tmp;
            }
               
        }
    }
    for(i=0;i<n;i++)
    {
            printf("%s %d\n",list[i]->name,list[i]->grade);
    }
    return 0;
}