#include<stdio.h>
int bit[1025][1025],n;
int low(int a)
{
    return a&(-a);
}
int sum(int x,int y)
{
    int s;
    int p;
    s=0;
    while(x>0)
    {
        p=y;
        while(p>0)
        {
            s+=bit[x][p];
            p=p-low(p);
        }
        x=x-low(x);
    }
    return s;
}
void merg(int x,int y,int s)
{
    int p;
    while(x<=n)
    {
        p=y;
        while(p<=n)
        {
            bit[x][p]+=s;
            p=p+low(p);
        }
        x=x+low(x);
    }
    return ;
}
