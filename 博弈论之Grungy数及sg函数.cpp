#include<stdio.h>
#include<string.h>
#define N 10000
int grun[N],b[N];
bool ha[N];
void grundy(int n)
{
    int i,j;
    memset(grun,0,sizeof(grun));
    for(i=1;i<=N;i++)
    {
        memset(ha,0,sizeof(ha));
        for(j=0;j<n;j++)
        {
            if(i>=b[j])
            {
                ha[grun[i-b[j]]]=1;
            }
        }
        for(j=0;j<=N;j++)
        {
            if(!ha[j])
                break;
        }
        grun[i]=j;
    }
}
//1.可选步数为1~m的连续整数，直接取模即可，SG(x) = x % (m+1);

//2.可选步数为任意步，SG(x) = x;

//3.可选步数为一系列不连续的数，用GetSG()
