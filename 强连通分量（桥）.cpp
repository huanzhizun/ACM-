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
void tarjin(int p,int pa,int n){
    int k,i;
    low[p]=dnf[p]=cal++;
    k=g[p].size();
    for(i=0;i<k;i++){
        int v=g[p][i];
        if(!dnf[v]){
            tarjin(v,p,n);
            low[p]=min(low[p],low[v]);
            if(low[v]>dnf[p]){//判断是否是桥
                pp++;//桥的个数
            }
        }
        else if(v!=pa){//一定要注意求桥时不能遍历父亲节点，因为判断条件是大于，否则变成了环。
            low[p]=min(low[p],dnf[v]);
        }
    }
}
void solve(int n){
    int i,m;
    cal=1;
    for(i=1;i<=n;i++){
        if(!dnf[i])
            tarjin(i,-1,i);
    }
}