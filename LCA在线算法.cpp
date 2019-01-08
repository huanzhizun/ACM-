#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string.h>
#define max 400005
using namespace std;
int deap[max],vis[max],dis[max],kk[32][max];
int maxlog;
struct pi
{
    int to;
    int cost;
}pp;
vector<pi>g[max];
void init(int v,int p,int d)
{
    vis[v]=1;
    deap[v]=d;
    int i,k;
     kk[0][v]=p;
    for(i=1;i<maxlog;i++)
    {
        if(kk[i-1][v]<0)
            kk[i][v]=-1;
        else
        {
            kk[i][v]=kk[i-1][kk[i-1][v]];
        }
    }
    k=g[v].size();
    for(i=0;i<k;i++)
    {
        if(!vis[g[v][i].to])
        {
            dis[g[v][i].to]=dis[v]+g[v][i].cost;
            init(g[v][i].to,v,d+1);
        }
    }
    return ;
}
int find(int a,int b)
{
    if(deap[a]>deap[b])
        swap(a,b);
    int i,f;
    f=deap[b]-deap[a];
    for(i=0;i<maxlog;i++)
    {
        if((f>>i)&1)
            b=kk[i][b];
    }
    if(b==a)
        return a;
    for(i=maxlog-1;i>=0;i--)
    {
        if(kk[i][a]!=kk[i][b])
        {
            a=kk[i][a];
            b=kk[i][b];
        }
    }
    return kk[0][a];
}
int solve(int a,int b)
{
    int f;
    f=find(a,b);
    return dis[a]+dis[b]-2*dis[f];
}