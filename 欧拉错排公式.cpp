void init()
{
    s[0]=0; s[1]=0; s[2]=1;
    int i;
    for (i=3;i<=100;i++)
        s[i]=(i-1)*(s[i-1]+s[i-2])%mod;
}