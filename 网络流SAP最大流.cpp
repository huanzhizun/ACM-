#include <iostream>
#include <cstdio>
#include <climits>
#include <cstring>
#include <algorithm>
using namespace std;
typedef  struct {int v,next,val;} edge;
const int MAXN=20010;
const int MAXM=500010;
edge e[MAXM];
int p[MAXN],eid;
inline void init(){memset(p,-1,sizeof(p));eid=0;}
//有向
inline void insert1(int from,int to,int val)
{
    e[eid].v=to;e[eid].val=val;
    e[eid].next=p[from];
    p[from]=eid++;
    swap(from,to);
    e[eid].v=to;e[eid].val=0;
    e[eid].next=p[from];
    p[from]=eid++;
}
//无向
inline void insert2(int from,int to,int val)
{
    e[eid].v=to;e[eid].val=val;
    e[eid].next=p[from];
    p[from]=eid++;
    swap(from,to);
    e[eid].v=to;e[eid].val=val;
    e[eid].next=p[from];
    p[from]=eid++;
}
int n,m;//n为点数 m为边数，点标号从0到n-1
int h[MAXN];
int gap[MAXN];
int source,sink;
inline int dfs(int pos,int cost)
{
    if (pos==sink) return cost;
    
    int j,minh=n-1,lv=cost,d;
    for (j=p[pos];j!=-1;j=e[j].next)
    {
        int v=e[j].v,val=e[j].val;
        if(val>0)
        {
            if (h[v]+1==h[pos])
            {
                if (lv<e[j].val) d=lv;
                else d=e[j].val;
                
                d=dfs(v,d);
                e[j].val-=d;
                e[j^1].val+=d;
                lv-=d;
                if (h[source]>=n) return cost-lv;
                if (lv==0) break;
            }
            if (h[v]<minh)    minh=h[v];
        }
    }
    if (lv==cost)
    {
        --gap[h[pos]];
        if (gap[h[pos]]==0) h[source]=n;
        h[pos]=minh+1;
        ++gap[h[pos]];
    }
    return cost-lv;
}

int isap(int st,int ed)
{
    
    source=st;sink=ed;
    int ret=0;
    memset(gap,0,sizeof(gap));
    memset(h,0,sizeof(h));
    gap[st]=n;
    while (h[st]<n)
    {
        ret+=dfs(st,INT_MAX);
    }
    return ret;
}
int main()
{
    while(cin>>m>>n)
    {
        init();
        for(int i=0;i<m;i++)
        {
            int u,v,c;
            scanf("%d%d%d",&u,&v,&c);
            insert1(u,v,c);
        }
        printf("%d\n",isap(1,n));
    }
    return 0;
}