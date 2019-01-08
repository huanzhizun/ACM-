#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
char c[100005];
int nex[100005];
int main()
{
    int i,j,m;
    cin>>c;
    m=strlen(c);
    i=0;j=-1;
    nex[0]=-1;
    while(i<m){
        if(j==-1||c[i]==c[j]){
            i++;
            j++;
            nex[i]=j;
        }
        else{
            j=nex[j];
        }
    }
    return 0;
}