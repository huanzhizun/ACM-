#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
const int maxn=100005;
struct pi{
    int sum;
    int lson;
    int rson;
}pp[maxn*18];
int root[maxn],tot;
void build(int cnt,int l,int r){
    pp[cnt].sum=0;
    if(l==r) return;
    pp[cnt].lson=tot+1;
    tot++;
    build(tot,l,(l+r)/2);
    pp[cnt].rson=tot+1;
    tot++;
    build(tot,(l+r)/2+1,r);
}
void merg(int qq,int cnt,int n,int p,int k){
    int le,ri,mid;
    le=1;
    ri=n;
    while(le<=ri){
        mid=(le+ri)/2;
        pp[cnt]=pp[qq];
        pp[cnt].sum+=k;
        if (le==ri) break;
        if(p<=mid){
            pp[cnt].lson=tot+1;
            tot++;
            ri=mid;
            cnt=tot;
            qq=pp[qq].lson;
        }
        else{
            pp[cnt].rson=tot+1;
            tot++;
            le=mid+1;
            cnt=tot;
            qq=pp[qq].rson;
        }
    }
}
int query(int cnt,int le,int ri,int l,int r){
    if(l>r) return 0;
    int s=0;
    int mid;
    if(le>=l&&ri<=r){
        return pp[cnt].sum;
    }
    mid=(le+ri)/2;
    if(l<=mid) s+=query(pp[cnt].lson,le,mid,l,r);
    if(r>mid) s+=query(pp[cnt].rson,mid+1,ri,l,r);
    return s;
}
int a[maxn];
vector<int>g[maxn];
int find(int l,int r,int t){
    int le=1,ri=100000;
    while(le<=ri){
        int mid=(le+ri)/2;
        int w=query(root[r],1,100000,1,mid);
        if(l!=1)
            w-=query(root[l-1],1,100000,1,mid);
        if(w<t) le=mid+1;
        else ri=mid-1;
    }
    return le;
}
int cnt[maxn],r[maxn],no;
int x[maxn],y[maxn];
int size[maxn];
int to[maxn];
void dfs(int u){
    size[u]=1;
    cnt[u]=++no;
    to[no]=u;
    for(int v:g[u]){
        dfs(v);
        size[u]+=size[v];
    }
    r[u]=no;
}
long long ans;
long long sum[maxn];
void dfs1(int u){
    sum[u]=x[u];
    for(int v:g[u]){
        dfs1(v);
        sum[u]+=sum[v];
    }
}
long long bit[maxn];
int low(int p){
    return p&(-p);
}
void merg(int p,int n,int k){
    while (p<=n) {
        bit[p]+=k;
        p=p+low(p);
    }
}
long long query(int p){
    long long s=0;
    while (p) {
        s+=bit[p];
        p=p-low(p);
    }
    return s;
}
void dfs2(int u,long long all){
    merg(1,100000,y[u]);
    merg(a[u]+1,100000,x[u]-y[u]);
    long long s=query(a[u]);
    s=all+s+sum[u]-x[u];
    ans=max(ans,s);
    for(int v:g[u]){
        dfs2(u,all+sum[u]-x[u]-sum[v]);
    }
    merg(1,100000,-y[u]);
    merg(a[u]+1,100000,-x[u]+y[u]);
}
int main()
{
    int n;
    while (scanf("%d",&n)!=EOF) {
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        for(int i=1;i<=n;i++) g[i].clear();
        for(int i=2;i<=n;i++){
            int p;
            scanf("%d",&p);
            g[p].push_back(i);
        }
        no=0;
        tot=0;
        dfs(1);
        build(0,1,100000);
        for(int i=1;i<=n;i++){
            int w=to[i];
            root[i]=++tot;
            merg(root[i-1],root[i],100000,a[w],1);
        }
        for(int i=1;i<=n;i++){
            x[i]=find(cnt[i],r[i],(size[i]+1)/2);
            if(size[i]==1){
                y[i]=100000;
            }
            else
            y[i]=find(cnt[i],r[i],(size[i]+1)/2+1);
        }
        ans=0;
        dfs1(1);
        ans=sum[1];
        dfs2(1,0);
        printf("%lld\n",ans);
    }
}
