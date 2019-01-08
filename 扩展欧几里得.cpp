int x,y;
int exgcd(int a,int b)
{
    if(b==0)
    {
        x=1;
        y=0;
        return a;
    }
    int p,t;
    p=exgcd(b,a%b);
    t=x;
    x=y;
    y=t-a/b*y;
    return p;
}