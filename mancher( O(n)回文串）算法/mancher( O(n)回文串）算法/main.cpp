#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
char d[200000],c[300000];
int p[300000],r[300005];//半径长度//加入以i为中心左边到a都是回文串那r[i]=i-a+1;
void mancher(int n){
    int i,id,mx;
    r[0]=1;
    mx=0;
    id=0;
    for(i=1;i<=2*n;i++){
        if(i>=mx) r[i]=1;
        else {
            r[i]=min(r[id-(i-id)],mx-i);
        }
        while(i-r[i]>=0&&i+r[i]<=2*n&&c[i-r[i]]==c[i+r[i]]) r[i]++;
        if(mx<r[i]+i){
            mx=r[i]+i;
            id=i;
        }
    }
}
int main()
{
    int i,j,n,p,id,re;
    while(scanf("%s",d)!=EOF){
        n=strlen(d);
        c[0]='#';
        for(i=1;i<=n;i++){
            c[2*i-1]=d[i-1];
            c[2*i]='#';
        }
        mancher(n);
        p=1;
        for(i=1;i<=2*n;i++){
            p=max(p,r[i]-1);
        }
        printf("%d\n",p);
    }
}