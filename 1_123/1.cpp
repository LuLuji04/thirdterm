#include<stdio.h>
int main()
{
    int hour,minute,second,lastsecond,startsecond,endsecond;
    int h,m,s;
    scanf("%d %d %d %d",&hour,&minute,&second,&lastsecond);
    startsecond=second+minute*60+hour*60*60;
    endsecond=startsecond+lastsecond;
    s=endsecond%60;
    endsecond=endsecond/60;
    m=endsecond%60;
    endsecond=endsecond/60;
    h=endsecond%24;
    if(h==0)
        printf("%d:%d:%dam",12,m,s);
    else if(h>=1&&h<=11)
    {
        printf("%d:%d:%dam",h,m,s);
    }  
    else if(h==12)
    printf("%d:%d:%dpm",h,m,s);
    else if(h>=13&&h<=23)
    {
        h=h%12;
        printf("%d:%d:%dpm",h,m,s);
    }
    printf("\n%.2f%%",(float)lastsecond/(24*60*60)*100);
    return 0;
}