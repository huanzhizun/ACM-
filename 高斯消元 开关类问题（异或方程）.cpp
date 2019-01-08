#include<cstdio>
#include<algorithm>
#include<cstring>
#define LL __int64
using namespace std;
int b[55][55],x[55],c[55][55];
int flag;//判断是否无解。
int guass(int equ,int val){
    int i,j,n,m,p,k,q;
    p=0;
    for(i=0;i<equ&&p<val;i++,p++){
        k=b[i][p];
        n=i;
        for(j=i+1;j<equ;j++){
            if(b[j][p]>k) {k=b[j][p];
                n=j;
            }
        }
        if(n!=i){
            for(j=p;j<val;j++){
                swap(b[i][j],b[n][j]);
            }
            swap(x[i],x[n]);
        }
        if(b[i][p]==0) {
            i--;
            continue;
        }
        for(j=i+1;j<equ;j++){
            if(b[j][p]==0) continue;
            for(m=p;m<val;m++){
                b[j][m]=b[i][m]^b[j][m];
            }
            x[j]=x[i]^x[j];
        }
    }
    m=0;
    for(i=0;i<equ;i++){
        p=0;
        for(j=0;j<val;j++){
            if(b[i][j]!=0){
                p=1;
                break;
            }
        }
        if(p==0&&x[i]!=0){
            flag=1;
            return 0;
        }
        if(p) m++;
    }
    return equ-m;//返回不确定变元个数
}