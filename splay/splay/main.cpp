#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
const int maxn=300005;
int ch[maxn][2],size[maxn],fa[maxn],flag[maxn];
void push(int tot){
    if(flag[tot]){
        swap(ch[tot][0],ch[tot][1]);
        if(ch[tot][0])
            flag[ch[tot][0]]^=1;
        if(ch[tot][1])
            flag[ch[tot][1]]^=1;
        flag[tot]=0;
    }
}
int root;
void update(int tot){
    size[tot]=1+size[ch[tot][0]]+size[ch[tot][1]];
}
int build(int l,int r,int ff){
    if(l>r) return 0;
    int mid=(l+r)/2;
    fa[mid]=ff;
    ch[mid][0]=build(l,mid-1,mid);
    ch[mid][1]=build(mid+1,r,mid);
    update(mid);
    return mid;
}
void roat(int p,int k){
    int f=fa[p];
    if(ch[p][k^1]){
        fa[ch[p][k^1]]=f;
    }
    ch[f][k]=ch[p][k^1];
    ch[p][k^1]=f;
    if(root==f){
        root=p;
    }
    else{
        int k=f==ch[fa[f]][1];
        ch[fa[f]][k]=p;
    }
    fa[p]=fa[f];
    fa[f]=p;
    update(f);
    update(p);
}
void splay(int p,int q){
    while(fa[p]!=q){
        push(fa[fa[p]]);
        push(fa[p]);
        push(p);
        if(fa[fa[p]]==q){
            roat(p,p==ch[fa[p]][1]);
            return ;
        }
        int kind=fa[p]==ch[fa[fa[p]]][1];
        if(p==ch[fa[p]][kind]){
            roat(p,kind);
            roat(p,kind);
        }
        else{
            roat(p,kind^1);
            roat(p,kind);
        }
    }
}
int get(int p,int k){
    push(p);
    if(size[ch[p][0]]+1==k) return p;
    if(size[ch[p][0]]<k) return get(ch[p][1],k-size[ch[p][0]]-1);
    return get(ch[p][0],k);
}
void flip(int l,int r,int n){
    if(l==1&&r==n){
        flag[root]^=1;
        return ;
    }
    if(l==1){
        r=get(root,r+1);
        splay(r,0);
        flag[ch[root][0]]^=1;
    }
    else if(r==n){
        l=get(root,l-1);
        splay(l,0);
        flag[ch[root][1]]^=1;
    }
    else{
        l=get(root,l-1);
        r=get(root,r+1);
        splay(l,0);
        splay(r,l);
        flag[ch[r][0]]^=1;
    }
}
void getle(int p){
    while(1){
        push(p);
        if(ch[p][0]==0) return ;
        push(ch[p][0]);
        roat(ch[p][0],0);
        p=fa[p];
    }
}
void insert(int l,int r,int x,int n){
    if(l==1&&r==n) return ;
    int w;
    int l1=l,r1=r;
    if(l==1){
        r=get(root,r+1);
        splay(r,0);
        w=ch[r][0];
        ch[r][0]=0;
        update(r);
    }
    else if(r==n){
        l=get(root,l-1);
        splay(l,0);
        w=ch[l][1];
        ch[l][1]=0;
        update(l);
    }
    else{
        l=get(root,l-1);
        r=get(root,r+1);
        splay(l,0);
        splay(r,l);
        w=ch[r][0];
        ch[r][0]=0;
        update(r);
        update(l);
    }
    if(x==0){
        getle(root);
        ch[root][0]=w;
        fa[w]=root;
        update(root);
    }
    else{
        int ww=get(root,x);
        splay(ww,0);
        if(x==n-(r1-l1+1)){
            ch[root][1]=w;
            fa[w]=root;
            update(root);
        }
        else{
            getle(ch[root][1]);
            ch[ch[root][1]][0]=w;
            fa[w]=ch[root][1];
            update(ch[root][1]);
            update(root);
        }
    }
}
char c[4];
int a[maxn];
int main()
{
    int i,n,m;
    while(1){
        scanf("%d%d",&n,&m);
        if(n==-1&&m==-1) break;
        memset(ch,0,sizeof(ch));
        memset(flag,0,sizeof(flag));
        root=0;
        fa[0]=size[0]=0;
        root=build(1,n,0);
        for(i=0;i<m;i++){
            scanf("%s",c);
            if(c[0]=='F'){
                int a,b;
                scanf("%d%d",&a,&b);
                flip(a,b,n);
            }
            else{
                int a,b,c;
                scanf("%d%d%d",&a,&b,&c);
                insert(a,b,c,n);
            }
        }
        for(i=1;i<=n;i++){
            splay(i,0) ;
            a[size[ch[root][0]]+1]=i;
        }
        for(i=1;i<=n;i++){
            if(i!=1) printf(" ");
            printf("%d",a[i]);
        }
        printf("\n");
    }
}