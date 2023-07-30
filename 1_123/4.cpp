#include<stdio.h>
int distance(int year,int month)
{
    int intervel,y,m;
    intervel=(year-1900)*365+(month-1)*30;
    for(y=1900;y<year;y++){
        if((y%400==0)||((y%4==0)&&(y%100!=0)))
        intervel+=1;
    }
    for(m=1;m<month;m++){
        if(m==1||m==3||m==5||m==7||m==8||m==10||m==12)
            intervel+=1;
        if(m==2)
            intervel-=2;
        if((year%400==0)||((year%4==0)&&(year%100!=0))&&(m==2))
            intervel+=1;
    }
    //printf("%d\n",intervel);
    return intervel%7+1;
}
int date(int a,int year,int month,int day)
{
    int i,j,d=30;
    if(month==1||month==3||month==5||month==7||month==8||month==10||month==12)
        d+=1;
    if(month==2)
        d-=2;
    if((year%400==0)||((year%4==0)&&(year%100!=0))&&(month==2))
        d+=1;
    if(year<1900||month>12||day>d){
        printf("error");
        return 0;
    }
    printf(" SUN MON TUE WED THU FRI SAT\n");
    for(i=1;i<=d;i++)
    {
        if(i<a+1)
            printf("    ");
        else
            break;
    }    
    for(j=1;j<=d;j++)
    {
        if(j==day)
            printf("%3d*",j);
        else
            printf("%4d",j);
        if(j%7==(7-a))
        printf("\n");              
    }
}
int main()
{
    int year,month,day,a,b;
    scanf("%d %d %d",&year,&month,&day);
    if((year%400==0)||((year%4==0)&&(year%100!=0)))
    {
        if(month==2)
    }

    printf("闰年\n");
    a=distance(year,month);
    date(a,year,month,day);
    //printf("%d",a);
    return 0;
}