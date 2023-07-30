#include <stdio.h>
#include <math.h>
#define EPSILON 1e-7

float f(float x,float a)
{
    return x+log(x)-a;
}
    

float fp(float x,float a)
{
    return 1+1/x;
}
    
int main()
{
    float a,x;
    scanf("%f",&a);
    x=0.5;
    while(fabs(f(x,a))>EPSILON)
    {
         x=x-f(x,a)/fp(x,a);
    }
    printf("%f",x);
}