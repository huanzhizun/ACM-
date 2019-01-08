#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string.h>
#include<queue>
#define maxn 1005
#define inf 100000000
using namespace std;
struct pi
{
    int to;
    int cost;
    int rev;
}pp;
vector<pi >g[maxn];
queue<int>q;
int s,t;
int line[maxn],leve[maxn];
int min(int a,int b)
{
    int p;
    p=a;
    if(b<a)
        p=b;
    return p;
}
void add(int a,int b,int cos)
{
    pp.to=b;
    pp.cost=cos;
    pp.rev=(int)g[b].size();
    g[a].push_back(pp);
    pp.to=a;
    pp.cost=0;
    pp.rev=(int)g[a].size()-1;
    g[b].push_back(pp);
    return ;
}
void bfs(void)
{
    q.push(s);
    int p,f,i;
    while(!q.empty())
    {
        p=q.front();
        q.pop();
        f=(int)g[p].size();
        for(i=0;i<f;i++)
        {
            pi &e=g[p][i];
            if(e.cost>0&&line[e.to]<0)
            {
                line[e.to]=line[p]+1;
                q.push(e.to);
            }
        }
    }
    return ;
}
int dfs(int v,int f)
{
    int p;
    if(v==t)
        return f;
    for(int &i=leve[v];i<g[v].size();i++)
    {
        pi &e=g[v][i];
        if(line[v]<line[e.to]&&e.cost>0)
        {
            p=dfs(e.to,min(f,e.cost));
            if(p>0)
            {
                e.cost-=p;
                g[e.to][e.rev].cost+=p;
                return p;
            }
        }
    }
    return 0;
}
int  dinic()
{
    int f;
    int flow=0;
    while(1)
    {
        memset(line,-1,sizeof(line));
        memset(leve,0,sizeof(leve));
        line[s]=0;
        bfs();
        if(line[t]<0)
            return flow;
        f=dfs(s,inf);
        if(f==0)
            continue;
        flow+=f;
        while((f=dfs(s,inf))>0)
        {
            flow+=f;
        }
    }
}
