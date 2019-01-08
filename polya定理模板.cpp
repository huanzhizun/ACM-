//设G是p个对象的一个置换群，用m种颜色涂染p个对象，则不同染色方案为：
//l=(sigma(m^(c(g[i]))))/|G|;c[g[i]]为c[i]循环节个数。
//其中G={g1 ,…gs}   c(gi )为置换gi的循环节数(i=1…s)
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<math.h>
using namespace std;
int gcd(int a,int b)
{
    while(b^=a^=b^=a%=b)
        ;
    return a;
}
//为环时的polay
void polya(int n,int m)
{
    int s=0,i,j,p;
    for(i=1;i<=n;i++)
    {
        s+=(int)pow((double)m,(double)gcd(n,i));
    }
    if(n&1)
        s+=n*(int)pow((double)m,(double)(n+1)/2);
    else
    {
        p=(int)pow((double)m,(double)n/2);
        s+=n/2*p+n/2*p*m;
    }
    s=s/n/2;
    return ;
}
//1. 对于旋转，有c(gi) = gcd(n,i)，i为转动几颗珠子。
//2. 对于翻转，当n为奇数时，c(gi) = n/2+1；当n为偶数时，有n/2个的循环节数为n/2+1，有n/2个的循环节数为n/2。
//如果旋转4下，及正方形的旋转//l=(m^(n^2)+2*m^([(n^2+3)/4])+m^([(n^2+1)/2]))
//为正方形时
int polya2(int n,int m)
{
    return ((int)pow((double)m,n*n)+2*(int)pow((double)m,(n*n+3)/4)+(int)pow((double)m,(n*n+1)/2))/4;
}