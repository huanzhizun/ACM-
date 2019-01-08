/*
 在背包容量为V的背包问题中，泛化物品是一个定义域为0..V中的整数的函数h，当分配给它的费用为v时，能得到的价值就是h(v)。
 如果面对两个泛化物品h和l，要用给定的费用从这两个泛化物品中得到最大的价值，怎么求呢？事实上，对于一个给定的费用v，只需枚举将这个费用如何分配给两个泛化物品就可以了。同样的，对于0..V的每一个整数v，可以求得费用v分配到h和l中的最大价值f(v)。即：f(v) = maxf{h(k) + l(v - k)} 0 <= k <= v
*/
/*
 对于要递归的子节点，直接把父节点的dp值赋给它
 更新子节点。
 用上面所说的更新泛化物品的方法对于父节点用完成递归的子节点进行更新。
 for (int k=lim-c[j];k>=0;k--) dp[j][k]=dp[now][k];
 DP(j,lim-c[j]);
 for (int k=c[j];k<=lim;k++)
 dp[now][k]=Max(dp[now][k],dp[j][k-c[j]]+v[j]);
 
 注意必须选择这个节点才能选下面的！
 注意下面的dp的取值范围！
*/
/*
void dfs(int u,int k,int pa,int gg){
    int j,p;
    p=head[u];
    for(;p!=-1;p=pp1[p].next){
        int q;
        q=pp1[p].to;
        if(q!=pa){
            if(gg>=pp[q].a){
                if(!vis[q])
                    for(j=0;j<=gg-pp[q].a;j++) dp[q][j]=dp[u][j];
                dfs(q,k^1,u,gg-pp[q].a);
                if(!vis[q]){
                    for(j=pp[q].a;j<=gg;j++) dp[u][j]=max(dp[u][j],dp[q][j-pp[q].a]+pp[q].b);
                }
                else{
                    for(j=gg;j>=pp[q].a;j--) dp[u][j]=max(dp[u][j],dp[u][j-pp[q].a]+pp[q].b);
                }
            }
        }
    }
}
*/