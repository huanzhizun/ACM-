#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
#define maxn 1105
using namespace std;
int low[maxn],dnf[maxn],que[maxn],tear,mark[maxn];
vector<int>g[maxn];
void init(int n){
    for(int i=1;i<=n;i++) g[i].clear();
}
int cal,tot;
void tarjin(int p){
    dnf[p]=low[p]=cal++;
    int i,k;
    k=g[p].size();
    que[tear++]=p;
    for(i=0;i<k;i++){
        int v=g[p][i];
        if(!dnf[v]){
            tarjin(v);
            low[p]=min(low[p],low[v]);//如果儿子就比较low
        }
        else if(!mark[v]){
            low[p]=min(low[p],dnf[v]);//与栈里面的点进行比较，如果mark[i]有值就代表已经出栈了。
        }
    }
    if(low[p]==dnf[p]){
        while(tear>0){
            mark[que[tear-1]]=tot;
            if(que[tear-1]==p){
                tear--;
                break;
            }
            tear--;
        }
        tot++;
    }
}
void solve(int n){
    int i;
    tear=0;
    cal=1;
    tot=1;
    memset(dnf,0,sizeof(dnf));
    memset(c,0,sizeof(c));
    memset(mark,0,sizeof(mark));
    for(i=1;i<=n;i++){
        tear=0;
        if(!dnf[i]) tarjin(i);
    }
    for(i=1;i<=n;i++){
        c[mark[i]]++;
    }
 }
int main()
{
    int i,j,n,m,p,t;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&m);
        init(n);
        for(i=0;i<m;i++){
            scanf("%d%d",&p,&j);
            g[p].push_back(j);
        }
        solve(n);
    }
}
