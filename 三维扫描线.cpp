#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#define maxn 50005
using namespace std;
typedef __int64 LL;
int y[maxn<<1];
int z[maxn<<1];
int tot;
struct pi{
    int x1;
    int y1;
    int z1;
    int x2;
    int y2;
    int z2;
}pp[maxn];
struct ppi{
    int x;
    int up;
    int down;
    int cover;
}pp1[maxn];
struct pppi{
    int l;
    int r;
    int cover;
    int len;
    int len1;
    int len2;
}pp2[maxn];
void build(int p,int l,int r){
    pp2[p].l=l;
    pp2[p].r=r;
    pp2[p].len=0;
    pp2[p].len1=0;
    pp2[p].len2=0;
    pp2[p].cover=0;
    if(r==l+1) return ;
    build(2*p,l,(l+r)/2);
    build(2*p+1,(l+r)/2,r);
}
void update(int k){
    if(pp2[k].cover>=3){
        pp2[k].len=y[pp2[k].r]-y[pp2[k].l];
        pp2[k].len1=0;
        pp2[k].len2=0;
        return ;
    }
    if(pp2[k].cover==2){
        if(pp2[k].l+1!=pp2[k].r){
            pp2[k].len=pp2[2*k].len1+pp2[2*k].len+pp2[2*k].len2+pp2[2*k+1].len2+pp2[2*k+1].len1+pp2[2*k+1].len;
            pp2[k].len1=y[pp2[k].r]-y[pp2[k].l]-pp2[k].len;
            pp2[k].len2=0;
        }
        else{
            pp2[k].len=0;
            pp2[k].len1=y[pp2[k].r]-y[pp2[k].l];
            pp2[k].len2=0;
        }
    }
    else if(pp2[k].cover==1){
        if(pp2[k].l+1!=pp2[k].r){
            pp2[k].len=pp2[2*k].len1+pp2[2*k].len+pp2[2*k+1].len1+pp2[2*k+1].len;
            pp2[k].len1=pp2[2*k].len2+pp2[2*k+1].len2;
            pp2[k].len2=y[pp2[k].r]-y[pp2[k].l]-pp2[k].len-pp2[k].len1;
        }
        else{
            pp2[k].len=0;
            pp2[k].len1=0;
            pp2[k].len2=y[pp2[k].r]-y[pp2[k].l];
        }
    }
    else{
        if(pp2[k].l+1!=pp2[k].r){
            pp2[k].len=pp2[2*k].len+pp2[2*k+1].len;
            pp2[k].len1=pp2[2*k].len1+pp2[2*k+1].len1;
            pp2[k].len2=pp2[2*k].len2+pp2[2*k+1].len2;
        }
        else{
            pp2[k].len=0;
            pp2[k].len1=0;
            pp2[k].len2=0;
        }
    }
}
void merg(int p,int l,int r,int cover){
    if(pp2[p].l>r||pp2[p].r<l) return ;
    if(pp2[p].l>=l&&pp2[p].r<=r){
        pp2[p].cover+=cover;
        update(p);
        return ;
    }
    merg(2*p,l,r,cover);
    merg(2*p+1,l,r,cover);
    update(p);
}
void add(int x1,int y1,int x2,int y2){
    pp1[tot].x=x1;
    pp1[tot].up=y2;
    pp1[tot].down=y1;
    pp1[tot].cover=1;
    tot++;
    pp1[tot].x=x2;
    pp1[tot].up=y2;
    pp1[tot].down=y1;
    pp1[tot].cover=-1;
    tot++;
}
int cmp(ppi a,ppi b){
    if(a.x!=b.x) return a.x<b.x;
    if(a.cover>0) return 1;
    return 0;
}
LL solve(int n,int cal){
    int i,j,m,len,too,k;
    LL s,are;
    sort(y,y+cal);
    sort(z,z+cal);
    s=0;
    len=unique(y, y+cal)-y;
    too=unique(z,z+cal)-z;
    build(1,0,len-1);
    tot=0;
    for(i=0;i<too-1;i++){
        are=0;
        tot=0;
        for(j=0;j<n;j++){
            if(pp[j].z1<=z[i]&&pp[j].z2>z[i]){
                add(pp[j].x1,pp[j].y1,pp[j].x2,pp[j].y2);
            }
        }
        sort(pp1,pp1+tot,cmp);
        for(j=0;j<tot;j++){
            m=lower_bound(y, y+len, pp1[j].up)-y;
            k=lower_bound(y, y+len, pp1[j].down)-y;
            merg(1,k,m,pp1[j].cover);
            if(j<tot-1)
                are+=1LL*(pp1[j+1].x-pp1[j].x)*pp2[1].len;
        }
        s+=are*(z[i+1]-z[i]);
    }
    return s;
}
int main(){
    int i,j,n,t,N,cal;
    scanf("%d",&t);
    N=t;
    while(t--){
        scanf("%d",&n);
        cal=0;
        for(i=0;i<n;i++){
            scanf("%d%d%d%d%d%d",&pp[i].x1,&pp[i].y1,&pp[i].z1,&pp[i].x2,&pp[i].y2,&pp[i].z2);
            y[cal]=pp[i].y1;
            z[cal]=pp[i].z1;
            cal++;
            y[cal]=pp[i].y2;
            z[cal]=pp[i].z2;
            cal++;
        }
        if(n<=2){
            printf("Case %d: 0\n",N-t);
            continue;
        }
        printf("Case %d: %I64d\n",N-t,solve(n,cal));
    }
}