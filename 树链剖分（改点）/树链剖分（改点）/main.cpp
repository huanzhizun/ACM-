#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#define maxn 30005
using namespace std;
int top[maxn],fa[maxn],size[maxn],son[maxn],id[maxn],dep[maxn],head[maxn],a[maxn],num,tot;
void init(void){
    memset(head,-1,sizeof(head));
    num=0;
    tot=0;
}
struct ppi{
    int to;
    int next;
}pp2[maxn<<1];
struct pi{
    int le;
    int ri;
    int sum;
}pp3[maxn<<2];
void add(int u,int v){
    pp2[tot].to=v;
    pp2[tot].next=head[u];
    head[u]=tot++;
    pp2[tot].to=u;
    pp2[tot].next=head[v];
    head[v]=tot++;
}
void build(int tot,int l,int r){
    pp3[tot].le=l;
    pp3[tot].ri=r;
    pp3[tot].sum=0;
    if(l==r) return ;
    build(2*tot,l,(l+r)/2);
    build(2*tot+1,(l+r)/2+1,r);
}
void merg(int tot,int x,int p){
    if(pp3[tot].le==pp3[tot].ri){
        pp3[tot].sum=p;
        return ;
    }
    int mid=(pp3[tot].le+pp3[tot].ri)/2;
    if(x<=mid) merg(2*tot,x,p);
    else merg(2*tot+1,x,p);
    pp3[tot].sum=pp3[2*tot].sum+pp3[2*tot+1].sum;
}
void dfs1(int u,int pa,int d){
    dep[u]=d;
    fa[u]=pa;
    size[u]=1;
    son[u]=0;
    int k,v;
    k=head[u];
    while(k!=-1){
        v=pp2[k].to;
        if(v!=pa){
            dfs1(v,u,d+1);
            size[u]+=size[v];
            if(size[son[u]]<size[v]) son[u]=v;
        }
        k=pp2[k].next;
    }
}
void dfs2(int u,int pa,int tp){
    top[u]=tp;
    id[u]=++num;
    if(son[u]) dfs2(son[u],u,tp);
    int k,v;
    k=head[u];
    while(k!=-1){
        v=pp2[k].to;
        if(v!=pa&&v!=son[u]){
            dfs2(v,u,v);
        }
        k=pp2[k].next;
    }
}
int query(int tot,int l,int r){
    if(pp3[tot].le>=l&&pp3[tot].ri<=r) return pp3[tot].sum;
    int s=0;
    int mid=(pp3[tot].le+pp3[tot].ri)/2;
    if(l<=mid) s+=query(2*tot,l,r);
    if(r>mid) s+=query(2*tot+1,l,r);
    return s;
}
int get(int u,int v){
    int to1,to2,s=0;
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
    if(dep[u]>dep[v]) swap(u,v);
    s+=query(1,id[u],id[v]);
    return s;
}
int main()
{
    int N=0,i,t,k,n,m,p;
    cin>>t;
    while(t--){
        printf("Case %d:\n",++N);
        scanf("%d",&n);
        init();
        for(i=1;i<=n;i++) scanf("%d",&a[i]);
        for(i=1;i<n;i++){
            scanf("%d%d",&p,&k);
            p++;
            k++;
            add(p,k);
        }
        build(1,1,n);
        dfs1(1,1,1);
        dfs2(1,1,1);
        for(i=1;i<=n;i++){
            merg(1,id[i],a[i]);
        }
        scanf("%d",&m);
        for(i=0;i<m;i++){
            scanf("%d",&p);
            if(p==0){
                scanf("%d%d",&p,&k);
                p++;
                k++;
                printf("%d\n",get(p,k));
            }
            else{
                scanf("%d%d",&p,&k);
                p++;
                merg(1,id[p],k);
            }
        }
    }
}