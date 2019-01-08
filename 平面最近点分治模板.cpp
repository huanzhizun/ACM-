#include<stdio.h>
#include<math.h>
#include<algorithm>
using namespace std;
struct pi
{
    double x;
    double y;
}pp[100001];
struct pi pp1[100001];
double pinfan(int a,int b)
{
    if(a==b)
        return 0;
    return sqrt((pp[a].x-pp[b].x)*(pp[a].x-pp[b].x)+(pp[a].y-pp[b].y)*(pp[a].y-pp[b].y));
}
double pinfan2(int a,int b)
{
    if(a==b)
        return 0;
    return sqrt((pp1[a].x-pp1[b].x)*(pp1[a].x-pp1[b].x)+(pp1[a].y-pp1[b].y)*(pp1[a].y-pp1[b].y));
}int cmp1(struct pi a,struct pi b)
{
    return a.y<b.y;
}
double jisuan(int a,int b)
{
    int p=(a+b)/2,t,m,i,tot,j;
    if(a==b)
        return 0;
    double min=1000000,f,k;
    if(b-a==2)
    {
        f=pinfan(a,a+1);
        if(f<min)
            min=f;
        f=pinfan(a,b);
        if(f<min)
            min=f;
        f=pinfan(a+1,b);
        if(f<min)
            min=f;
        return min;
    }
    if(b-a==1)
        return pinfan(a,b);
    k=jisuan(a,p);
    f=jisuan(p,b);
    if(k>f)
        k=f;
    t=p;
    while(t<=b&&(pp[t].x-pp[p].x)<=k)
        t++;
    m=p;
    while(m>=a&&(pp[p].x-pp[t].x)<=k)
        m--;
    tot=0;
    for(i=m+1;i<=t-1;i++)
    {
        pp1[tot].x=pp[i].x;
        pp1[tot++].y=pp[i].y;
    }
    sort(pp1,pp1+tot,cmp1);
    for(i=0;i<tot;i++)
    {
        for(j=1;j<=7;j++)
        {
            if(i+j>=tot)
                break;
            f=pinfan2(i,i+j);
            if(f<min)
                min=f;
        }
    }
    if(min>k)
        min=k;
    return min;
}
int cmp(struct pi a,struct pi b)
{
    return a.x<b.x;
}
int main()
{
    int n,i;
    double s;
    while(1)
    {
        scanf("%d",&n);
        if(n==0)
            break;
        for(i=0;i<n;i++)
        {
            scanf("%lf%lf",&pp[i].x,&pp[i].y);
        }
        if(n==2)
        {
            printf("%.2lf\n",pinfan(0,1)/2);
            continue;
        }
        sort(pp,pp+n,cmp);
        s=jisuan(0,n-1);
        printf("%.2lf\n",s/2);
    }
    return 0;
}