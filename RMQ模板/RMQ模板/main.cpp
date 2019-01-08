#include <iostream>
#include <cmath>
using namespace std;
#define maxn 50010

int maxl[maxn][16], minl[maxn][16];
void S_table(int n)
{
    int l = int(log((double)n)/log(2.0));
    for (int j=1;j<=l;j++)
    {
        for (int i=1; i + (1 << (j-1) ) - 1 <=n;++i)
        {
            maxl[i][j] = max(maxl[i][j-1], maxl[i + (1 << (j-1) )][j-1]);
            minl[i][j] = min(minl[i][j-1], minl[i + (1 << (j-1) )][j-1]);
        }
    }
}

int rmq(int l, int r)
{
    int k = int(log((double)(r-l+1))/log(2.0));
    int a1 = max(maxl[l][k], maxl[r - (1<<k) + 1][k]);
    int a2 = min(minl[l][k], minl[r - (1<<k) + 1][k]);
    printf("Max: %d Min: %d\n", a1, a2);
}
