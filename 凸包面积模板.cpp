#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
#define eps 1e-8
using namespace std;
struct pi
{
    double x;
    double y;
}pp[10005];
pi pp1[10005];
int tot;
int dd(double x,double y)
{
    return fabs(x-y)<eps;
}
int xy(double x,double y)
{
    return x+eps<y;
}
int yx(double x,double y)
{
    return y+eps<x;
}
int xdy(double x,double y)
{
    return x<y+eps;
}
int ydx(double x,double y)
{
    return y<x+eps;
}
double cross(pi p1,pi p2,pi p3)
{
    double a;
    a=(p2.x-p1.x)*(p3.y-p1.y)-(p2.y-p1.y)*(p3.x-p1.x);
    return a;
}
double dist(pi a,pi b)
{
    return sqrt((double)(b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y));
}
int cmp1(pi a,pi b)
{
    if(dd(a.x,b.x))
        return xy(a.y,b.y);
    return xy(a.x,b.x);
}
int cmp2(pi a,pi b)
{
    int p;
    p=cross(pp[0],a,b);
    if(p==0)
    {
        return xy(dist(pp[0],a),dist(pp[0],b));
    }
    return yx(p,0);
}
double mianji(void)
{
    int i;
    double s;
    s=0;
    for(i=2;i<=tot-1;i++)
    {
        s+=cross(pp1[1],pp1[i],pp1[i+1]);
    }
    return s/2.0;
}
double ghama(int n)
{
    tot=0;
    sort(pp,pp+n,cmp1);
    sort(pp+1,pp+n,cmp2);
    pp1[++tot]=pp[0];
    pp1[++tot]=pp[1];
    for(int i=2;i<n;i++)
    {
        if(ydx(cross(pp1[tot],pp[i],pp1[tot-1]),0))
        {
            pp1[++tot]=pp[i];
            continue;
        }
        while(xy(cross(pp1[tot],pp[i],pp1[tot-1]),0))
            tot--;
        pp1[++tot]=pp[i];
    }
    return mianji();
}
int main()
{
    int i,n,q;
    double s,j,p;
    while(cin>>n)
    {
        for(i=0;i<n;i++)
        {
            scanf("%lf%lf",&j,&p);
            pp[i].x=j;
            pp[i].y=p;
        }
        s=ghama(n);
        q=floor((s+eps)/50+eps);
        printf("%d\n",q);
    }
    return 0;
}