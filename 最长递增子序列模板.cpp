#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int LIS(int d[], int n){
    int *B = new int[n];
    int i,left, right, mid, len = 1;
    B[1] = d[1]; //为了和上面的一致，我们从1开始计数吧:)
    for(i = 2; i <= n; ++i){
        left = 1, right = len;
        while(left <= right){
            mid = (left + right) / 2;
            if(B[mid] < d[i]) left = mid + 1; //二分查找d[i]的插入位置
            else right = mid - 1;
        }
        B[left] = d[i]; //插入
        if(left > len) len++; //d[i]比现有的所有数字都大，所以left 才会大于 len。
    }
    delete[] B;
    return len;
}

int main(){
    int d[]={0, 2, 1, 5, 3, 6, 4, 8, 9, 7};
    printf("%d\n",LIS(d,9));
    return 0;
}