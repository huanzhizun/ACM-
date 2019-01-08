#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
vector<int >g[10005];
int vis[100005];
int in[10005],out[10005],use[10005];
char c[6];
int a[200005],cnt;
int change(char c){
    if(c>='a'&&c<='z') return c-'a';
    if(c>='A'&&c<='Z') return 26+c-'A';
    return 52+c-'0';
}
void add(int a,int b){
    g[a].push_back(b);
}
int it[10005];
void dfs(int u,int ee){
    int p;
    p=(int)g[u].size();
    while(it[u]<p){
        int m=it[u];
        it[u]++;
        use[g[u][m]]=1;
        dfs(g[u][m],0);
    }
    a[cnt++]=u;//放外面的好处是对于不能走的点也可以记录，而且一定要后序（因为后序能保证不能走的点一定是终点，而先序却不行）
}
int main()
{
    int i,m;
    int x=0,y=0;
    m=0;
    for(i=0;i<=10000;i++){
        if(in[i]!=out[i]){
            if(in[i]==out[i]+1){
                x++;
            }
            else if(out[i]==in[i]+1){
                y++;
            }
            else{
                m=1;
            }
        }
    }
    if(!((x==0&&y==0)||(x==1&&y==1))) m=1;//
    if(m) printf("NO\n");
    else{
        if(x==0){
            for(i=0;i<=10000;i++){
                if(in[i]!=0){
                    use[i]=1;
                    dfs(i,0);
                    break;
                }
            }
        }
        else{
            for(i=0;i<=10000;i++){
                if(out[i]==in[i]+1){
                    use[i]=1;
                    dfs(i,0);
                    break;
                }
            }
        }
        for(i=0;i<=10000;i++){
            if(!(in[i]==0&&out[i]==0)){
                if(!use[i]){
                    m=1;
                    break;
                }
            }
        }
        if(m) printf("NO\n");
        else{
            printf("YES\n");
        }
    }
}
