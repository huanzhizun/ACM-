#include<stdio.h>
#include<string.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
__int64 p;
__int64 jieji[200005];
__int64 ppow(__int64 n,__int64 m)
{
    
    __int64 s=1,k=n%p;
    while(m>0)
    {
        if(m&1)
        {
            s=(s*k)%p;
        }
        k=(k*k)%p;
        m>>=1;
    }
    return s;
}
__int64  zuhe(__int64 n,__int64 m)
{
    if(m==0)
        return 1;
    __int64 s=1;
    __int64 q,f;
    while(n>0&&m>0)
    {
        q=n%p;
        f=m%p;
        if(q<f)
            return 0;
        s=((s*jieji[q])%p*ppow((jieji[f]*jieji[q-f])%p,p-2))%p;
        n=n/p;
        m=m/p;
    }
    return s;
}
int main()
{
    __int64 n,m,t,k;
    int i;
    cin>>t;
    while(t--)
    {
        scanf("%I64d%I64d%I64d",&n,&m,&p);
        jieji[0]=1;
        jieji[1]=1;
        for(i=2;i<=p;i++)
            jieji[i]=(jieji[i-1]*i)%p;
        k=zuhe(n+m,n);
        printf("%I64d\n",k);
    }
    return 0;
}
