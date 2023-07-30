#include <stdio.h>
#include <string.h>
#include <math.h>
struct node {
    long long int x, y, z;
    int d;
} e[1000010],q[1000010];
int n, l, rear;
long long int h, r;
int vis[1000010];
long long int check(struct node a, struct node b){
	return 4*r*r-((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z));
}
int bfs(int u) {
    while (l < rear) {
        struct node now = q[l++];
        //printf("h-z=%d r=%lld\n",h-now.z,r);
        if (h-now.z <= r) {
            return now.d;
        }
        for (int i = 1; i <= n; i++) {
        	long long int tx,ty,tz;
        	//printf("1=%lld i=%d\n",check(e[i],now),vis[i]);
        	if(check(e[i],now) >= 0 && !vis[i]){
        		//printf("hh");
        		tx = e[i].x;
        		ty = e[i].y;
        		tz = e[i].z;
        		vis[tx] = 1;
        		//printf(" x-%d y-%d z-%d d-%d\n",tx,ty,tz, now.d);
        		struct node t = {tx, ty, tz, now.d + 1};
                //printf(" %d-%d \n",now.d+1,tx);
                q[rear++] = t;
			}
        }
    }
    return -1;
}
int main() {
	int number;
	scanf("%d",&number);
	for(int w=0; w < number; w++){
		memset(vis, 0, sizeof(vis));
        memset(e,0,sizeof(e));
	    scanf("%d %lld %lld", &n, &h, &r);
	    for (int i = 1; i <= n; i++) {
	        scanf("%lld %lld %lld", &e[i].x, &e[i].y, &e[i].z);
	    }
	    l = 0, rear = 0;
		for (int i = 1; i <= n; i++) {
		    if (!vis[i] && e[i].z <= r) {
		    	//printf("q");
		        struct node t = {e[i].x, e[i].y, e[i].z, 1};
			    q[rear++] = t;
			    vis[i]=1;
		    }
		}
	    printf("%d\n",bfs(1));
	}
	return 0;
}