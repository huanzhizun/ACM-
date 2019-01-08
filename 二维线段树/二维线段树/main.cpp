#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
const int maxn=805;
struct pi{
    int max;
    int min;
}pp[maxn<<2][maxn<<2];
void init(){
    int i,j;
    for(i=0;i<maxn<<2;i++){
        for(j=0;j<maxn<<2;j++){
            pp[i][j].max=0;
            pp[i][j].min=1000000000;
        }
    }
}
void merg1(int tot,int l,int r,int y,int k,int to1,int la){
    if(l==r){
        if(la==1) pp[to1][tot].max=pp[to1][tot].min=k;
        else{
            pp[to1][tot].max=max(pp[2*to1][tot].max,pp[2*to1+1][tot].max);
            pp[to1][tot].min=min(pp[2*to1][tot].min,pp[2*to1+1][tot].min);
        }
    }
    else{
        int mid=(l+r)/2;
        if(y<=mid) merg1(2*tot,l,mid,y,k,to1,la);
        else merg1(2*tot+1,mid+1,r,y,k,to1,la);
        pp[to1][tot].max=max(pp[to1][2*tot].max,pp[to1][2*tot+1].max);
        pp[to1][tot].min=min(pp[to1][2*tot].min,pp[to1][2*tot+1].min);
    }
}
int n;
void merg2(int tot,int l,int r,int x,int y,int k){
    if(l==r){
        merg1(1,1,n,y,k,tot,1);
    }
    else{
        int mid=(l+r)/2;
        if(x<=mid) merg2(2*tot,l,mid,x,y,k);
        else merg2(2*tot+1,mid+1,r,x,y,k);
        merg1(1,1,n,y,k,tot,0);
    }
}
int query1(int tot,int l,int r,int x,int y,int to1,int k){
    if(l>=x&&r<=y){
        if(k==0) return pp[to1][tot].max;
        return pp[to1][tot].min;
    }
    int s;
    if(k==0) s=0;
    else s=1000000000;
    int mid=(l+r)/2;
    if(k==0){
        if(x<=mid) s=max(s,query1(2*tot,l,mid,x,y,to1,k));
        if(y>mid) s=max(s,query1(2*tot+1,mid+1,r,x,y,to1,k));
    }
    else{
        if(x<=mid) s=min(s,query1(2*tot,l,mid,x,y,to1,k));
        if(y>mid) s=min(s,query1(2*tot+1,mid+1,r,x,y,to1,k));
    }
    return s;
}
int query2(int tot,int l,int r,int x1,int y1,int x,int y,int k){
    if(l>=x1&&r<=y1){
        return query1(1, 1, n, x, y, tot, k);
    }
    int s,mid;
    mid=(l+r)/2;
    if(k==0){
        s=0;
        if(x1<=mid){
            s=max(s,query2(2*tot,l,mid,x1,y1,x,y,k));
        }
        if(y1>mid)s=max(s,query2(2*tot+1,mid+1,r,x1,y1,x,y,k));
    }
    else{
        s=1000000000;
        if(x1<=mid){
            s=min(s,query2(2*tot,l,mid,x1,y1,x,y,k));
        }
        if(y1>mid)s=min(s,query2(2*tot+1,mid+1,r,x1,y1,x,y,k));
    }
    return s;
}
int main()
{
    int i,j,m,t,N=0;
    cin>>t;
    while(t--){
        cin>>n;
        init();
        for(i=1;i<=n;i++){
            for(j=1;j<=n;j++){
                scanf("%d",&m);
                merg2(1,1,n,i,j,m);
            }
        }
        cin>>m;
        printf("Case #%d:\n",++N);
        for(i=0;i<m;i++){
            int a,b,l;
            int x,y,x1,y1,x2,y2;
            scanf("%d%d%d",&a,&b,&l);
            x1=a-(l-1)/2;
            if(x1<1) x1=1;
            y1=a+(l-1)/2;
            if(y1>n) y1=n;
            x2=b-(l-1)/2;
            if(x2<1) x2=1;
            y2=b+(l-1)/2;
            if(y2>n) y2=n;
            x=query2(1,1,n,x1,y1,x2,y2,0);
            y=query2(1,1,n,x1,y1,x2,y2,1);
            printf("%d\n",(x+y)/2);
            merg2(1,1,n,a,b,(x+y)/2);
        }
    }
}