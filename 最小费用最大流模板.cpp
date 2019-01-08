#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<iostream>
#include<vector>
#include<queue>
#include<queue>
#define inf 1000000000
#define maxn 10005
using namespace std;
struct pi
{
    int to;
    int cap;
    int cost;
    int rev;
};
vector<pi>g[maxn];
int dis[maxn];
int pre[maxn],pree[maxn];
int sink,source;
int vis[maxn];
int a[maxn];
char c[maxn];
void add(int a,int b,int cap,int cost)
{
    pi pp;
    pp.to=b;
    pp.cap=cap;
    pp.cost=cost;
    pp.rev=(int)g[b].size();
    g[a].push_back(pp);
    pp.to=a;
    pp.cap=0;
    pp.cost=-cost;
    pp.rev=(int)g[a].size()-1;
    g[b].push_back(pp);
    return ;
}
int spfa(void)
{
    int i,p,k;
    memset(dis,0x3f ,sizeof(dis));
    memset(vis,0,sizeof(vis));
    memset(pre,-1,sizeof(pre));
    memset(pree,-1,sizeof(pree));
    dis[source]=0;
    vis[source]=1;
    queue<int>q;
    pi pp;
    q.push(source);
    while(!q.empty())
    {
        p=q.front();
        k=(int)g[p].size();
        q.pop();
        vis[p]=0;
        if(p==sink)
            continue;
        for(i=0;i<k;i++)
        {
            pp=g[p][i];
            if(pp.cap>0&&dis[pp.to]>dis[p]+pp.cost)
            {
                dis[pp.to]=dis[p]+pp.cost;
                pre[pp.to]=p;
                pree[pp.to]=i;
                if(!vis[pp.to])
                {
                    q.push(pp.to);
                    vis[pp.to]=1;
                }
            }
        }
    }
    return pre[sink]!=-1;
}
int min(int a,int b)
{
    int p;
    p=a;
    if(b<a)
        p=b;
    return p;
}
int minflow(void)
{
    int i,f;
    int res=0;
    while(spfa())
    {
        f=inf;
        for(i=sink;i!=source;i=pre[i])
        {
            f=min(f,g[pre[i]][pree[i]].cap);
        }
        res+=f*dis[sink];
        for(i=sink;i!=source;i=pre[i])
        {
            pi &e=g[pre[i]][pree[i]];
            e.cap-=f;
            g[i][e.rev].cap+=f;
        }
    }
    return res;
}
