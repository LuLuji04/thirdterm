#include <stdio.h>
#include<string.h>
#include "run.h"

int main()
{
	const char *name_program = "./program";
	const char *name_in = "./in.txt";
	const char *name_out = "./out.txt";
	const char *name_right = "./right.txt";
	run(name_program, name_in, name_out);
	FILE *fpright = fopen(name_right, "r");
	FILE *fpout = fopen(name_out, "r");

	// Input your code here.
    run(name_program,name_in,name_out);
    char buf1[2000],buf2[2000];
    memset(buf1,'\0',2000);
    memset(buf2,'\0',2000);
    fread(buf1,1,2000,fpright);
    fread(buf2,1,2000,fpout);
    int k=0,count=0;
    
    int len1,len2;
    len1=strlen(buf1);
    len2=strlen(buf2);
    
    if(len1-len2 >1 || len2-len1 > 1)
    {
        printf("Wrong Answer");
        fclose(fpout);
	    fclose(fpright);
	    return 0;
    }
    
    while(buf1[k] !='\0' && buf2[k] != '\0')
    {
        if(buf1[k]!=buf2[k])
        {
            count++;
        }
        k++;
    }
    if(count>=2)
    {
        printf("Wrong Answer");
        fclose(fpout);
	    fclose(fpright);
	    return 0;
    }
    else if(count==1)
    {
        if((buf1[k-1]=='\n' && buf2[k-1]=='\0') || (buf2[k-1]=='\n' && buf1[k-1]=='\0'))
        {
            printf("Accept");
            fclose(fpout);
	        fclose(fpright);
	        return 0;
        }
        else
        {
            printf("Wrong Answer");
        fclose(fpout);
	    fclose(fpright);
	    return 0;
        }
    }
    else
    {
        printf("Accept");
        fclose(fpout);
	    fclose(fpright);
	    return 0;
    }
}
