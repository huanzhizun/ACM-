/*
 我们假设k<j<i。如果在j的时候决策要比在k的时候决策好，那么也是就是dp[j]+M+(sum[i]-sum[j])^2<dp[k]+M+(sum[i]-sum[k])^2。(因为是最小花费嘛，所以优就是小于)
 
 两边移项一下，得到：(dp[j]+num[j]^2-(dp[k]+num[k]^2))/(2*(num[j]-num[k]))<sum[i]。我们把dp[j]-num[j]^2看做是yj，把2*num[j]看成是xj。
 
 那么不就是yj-yk/xj-xk<sum[i]么？   左边是不是斜率的表示？
 
 那么yj-yk/xj-xk<sum[i]说明了什么呢？  我们前面是不是假设j的决策比k的决策要好才得到这个表示的？ 如果是的话，那么就说明g[j,k]=yj-jk/xj-xk<sum[i]代表这j的决策比k的决策要更优。
 
 
 
 关键的来了：现在从左到右，还是设k<j<i，如果g[i,j]<g[j,k]，那么j点便永远不可能成为最优解，可以直接将它踢出我们的最优解集。为什么呢？
 
 我们假设g[i,j]<sum[i]，那么就是说i点要比j点优，排除j点。
 
 如果g[i,j]>=sum[i]，那么j点此时是比i点要更优，但是同时g[j,k]>g[i,j]>sum[i]。这说明还有k点会比j点更优，同样排除j点。
 
 排除多余的点，这便是一种优化！
 
 
 
 接下来看看如何找最优解。
 
 设k<j<i。
 
 由于我们排除了g[i,j]<=g[j,k]的情况，所以整个有效点集呈现一种上凸性质，即k j的斜率要大于j i的斜率。
 
 
 
 这样，从左到右，斜率之间就是单调递减的了。当我们的最优解取得在j点的时候，那么k点不可能再取得比j点更优的解了，于是k点也可以排除。换句话说，j点之前的点全部不可能再比j点更优了，可以全部从解集中排除。
 
 于是对于这题我们对于斜率优化做法可以总结如下：
 
 1，用一个单调队列来维护解集。
 
 2，假设队列中从头到尾已经有元素a b c。那么当d要入队的时候，我们维护队列的上凸性质，即如果g[d,c]<g[c,b]，那么就将c点删除。直到找到g[d,x]>=g[x,y]为止，并将d点加入在该位置中。
 
 3，求解时候，从队头开始，如果已有元素a b c，当i点要求解时，如果g[b,a]<sum[i]，那么说明b点比a点更优，a点可以排除，于是a出队。最后dp[i]=getDp(q[head])。
 
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef int LL;
LL a[500005];
LL dp[500005];
int q[500005];
LL s[500005];
LL get1(int n,int m){
    return dp[n]-dp[m]+s[n]*s[n]-s[m]*s[m];
}
LL get2(int n,int m){
    return s[n]-s[m];
}
int main()
{
    int i,n,m,tear,rear;
    while(scanf("%d%d",&n,&m)!=EOF){
        s[0]=0;
        dp[0]=0;
        for(i=1;i<=n;i++){
            scanf("%d",&a[i]);
            s[i]=s[i-1]+a[i];
        }
        rear=0;
        tear=0;
        q[tear++]=0;
        for(i=1;i<=n;i++){
            while(rear+1<tear){
                if(get1(q[rear+1],q[rear])<=2*s[i]*get2(q[rear+1],q[rear])) rear++;
                else break;
            }
            dp[i]=dp[q[rear]]+(s[i]-s[q[rear]])*(s[i]-s[q[rear]])+m;
            while(tear>rear+1){
                if(get1(i,q[tear-1])*get2(q[tear-1],q[tear-2])<=get1(q[tear-1],q[tear-2])*get2(i,q[tear-1])) tear--;
                else break;
            }
            q[tear++]=i;
        }
        printf("%d\n",dp[n]);
    }
}