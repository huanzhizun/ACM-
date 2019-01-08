#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define maxn 1005
using namespace std;
int vis[maxn],low[maxn],dnf[maxn],yes[maxn],fa[maxn];
vector<int > g[maxn];
void init(int n){
    for(int i=1;i<=n;i++) g[i].clear();
}
int zi[maxn],pp;
int cal;
void tarjin(int p,int pa){
    int k,i,q=0;
    low[p]=dnf[p]=cal++;
    k=g[p].size();
    for(i=0;i<k;i++){
        int v=g[p][i];
        if(!dnf[v]){
            tarjin(v,p);
            low[p]=min(low[p],low[v]);
            q++;
            if((pa==-1&&q>1)||(pa!=-1&&low[v]>=dnf[p])){
                yes[p]=1;//表示p是割点，可以包含p的环
            }
        }
        else if(v!=pa){
            low[p]=min(low[p],dnf[v]);
        }
    }
    if(p==n) zi[p]=q;//根节点不加1.
    else zi[p]=q+1;//有多个分子图，也就是连着几块联通块。
}
void solve(int n){
    int i,m;
    memset(zi,0,sizeof(zi));
    cal=1;
    for(i=1;i<=n;i++){
    if(!dnf[i])
    tarjin(i,-1);
    }
}