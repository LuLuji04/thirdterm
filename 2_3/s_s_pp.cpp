#include <stdio.h>
int l[30];
int sum, n;
int ok;
int vis[30];
void dfs(int id,int nowsum,int st) {
    if(ok==1)
    return ;
    if(id > 4)
    {
        ok=1;
        return;
    }
    for(int i=st;i<n;i++)
    {
        if(vis[i]==0)
        {
            vis[i]=1;
            if(nowsum+l[i]==sum)
            dfs(id+1,0,0);
            else
            dfs(id,nowsum+l[i],i+1);
            vis[i]=0;
        }
    }

}
int main() 
{
    scanf("%d", &n);
    sum = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &l[i]);
        sum += l[i];
    }
    ok = 0;
    if(sum%4!=0)
    {
        puts("No");
        return 0;
    }
    sum /= 4;
    dfs(1,0,0);
    if (ok) {
        puts("Yes");
    } else {
        puts("No");
    }
    return 0;
}