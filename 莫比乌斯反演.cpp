#include<stdio.h>
#include<string.h>
#include<iostream>
#include<algorithm>
#define max 100000
using namespace std;
int u[max+20];
long long f[max+20];
long long g[max+20];
bool vis[max+20];
int mmax(int a,int b)
{
    int p;
    p=a;
    if(b<a)
        p=b;
    return p;
}
int main()
{
    int n,i,j,k,p,t,N,m;
    fill(u,u+max+19,1);
    u[1]=1;
    memset(vis,0,sizeof(vis));
    for(i=2;i<=max+18;i++)
    {
        if(vis[i])
            continue;
        if(u[i]==0)
            continue;
        for(j=i;j<=max+2;j=j+i)
        {
            if(u[j]==0)
            {
                continue;
            }
            if((j/i)%i==0)
            {
                u[j]=0;
            }
            else
            {
                u[j]=-u[j];
            }
            vis[j]=1;
        }
    }
    return 0;
}