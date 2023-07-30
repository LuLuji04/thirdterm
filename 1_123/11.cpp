#include<stdio.h>
#define maxsize 10000 
int main()
{
    unsigned int A;
    scanf("%lu",&A);
    int num[maxsize];
    while(A!=0)
    {
        int idx=0;
        while(A>0)
        {
            num[idx++] = A % 2;
            if(A % 2 == 1)
                break;
            A =A >> 1;
        }
        int A2=0;
        idx--;
        for(;idx>=0;idx--)
        {
            A2 = A2*2 + num[idx];
        }
        printf("%u\n",A2);
        scanf("%lu",&A);
    }
    
    return 0;
}