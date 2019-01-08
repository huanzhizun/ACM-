//用一个点是否在三角形内判断用面积小面积之和是否等于大面积
#include <queue>
#include <stack>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <limits.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int MAX = 10010;
const double eps = 1e-6;
struct pi
{
    int x;
    int y;
}pp[MAX];
int chaji(int a,int b,int c)
{
    return (pp[b].x-pp[a].x)*(pp[c].y-pp[a].y)-(pp[b].y-pp[a].y)*(pp[c].x-pp[a].x);
}
int panduan(int a,int b,int c,int d)
{
    if(abs(chaji(a,b,c))==abs(chaji(d,a,b))+abs(chaji(d,b,c))+abs(chaji(d,c,a)))
    {
        return 0;
    }
    if(abs(chaji(d,b,c))==abs(chaji(a,b,c))+abs(chaji(a,c,d))+abs(chaji(a,d,b)))
    {
        return 0;
    }
    if(abs(chaji(a,d,c))==abs(chaji(b,a,c))+abs(chaji(b,c,d))+abs(chaji(b,d,a)))
    {
        return 0;
    }
    if(abs(chaji(a,b,d))==abs(chaji(c,a,b))+abs(chaji(c,b,d))+abs(chaji(c,d,a)))
    {
        return 0;
    }
    return 1;
}