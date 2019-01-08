/*
 照求无源汇可行流的方法(如1)，建附加源点S'与汇点T'，求一遍S'->T‘的最大流. 但是注意这一遍不加汇点到源点的这条边，即不使之改为无源汇的网络去求解. 求完后，再加上那条汇点到源点上限INF的边. 因为这条边下限为0，所以S',T'无影响. 再直接求一遍S'->T'的最大流. 若S’出去的边全满流，T->S边上的流量即为答案原图最小流，否则若不全满流即无解. 
 */
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string.h>
#include<queue>
#define LL int
#define inf 100000000
#define maxn 150
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
    pp.rev=(int)g[b].size();
    pp.id=id;
    g[a].push_back(pp);
    pp.to=a;
    pp.cost=0;
    pp.rev=(int)g[a].size()-1;
    pp.id=-1;
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
struct ppi{
    int from;
    int to;
    int a;
    int b;
}pp1[100005];
char c[1005];
int a[105];
int b[100005];
int main()
{
    int i,j,n,m,p,k,N=0,le,ri,mid;
    while(scanf("%d%d",&n,&m)!=EOF){
        memset(a,0,sizeof(a));
        for(i=0;i<=n+1;i++) g[i].clear();
        for(i=0;i<m;i++){
            scanf("%d%d%d",&pp1[i].from,&pp1[i].to,&pp1[i].b);
            scanf("%d",&p);
            if(p==0){
                pp1[i].a=0;
            }
            else pp1[i].a=pp1[i].b;
            a[pp1[i].from]+=pp1[i].a;
            a[pp1[i].to]-=pp1[i].a;
        }
        s=0;
        t=n+1;
        le=0;
        ri=1000000000;
        while(le<=ri){//将t-》s连一条有上界的边，二分上界。
            mid=(le+ri)/2;
            for(i=0;i<=t;i++) g[i].clear();
            for(i=0;i<m;i++){
                add(pp1[i].from,pp1[i].to,pp1[i].b-pp1[i].a,i);
            }
            for(i=1;i<=n;i++){
                if(a[i]==0) continue;
                if(a[i]>0) add(i,t,a[i],-1);
                else add(s,i,-a[i],-1);
            }
            add(n,1,mid,-1);
            dinic();
            p=0;
            k=g[s].size();
            for(i=0;i<k;i++){
                if(g[s][i].cost!=0){
                    p=1;
                    break;
                }
            }
            if(p) le=mid+1;
            else ri=mid-1;
        }
        if(le>=1000000000){
            printf("Impossible\n");
        }
        else{
            printf("%d\n",le);
            for(i=0;i<=t;i++) g[i].clear();
            for(i=0;i<m;i++){
                add(pp1[i].from,pp1[i].to,pp1[i].b-pp1[i].a,i);
            }
            for(i=1;i<=n;i++){
                if(a[i]==0) continue;
                if(a[i]>0) add(i,t,a[i],-1);
                else add(s,i,-a[i],-1);
            }
            add(n,1,le,-1);
            dinic();
            for(i=1;i<=n;i++){
                k=g[i].size();
                for(j=0;j<k;j++){
                    if(g[i][j].id!=-1){
                        b[g[i][j].id]=pp1[g[i][j].id].b-g[i][j].cost;
                    }
                }
            }
            for(i=0;i<m;i++){
                if(i==0) printf("%d",b[i]);
                else printf(" %d",b[i]);
            }
            printf("\n");
        }
    }
}