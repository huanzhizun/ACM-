#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
const int maxn=550;
typedef long long LL;
int map[maxn][maxn];
int w[maxn];
bool vis[maxn],use[maxn];
int m1,s,t;
void store(int n){
    memset(vis,0,sizeof(vis));
    memset(w,0,sizeof(w));
    int i,j,mm,f=0;
    for(i=0;i<n;i++){
        mm=-100000;
        for(j=0;j<n;j++){
            if(!vis[j]&&!use[j]){
                if(mm<w[j]){
                    mm=w[j];
                    f=j;
                }
            }
        }
        if(t==f){
            m1=w[t];
            return ;
        }
        s=t;
        t=f;
        vis[f]=1;
        for(j=0;j<n;j++){
            if(!vis[j]&&!use[j]){
                w[j]+=map[f][j];
            }
        }
    }
    m1=w[t];
}
int  solve(int n){
    int ans=1000000000;
    int i,j;
    memset(use,0,sizeof(use));
    for(i=0;i<n-1;i++){
        s=-1;
        t=-1;
        store(n);
        if(ans>m1) ans=m1;
        use[t]=1;
        for(j=0;j<n;j++){
            map[s][j]+=map[t][j];
            map[j][s]=map[s][j];
        }
    }
    return ans;
}
