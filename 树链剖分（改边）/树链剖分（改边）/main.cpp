#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#define maxn 100005
using namespace std;
int top[maxn],fa[maxn],son[maxn],size[maxn],id[maxn],num,dep[maxn],tot;
struct pppi{
    int to;
    int next;
}pp2[2*maxn];
int head[maxn];
vector<int >g[maxn];
void add(int u,int v){
    pp2[tot].to=v;
    pp2[tot].next=head[u];
    head[u]=tot++;
    pp2[tot].to=u;
    pp2[tot].next=head[v];
    head[v]=tot++;
}
struct ppi{
    int from;
    int to;
    int cost;
}pp1[maxn];
struct pi{
    int le,ri;
    int sum;
}pp[4*maxn];
void build(int tot,int l,int r){
    pp[tot].sum=0;
    pp[tot].le=l;
    pp[tot].ri=r;
    if(l==r) return ;
    build(2*tot,l,(l+r)/2);
    build(2*tot+1,(l+r)/2+1,r);
}
void merg(int tot,int l,int k){
    if(pp[tot].ri==pp[tot].le){
        pp[tot].sum=k;
        return ;
    }
    int mid;
    mid=(pp[tot].le+pp[tot].ri)/2;
    if(l<=mid) merg(2*tot,l,k);
    else merg(2*tot+1,l,k);
    pp[tot].sum=pp[2*tot].sum+pp[2*tot+1].sum;
}
int query(int tot,int l,int r){
    if(pp[tot].le>=l&&pp[tot].ri<=r){
        return pp[tot].sum;
    }
    int s=0;
    int mid=(pp[tot].le+pp[tot].ri)/2;
    if(l<=mid) s+=query(2*tot,l,r);
    if(r>mid) s+=query(2*tot+1,l,r);
    return s;
}
void dfs1(int u,int pa,int d){
    dep[u]=d;
    size[u]=1;
    son[u]=0;
    fa[u]=pa;
    int k,v;
    k=head[u];
    while(k!=-1){
        v=pp2[k].to;
        if(v==pa){
            k=pp2[k].next;
            continue;
        }
        dfs1(v,u,d+1);
        size[u]+=size[v];
        if(size[son[u]]<size[v]) son[u]=v;
        k=pp2[k].next;
    }
}
void dfs2(int u,int pa,int tp){
    int k,v;
    id[u]=num++;
    top[u]=tp;
    if(son[u]) dfs2(son[u],u,tp);
    k=head[u];
    while(k!=-1){
        v=pp2[k].to;
        if(v==pa||v==son[u]){
            k=pp2[k].next;
            continue;
        }
        dfs2(v,u,v);
        k=pp2[k].next;
    }
}
int get(int u,int v){
    int s=0,to1,to2;
    to1=top[u];
    to2=top[v];
    while(to1!=to2){
        if(dep[to1]<dep[to2]){
            swap(to1,to2);
            swap(u,v);
        }
        s+=query(1,id[to1],id[u]);
        u=fa[to1];
        to1=top[u];
    }
    if(u==v) return s;
    if(dep[u]>dep[v]) swap(u,v);
    s+=query(1,id[u]+1,id[v]);
    return s;
}
int main()
{
    int i,n,m,p,k,s;
    scanf("%d%d%d",&n,&m,&s);
    build(1,1,n-1);
    memset(head,-1,sizeof(head));
    tot=0;
    for(i=1;i<=n-1;i++){
        scanf("%d%d%d",&pp1[i].from,&pp1[i].to,&pp1[i].cost);
        add(pp1[i].from,pp1[i].to);
    }
    num=0;
    dfs1(1,1,1);
    dfs2(1,1,1);
    for(i=1;i<n;i++){
        if(fa[pp1[i].from]==pp1[i].to){
            merg(1,id[pp1[i].from],pp1[i].cost);
        }
        else merg(1,id[pp1[i].to],pp1[i].cost);
    }
    for(i=0;i<m;i++){
        scanf("%d",&p);
        if(p==0){
            scanf("%d",&k);
            printf("%d\n",get(s,k));
            s=k;
        }
        else{
            scanf("%d%d",&p,&k);
            if(fa[pp1[p].from]==pp1[p].to) merg(1,id[pp1[p].from],k);
            else  merg(1,id[pp1[p].to],k);
        }
    }
}