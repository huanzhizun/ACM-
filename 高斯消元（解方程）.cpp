#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace  std;
double b[205][205],x[205],a[25][25];
void guass(int equ,int val){
    int i,j,n,p ,k;
    double s2,q;
    p=0;
    for(i=0;i<equ&&p<val;i++,p++){
        n=i;
        for(j=i+1;j<equ;j++){
            if(fabs(b[j][p])>fabs(b[n][p])) n=j;
        }
        if(n!=i){
            for(j=p;j<val;j++){
                swap(b[i][j],b[n][j]);
            }
            swap(x[i],x[n]);
        }
        if(fabs(b[i][p])<1e-6){
            i--;
            continue;
        }
        for(j=i+1;j<equ;j++){
            if(fabs(b[j][p])<1e-9) continue;
            q=b[j][p]/b[i][p];
            for(k=p;k<val;k++){
                b[j][k]=q*b[i][k]-b[j][k];
            }
            x[j]=q*x[i]-x[j];
        }
    }
    for(i=equ-1;i>=0;i--){
        s2=x[i];
        for(j=val-1;j>i;j--) s2-=b[i][j]*x[j];
        x[i]=s2/b[i][i];
    }
}
int aabs(int p,int f){
    if(f>p) return f-p;
    return p-f;
}
int main()
{
    int i,j,n,m,p,k,f,v,N=0;
    while(1){
        scanf("%d%d%d",&m,&n,&p);
        if(m==0&&n==0&&p==0) break;
        if(N!=0) printf("\n");
        N++;
        for(i=0;i<n;i++){
            for(j=0;j<m;j++)
                scanf("%lf",&a[i][j]);
        }
        memset(b,0,sizeof(b));
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                v=0;
                for(f=0;f<n;f++){
                    for(k=0;k<m;k++){
                        if(aabs(i,f)+aabs(j,k)<=p){
                            b[i*m+j][f*m+k]=1;
                            v++;
                        }
                    }
                }
                x[i*m+j]=v*a[i][j];
            }
        }
        guass(n*m,m*n);
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                printf("%8.2lf",x[i*m+j]);
            }
            printf("\n");
        }
    }
}