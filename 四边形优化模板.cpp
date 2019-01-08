/*
对于dp[i][j]=dp[i][k]+d[k][j]+w[i][j]的dp方程，如果满足w[i][j]+w[i'][j']<=w[i'][j]+w[i][j']    (i'<=i<=j<=j')则w[i][j]是凸的，也就是说，对于dp[i][j]的决策s[i][j],必然满足不等式s[i][j-1]<=s[i][j]<=s[i+1][j].所以求决策时只需要循环从s[i][j-1]到s[i+1][j]就行，然后求s[i][j],注意循环长度。
 区间dp一般用四边形优化
 */
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[1005][1005];
int s[1005][1005];
struct pi{
    int x;
    int y;
}pp[1005];
int main()
{
    int i,j,n,m,k;
    while(scanf("%d",&n)!=EOF){
        memset(dp,0x3f,sizeof(dp));
        memset(s,0,sizeof(s));
        for(i=1;i<=n;i++) {scanf("%d%d",&pp[i].x,&pp[i].y);
            s[i][i]=i;
            dp[i][i]=0;
        }
        for(i=1;i<=n-1;i++){//四边形优化一定要优化长度
            for(j=1;j+i<=n;j++){
                for(k=s[j][j+i-1];k<=s[j+1][j+i];k++){
                    m=pp[k].y-pp[j+i].y+pp[k+1].x-pp[j].x;
                    if(dp[j][j+i]>dp[j][k]+dp[k+1][j+i]+m){
                        dp[j][j+i]=dp[j][k]+dp[k+1][j+i]+m;
                        s[j][j+i]=k;
                    }
                }
            }
        }
        printf("%d\n",dp[1][n]);
    }
}