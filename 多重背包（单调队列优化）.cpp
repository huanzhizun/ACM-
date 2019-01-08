#include<stdio.h>
#include<string.h>
#define MAXN 105
struct Queue
{
    int num,value;
}que[250005];
int head,tail;
int v[MAXN],w[MAXN],c[MAXN];
int dp[250005];
void enqueue (int x,int y)
{
    while (head<=tail && que[tail].value<y) tail--;
    que[++tail].num=x;que[tail].value=y;
}
int main()
{
    int i,j,d,sum,n,tempsum;
    while (scanf("%d",&n) && n>=0)
    {
        sum=0;
        for (i=1 ; i<=n ; ++i)
        {
            scanf("%d%d",&v[i],&c[i]);
            w[i]=v[i];
            sum+=w[i]*c[i];
        }
        tempsum=sum;
        sum/=2;
        for (i=1 ; i<=sum ; ++i) dp[i]=0;
        for (i=1 ; i<=n ; ++i)
        {
            if (c[i] > sum/w[i]) c[i]=sum/w[i];
            for (d=0 ; d<w[i] ; ++d)
            {
                head=1;tail=0;
                for (j=0 ; j<=(sum-d)/w[i] ; ++j)
                {
                    enqueue(j , dp[j*w[i]+d]-j*v[i]);
                    while (que[head].num<j-c[i] && head<=tail) head++;
                    dp[j*w[i]+d]=que[head].value+j*v[i];
                }
            }
        }
        printf("%d %d/n",tempsum-dp[sum],dp[sum]);
    }
    return 0;
}