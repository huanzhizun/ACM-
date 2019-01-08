#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
bool dp[100005];
int num[100005];
int a[105],b[105];
int main()
{
    int n,i,j,m,sum;
    double s;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        for(i=0;i<n;i++)
            scanf("%d",&a[i]);
        for(i=0;i<n;i++)
            scanf("%d",&b[i]);
        memset(dp,0,sizeof(dp));
        sum=0;
        dp[0]=1;
        for(i=0;i<n;i++)
        {
            memset(num,0,(m+1)*sizeof(num[0]));
            for(j=a[i];j<=m;j++)
            {
                if(!dp[j]&&dp[j-a[i]]&&num[j-a[i]]<b[i])
                {
                    dp[j]=1;
                    num[j]=num[j-a[i]]+1;
                    sum++;
                }
            }
        }
        s=(double)sum/m;
        printf("%.3lf%%\n",s*100);
    }
    return 0;
}