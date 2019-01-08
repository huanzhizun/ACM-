#include<stdio.h>
#include<math.h>
#include<algorithm>
using namespace std;
int x, y,q;
int exgcd(int a,int b)
{
    int p;
    if(b==0)
    {
        x=1;
        y=0;
        return a;
    }
    q=exgcd(b,a%b);
    p=x;
    x=-y;
    y=-p-(a/b)*y;
    return q;
}
int main()
{
    int p,e,i,d,count,q,t,f,k,N=0;
    while(1)
    {
        N++;
        scanf("%d%d%d%d",&p,&e,&i,&d);
        if(p==-1&&e==-1&&i==-1&&d==-1)
            break;
        if(p==0)
            p=23;
        if(e==0)
            e=28;
        if(i==0)
            i=33;
        q=23*28*33;
        count=0;
        t=28*33;
        f=23*33;
        k=23*28;
        exgcd(t,23);
        if(x<0)
            x=x%23+23;
        count+=p*x*t;
        exgcd(f,28);
        if(x<0)
            x=x%28+28;
        count+=f*x*e;
        exgcd(k,33);
        if(x<0)
            x=x%33+33;
        count+=k*x*i-d;
        count=count%q;
        if(count<=0)
            count+=q;
        printf("Case %d: the next triple peak occurs in %d days.\n",N,count);
    }
    return 0;
}