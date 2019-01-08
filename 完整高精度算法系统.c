#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char a1[10005],b1[10005],x1[10005],q[10005],f[10005];
int d[10005];
void plus(char *a,char *b,char *c){
    int s,t,p,i;
    memset(d,0,sizeof(d));
    s=(int)strlen(a);
    t=(int)strlen(b);
    p=0;
    s--;
    t--;
    while(s>=0&&t>=0){
        d[p]+=a[s]-'0'+b[t]-'0';
        if(d[p]>=10){
            d[p+1]+=d[p]/10;
            d[p]%=10;
        }
        p++;
        s--;
        t--;
    }
    if(s<0&&t>=0){
        while(t>=0){
            d[p]+=b[t]-'0';
            d[p+1]+=d[p]/10;
            d[p]%=10;
            t--;
            p++;
        }
    }
    else if(s>=0&&t<0){
        while(s>=0){
            d[p]+=a[s]-'0';
            d[p+1]+=d[p]/10;
            d[p]%=10;
            p++;
            s--;
        }
    }
    while(p>=0&&d[p]==0) p--;
    if(p<0){
        c[0]='0';
        c[1]='\0';
        return ;
    }
    for(i=0;i<=p;i++) c[i]=d[p-i]+'0';
    c[p+1]='\0';
}
void minus(char *a,char *b,char *c){
    int i,n,m,p,k;
    n=(int)strlen(a);
    m=(int)strlen(b);
    p=0;
    while(p<n&&a[0]=='0'){
        p++;
    }
    if(p==n){
        a[0]='0';
        a[1]='\0';
    }
    else{
        for(i=0;i<n-p;i++) a[i]=a[i+p];
        a[n-p]='\0';
    }
    p=0;
    while(p<m&&b[0]=='0') p++;
    if(p==m) b[1]='\0';
    else{
        for(i=0;i<m-p;i++) b[i]=b[i+p];
        b[m-p]='\0';
    }
    n=strlen(a);
    m=strlen(b);
    p=0;
    if(n<m){
        p=1;
    }
    else if(n==m){
        if(strcmp(a,b)<0) p=1;
    }
    memset(d,0,sizeof(d));
    k=0;
    if(p==1){
        for(i=n-1;i>=0;i--){
            d[k]+=b[m-n+i]-a[i];
            while(d[k]<0){
                d[k]=d[k]+10;
                d[k+1]--;
            }
            k++;
        }
        for(i=m-n-1;i>=0;i--){
            d[k]+=b[i]-'0';
            while(d[k]<0){
                d[k]+=10;
                d[k+1]--;
            }
            k++;
        }
        k++;
        while(k>=0&&d[k]==0) k--;
        if(k<0){
            c[0]='0';
            c[1]='\0';
        }
        else{
            c[0]='-';
            for(i=k;i>=0;i--) c[i+1]=d[k-i]+'0';
            c[k+2]='\0';
        }
        return ;
    }
    for(i=m-1;i>=0;i--){
        d[k]+=a[n-m+i]-b[i];
        while(d[k]<0){
            d[k]+=10;
            d[k+1]--;
        }
        k++;
    }
    for(i=n-m-1;i>=0;i--){
        d[k]+=a[i]-'0';
        while(d[k]<0){
            d[k]+=10;
            d[k+1]--;
        }
        k++;
    }
    k++;
    while(k>=0&&d[k]==0) k--;
    if(k<0){
        c[0]='0';
        c[1]='\0';
    }
    else{
        for(i=0;i<=k;i++) c[i]=d[k-i]+'0';
        c[k+1]='\0';
    }
    return ;
}
void mul(char *a,char *b,char *c){
    int i,j,n,m,k;
    n=strlen(a);
    m=strlen(b);
    memset(d,0,sizeof(d));
    for(i=m-1;i>=0;i--){
        for(j=n-1;j>=0;j--){
            d[(m-1-i)+(n-1-j)]+=(a[j]-'0')*(b[i]-'0');
            if(d[(m-1-i)+(n-1-j)]>=10){
                d[(m-1-i)+(n-1-j)+1]+=d[(m-1-i)+(n-1-j)]/10;
                d[(m-1-i)+(n-1-j)]%=10;
            }
        }
    }
    k=n+m-1;
    while(d[k]>=10){
        d[k+1]+=d[k]/10;
        d[k]=d[k]%10;
        k++;
    }
    while(d[k]==0&&k>=0) k--;
    if(k<0){
        c[0]='0';
        c[1]='\0';
    }
    else{
        for(i=0;i<=k;i++) c[i]=d[k-i]+'0';
        c[k+1]='\0';
    }
}
void mi(char *a,int p,char *c){
    strcpy(q,a);
    c[0]='1';
    c[1]='\0';
    while(p>0){
        if(p&1){
            mul(c,q,c);
        }
        mul(q,q,q);
        p>>=1;
    }
}
void chu(char *a,int p,char *c){
    memset(d,0,sizeof(d));
    int n,m,i,j;
    n=strlen(a);
    m=0;
    int k=0;
    for(i=0;i<n;i++){
        m=m*10+a[i]-'0';
        if(m>=p){
            d[k]+=m/p;
            k++;
            m=m%p;
        }
    }
    for(i=0;i<k;i++) c[i]=d[i]+'0';
    c[k]='\0';
}