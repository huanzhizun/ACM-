#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<algorithm>
#include<cmath>
#define eps 1e-12
using namespace std;
struct pi
{
    int l;
    int r;
    int cover;
    double len;
}pp[2005];
struct line
{
    double up;
    double down;
    double x;
    int cover;
}pp1[255];
double y[255];
int n,len;
void build(int a,int p,int q)
{
    pp[a].l=p;
    pp[a].r=q;
    int mid;
    mid=(p+q)/2;
    pp[a].cover=0;
    pp[a].len=0;
    if(p+1==q)
        return ;
    build(2*a,p,mid);
    build(2*a+1,mid,q);
}
void maintan(int k)
{
    if(pp[k].cover>0)
    {
        pp[k].len=y[pp[k].r]-y[pp[k].l];
        return ;
    }
    if(pp[k].r==pp[k].l+1)
    {
        pp[k].len=0;
        return ;
    }
    pp[k].len=pp[2*k].len+pp[2*k+1].len;
}
void merg(int k,int l,int r,int cover)
{
    if(pp[k].l>r||pp[k].r<l)
        return ;
    if(pp[k].l>=l&&pp[k].r<=r)
    {
        pp[k].cover+=cover;
        maintan(k);
        return ;
    }
    merg(2*k,l,r,cover);
    merg(2*k+1,l,r,cover);
    maintan(k);
    return ;
}
int cmp(struct line a,struct line b)
{
    return   a.x<b.x;
}
int find(double a)
{
    int l=0,r=len,mid;
    while(l<=r)
    {
        mid=(l+r)/2;
        if(y[mid]==a)
            return mid;
        if(y[mid]>a)
        {
            r=mid-1;
        }
        else
            l=mid+1;
    }
    return l;
}
int main()
{
    int i,p,q,N=0;
    double x1,y1,x2,y2,s;
    while(1)
    {
        N++;
        cin>>n;
        if(n==0)
            break;
        for(i=0;i<n;i++)
        {
            cin>>x1>>y1>>x2>>y2;
            pp1[2*i].x=x1;
            pp1[2*i].up=y2;
            pp1[2*i].down=y1;
            pp1[2*i].cover=1;
            pp1[2*i+1].x=x2;
            pp1[2*i+1].up=y2;
            pp1[2*i+1].down=y1;
            pp1[2*i+1].cover=-1;
            y[2*i]=y1;
            y[2*i+1]=y2;
        }
        s=0;
        sort(y,y+2*n);
        sort(pp1,pp1+2*n,cmp);
        len=1;
        for(i=1;i<2*n;i++)
        {
            if(y[i-1]!=y[i])
            {
                y[len++]=y[i];
            }
        }
        len--;
        build(1,0,len);
        for(i=0;i<2*n-1;i++)
        {
            p=find(pp1[i].down);
            q=find(pp1[i].up);
            merg(1,p,q,pp1[i].cover);
            s+=(pp1[i+1].x-pp1[i].x)*pp[1].len;
        }
        printf("Test case #%d\n",N);
        printf("Total explored area: %0.2lf\n\n",s);
    }
    return 0;
}