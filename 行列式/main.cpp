int mat[500][500];
int gcd(int a,int b){
    if(b==0) return a;
    return gcd(b,a%b);
}
int Gauss(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            mat[i][j] = (mat[i][j] + mod) % mod;
    }
    int col = 0, k;
    LL ans = 1;
    for(k = 0; k < n && col < n; ++k, ++col) {
        if(mat[k][col] == 0) {
            for(int i = k + 1; i < n; ++i) {
                if(!(mat[i][col] == 0)) {
                    for(int j = col; j < n; ++j) swap(mat[k][j], mat[i][j]);
                    ans *= -1;
                    break;
                }
            }
        }
        int x = mat[k][col];
        ans *= x;
        ans %=  mod;
        for(int i = k + 1; i < n; ++i) {
            int y = mat[i][col];
            if(x == 0 || y == 0) continue;
            int d = gcd(abs(x),abs(y));
            LL lcm = abs((LL)x * y / d);
            LL tx = lcm / x,ty = lcm / y;
            for(int j = col; j < n; ++j) {
                mat[i][j] = (-tx * mat[k][j] + ty * mat[i][j])%mod;
            }
            ans = (ans * mm(ty,mod-2)) % mod;
        }
    }
    ans %= mod;
    ans += mod;
    ans %= mod;
    return ans;
}