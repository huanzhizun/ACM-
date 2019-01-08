//三分求极值法
//    二分法早就失去了他的意义了。不过还是可以用三分法来实现的，就是二分中再来二分。比如我们定义了L和R，m = (L + R) / 2，mm = (mid + R) / 2; 如果mid靠近极值点，则R = mm；否则就是mm靠近极值点，则L = m;这样的话，极值还是可以求的
#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;
const double EPS = 1e-10;
double calc(double n)
{
    return;
}
double solve(double L, double R)
{
    double M, RM;
    while (L + EPS < R)
    {
        M = (L + R) / 2;
        RM = (M + R) / 2;
        if (calc(M) < calc(RM)) //计算最小值
            R = RM;
        else
            L = M;
    }
    return R;
}