#include<stdio.h>

#include<iostream>

#include<algorithm>

#include<string.h>

#include<vector>
using namespace std;
//************************************************
const int MAXN=9;//这个值要超过两边个数的较大者，因为有linker

int linker[MAXN];

bool used[MAXN];

vector<int>map[MAXN];

int uN;

bool dfs(int u)

{
    
    for(int i=0;i<map[u].size();i++)
        
    {
        
        if(!used[map[u][i]])
            
        {
            
            used[map[u][i]]=true;
            
            if(linker[map[u][i]]==-1||dfs(linker[map[u][i]]))
                
            {
                
                linker[map[u][i]]=u;
                
                return true;
                
            }
            
        }
        
    }
    
    return false;
    
}
int hungary()

{
    
    int u;
    
    int res=0;
    
    memset(linker,-1,sizeof(linker));
    
    for(u=0;u<uN;u++)
        
    {
        
        memset(used,false,sizeof(used));
        
        if(dfs(u)) res++;
        
    }
    
    return res;
    
}
int vis[9][9];
int a[9];
int ans;
void solve(int n){
    for(int i=0;i<n;i++)
        map[i].clear();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(vis[i][a[j]]==0&&vis[i][a[(j+1)%n]]==0){
                map[i].push_back(j);
            }
        }
    }
    uN=n;
    ans=min(ans,n-hungary());
}
int use[9];
void dfs(int u,int n){
    if(u==n){
        solve(n);
        return;
    }
    for(int i=0;i<n;i++){
        if(!use[i]){
            a[u]=i;
            use[i]=1;
            dfs(u+1,n);
            use[i]=0;
        }
    }
}
int main()
{
    int n,m;
    while(scanf("%d%d",&n,&m)!=EOF){
        ans=n;
        memset(vis,0,sizeof(vis));
        for(int i=0;i<m;i++){
            int x,y;
            scanf("%d%d",&x,&y);
            x--;
            y--;
            vis[x][y]=1;
        }
        dfs(0,n);
        printf("%d\n",ans);
    }
}