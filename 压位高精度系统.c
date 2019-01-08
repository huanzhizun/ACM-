#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define mm 100000000
#define LL long long
char a1[10005],b1[10005];
int x[1300],y[1300],z[1300],jie[10005][1250],v[1500],u[1500],w[1500];
int d[10005];
int f1,f2;
int max(int a,int b){
    if(a<b) return b;
    return a;
}
int plus(int *a,int *b,int *c,int n,int m){
    int i,j;
    if(n<m){
        for(i=n+1;i<=m;i++) a[i]=0;
    }
    else{
        for(i=m+1;i<=n;i++) b[i]=0;
    }
    memset(z,0,(max(n,m)+2)*sizeof(z[0]));
    for(i=0;i<=max(n,m);i++){
        z[i]+=b[i]+a[i];
        if(z[i]>=mm){
            z[i+1]+=z[i]/mm;
            z[i]=z[i]%mm;
        }
    }
    j=max(n,m)+1;
    while(z[j]>=mm){
        z[j+1]+=z[j]/mm;
        z[j]%=mm;
        j++;
    }
    while(j>=0&&z[j]==0) j--;
    if(j<0) j=0;
    for(i=0;i<=j;i++) c[i]=z[i];
    return j;
}
int minus(int *a,int *b,int *c,int n,int m){//必须a>=b
    int i,p;
    memset(z,0,(n+2)*sizeof(z[0]));
    for(i=m+1;i<=n;i++) b[i]=0;
    for(i=0;i<=n;i++){
        z[i]+=a[i]-b[i];
        if(z[i]<0){
            z[i+1]--;
            z[i]+=mm;
        }
    }
    p=n;
    while(p>=0&&z[p]==0) p--;
    if(p<0) p=0;
    for(i=0;i<=p;i++) c[i]=z[i];
    return p;
}
int mul(int *a,int p,int *c,int n){
    int i,m;
    LL s1;
    memset(z,0,(n+2)*sizeof(z[0]));
    for(i=0;i<=n;i++){
        s1=(LL)a[i]*p+z[i];
        if(s1>=mm){
            z[i+1]+=s1/mm;
            z[i]=s1%mm;
        }
        else z[i]=s1;
    }
    m=n+1;
    while(z[m]>=mm){
        z[m+1]+=z[m]/mm;
        z[m]%=mm;
    }
    while(m>=0&&z[m]==0) m--;
    if(m<0) m=0;
    for(i=m;i>=0;i--) c[i]=z[i];
    c[m+1]=0;
    c[m+2]=0;
    return m;
}
int main()
{
    int i,j,n,m,p,q;
    while(scanf("%d %d",&n,&m)!=EOF){
        p=0;
        while(n>0){
            x[p++]=n%mm;
            n=n/mm;
        }
       /* q=0;
        while(m>0){
            y[q++]=m%mm;
            m=m/mm;
        }
        p--;*/
        q--;
        memset(z,0,sizeof(z));
        j=mul(x,m,z,p);
        if(j<0){
            z[0]=0;
            j=0;
        }
        for(i=j;i>=0;i--){
            if(i==j) printf("%d",z[i]);
            else{
                printf("%08d",z[i]);
            }
        }
        printf("\n");
    }
}