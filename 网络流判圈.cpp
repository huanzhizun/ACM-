#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string.h>
#include<queue>
#define inf 100000000
#define LL long long
#define maxn 820
using namespace std;
struct pi
{
    int to;
    int cost;
    int rev;
}pp;
vector<pi >g[maxn];
queue<int>q;
int c[450][450];
int s,t;
int line[maxn],leve[maxn];
bool vis[452][452];
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
long long  dinic()
{
    int f;
    long long flow=0;
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
int main()
{
    int i,j,n,m,p,k,f,f1,f2;
    LL flow,s1,s2;
    while(scanf("%d%d%d",&n,&m,&k)!=EOF){
        for(i=0;i<=n+m+1;i++) g[i].clear();
        s1=0;
        s2=0;
        f=0;
        for(i=1;i<=n;i++){
            scanf("%d",&p);
            add(0,i,p);
            if(p>k*m||p<0){
                f=1;
            }
            s1+=p;
        }
        for(i=1;i<=m;i++){
            scanf("%d",&p);
            if(p>k*n||p<0){
                f=1;
            }
            add(n+i,n+m+1,p);
            s2+=p;
        }
        if(f){
            printf("Impossible\n");
            continue;
        }
        if(s1!=s2){
            printf("Impossible\n");
            continue;
        }
        for(i=1;i<=n;i++){
            for(j=1;j<=m;j++){
                add(i,n+j,k);
            }
        }
        s=0;
        t=n+m+1;
        flow=dinic();
        if(flow!=s1){
            printf("Impossible\n");
            continue;
        }
        for(i=1;i<=n;i++){
            p=(int)g[i].size();
            for(j=0;j<p;j++){
                pp=g[i][j];
                if(pp.to>n&&pp.to<=n+m)
                    c[i][pp.to-n]=pp.cost;//用残量网络判断是否含环
            }
        }
        memset(vis,0,sizeof(vis));//如果残量网络有两行全未达到极值说明图中流量不唯一，也就是说明图中含环
        int flag=0;
        for(i=1;i<=n;i++){
            for(j=1;j<=m;j++){
                for(p=j+1;p<=m;p++){
                    f1=0,f2=0;
                    if(c[i][j]!=0&&c[i][p]!=k){
                        if(vis[p][j]){
                            flag=1;
                            break;
                        }
                        f1=1;
                    }
                    if(flag) break;
                    if(c[i][j]!=k&&c[i][p]!=0){
                        if(vis[j][p]){
                            flag=1;
                            break;
                        }
                        f2=1;
                    }
                    if(f1) vis[j][p]=1;
                    if(f2) vis[p][j]=1;
                }
                if(flag) break;
            }
            if(flag) break;
        }
        if(flag){
            printf("Not Unique\n");
        }
        else{
            printf("Unique\n");
            for(i=1;i<=n;i++){
                for(j=1;j<=m;j++){
                    if(j==1){
                        printf("%d",k-c[i][j]);
                    }
                    else{
                        printf(" %d",k-c[i][j]);
                    }
                }
                printf("\n");
            }
        }
    }
}