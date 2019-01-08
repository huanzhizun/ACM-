#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <iostream>
#include <cmath>
#define N 405
using namespace std;
typedef long long LL;
int dp[N][N][9][9],dp1[N][N][9][9]; ;
int n , m ;
void init() {
    for(int i = 1 ; i <= n ; ++i) {
        for(int j = 1 ; j <= m ;++j) {
            scanf("%d" ,&dp[i][j][0][0]) ;
            dp1[i][j][0][0]=dp[i][j][0][0];
        }
    }
    for(int r = 0 ; (1<<r) <= n ; ++r) {
        for(int c = 0 ; (1<<c) <= m ; ++c) {
            if(r == 0 && c == 0) continue ;
            for(int i = 1 ; i+(1<<r)-1 <= n ; ++i) {
                for(int j = 1 ; j+(1<<c)-1 <= m ; ++j) {
                    if(r) {
                        dp[i][j][r][c] = max(dp[i][j][r-1][c] , dp[i+(1<<(r-1))][j][r-1][c]) ;
                    }else {
                        dp[i][j][r][c] = max(dp[i][j][r][c-1] , dp[i][j+(1<<(c-1))][r][c-1]) ;//先算当r为0的时候
                    }
                }
            }
        }
    }
    for(int r = 0 ; (1<<r) <= n ; ++r) {
        for(int c = 0 ; (1<<c) <= m ; ++c) {
            if(r == 0 && c == 0) continue ;
            for(int i = 1 ; i+(1<<r)-1 <= n ; ++i) {
                for(int j = 1 ; j+(1<<c)-1 <= m ; ++j) {
                    if(r) {
                        dp1[i][j][r][c] = min(dp1[i][j][r-1][c] , dp1[i+(1<<(r-1))][j][r-1][c]) ;
                    }else {
                        dp1[i][j][r][c] = min(dp1[i][j][r][c-1] , dp1[i][j+(1<<(c-1))][r][c-1]) ;//先算当r为0的时候
                    }
                }
            }
        }
    }
}

int query(int x1 , int y1 , int x2 , int y2) {
    int kx = (int)(log(x2 - x1 + 1.0)/log(2.0)) ;
    int ky = (int)(log(y2 - y1 + 1.0)/log(2.0)) ;//log2居然CE
    int m1 = dp[x1][y1][kx][ky] ;
    int m2 = dp[x2-(1<<kx)+1][y1][kx][ky] ;
    int m3 = dp[x1][y2-(1<<ky)+1][kx][ky] ;
    int m4 = dp[x2-(1<<kx)+1][y2-(1<<ky)+1][kx][ky] ;
    int tmp = max(m1 , max(m2 , max(m3 , m4))) ;//分为4个部分
    return tmp;
}
int query1(int x1 , int y1 , int x2 , int y2) {
    int kx = (int)(log(x2 - x1 + 1.0)/log(2.0)) ;
    int ky = (int)(log(y2 - y1 + 1.0)/log(2.0)) ;//log2居然CE
    int m1 = dp1[x1][y1][kx][ky] ;
    int m2 = dp1[x2-(1<<kx)+1][y1][kx][ky] ;
    int m3 = dp1[x1][y2-(1<<ky)+1][kx][ky] ;
    int m4 = dp1[x2-(1<<kx)+1][y2-(1<<ky)+1][kx][ky] ;
    int tmp = min(m1 , min(m2 , min(m3 , m4))) ;//分为4个部分
    return tmp;
}
