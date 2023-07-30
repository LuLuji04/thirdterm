#include<stdio.h>
#include<string.h>
#define maxsize 100

void judge(char *input)
{
    char output[maxsize]={0};
    int i=0,j=0,k;
    //char *p=input,*q=output;
    int start=0;
    if(input[0]=='\\'||input[0]=='/')
    {
        start=1;
        output[0]='/';
        i++;
        j++;
    }
    while(i<strlen(input))
    {
        switch (input[i])
        {
        case '/':
        case '\\':
            if((output[j-1]!='/'&&output[j-1]!='\\')&&input[i+1]!='\0')
            {
                output[j]='/';
                j++;
            }  
            break;
        case '.':
            if(input[i+1]=='.')
            {
                int flag=0;
                j--;
                if(j==0||j==-1)
                {
                    printf("Value Error\n");
                    return;
                }
                while(j>0)
                {   
                    if(output[j-1]=='/')
                    {
                        flag=1;
                        break;
                    }
                    j--;
                }
                /*if(flag==0&&input[i+2]!='/')
                {
                    
                }*/
            }
            i++;
            break;
        default:
            output[j]=input[i];
            j++;
            break;
        }
        i++;
    }
    if(start==0&&output[0]=='/')
    {
        for(k=0;k<j;k++)
        output[k]=output[k+1];

        j--;
    }
    
    if(j>1&&output[j-1]=='/')
    j--;

    output[j]='\0';
    printf("%s\n",output);
    
    
}
int main()
{
    char input[maxsize],output[maxsize];
    while(scanf("%s",input)!=EOF)
    {
        judge(input);
    //char *p=input,*q=output;
    }
    return 0;
}
/*./jisuanke\\./suantou/../bin/
..
/\./\.\/
1/../2
/1/../2
/1/2/3/../4/../..
..
/..
1/../..
/1/../..
/
.
/.
1/..
1/../
/1/..
/1/../*/