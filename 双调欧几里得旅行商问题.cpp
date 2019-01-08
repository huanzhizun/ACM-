//d[i][j]=d[i-1][j]+p[i][i-1];

//d[i][i-1]=min(d[i-1][j]+p[j][i]);
void work_p()
{
    for (int i=1;i<n;i++)
        for (int j=i+1;j<=n;j++)
            p[i][j]=p[j][i]=cnt(a[i].x,a[i].y,a[j].x,a[j].y);
}
void DP()
{
    d[1][1]=0;
    for (int i=2;i<=n;i++)
        d[i][1]=p[i][1];
    for (int i=2;i<n;i++)
    {
        d[i+1][i]=INT_MAX;
        for (int j=1;j<=i-1;j++)
        {
            d[i+1][j]=d[i][j]+p[i][i+1];
            d[i+1][i]=min(d[i+1][i],d[i][j]+p[j][i+1]);
        }
    }
}