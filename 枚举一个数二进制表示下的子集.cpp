#include<cstdio>
int main()
{
    int i,j,s;
    for(i=s;i;i=(i-1)&s);//枚举s子集
    for(i=0;i<20;i++){//先枚举第几位
        for(j=0;j<maxn;j++){
            if(j&(1<<i)){
                p[j^(1<<i)]+=p[j];
            }
        }
    }
}