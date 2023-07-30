#include <stdio.h>
int l[30];
int sum, n;
int ok;
void dfs(int id, int l1, int l2, int l3,int l4) {
    if(ok==1)
    return ;
    if (id == n) {
        if (l1 == sum && l2 == sum && l3 == sum && l4 == sum) {
            ok = 1;
        }
        return;
    }
    if(l1>sum||l2>sum||l3>sum||l4>sum)
    return;
    dfs(id + 1, l1 + l[id], l2, l3, l4);
    dfs(id + 1, l1, l2 + l[id], l3, l4);
    dfs(id + 1, l1, l2, l3 + l[id], l4);
    dfs(id + 1, l1, l2, l3 ,l4 + l[id]);
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
    dfs(0, 0, 0, 0,0);
    if (ok) {
        puts("Yes");
    } else {
        puts("No");
    }
    return 0;
}