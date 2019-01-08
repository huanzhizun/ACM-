int bit[100001],n;
int sum(int a)
{
    int s=0;
    while(a>=0)
    {
        s+=bit[a];
        a-=a&(-a);
    }
    return s;
}
void merg(int a,int b)
{
    while(a<=n)
    {
        bit[a]+=b;
        a+=a&(-a);
    }
    return ;
}
