/*一种方法是 添加附加源汇S,T  对于某点 u, 设 M(u)=sigma(B[i,u])-sigma(B[u,j]) ，
 则根据流量平衡条件有 M(u)同时等于 sigma(g[u,j])-sigma(g[i,u])
 若M(u)<0，即sigma(g[u,j]) < sigma(g[i,u]) 进入u的流量比从u 出去的多，
 所以 u -> T 连容量为  -(sigma(B[i,u])-sigma(B[u,j]) ) 的边
 同理. M(u)>0时，即 S->u 连容量为 sigma(B[i,u])-sigma(B[u,j])  的边.
 然后再 对于任意边(i,u)/(u,j) 连一条 C[u,v]-B[u,v]的边.
 这样 只需对新的网络求一遍最大流即可. 若出附加源点的边都满流即是存在可行流，反之不然.
 满流的必要条件是显然的. 不满流不能保证加上B[,]后流量平衡. 前面都白费了
 
 
 S->v 容量 B[u,v]   ,  u->T 容量 B[u,v]  ， u->v 容量 C[u,v]-B[u,v]
 可以这样理解，边S->v : 求的时候直接从S流过来的流量值B[u,v], 与最终解中边(u,v)强制加上的从 u流过来的流量B[u,v]，对v点的流量平衡条件的影响 实质等价.
 边u->T同理.
 最后，一样也是求一下新网络的最大流，判断从附加源点的边，是否都满流即可.
 
*/
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string.h>
#include<queue>
#define LL int
#define inf 100000000
#define maxn 1500
using namespace std;
struct pi
{
    int to;
    int cost;
    int rev;
    int id;
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
void add(int a,int b,int cos,int id)
{
    pp.to=b;
    pp.cost=cos;
    pp.id=id;
    pp.rev=(int)g[b].size();
    g[a].push_back(pp);
    pp.to=a;
    pp.cost=0;
    pp.id=-1;
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
LL  dinic()
{
    int f;
    LL flow=0;
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
int a[20005];
struct ppi{
    int x;
    int y;
    int co1;
    int co2;
}pp1[100005];
int main()
{
    int i,j,n,m,p,k,f,q;
    s=0;
    while(scanf("%d%d",&n,&m)!=EOF){
        t=n+1;
        for(i=0;i<=n+1;i++) g[i].clear();
        for(i=0;i<m;i++){
            scanf("%d%d%d%d",&pp1[i].x,&pp1[i].y,&pp1[i].co1,&pp1[i].co2);
            add(pp1[i].x,pp1[i].y,pp1[i].co2-pp1[i].co1,i);
            a[pp1[i].x]+=pp1[i].co1;
            a[pp1[i].y]-=pp1[i].co1;
        }
        for(i=1;i<=n;i++){
            if(a[i]>0) add(i,t,a[i],0);
            else add(s,i,-a[i],0);
        }//必要流量出流量比较多的与T连边，入的多的与S连边，跑一遍最大流。
        p=dinic();
        memset(a,0,sizeof(a));
        k=0;
        f=g[0].size();
        for(i=0;i<f;i++){//如果与源点连的边都满流则为可行流，否则不可行。
            if(g[0][i].cost!=0){
                k=1;
                break;
            }
        }
        if(k) printf("NO\n");
        else{
            for(i=1;i<=n;i++){
                k=g[i].size();
                for(j=0;j<k;j++){
                    if(g[i][j].id!=-1&&g[i][j].to!=s&&g[i][j].to!=t){
                        a[g[i][j].id]=pp1[g[i][j].id].co2-g[i][j].cost;//基础流量加上必要流量，注意网络里这条边的流量就是除基础流量外的跑的流量。
                    }
                }
            }
            printf("YES\n");
            for(i=0;i<m;i++){
                printf("%d\n",a[i]);
            }
        }
    }
}