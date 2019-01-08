#include<stdio.h>
#include<algorithm>
#include<vector>
#define maxn 1000000
using namespace std;
int fa[maxn],lca[maxn];//lca[maxn]记录某条边的祖先值，而非节点
struct pi
{
    int to;
    int cost;
    int num;
}pp;
vector<pi>g[maxn];
vector<pi>gg[maxn];//输入待处理的值
int vis[maxn];
int find(int a)
{
    if(fa[a]==a)
        return a;
    return fa[a]=find(fa[a]);
}
void add(int a,int b,int cost)
{
    pp.to=b;
    pp.cost=cost;
    g[a].push_back(pp);
    pp.to=a;
    pp.cost=cost;
    g[b].push_back(pp);
}
void add1(int a,int b,int tot)
{
    pp.to=b;
    pp.num=tot;
    gg[a].push_back(pp);
    pp.to=a;
    pp.num=tot;
    gg[b].push_back(pp);
}
void LCA(int u)
{
    int k,i,p;
    k=gg[u].size();
    fa[u]=u;
    for(i=0;i<k;i++)
    {
        pp=gg[u][i];
        if(vis[pp.to])
        {
            lca[pp.num]=find(pp.to);//运用回溯，当正好回溯到一点时他的儿子节点的祖先为他，一层一层的往上回溯。
        }
    }
    vis[u]=1;
    k=g[u].size();
    for(i=0;i<k;i++)
    {
        pp=g[u][i];
        if(!vis[pp.to])
        {
            p=pp.to;
            LCA(p);
            fa[p]=u;
        }
    }
    return ;
}