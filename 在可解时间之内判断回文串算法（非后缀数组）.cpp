#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<string.h>
#define maxn 5005//几乎是极限
using namespace std;
char a[5005];
int pan[5005][5005];
int main()
{
    int n,i,k;
    cin>>a;
    n=strlen(a);
    for(i=0;i<n;i++)
        pan[i][i]=1;
    for(k=2;k<=n;k++){
        for(i=0;i<n;i++){
            if(i+k-1>=n)
                break;
            if(k==2&&a[i]==a[i+k-1])
                pan[i][i+k-1]=1;
            else if(k>2&&a[i]==a[i+k-1]&&pan[i+1][i+k-2])
                pan[i][i+k-1]=1;
        }
    }
}

