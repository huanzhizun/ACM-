#include <stdio.h>
#include <string.h>
#define MAX(a,b) ((a)>(b)?(a):(b))
#define NODE 3200010
#define N 100010
int n;
__int64 v[N];
__int64 node;
__int64 next[NODE][2];
__int64 end[NODE];
void add(__int64 cur,__int64 k)
{
    memset(next[node],0,sizeof(next[node]));
    end[node]=0;
    next[cur][k]=node++;
}
__int64 cal(__int64 x)
{
    int i;
    __int64 cur=0;
    __int64 k;
    for(i=32;i>=0;i--)
    {
        k=(((__int64)1<<i)&x)?0:1;
        if(next[cur][k]) cur=next[cur][k];
        else    cur=next[cur][1-k];
    }
    return (x^end[cur]);
}
int main()
{
    int  i,j,k,t,NN,m;
    __int64 cur ,p,x;
    scanf("%d",&t);
    NN=t;
    while(t--)
    {
        scanf("%d%d",&n,&m);
        node=1;
        memset(next[0],0,sizeof(next[0]));
        for(i=0;i<n;i++)
        {
            scanf("%I64d",&x);
            v[i]=x;
            cur=0;
            for(j=32;j>=0;j--)
            {
                k=(((__int64)1<<j)&x)?1:0;
                if(next[cur][k]==0) add(cur,k);
                cur=next[cur][k];
            }
            end[cur]=x;
        }
        printf("Case #%d:\n",NN-t);
        for(i=0;i<m;i++)
        {
            scanf("%I64d",&p);
            printf("%I64d\n",cal(p)^p);
        }
    }
    return 0;
}