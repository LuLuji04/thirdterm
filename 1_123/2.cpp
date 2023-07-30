#include<stdio.h>
#include<string.h>
#define maxsize 20000
int main()
{
    char sentence[maxsize];
    gets(sentence);
    int i=0,j=0,lenth=0;
    
    while(sentence[i]!='\0')
    {
        while(sentence[i]!=' '&&sentence[i]!='\0')
            i++;
        
        j=i-1;
        while(sentence[j]!=' '&&j!=-1)
        {
            printf("%c",sentence[j]);
            j--;
        }
        i++;   
        
        printf(" ");
    }
    return 0;
}