#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace  std;
int main()
{
    int i,n;
    double s;
    while(cin>>n){
        if(n<=1000000){
            s=0;
            for(i=1;i<=n;i++) s+=1.0/i;
        }
        else{
            s=0.5772156649+log(n+1.0);
        }
        printf("%.4lf\n",s);
    }
}